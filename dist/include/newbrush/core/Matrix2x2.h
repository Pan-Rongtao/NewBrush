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
#include "Vec2.h"

namespace nb{ namespace core{

class NB_API Matrix2x2
{
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
	Matrix2x2(float *data, uint32_t count);

	//����һ��2x2��λ����
	static Matrix2x2 identity();

	//��other����һ��Matrix2x2
	Matrix2x2(const Matrix2x2 &other);

	void operator =(const Matrix2x2 &other);
	bool operator == (const Matrix2x2 &other) const;
	bool operator != (const Matrix2x2 &other) const;
	Vec2 & operator[] (uint32_t row);
	const Vec2 & operator[] (uint32_t row) const;
	Matrix2x2 operator + (float f) const;
	Matrix2x2 operator + (const Matrix2x2 &other) const;
	Matrix2x2 operator - (float f) const;
	Matrix2x2 operator - (const Matrix2x2 &other) const;
	Matrix2x2 operator * (float f) const;
	Matrix2x2 operator * (const Matrix2x2 &right) const;
	Matrix2x2 operator / (float f) const;

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

private:
	Vec2	m_d[2];
};

}}
