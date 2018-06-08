/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Vec4I
				
				����ά��Ϊ4����������

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "math/VecI.h"
#include "math/Vec2I.h"
#include "math/Vec3I.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec4I : public VecI
{
public:
	//����x����������
	int &X();
	const int &X() const;

	//����y����������
	int &Y();
	const int &Y() const;

	//����z����������
	int &Z();
	const int &Z() const;

	//����w����������
	int &W();
	const int &W() const;

	//����xy����
	Vec2I XY() const;

	//����yz����
	Vec2I YZ() const;

	//����zw����
	Vec2I ZW() const;

	//����xyz����
	Vec3I XYZ() const;

	//����yzw����
	Vec3I YZW() const;

public:
	//����һ��Vec4I����������Ϊ(0.0, 0.0, 0.0, 0.0)
	Vec4I();

	//����һ��Vec4I����������Ϊ(x, y, z, w);
	Vec4I(int x, int y, int z, int w);

	//��Vec2I����һ��Vec4I
	Vec4I(const Vec2I &xy, const Vec2I &zw);

	//��Vec2I����һ��Vec4I
	Vec4I(int x, const Vec2I &yz, int w);

	//��Vec2I����һ��Vec4I
	Vec4I(int x, int y, const Vec2I &zw);

	//��Vec3I����һ��Vec4I
	Vec4I(const Vec3I &xyz, int w);

	//��Vec3I����һ��Vec4I
	Vec4I(int x, const Vec3I &yzw);
};

}}
