#include "gles/SourceDecoder.h"
#include "glm/glm.hpp"

using namespace nb::gl;

constexpr char KeywordMain[] = "main";
constexpr char KeywordUniform[] = "uniform";
constexpr char KeywordStruct[] = "struct";
constexpr size_t KeywordUniformSize = sizeof(KeywordUniform) - 1;
constexpr size_t KeywordStructSize = sizeof(KeywordStruct) - 1;

SourceDecoder::SourceDecoder()
{
}

void SourceDecoder::decode(const std::string & verSource, const std::string & fragSource)
{
	m_uniforms.clear();
	decodeOne(verSource);
	decodeOne(fragSource);
}

void SourceDecoder::getUniforms(std::map<std::string, VarTypeE> &uniforms)
{
	uniforms = m_uniforms;
}

void SourceDecoder::decodeOne(const std::string &source)
{
	std::string sCutMain = cutMain(source);
	if (source.empty())
		return;

	for (unsigned int i = 0; i <= sCutMain.size() - KeywordUniformSize;)
	{
		std::string sSubStruct = sCutMain.substr(i, KeywordStructSize);
		std::string sSubUniform = sCutMain.substr(i, KeywordUniformSize);
		if (toLower(sSubStruct) == KeywordStruct)
		{
			int offset = i + KeywordStructSize + 1;
			auto end = sCutMain.find('}', offset);
			if (end != std::string::npos)
			{
				std::string sStructDefineStr = sCutMain.substr(i + KeywordStructSize, end - (i + KeywordStructSize) + 1);
				std::string structName;
				std::map<std::string, VarTypeE> structMembers;
				extractStruct(sStructDefineStr, structName, structMembers);
				i = end + 1;
			}
			else
			{
				nbThrowException(std::runtime_error, "decode error");
			}
		}
		else if (toLower(sSubUniform) == KeywordUniform)
		{
			//+6表示后6个字符肯定不是';'，被空白符和类型、变量名占位。
			int offset = i + KeywordUniformSize + 6;
			int end = sCutMain.find(';', offset);
			if (end != std::string::npos)
			{
				std::string varTypeName;
				std::string varName;
				VarTypeE varType;
				std::string sVarDefineStr = sCutMain.substr(i, end - i);
				extractVar(sVarDefineStr, varTypeName, varName, varType);
				if (varType != VarTypeE::unknown)
				{
					if (varType == VarTypeE::structure)
					{
						auto structMembers = m_structDefines.find(varTypeName)->second;
						for (auto const &member : structMembers)
						{
							m_uniforms.insert({varName + "." + member.first, member.second});
						}
					}
					else
					{
						m_uniforms.insert({ varName, varType });
					}
				}
				i = end + 1;
			}
			else
			{
				nbThrowException(std::runtime_error, "decode error");
			}
		}
		else
		{
			++i;
		}
	}

}

std::string SourceDecoder::cutMain(const std::string & s)
{
	size_t mainP = s.find(KeywordMain);
	return mainP != std::string::npos ? s.substr(0, mainP - 5) : "";	//prev 'void'
}

void SourceDecoder::extractStruct(const std::string & sStructDefineStr, std::string & structName, std::map<std::string, VarTypeE>& structMembers)
{
	std::string::const_iterator a = std::find_if(sStructDefineStr.begin(), sStructDefineStr.end(), [](char c) {return !isblank(c); });
	auto b = std::find_if(a, sStructDefineStr.end(), [](char c) {return isblank(c) || c == '{'; });
	structName.assign(a, b);
	std::string memberDefineStr(b, sStructDefineStr.end());
	size_t n = memberDefineStr.find(';');
	std::map<std::string, VarTypeE> members;
	while (n != std::string::npos) 
	{
		std::string sVarDefStr = memberDefineStr.substr(0, n);
		std::string memberTypeName;
		std::string memberName;
		VarTypeE memberType;
		extractVar(sVarDefStr, memberTypeName, memberName, memberType);
		if (memberType != VarTypeE::unknown && memberType != VarTypeE::structure)
			members.insert({ memberName, memberType });
		n = memberDefineStr.find(';', n + 1);
	}
	m_structDefines.insert({ structName, members });
}

void SourceDecoder::extractVar(const std::string &sVarDefineStr, std::string &varTypeName, std::string &varName, VarTypeE &varType)
{
	//如果';'前面有空白字符，需要先把空白字符去掉
	std::string sDef = sVarDefineStr;
	if (isblank(sVarDefineStr.back()))
	{
		for (int i = sVarDefineStr.size() - 2; i >= 0; --i)
		{
			if (!isblank(sVarDefineStr[i]))
			{
				sDef = sVarDefineStr.substr(0, i + 1);
				break;
			}
		}
	}
	int nNameBeg = std::string::npos;
	int nTypeBeg = std::string::npos;
	int nTypeEnd = std::string::npos;
	for (int i = sDef.size() - 1; i >= 0; --i)
	{
		if (nNameBeg == std::string::npos)
		{
			if (isBlank(sDef[i]))
			{
				nNameBeg = i + 1;
				varName = sDef.substr(nNameBeg);
			}
		}
		else
		{
			if (nTypeEnd == std::string::npos)
			{
				if (!isBlank(sDef[i]))
				{
					nTypeEnd = i + 1;
				}
			}
			else
			{
				if (isBlank(sDef[i]))
				{
					nTypeBeg = i + 1;
					break;
				}
			}
		}
	}
	varTypeName = sDef.substr(nTypeBeg, nTypeEnd - nTypeBeg);
	std::string sLower = toLower(varTypeName);
	if (sLower == "bool")							varType = VarTypeE::boolean;
	else if (sLower == "int")						varType = VarTypeE::integer;
	else if (sLower == "float")						varType = VarTypeE::real;
	else if (sLower == "vec2")						varType = VarTypeE::vec2;
	else if (sLower == "vec3")						varType = VarTypeE::vec3;
	else if (sLower == "vec4")						varType = VarTypeE::vec4;
	else if (sLower == "mat2" || sLower == "mat2x2")varType = VarTypeE::mat2x2;
	else if (sLower == "mat3" || sLower == "mat3x3")varType = VarTypeE::mat3x3;
	else if (sLower == "mat4" || sLower == "mat4x4")varType = VarTypeE::mat4x4;
	else if (sLower == "mat2x3")					varType = VarTypeE::mat2x2;
	else if (sLower == "mat2x4")					varType = VarTypeE::mat2x2;
	else if (sLower == "mat3x2")					varType = VarTypeE::mat2x2;
	else if (sLower == "mat3x4")					varType = VarTypeE::mat2x2;
	else if (sLower == "mat4x2")					varType = VarTypeE::mat2x2;
	else if (sLower == "mat4x3")					varType = VarTypeE::mat2x2;
	else
	{
		if (m_structDefines.find(varTypeName) != m_structDefines.end())
		{
			varType = VarTypeE::structure;
		}
		else
		{
			varType = VarTypeE::unknown;
		}
	}

}

bool SourceDecoder::isBlank(char c) const
{
	return c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v';
}

std::string SourceDecoder::toLower(const std::string &s) const
{
	std::string ret = s;
	for (int i = 0; i != ret.size(); ++i)
		if (ret[i] >= 'A' && ret[i] <= 'Z')
			ret[i] += 32;
	return ret;
}
