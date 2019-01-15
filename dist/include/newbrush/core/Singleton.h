/******************************************************************************

* Copyright (c) 2017���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-03

* ��Ҫ����: Singleton
			SingletonS���̰߳�ȫ��
				
				Singleton(S)�����ڶ��嵥��ģʽ�����ݽṹ������ʹ���������������͵�
				Ψһʵ����

			ע�⣺����ʹ����������֮�䣬���򲻻ᱣ֤��һ��ʵ�������ܻ�����������ϵ�ʵ��
* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "../core/Def.h"
#include <mutex>

namespace nb{ namespace core{

template<class T>
class NB_API Singleton
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
template<class T> T *Singleton<T>::t = nullptr;

template<class T>
class SingletonS
{
public:
	static T *Current()
	{
		//��һ���жϣ�����lock����
		if(!t)
		{
			lock.lock();
			if(!t)	t = new T();
			lock.unlock();
		}
		return t;
	}

private:
	static T					*t;
	static std::mutex			lock;
};
template<class T> T *SingletonS<T>::t = nullptr;
template<class T> std::mutex SingletonS<T>::lock;

}}
