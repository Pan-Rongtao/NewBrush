/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2016-09

* ��Ҫ����: CriticalSection
				
				�ٽ��������������̷߳��ʽ��޵����ݽṹ��
				һ����ԣ������Բ�ͬ�̶߳�ͬһ���ݵ�ͬ����д����
				ÿ��Lock��Unlock��������������

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "../core/Def.h"
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
#include <Windows.h>
#define  WIN32_LEAN_AND_MEAN
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
#include <pthread.h>
#endif

namespace nb{ namespace System{

class NB_API CriticalSection
{
public:
	//+1������
	void Lock();

	//-1������
	void Unlock();

public:
	//����һ���ٽ���
	CriticalSection();
	~CriticalSection();

private:
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
	CRITICAL_SECTION	m_Win32CriticalSection;
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	pthread_mutex_t		m_mutex;
#endif
};

}}
