#pragma once
#include "../core/Def.h"

namespace nb{ namespace gl{

class NB_API Configure
{
public:
	Configure();
	Configure(int *attributes);

	bool isNull() const;

	int *attributes() const;

	void *handle() const;

public:
	//ϵͳ�Ƽ������������s
	static int systemRecommendMaxSupportCount();

	//��ϵͳ�Ƽ��й���
	static Configure fromSystemRecommend(int index);

private:
	void		*m_handle;
};

}}
