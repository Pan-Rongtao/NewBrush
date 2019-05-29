/*******************************************************
**	Triangle
**
**	������ģ��
**		Triangle������������ģ�͵����ݽṹ
**
**
**		������
**
********************************************************/
#pragma once
#include "Model.h"

namespace nb{namespace gl{

class NB_API Triangle : public Model
{
public:
	//����һ�������Σ����������������궼��0.0��������ɫ��0.0
	Triangle();

	//����һ�������Σ�������������������(p0, p1, p2)��������ɫ��0.0
	Triangle(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2);

	//����һ�������Σ�������������������(p0, p1, p2)��
	//���������������ɫ����color
	Triangle(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2, const nb::core::Vec4 &color);

	//����һ�������Σ�������������������(p0, p1, p2)�����������������ɫ����(color0, color1, color2)
	Triangle(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2, const nb::core::Vec4 &color0, const nb::core::Vec4 &color1, const nb::core::Vec4 &color2);

private:
	std::vector<uint16_t> getIndices() const;
	double distance(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1) const;
	//����
	nb::core::Vec2 center(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2) const;
};

}}
