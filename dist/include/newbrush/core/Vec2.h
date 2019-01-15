/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Vec2
				
				����ά��Ϊ2�ĸ���������

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "../core/Def.h"

namespace nb{ namespace core{

//class Vec2
class NB_API Vec2
{
public:
	//����һ��Vec2����, ���ķ���Ϊ��0.0, 0.0)
	Vec2();

	//��������������һ��Vec2�����ķ���Ϊ(x, y)
	Vec2(float x, float y);

	Vec2(const Vec2 &other);
	~Vec2();

	void operator = (const Vec2 &other);
	bool operator == (const Vec2 &other) const;
	bool operator != (const Vec2 &other) const;
	float & operator [] (uint32_t index);
	const float & operator [] (uint32_t index) const;
	Vec2 operator + (float f) const;
	Vec2 operator + (const Vec2 &v) const;
	Vec2 operator - (float f) const;
	Vec2 operator - (const Vec2 &v) const;
	Vec2 operator * (float f) const;
	Vec2 operator / (float f) const;
	void operator += (float f);
	void operator += (const Vec2 &other);
	void operator -= (float f);
	void operator -= (const Vec2 &other);
	void operator *= (float f);
	void operator /= (float f);

	Vec2 operator - () const;

public:
	//����
	float *data();
	const float *data() const;

	//ά��
	uint32_t dimension() const;

	//����x����
	float &x();
	const float &x() const;

	//����y����
	float &y();
	const float &y() const;

	//�����±�Ϊindex����
	float &at(uint32_t index);
	const float &at(uint32_t index) const;

	//ģ/����
	float norm() const;
	float length() const;

	//��׼��
	Vec2 normalized() const;

	//��ˣ���������
	Vec2 crossProduct(const Vec2 &other) const;

private:
	float	m_d[2];
};

//class Vec2I
class NB_API Vec2I
{
public:
	//����һ��Vec2I����, ��������Ϊ��0.0, 0.0)
	Vec2I();

	//��������������һ��Vec2I����������Ϊ(x, y)
	Vec2I(int x, int y);

	Vec2I(const Vec2I &other);
	~Vec2I();

	void operator = (const Vec2I &other);
	bool operator == (const Vec2I &other) const;
	bool operator != (const Vec2I &other) const;
	int & operator [] (uint32_t index);
	const int & operator [] (uint32_t index) const;
	Vec2I operator + (int n) const;
	Vec2I operator + (const Vec2I &v) const;
	Vec2I operator - (int n) const;
	Vec2I operator - (const Vec2I &v) const;
	Vec2I operator * (int n) const;
	Vec2I operator / (int n) const;
	void operator += (int n);
	void operator += (const Vec2I &other);
	void operator -= (int n);
	void operator -= (const Vec2I &other);
	void operator *= (int n);
	void operator /= (int n);

	Vec2I operator - () const;

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

	//�����±�Ϊindex��ֵ
	int &at(uint32_t index);
	const int &at(uint32_t index) const;

	//ģ/����
	float norm() const;
	float lenght() const;

	Vec2I normalized() const;

	//��ˣ���������
	Vec2I crossProduct(const Vec2I &other) const;

private:
	int		m_d[2];
};


//class Vec2B
class NB_API Vec2B
{
public:
	//����һ��Vec2B����, ���ķ���Ϊ��false, false)
	Vec2B();

	//��������������һ��Vec2B�����ķ���Ϊ(x, y)
	Vec2B(bool x, bool y);

	Vec2B(const Vec2B &other);
	~Vec2B();

	void operator = (const Vec2B &other);
	bool operator == (const Vec2B &other) const;
	bool operator != (const Vec2B &other) const;
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

	//�����±�Ϊindex��ֵ
	bool &at(uint32_t index);
	const bool &at(uint32_t index) const;

	//ģ/����
	float norm() const;
	float lenght() const;

	Vec2B crossProduct(const Vec2B &other) const;

private:
	bool	m_d[2];
};


}}
