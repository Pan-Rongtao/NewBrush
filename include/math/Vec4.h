/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Vec4
				
				����ά��Ϊ4�ĸ���������

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "math/Vec.h"
#include "math/Vec2.h"
#include "math/Vec3.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec4 : public Vec
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

	//����w����������
	float &W();
	const float &W() const;

	//����xy����
	Vec2 XY() const;

	//����yz����
	Vec2 YZ() const;

	//����zw����
	Vec2 ZW() const;

	//����xyz����
	Vec3 XYZ() const;

	//����yzw����
	Vec3 YZW() const;

public:
	//����һ��Vec4����������Ϊ(0.0, 0.0, 0.0, 0.0)
	Vec4();

	//����һ��Vec4����������Ϊ(x, y, z, w);
	Vec4(float x, float y, float z, float w);

	//��Vec2����һ��Vec4
	Vec4(const Vec2 &xy, const Vec2 &zw);

	//��Vec2����һ��Vec4
	Vec4(float x, const Vec2 &yz, float w);

	//��Vec2����һ��Vec4
	Vec4(float x, float y, const Vec2 &zw);

	//��Vec3����һ��Vec4
	Vec4(const Vec3 &xyz, float w);

	//��Vec3����һ��Vec4
	Vec4(float x, const Vec3 &yzw);
};

}}
