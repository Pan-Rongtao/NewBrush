/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Vec3
				
				����ά��Ϊ3�ĸ���������

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "Vec2.h"

namespace nb{ namespace core{

//class Vec3
class NB_API Vec3
{
public:
	//����һ��Vec3�����ķ���Ϊ(0.0, 0.0, 0.0)
	Vec3();

	//����һ��Vec3����������Ϊ(x, y, z)
	Vec3(float x, float y, float z);

	//��һ��Vec2����һ��Vec3
	Vec3(const Vec2 &xy, float z);

	//��һ��Vec2����һ��
	Vec3(float x, const Vec2 &yz);

	Vec3(const Vec3 &other);

	void operator = (const Vec3 &other);
	bool operator == (const Vec3 &other) const;
	bool operator != (const Vec3 &other) const;
	float & operator [] (uint32_t index);
	const float & operator [] (uint32_t index) const;
	Vec3 operator + (float f) const;
	Vec3 operator + (const Vec3 &v) const;
	Vec3 operator - (float f) const;
	Vec3 operator - (const Vec3 &v) const;
	Vec3 operator * (float f) const;
	Vec3 operator / (float f) const;
	void operator += (float f);
	void operator += (const Vec3 &other);
	void operator -= (float f);
	void operator -= (const Vec3 &other);
	void operator *= (float f);
	void operator /= (float f);

	Vec3 operator - () const;

public:
	//����
	float *data();
	const float *data() const;

	//ά��
	uint32_t dimension() const;

	//����x����������
	float &x();
	const float &x() const;

	//����y����������
	float &y();
	const float &y() const;

	//����z����������
	float &z();
	const float &z() const;

	//����xy����
	Vec2 xy() const;

	//����yz����
	Vec2 yz() const;

	//�����±�Ϊindex����
	float &at(uint32_t index);
	const float &at(uint32_t index) const;

	//ģ/����
	float norm() const;
	float length() const;

	//��׼��
	Vec3 normalized() const;

	//��ˣ���������
	float dotProduct(const Vec3 &other) const;

	//��ˣ���������
	Vec3 crossProduct(const Vec3 &other) const;

private:
	float	m_d[3];
};

//class Vec3I
class NB_API Vec3I
{
public:
	//����һ��Vec3I����������Ϊ(0.0, 0.0, 0.0)
	Vec3I();

	//����һ��Vec3I����������Ϊ(x, y, z)
	Vec3I(int x, int y, int z);

	//��һ��Vec2I����һ��Vec3I
	Vec3I(const Vec2I &xy, int z);

	//��һ��Vec2I����һ��
	Vec3I(int x, const Vec2I &yz);

	Vec3I(const Vec3I &other);

	void operator = (const Vec3I &other);
	bool operator == (const Vec3I &other) const;
	bool operator != (const Vec3I &other) const;
	int & operator [] (uint32_t index);
	const int & operator [] (uint32_t index) const;
	Vec3I operator + (int n) const;
	Vec3I operator + (const Vec3I &v) const;
	Vec3I operator - (int n) const;
	Vec3I operator - (const Vec3I &v) const;
	Vec3I operator * (int n) const;
	Vec3I operator / (int n) const;
	void operator += (int n);
	void operator += (const Vec3I &other);
	void operator -= (int n);
	void operator -= (const Vec3I &other);
	void operator *= (int n);
	void operator /= (int n);

	Vec3I operator - () const;


public:
	//����
	int *data();
	const int *data() const;

	//ά��
	uint32_t dimension() const;

	//����x����������
	int &x();
	const int &x() const;

	//����y����������
	int &y();
	const int &y() const;

	//����z����������
	int &z();
	const int &z() const;

	//����xy����
	Vec2I xy() const;

	//����yz����
	Vec2I yz() const;

	//�����±�Ϊindex��ֵ
	int &at(uint32_t index);
	const int &at(uint32_t index) const;

	//ģ/����
	float norm() const;
	float lenght() const;

	Vec3I normalized() const;

	//��ˣ���������
	Vec3I crossProduct(const Vec3I &other) const;

private:
	int		m_d[3];
};

//class Vec3B
class NB_API Vec3B
{
public:
	//����һ��Vec3B����������Ϊ(0.0, 0.0, 0.0)
	Vec3B();

	//����һ��Vec3B����������Ϊ(x, y, z)
	Vec3B(bool x, bool y, bool z);

	//��һ��Vec2B����һ��Vec3B
	Vec3B(const Vec2B &xy, bool z);

	//��һ��Vec2B����һ��
	Vec3B(bool x, const Vec2B &yz);

	Vec3B(const Vec3B &other);

	void operator = (const Vec3B &other);
	bool operator == (const Vec3B &other) const;
	bool operator != (const Vec3B &other) const;
	bool & operator [] (uint32_t index);
	const bool & operator [] (uint32_t index) const;

public:
	//����
	bool *data();
	const bool *data() const;

	//ά��
	uint32_t dimension() const;

	//����x����������
	bool &x();
	const bool &x() const;

	//����y����������
	bool &y();
	const bool &y() const;

	//����z����������
	bool &z();
	const bool &z() const;

	//����xy����
	Vec2B xy() const;

	//����yz����
	Vec2B yz() const;

	//�����±�Ϊindex��ֵ
	bool &at(uint32_t index);
	const bool &at(uint32_t index) const;

	//ģ/����
	float norm() const;
	float lenght() const;

	Vec3B crossProduct(const Vec3B &other) const;

private:
	bool	m_d[3];
};


static nb::core::Vec3 operator * (float f, nb::core::Vec3 v)
{
	return v * f;
}

}}
