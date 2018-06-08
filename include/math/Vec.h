/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-01

* ��Ҫ����: Vec2
				
				�������������������д�С�ͷ����ֵ�������ݽṹ
				Vec��Ϊ������ڣ�Vec2��Vec3��Vec4�ֱ�Ϊά��Ϊ2��3��4�ĸ������������ͣ�
				��ʹ��x��y��z��w�Ľ��з����ķ��ʺ��޸ģ�Ҳ����xy��yz��zw��xyz��yzw�����ʶ������
* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "core/NewBrushDef.h"

namespace nb{ namespace Math{

class NB_EXPORT Vec
{
public:
	//��ȡά��
	int GetDimension() const;

	//��ȡ��index������
	//�쳣��indexԽ��
	float &At(int index);
	const float &At(int index) const;

	//ģ/����
	float Norm() const;
	float Lenght() const;

	//��׼��
	Vec Normalized() const;

	const float *GetData() const;
	float *GetData();

	//��ˣ���������
	float DotProduct(const Vec &other) const;

public:
	//����һ��ά��Ϊdimension��������Ԫ�س�ʼ��Ϊ0.0
	//�쳣��dimension<=0
	explicit Vec(int dimension);
	
	//������Vec����һ��Vec
	Vec(const Vec &other);
	virtual ~Vec();

	//�ȺŲ�����
	//�쳣��dimension��ͬ
	Vec & operator = (const Vec &other);

public:
	bool operator == (const Vec &other) const;
	bool operator != (const Vec &other) const;

	float & operator [] (int index);
	const float & operator [] (int index) const;

	Vec operator + (float f) const;
	Vec operator + (const Vec &v) const;
	Vec operator - (float f) const;
	Vec operator - (const Vec &v) const;
	Vec operator * (float f) const;
	Vec operator / (float f) const;

	void operator += (float f);
	//�ȺŲ�����
	//�쳣��dimension��ͬ
	void operator += (const Vec &other);
	void operator -= (float f);
	//�ȺŲ�����
	//�쳣��dimension��ͬ
	void operator -= (const Vec &other);
	void operator *= (float f);
	void operator /= (float f);

	Vec operator - () const;


protected:
	float	*m_Data;
	int		m_Dimension;
};

}}

