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

class Display;
class NB_API Configure
{
public:
	//����һ�����ã�������display������Ϊattributes
	Configure(std::shared_ptr<Display> display, int *attributes);

	//��ȡ����
	int *attributes() const;

	//���
	void *handle() const;

public:
	//ϵͳ�Ƽ������������
	static int systemRecommendMaxSupportCount(std::shared_ptr<Display> display);

	//��ϵͳ�Ƽ��й���
	static Configure fromSystemRecommend(std::shared_ptr<Display> display, int index);

private:
	Configure();
	void						*m_handle;
	std::shared_ptr<Display>	m_display;
};

}}
