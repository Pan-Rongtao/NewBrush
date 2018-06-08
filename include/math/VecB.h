/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-01

* ��Ҫ����: VecB2
				
				���������������������д�С�ͷ����ֵ�������ݽṹ
				VecB��Ϊ������ڣ�VecB2��VecB3��VecB4�ֱ�Ϊά��Ϊ2��3��4�Ĳ������������ͣ�
				��ʹ��x��y��z��w�Ľ��з����ķ��ʺ��޸ģ�Ҳ����xy��yz��zw��xyz��yzw�����ʶ������
* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "core/NewBrushDef.h"

namespace nb{ namespace Math{

class NB_EXPORT VecB
{
public:
	//��ȡά��
	int GetDimension() const;

	//��ȡ��index������
	//�쳣��indexԽ��
	bool &At(int index);
	const bool &At(int index) const;

	//ģ/����
	float Norm() const;
	float Lenght() const;

	const bool *GetData() const;
	bool *GetData();

public:
	//����һ��ά��Ϊdimension��������Ԫ�س�ʼ��Ϊfalse
	//�쳣��dimension<=0
	explicit VecB(int dimension);
	
	//������VecB����һ��VecB
	VecB(const VecB &other);
	virtual ~VecB();

	//�ȺŲ�����
	//�쳣��dimension��ͬ
	VecB & operator = (const VecB &other);

public:
	bool operator == (const VecB &other) const;
	bool operator != (const VecB &other) const;

	bool & operator [] (int index);
	const bool & operator [] (int index) const;

protected:
	bool	*m_Data;
	int		m_Dimension;
};

}}

