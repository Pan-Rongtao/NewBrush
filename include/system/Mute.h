/******************************************************************************

* Copyright (c) 2017���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-03

* ��Ҫ����: Mute
				
				�������壬���ڽ����ͬ���̻�ȡ�̼߳����Դ��������

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "Global.h"

namespace nb{ namespace System{

class Mute_Internal;
class NB_EXPORT Mute
{
public:
	//����һ������Ϊname������
	//����������Ѵ��ڣ��������û�����ĸ���
	explicit Mute(const char *name);
	~Mute();

	//+1������
	void Lock();

	//-1������
	void Unlock();

public:
	//�������Ƿ����
	static bool IsExists(const char *name);

private:
	Mute_Internal	*m_internal;
};

}}
