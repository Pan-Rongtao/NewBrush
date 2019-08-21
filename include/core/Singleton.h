/******************************************************************************

* Copyright (c) 2017���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-03

* ��Ҫ����: Singleton
			SingletonS���̰߳�ȫ��
				
				Singleton(S)�����ڶ��嵥��ģʽ�����ݽṹ������ʹ���������������͵�
				Ψһʵ����

			ע�⣺!!!����ʹ����������֮�䣬���򲻻ᱣ֤��һ��ʵ�������ܻ�����������ϵ�ʵ��!!!
* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "../core/Def.h"
#include <mutex>

namespace nb{

template<class T>
class NB_API Singleton
{
public:
	static T *instance()
	{
		static T *t = nullptr;
		if(!t)	t = new T();
		return t;
	}
};

template<class T>
class SingletonS
{
public:
	static T *instance()
	{
		static T *t = nullptr;
		static std::mutex lock;
		//��һ���жϣ�����lock����
		if(!t)
		{
			lock.lock();
			if(!t)	t = new T();
			lock.unlock();
		}
		return t;
	}

};

}
