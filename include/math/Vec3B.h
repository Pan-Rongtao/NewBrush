/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Vec3B
				
				����ά��Ϊ3�Ĳ���������

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "math/VecB.h"
#include "math/Vec2B.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec3B : public VecB
{
public:
	//����x����������
	bool &X();
	const bool &X() const;

	//����y����������
	bool &Y();
	const bool &Y() const;

	//����z����������
	bool &Z();
	const bool &Z() const;

	//����xy����
	Vec2B XY() const;

	//����yz����
	Vec2B YZ() const;

public:
	//����һ��Vec3B����������Ϊ(0.0, 0.0, 0.0)
	Vec3B();

	//����һ��Vec3B����������Ϊ(x, y, z)
	Vec3B(bool x, bool y, bool z);

	//��һ��Vec2B����һ��Vec3B
	Vec3B(const Vec2B &xy, bool z);

	//��һ��Vec2B����һ��
	Vec3B(bool x, const Vec2B &yz);
};

}}
