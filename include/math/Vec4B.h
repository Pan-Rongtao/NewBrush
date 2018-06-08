/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Vec4
				
				����ά��Ϊ4�Ĳ���������

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "math/VecB.h"
#include "math/Vec2B.h"
#include "math/Vec3B.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec4B : public VecB
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

	//����w����������
	bool &W();
	const bool &W() const;

	//����xy����
	Vec2B XY() const;

	//����yz����
	Vec2B YZ() const;

	//����zw����
	Vec2B ZW() const;

	//����xyz����
	Vec3B XYZ() const;

	//����yzw����
	Vec3B YZW() const;

public:
	//����һ��Vec4B����������Ϊ(0.0, 0.0, 0.0, 0.0)
	Vec4B();

	//����һ��Vec4B����������Ϊ(x, y, z, w);
	Vec4B(bool x, bool y, bool z, bool w);

	//��Vec2B����һ��Vec4B
	Vec4B(const Vec2B &xy, const Vec2B &zw);

	//��Vec2B����һ��Vec4B
	Vec4B(bool x, const Vec2B &yz, bool w);

	//��Vec2B����һ��Vec4B
	Vec4B(bool x, bool y, const Vec2B &zw);

	//��Vec3B����һ��Vec4B
	Vec4B(const Vec3B &xyz, bool w);

	//��Vec3B����һ��Vec4B
	Vec4B(bool x, const Vec3B &yzw);
};

}}
