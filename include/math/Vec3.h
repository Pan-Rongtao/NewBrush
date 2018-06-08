/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Vec3
				
				����ά��Ϊ3�ĸ���������

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "math/Vec.h"
#include "math/Vec2.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec3 : public Vec
{
public:
	//����x����������
	float &X();
	const float &X() const;

	//����y����������
	float &Y();
	const float &Y() const;

	//����z����������
	float &Z();
	const float &Z() const;

	//����xy����
	Vec2 XY() const;

	//����yz����
	Vec2 YZ() const;

	//��׼��
	Vec3 Normalized() const;

	//��ˣ���������
	Vec3 CrossProduct(const Vec3 &other) const;

public:
	//����һ��Vec3����������Ϊ(0.0, 0.0, 0.0)
	Vec3();

	//����һ��Vec3����������Ϊ(x, y, z)
	Vec3(float x, float y, float z);

	//��һ��Vec2����һ��Vec3
	Vec3(const Vec2 &xy, float z);

	//��һ��Vec2����һ��
	Vec3(float x, const Vec2 &yz);

public:
	Vec3 operator + (const Vec3 &other) const;
	Vec3 operator - (const Vec3 &other) const;
};


}}
