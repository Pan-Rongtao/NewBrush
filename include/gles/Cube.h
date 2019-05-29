/*******************************************************
**	Cube
**
**	������ģ��
**		Cube������������ģ�͵����ݽṹ
**
**
**		������
**
********************************************************/
#pragma once
#include "Model.h"

namespace nb{ namespace gl{

//һ��mesh��mesh��8�����㣬36����������
class NB_API Cube : public Model
{
public:
	//����һ�������壬����������(0.0, 0.0, 0.0)�����ĳ���߶���0.0
	Cube();

	//����һ�������壬�������ĵ���centerPosition�����ĳ������lenght, wide, height
	Cube(const nb::core::Vec3 &centerPosition, float lenght, float width, float height);

private:
	virtual void cullFace() override;

	std::vector<uint16_t> getIndices() const;
};

}}
