/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Vec2I
				
				����ά��Ϊ2����������

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "math/VecI.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec2I : public VecI
{
public:
	//����x����������
	int &X();
	const int &X() const;

	//����y����������
	int &Y();
	const int &Y() const;

	//��ˣ���������
	Vec2I CrossProduct(const Vec2I &other) const;

public:
	//����һ��Vec2I����, ��������Ϊ��0.0, 0.0)
	Vec2I();

	//��������������һ��Vec2I����������Ϊ(x, y)
	Vec2I(int x, int y);

	Vec2I(const Vec2I &other);
	~Vec2I();
};

}}
