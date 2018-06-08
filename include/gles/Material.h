/*******************************************************
**	Material
**
**	����
**	
**	����������Թ�Ľ��������䡢����ȣ����ʵ�������
**	�����ձ����Ϊ��ɫ������Ҳ���������ⲿ�����ݣ��Լ���
**		����Ӱ��ķ�ӳ����������Ч��
**		
**		������
**	
********************************************************/
#pragma once
#include "system/Global.h"

namespace nb{ namespace gl{ namespace Gles{

class Program;
class Texture;
class MaterialEventListener;
class NB_EXPORT Material
{
public:
	//����program
	void SetProgram(Program *program);

	//��ȡprogram
	Program *GetProgram() const;

	//��������
	void SetTexture(Texture *texture);

	//��ȡ����
	Texture *GetTexture() const;

	//�ж��Ƿ������material��ͬ
	bool Equal(Material *material) const;

	//
	void SetListener(MaterialEventListener *listener);

public:
	//����һ�����ʣ�����ProgramΪ�գ�����Ϊ��
	Material();

	//����һ�����ʣ�����ProgramΪprogram����������Ϊ��
	Material(Program *program);

	//����һ�����ʣ�����ProgramΪprogram����������texture
	Material(Program *program, Texture *texture);

private:
	Program					*m_Program;
	Texture					*m_Texture;
	MaterialEventListener	*m_Listener;
};

class NB_EXPORT MaterialEventListener
{
public:
	virtual void On_Texture_Changed() {}
};

}}}
