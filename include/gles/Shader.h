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
#include "../core/Def.h"
#include <string>

namespace nb{ namespace gl{

class NB_API Shader
{
public:
	//����Դ��
	void setSource(const std::string &source);

	//��ȡԴ��
	const std::string &source() const;

	//����
	//�쳣������ʧ��
	void compile();

	//�Ƿ��ѱ���
	bool hasCompiled() const;

	//��ȡshader���
	unsigned int handle() const;

	virtual ~Shader();

protected:
	Shader();
	Shader(const std::string &source);

	std::string			m_Source;
	unsigned int		m_ShaderHandle;
};

class NB_API VertexShader : public Shader
{
public:
	//����һ��������ɫ����Դ��Ϊ��
	VertexShader();

	//����һ��������ɫ����Դ��ΪsourceCode
	VertexShader(const std::string &source);

};

class NB_API FragmentShader : public Shader
{
public:
	FragmentShader();
	FragmentShader(const std::string &source);

};

}}
