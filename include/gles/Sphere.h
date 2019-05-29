/*******************************************************
**	Sphere
**
**	��ģ��
**		������������ģ�͵����ݽṹ
**	
**
**		������
**
********************************************************/
#pragma once
#include "Model.h"

namespace nb{ namespace gl{

class NB_API Sphere : public Model
{
public:
	//����һ�����壬����Բ����centerPoint�����İ뾶��r
	Sphere(const nb::core::Vec3 &centerPoint, float r, bool cartesian);

private:
	virtual void cullFace() override;
	std::vector<uint16_t> getIndices() const;

};

}}
