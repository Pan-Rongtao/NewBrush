/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Vec2B
				
				����ά��Ϊ2�Ĳ���������

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "math/VecB.h"

namespace nb{ namespace Math{


class NB_EXPORT Vec2B : public VecB
{
public:
	//����x����������
	bool &X();
	const bool &X() const;

	//����y����������
	bool &Y();
	const bool &Y() const;

public:
	//����һ��Vec2B����, ��������Ϊ��0.0, 0.0)
	Vec2B();

	//��������������һ��Vec2B����������Ϊ(x, y)
	Vec2B(bool x, bool y);

	Vec2B(const Vec2B &other);
	~Vec2B();
};


}}
