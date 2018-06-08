/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Matrix3x3
				
				����3 x 3�ľ������ݽṹ

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "math/Matrix.h"
#include "math/Vec3.h"

namespace nb{ namespace Math{

class NB_EXPORT Matrix3x3 : public Matrix
{
public:
	//ת��Ϊ��λ����
	void ToIdentity();

	//�ƶ�
	void Translate(float x, float y);
	void TranslateX(float x);
	void TranslateY(float y);

	//��ת�Ƕ�
	void RotateRadian(float radian, float x, float y);
	void RotateRadianX(float radian);
	void RotateRadianY(float radian);

	//��ת����
	void RotateAngle(float angle, float x, float y);
	void RotateAngleX(float angle);
	void RotateAngleY(float angle);

	//����
	void Scale(float x, float y);
	void ScaleX(float x);
	void ScaleY(float y);

public:
	//����һ��Matrix3x3������������
	//[0.0, 0.0, 0.0]
	//[0.0, 0.0, 0.0]
	//[0.0, 0.0, 0.0]
	Matrix3x3();

	//����һ��Matrix3x3���������ݱ���ʼ��
	Matrix3x3(float m0n0, float m0n1, float m0n2, float m1n0, float m1n1, float m1n2, float m2n0, float m2n1, float m2n2);

	//����һ��Matrix3x3��ʹ��Vec2����ʼ��
	Matrix3x3(const Vec3 &m0, const Vec3 &m1, const Vec3 &m2);

	//����һ��Matrix3x3��ʹ��float��������ʼ��
	explicit Matrix3x3(float *data);

	//����һ��Matrix3x3��ʹ��float�����count��Ԫ������ʼ��
	Matrix3x3(float *data, int count);

public:
	Matrix3x3 operator + (float f) const;
	Matrix3x3 operator + (const Matrix3x3 &other) const;
	Matrix3x3 operator - (float f) const;
	Matrix3x3 operator - (const Matrix3x3 &other) const;
	Matrix3x3 operator * (float f) const;
	Matrix3x3 operator * (const Matrix &right) const;

public:
	//����һ��3x3��λ����
	static Matrix3x3 Identity();
};

}}
