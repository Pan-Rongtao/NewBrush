/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Matrix4x4
				
				����4 x 4�ľ������ݽṹ

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "math/Matrix.h"
#include "math/Vec4.h"

namespace nb{ namespace Math{

class NB_EXPORT Matrix4x4 : public Matrix
{
public:
	//ת��Ϊ��λ����
	void ToIdentity();

	//�ƶ�
	Matrix4x4 Translate(float offsetX, float offsetY, float offsetZ);
	Matrix4x4 TranslateX(float offsetX);
	Matrix4x4 TranslateY(float offsetY);
	Matrix4x4 TranslateZ(float offsetZ);

	//��ת�Ƕ�
	Matrix4x4 RotateRadian(float radian, float x, float y, float z);
	Matrix4x4 RotateRadianX(float radian);
	Matrix4x4 RotateRadianY(float radian);
	Matrix4x4 RotateRadianZ(float radian);

	//��ת����
	Matrix4x4 RotateAngle(float angle, float x, float y, float z);
	Matrix4x4 RotateAngleX(float angle);
	Matrix4x4 RotateAngleY(float angle);
	Matrix4x4 RotateAngleZ(float angle);

	//����
	Matrix4x4 Scale(float scaleX, float scaleY, float scaleZ);
	Matrix4x4 ScaleX(float scaleX);
	Matrix4x4 ScaleY(float scaleY);
	Matrix4x4 ScaleZ(float scaleZ);
	Matrix4x4 ScaleUniform(float uniform);

public:
	//����һ��Matrix4x4������������
	//[0.0, 0.0, 0.0, 0.0]
	//[0.0, 0.0, 0.0, 0.0]
	//[0.0, 0.0, 0.0, 0.0]
	//[0.0, 0.0, 0.0, 0.0]
	Matrix4x4();

	//����һ��Matrix4x4���������ݱ���ʼ��
	Matrix4x4(float m0n0, float m0n1, float m0n2, float m0n3, float m1n0, float m1n1, float m1n2, float m1n3, float m2n0, float m2n1, float m2n2, float m2n3, float m3n0, float m3n1, float m3n2, float m3n3);

	//����һ��Matrix4x4��ʹ��Vec2����ʼ��
	Matrix4x4(const Vec4 &m0, const Vec4 &m1, const Vec4 &m2, const Vec4 &m3);

	//����һ��Matrix4x4��ʹ��float��������ʼ��
	explicit Matrix4x4(float *data);

	//����һ��Matrix4x4��ʹ��float�����count��Ԫ������ʼ��
	Matrix4x4(float *data, int count);

public:
	Matrix4x4 operator + (float f) const;
	Matrix4x4 operator + (const Matrix4x4 &other) const;
	Matrix4x4 operator - (float f) const;
	Matrix4x4 operator - (const Matrix4x4 &other) const;
	Matrix4x4 operator * (float f) const;
	Matrix4x4 operator * (const Matrix4x4 &right) const;

public:
	//��λMatrix4x4
	static Matrix4x4 Identify();

	//ƽ�ƾ���
	static Matrix4x4 TranslateMatrix(float offsetX, float offsetY, float offsetZ);

	//���ž���
	static Matrix4x4 ScaleMatrix(float scaleX, float scaleY, float scaleZ);

	//��ת����
	static Matrix4x4 RotateMatrix();
};

}}
