#pragma once
#include "core/NewBrushDef.h"

namespace nb{ namespace gl{ namespace egl{

class NB_EXPORT Configure
{
public:
	Configure();
	Configure(int *attributes);

	bool IsNull() const;

	int *GetAttributes() const;

	void *GetEGLHandle() const;

public:
	//ϵͳ�Ƽ������������
	static int SystemRecommendMaxSupportCount();

	//��ϵͳ�Ƽ��й���
	static Configure FromSystemRecommend(int index);

private:
	Configure(void *eglHandle);

	void		*m_Handle;
};

}}}
