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
#include "Vec4.h"

namespace nb{ namespace core {

class NB_API Matrix4x4
{
public:
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
	Matrix4x4(float *data, uint32_t count);

	//��λMatrix4x4
	static Matrix4x4 identity();

	//ƽ�ƾ���
	static Matrix4x4 translateMatrix(float x, float y, float z);

	//���ž���
	static Matrix4x4 scaleMatrix(float scaleX, float scaleY, float scaleZ);

	//��other����һ��Matrix2x2
	Matrix4x4(const Matrix4x4 &other);

	void operator = (const Matrix4x4 &other);
	bool operator == (const Matrix4x4 &other) const;
	bool operator != (const Matrix4x4 &other) const;
	Vec4 & operator[] (uint32_t row);
	const Vec4 & operator[] (uint32_t row) const;
	Matrix4x4 operator + (float f) const;
	Matrix4x4 operator + (const Matrix4x4 &other) const;
	Matrix4x4 operator - (float f) const;
	Matrix4x4 operator - (const Matrix4x4 &other) const;
	Matrix4x4 operator * (float f) const;
	Matrix4x4 operator * (const Matrix4x4 &right) const;
	Matrix4x4 operator / (float f) const;

public:
	//����
	float *data();
	const float *data() const;

	//Ԫ�ظ���
	uint32_t size() const;

	//����
	uint32_t row() const;

	//����
	uint32_t column() const;

	//�±�Ϊrow, col������
	float &at(uint32_t row, uint32_t col);
	const float &at(uint32_t row, uint32_t col) const;

	//�Ƿ��ǵ�λ����
	bool isIdentity() const;

	//ת��Ϊ��λ����
	void toIdentity();

	//�ƶ�
	Matrix4x4 &translate(float x, float y, float z);
	Matrix4x4 &translateX(float x);
	Matrix4x4 &translateY(float y);
	Matrix4x4 &translateZ(float z);

	//��ת�Ƕ�
	Matrix4x4 &rotateRadian(float radian, float x, float y, float z);
	Matrix4x4 &rotateRadianX(float radian);
	Matrix4x4 &rotateRadianY(float radian);
	Matrix4x4 &rotateRadianZ(float radian);

	//��ת����
	Matrix4x4 &rotateAngle(float angle, float x, float y, float z);
	Matrix4x4 &rotateAngleX(float angle);
	Matrix4x4 &rotateAngleY(float angle);
	Matrix4x4 &rotateAngleZ(float angle);

	//����
	Matrix4x4 &scale(float x, float y, float z);
	Matrix4x4 &scaleX(float x);
	Matrix4x4 &scaleY(float y);
	Matrix4x4 &scaleZ(float z);
	Matrix4x4 &scaleUniform(float uniform);

private:
	Vec4	m_d[4];
};

}}
