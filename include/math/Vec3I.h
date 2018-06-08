/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Vec3I
				
				����ά��Ϊ3����������

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "math/VecI.h"
#include "math/Vec2I.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec3I : public VecI
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

	//����xy����
	Vec2I XY() const;

	//����yz����
	Vec2I YZ() const;

	//��ˣ���������
	Vec3I CrossProduct(const Vec3I &other) const;

public:
	//����һ��Vec3I����������Ϊ(0.0, 0.0, 0.0)
	Vec3I();

	//����һ��Vec3I����������Ϊ(x, y, z)
	Vec3I(int x, int y, int z);

	//��һ��Vec2I����һ��Vec3I
	Vec3I(const Vec2I &xy, int z);

	//��һ��Vec2I����һ��
	Vec3I(int x, const Vec2I &yz);
};

}}
