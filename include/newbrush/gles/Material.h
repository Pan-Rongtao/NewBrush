/*******************************************************
**	Material
**
**	����
**	
**	����������Թ�Ľ��������䡢����ȣ����ʵ�������
**	�����ձ�����Ϊ��ɫ������Ҳ���������ⲿ�����ݣ��Լ���
**		����Ӱ��ķ�ӳ����������Ч��
**		
**		������
**	
********************************************************/
#pragma once
#include <vector>
#include "newbrush/core/Def.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Texture.h"

namespace nb{

class NB_API Material
{
public:
	//����һ�����ʣ�����ProgramΪ�գ�����Ϊ��
	Material();

	//����һ�����ʣ�����ProgramΪprogram����������Ϊ��
	Material(std::shared_ptr<Program> program);

	//����һ�����ʣ�����ProgramΪprogram����������texture
	Material(std::shared_ptr<Program> program, const std::vector<std::shared_ptr<Texture>> &textures);

	//����program
	void setProgram(std::shared_ptr<Program> program);

	//��ȡprogram
	std::shared_ptr<Program> program();

	//����
	std::vector<std::shared_ptr<Texture>> &textures();
	const std::vector<std::shared_ptr<Texture>> &textures() const;

private:
	std::shared_ptr<Program>				m_program;
	std::vector<std::shared_ptr<Texture>>	m_textures;
};

}