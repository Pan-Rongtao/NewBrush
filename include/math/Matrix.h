/******************************************************************************

* Copyright (c) 2016���������������������޹�˾

* All rights reserved

* ��д��: ������

* ��д����: 2017-02

* ��Ҫ����: Matrix
				
				�������������������ݵļ��ϣ�����col�к�row�й��ɣ�����Ԫ�ظ���Ϊcol x row����
				Ϊ������洢�ṹ

* �޸ļ�¼:

*****************************************************************************/
#pragma once
#include "core/NewBrushDef.h"

namespace nb {namespace Math{

class NB_EXPORT Matrix
{
public:
	//��ȡ��
	unsigned int GetColumn() const;

	//��ȡ��
	unsigned int GetRow() const;

	//��col�У���row�е�Ԫ��
	const float &At(unsigned int col, unsigned int row) const;
	float &At(unsigned int col, unsigned int row);

	//�±�Ϊindex������
	//�쳣��indexԽ��
	const float *GetData() const;
	float *GetData();

	//�ж��Ƿ��ǵ�λ����
	//��λ������ж�Ϊ�������ҶԽ���Ԫ��Ϊ1������Ԫ��Ϊ0
	bool IsIdentity() const;

public:
	//����һ��col x row�ľ�����������ȫ����ʼ��Ϊ0.0
	Matrix(unsigned int col, unsigned int row);

	//����һ��col x row��������ֵ��data��col x row��Ԫ�������г�ʼ����ע�����dataָ������ݿ鲻��col x row��Ԫ�أ����ܻ������������
	//�쳣��col >= ���� || n >= ����
	Matrix(unsigned int col, unsigned int row, float *data);

	//����һ��col x row��������ֵ��data��count��Ԫ�������г�ʼ�������count�ĸ�������col x row��ʣ�ಿ�ֳ�ʼ��Ϊ0.0�������ֻȡdata��col x row��Ԫ������ʼ������
	//�쳣��col >= ���� || row >= ����
	Matrix(unsigned int col, unsigned int row, float *data, unsigned int count);

	//����һ��Matrix����һ��Matrix
	Matrix(const Matrix &other);

	virtual ~Matrix();

public:
	//�쳣��other��m, n�ײ�ͬ
	Matrix & operator = (const Matrix &other);
	
	bool operator == (const Matrix &other) const;
	bool operator != (const Matrix &other) const;

//	const float & operator [] (int index) const;
//	float & operator [] (int index);
	
	Matrix operator * (const Matrix &other) const;

public:
	//�ж����������Ƿ�������
	static bool CanMultiply(const Matrix &matrix1, const Matrix &matrix2);

protected:
	unsigned int 	m_col;
	unsigned int 	m_row;
	float			*m_Data;
};


}}
