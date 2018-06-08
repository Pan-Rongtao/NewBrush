/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-01

* ��Ҫ����: VecI2
				
				�������������������д�С�ͷ����ֵ�������ݽṹ
				VecI��Ϊ������ڣ�VecI2��VecI3��VecI4�ֱ�Ϊά��Ϊ2��3��4�������������ͣ�
				��ʹ��x��y��z��w�Ľ��з����ķ��ʺ��޸ģ�Ҳ����xy��yz��zw��xyz��yzw�����ʶ������
* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "core/NewBrushDef.h"

namespace nb{ namespace Math{

class NB_EXPORT VecI
{
public:
	//��ȡά��
	int GetDimension() const;

	//��ȡ��index������
	//�쳣��indexԽ��
	int &At(int index);
	const int &At(int index) const;

	//ģ/����
	float Norm() const;
	float Lenght() const;

	//��׼��
	VecI Normalized();

	const int *GetData() const;
	int *GetData();

	//��ˣ���������
	int DotProduct(const VecI &other) const;

public:
	//����һ��ά��Ϊdimension��������Ԫ�س�ʼ��Ϊ0
	//�쳣��dimension<=0
	explicit VecI(int dimension);
	
	//������VecI����һ��VecI
	VecI(const VecI &other);
	virtual ~VecI();

	//�ȺŲ�����
	//�쳣��dimension��ͬ
	VecI & operator = (const VecI &other);

public:
	bool operator == (const VecI &other) const;
	bool operator != (const VecI &other) const;

	int & operator [] (int index);
	const int & operator [] (int index) const;

	VecI operator + (int n) const;
	VecI operator + (const VecI &v) const;
	VecI operator - (int n) const;
	VecI operator - (const VecI &v) const;
	VecI operator * (int n) const;
	VecI operator / (int n) const;

	void operator += (int n);
	//�ȺŲ�����
	//�쳣��dimension��ͬ
	void operator += (const VecI &other);
	void operator -= (int n);
	//�ȺŲ�����
	//�쳣��dimension��ͬ
	void operator -= (const VecI &other);
	void operator *= (int n);
	void operator /= (int n);

	VecI operator - () const;

protected:
	int		*m_Data;
	int		m_Dimension;
};

}}

