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
#include "core/NewBrushDef.h"

namespace nb{ namespace System{

class CriticalSection_Internal;
class NB_EXPORT CriticalSection
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
	CriticalSection_Internal	*m_pInternal;
};

}}
