/******************************************************************************

* Copyright (c) 2017���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-03

* ��Ҫ����: Singleton
			SingletonS���̰߳�ȫ��
				
				Singleton(S)�����ڶ��嵥��ģʽ�����ݽṹ������ʹ���������������͵�
				Ψһʵ����

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "CriticalSection.h"

namespace nb{ namespace System{

template<class T>
class NB_EXPORT Singleton
{
public:
	static T *Current()
	{
		if(!t)	t = new T();
		return t;
	}

private:
	static T			*t;
};
template<class T> T *Singleton<T>::t = NULL;

template<class T>
class SingletonS
{
public:
	static T *Current()
	{
		//��һ���жϣ�����lock����
		if(!t)
		{
			lock.Lock();
			if(!t)	t = new T();
			lock.Unlock();
		}
		return t;
	}

private:
	static T					*t;
	static CriticalSection		lock;
};
template<class T> T *SingletonS<T>::t = NULL;
template<class T> CriticalSection SingletonS<T>::lock;

}}
