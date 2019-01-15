/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Vec4
				
				����ά��Ϊ4�ĸ���������

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "Vec2.h"
#include "Vec3.h"

namespace nb{ namespace core{

//class Vec4
class NB_API Vec4
{
public:
	//����һ��Vec4�����ķ���Ϊ(0.0, 0.0, 0.0, 0.0)
	Vec4();

	//����һ��Vec4�����ķ���Ϊ(x, y, z, w);
	Vec4(float x, float y, float z, float w);

	//��Vec2����һ��Vec4
	Vec4(const Vec2 &xy, const Vec2 &zw);

	//��Vec2����һ��Vec4
	Vec4(float x, const Vec2 &yz, float w);

	//��Vec2����һ��Vec4
	Vec4(float x, float y, const Vec2 &zw);

	//��Vec3����һ��Vec4
	Vec4(const Vec3 &xyz, float w);

	//��Vec3����һ��Vec4
	Vec4(float x, const Vec3 &yzw);

	Vec4(const Vec4 &other);

	void operator = (const Vec4 &other);
	bool operator == (const Vec4 &other) const;
	bool operator != (const Vec4 &other) const;
	float & operator [] (uint32_t index);
	const float & operator [] (uint32_t index) const;
	Vec4 operator + (float f) const;
	Vec4 operator + (const Vec4 &v) const;
	Vec4 operator - (float f) const;
	Vec4 operator - (const Vec4 &v) const;
	Vec4 operator * (float f) const;
	Vec4 operator / (float f) const;
	void operator += (float f);
	void operator += (const Vec4 &other);
	void operator -= (float f);
	void operator -= (const Vec4 &other);
	void operator *= (float f);
	void operator /= (float f);

	Vec4 operator - () const;

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

	//����w����������
	float &w();
	const float &w() const;

	//����xy����
	Vec2 xy() const;

	//����yz����
	Vec2 yz() const;

	//����zw����
	Vec2 zw() const;

	//����xyz����
	Vec3 xyz() const;

	//����yzw����
	Vec3 yzw() const;

	//�����±�Ϊindex����
	float &at(uint32_t index);
	const float &at(uint32_t index) const;

	//ģ/����
	float norm() const;
	float length() const;

	//��׼��
	Vec4 normalized() const;

private:
	float	m_d[4];
};

//class Vec4I
class NB_API Vec4I
{
public:
	//����һ��Vec4I����������Ϊ(0.0, 0.0, 0.0, 0.0)
	Vec4I();

	//����һ��Vec4I����������Ϊ(x, y, z, w);
	Vec4I(int x, int y, int z, int w);

	//��Vec2I����һ��Vec4I
	Vec4I(const Vec2I &xy, const Vec2I &zw);

	//��Vec2I����һ��Vec4I
	Vec4I(int x, const Vec2I &yz, int w);

	//��Vec2I����һ��Vec4I
	Vec4I(int x, int y, const Vec2I &zw);

	//��Vec3I����һ��Vec4I
	Vec4I(const Vec3I &xyz, int w);

	//��Vec3I����һ��Vec4I
	Vec4I(int x, const Vec3I &yzw);

	Vec4I(const Vec4I &other);

	void operator = (const Vec4I &other);
	bool operator == (const Vec4I &other) const;
	bool operator != (const Vec4I &other) const;
	int & operator [] (uint32_t index);
	const int & operator [] (uint32_t index) const;
	Vec4I operator + (int n) const;
	Vec4I operator + (const Vec4I &v) const;
	Vec4I operator - (int n) const;
	Vec4I operator - (const Vec4I &v) const;
	Vec4I operator * (int n) const;
	Vec4I operator / (int n) const;
	void operator += (int n);
	void operator += (const Vec4I &other);
	void operator -= (int n);
	void operator -= (const Vec4I &other);
	void operator *= (int n);
	void operator /= (int n);

	Vec4I operator - () const;

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

	//����w����������
	int &w();
	const int &w() const;

	//����xy����
	Vec2I xy() const;

	//����yz����
	Vec2I yz() const;

	//����zw����
	Vec2I zw() const;

	//����xyz����
	Vec3I xyz() const;

	//����yzw����
	Vec3I yzw() const;

	//�����±�Ϊindex��ֵ
	int &at(uint32_t index);
	const int &at(uint32_t index) const;

	//ģ/����
	float norm() const;
	float lenght() const;

	Vec4I normalized() const;

private:
	int		m_d[4];
};

//class Vec4B
class NB_API Vec4B
{
public:
	//����һ��Vec4B����������Ϊ(0.0, 0.0, 0.0, 0.0)
	Vec4B();

	//����һ��Vec4B����������Ϊ(x, y, z, w);
	Vec4B(bool x, bool y, bool z, bool w);

	//��Vec2B����һ��Vec4B
	Vec4B(const Vec2B &xy, const Vec2B &zw);

	//��Vec2B����һ��Vec4B
	Vec4B(bool x, const Vec2B &yz, bool w);

	//��Vec2B����һ��Vec4B
	Vec4B(bool x, bool y, const Vec2B &zw);

	//��Vec3B����һ��Vec4B
	Vec4B(const Vec3B &xyz, bool w);

	//��Vec3B����һ��Vec4B
	Vec4B(bool x, const Vec3B &yzw);

	Vec4B(const Vec4B &other);

	void operator = (const Vec4B &other);
	bool operator == (const Vec4B &other) const;
	bool operator != (const Vec4B &other) const;
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

	//����w����������
	bool &w();
	const bool &w() const;

	//����xy����
	Vec2B xy() const;

	//����yz����
	Vec2B yz() const;

	//����zw����
	Vec2B zw() const;

	//����xyz����
	Vec3B xyz() const;

	//����yzw����
	Vec3B yzw() const;

	//�����±�Ϊindex��ֵ
	bool &at(uint32_t index);
	const bool &at(uint32_t index) const;

	//ģ/����
	float norm() const;
	float lenght() const;

	Vec4B crossProduct(const Vec4B &other) const;

private:
	bool	m_d[4];
};


}}
