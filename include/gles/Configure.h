#pragma once
#include "../core/Def.h"
#include "Display.h"

namespace nb{ namespace gl{

class NB_API Configure
{
public:
	Configure(std::shared_ptr<Display> display, int *attributes);

	bool isNull() const;

	int *attributes() const;

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
