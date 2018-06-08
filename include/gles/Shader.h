/*******************************************************
**	Shader
**
**	��ɫ��
**	
**		ģ����Opengl�ɱ�̵�Ƭ�Σ���������GPU�Ĵ���Ρ�һ����ԣ�
**	Shader��Ϊ������ɫ��VertexShader ��ƬԪ��ɫ��FragmentShader��
**	Shader������辭��Program link��������
**
**		Shader����ɫ�����ࣩ
**		VertexShader��������ɫ����
**		FragmentShader��ƬԪ��ɫ����
**		
**		������
**	
********************************************************/
#pragma once
#include "system/String.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT Shader
{
public:
	//����Դ��
	void SetSourceCode(const nb::System::String &sourceCode);

	//��ȡԴ��
	nb::System::String GetSourceCode() const;

	//����
	//�쳣������ʧ��
	void Compile();

	//�Ƿ��ѱ���
	bool HasCompiled() const;

	//��ȡshader���
	unsigned int GetShaderHandle() const;

	//�Ƿ���ͬ
	bool Equal(Shader *shader) const;

	virtual ~Shader();

protected:
	Shader();
	Shader(const nb::System::String &sourceCode);

	nb::System::String	m_SourceCode;
	unsigned int		m_ShaderHandle;
};

class NB_EXPORT VertexShader : public Shader
{
public:
	//����һ��������ɫ����Դ��Ϊ��
	VertexShader();

	//����һ��������ɫ����Դ��ΪsourceCode
	VertexShader(const nb::System::String &sourceCode);

public:
	//ͨ�ö�����ɫ��
	static VertexShader *Common();
};

class NB_EXPORT FragmentShader : public Shader
{
public:
	FragmentShader();
	FragmentShader(const nb::System::String &sourceCode);

public:
	//ͨ��ƬԪ��ɫ��
	static FragmentShader *Common();
};

}}}
