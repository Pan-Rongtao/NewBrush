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
#include "Vec3.h"

namespace nb{ namespace core {

class NB_API Matrix3x3
{
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
	Matrix3x3(float *data, uint32_t count);

	//����һ��3x3��λ����
	static Matrix3x3 identity();

	//��other����һ��Matrix3x3
	Matrix3x3(const Matrix3x3 &other);

	void operator =(const Matrix3x3 &other);
	bool operator == (const Matrix3x3 &other) const;
	bool operator != (const Matrix3x3 &other) const;
	Vec3 & operator[] (uint32_t row);
	const Vec3 & operator[] (uint32_t row) const;
	Matrix3x3 operator + (float f) const;
	Matrix3x3 operator + (const Matrix3x3 &other) const;
	Matrix3x3 operator - (float f) const;
	Matrix3x3 operator - (const Matrix3x3 &other) const;
	Matrix3x3 operator * (float f) const;
	Matrix3x3 operator * (const Matrix3x3 &right) const;
	Matrix3x3 operator / (float f) const;

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

	//��row�е�col��Ԫ��
	float &at(uint32_t row, uint32_t col);
	const float &at(uint32_t row, uint32_t col) const;

	//�Ƿ��ǵ�λ����
	bool isIdentity() const;

	//ת��Ϊ��λ����
	void toIdentity();
	/*
	//�ƶ�
	void translate(float x, float y);
	void translateX(float x);
	void translateY(float y);

	//��ת�Ƕ�
	void rotateRadian(float radian, float x, float y);
	void rotateRadianX(float radian);
	void rotateRadianY(float radian);

	//��ת����
	void rotateAngle(float angle, float x, float y);
	void rotateAngleX(float angle);
	void rotateAngleY(float angle);

	//����
	void scale(float x, float y);
	void scaleX(float x);
	void scaleY(float y);
	*/
private:
	Vec3	m_d[3];
};

}}
