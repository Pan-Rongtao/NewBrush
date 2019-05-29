/*******************************************************
**	Display
**
**	��ʵ������
**		Display��elg�������ʾ�豸�����е�gl
**	����������display�ĳ�ʼ��
**
**		������
**
********************************************************/
#pragma once
#include "../core/Def.h"

namespace nb{ namespace gl{

class NB_API Display
{
public:
	//����һ��IDΪid��Display�������г�ʼ�����������ʧ�ܣ����׳��쳣
	Display(long id);

	//Ĭ��Display
	static Display defaultx();

	//�Ƿ�Ϊ��
	bool isNull() const;

	//��ȡid
	long id() const;

	//���
	void *handle() const;

private:
	void				*m_handle;
	long				m_id;
};

}}
