/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Vec2
				
				����ά��Ϊ2�ĸ���������

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "math/Vec.h"

namespace nb{ namespace Math{


class NB_EXPORT Vec2 : public Vec
{
public:
	//����x����������
	float &X();
	const float &X() const;

	//����y����������
	float &Y();
	const float &Y() const;

	//��׼��
	Vec2 Normalized() const;

	//��ˣ���������
	Vec2 CrossProduct(const Vec2 &other) const;

public:
	//����һ��Vec2����, ��������Ϊ��0.0, 0.0)
	Vec2();

	//��������������һ��Vec2����������Ϊ(x, y)
	Vec2(float x, float y);

	Vec2(const Vec2 &other);
	~Vec2();
};


}}
