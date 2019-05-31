/*******************************************************
**	Configure
**
**	GL������
**		Configure������OpenGL��Ⱦ������
**	��ɫͨ�����ԡ�λ��Լ��������Ե����ݽṹ
**	
**
**		������
**
********************************************************/
#pragma once
#include "../core/Def.h"

namespace nb{ namespace gl{

class NB_API Configure
{
public:
	//����һ�����ã�������display������Ϊattributes
	Configure(const int *attributes);

	//��ȡ����
	int *attributes() const;

	//���
	void *handle() const;

public:
	//ϵͳ�Ƽ������������
	static uint32_t systemRecommendMaxSupportCount();

	//��ϵͳ�Ƽ��й���
	static Configure fromSystemRecommend(uint32_t index);

private:
	Configure();
	void						*m_handle;
};

}}
