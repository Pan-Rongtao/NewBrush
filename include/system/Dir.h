/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Dir
				
				�ļ��С���������ϵͳ�ļ��нڵ�����ݽṹ
				

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "String.h"

namespace nb{ namespace System{

class Dir
{
public:
	bool Exists() const;

public:
	Dir();

	//����һ��Dir����ָ�����·��absolute
	Dir(const nb::System::String &absolute);

public:
	//�ļ����Ƿ����
	static bool IsExists();
};

}}

