/*******************************************************
**	Ellipse
**
**	��Բģ��
**		Ellipse��������Բģ�͵����ݽṹ
**	Բ��һ���������Բ
**
**		������
**
********************************************************/
#pragma once
#include "Model.h"

namespace nb{ namespace gl{

class NB_API Circle : public Model
{
public:
	//����һ����Բ���������ĵ���center�������������᳤�ȷֱ�Ϊa��b��cartesian�Ƿ�Ϊ�ѿ�������ϵ
	//
	Circle(float x, float y, float a, float b, bool cartesian);

private:
	std::vector<uint16_t> getIndices() const;

};

}}
