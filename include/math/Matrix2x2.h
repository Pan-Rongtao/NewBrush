/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Matrix2x2
				
				����2 x 2�ľ������ݽṹ

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "math/Matrix.h"
#include "math/Vec2.h"

namespace nb{ namespace Math{

class NB_EXPORT Matrix2x2 : public Matrix
{
public:
	//ת��Ϊ��λ����
	void ToIdentity();

public:
	//����һ��Matrix2x2������������
	//[0.0, 0.0]
	//[0.0, 0.0]
	Matrix2x2();

	//����һ��Matrix2x2���������ݱ���ʼ��
	Matrix2x2(float m0n0, float m0n1, float m1n0, float m1n1);

	//����һ��Matrix2x2��ʹ��Vec2����ʼ��
	Matrix2x2(const Vec2 &m0, const Vec2 &m1);

	//����һ��Matrix2x2��ʹ��float��������ʼ��
	explicit Matrix2x2(float *data);

	//����һ��Matrix2x2��ʹ��float�����count��Ԫ������ʼ��
	Matrix2x2(float *data, int count);

public:
	Matrix2x2 operator + (float f) const;
	Matrix2x2 operator + (const Matrix2x2 &other) const;
	Matrix2x2 operator - (float f) const;
	Matrix2x2 operator - (const Matrix2x2 &other) const;
	Matrix2x2 operator * (float f) const;
	Matrix2x2 operator * (const Matrix &right) const;

public:
	//����һ��2x2��λ����
	static Matrix2x2 Identity();
};


}}
