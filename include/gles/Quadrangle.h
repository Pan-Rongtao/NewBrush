#pragma once
#include "../core/Vec2.h"
#include "Model.h"

namespace nb{ namespace gl{

class NB_API Quadrangle : public Model
{
public:
	//����һ�����Σ������ĸ��������궼Ϊ0.0����ɫΪ0.0
	Quadrangle();

	//����һ�����Σ��������ĵ���centerPoint�����Ϊwidth, height
	//�����ĸ�������ɫ��Ϊ0.0
	Quadrangle(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2, const nb::core::Vec2 &p3);

	//����һ�����Σ��������ĵ���centerPoint�����Ϊwidth, height
	//�����ĸ�������ɫ��ΪunifyColor
	Quadrangle(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2, const nb::core::Vec2 &p3, const nb::core::Vec4 &color);

	//����һ�����Σ��������ĵ���centerPoint�����Ϊwidth, height
	//�����ĸ�������ɫΪ(color0, color1, color2, color3)
	Quadrangle(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2, const nb::core::Vec2 &p3, const nb::core::Vec4 &color0, const nb::core::Vec4 &color1, const nb::core::Vec4 &color2, const nb::core::Vec4 &color3);

private:
	std::vector<uint16_t> getIndices() const;
	nb::core::Vec3 getCenter(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2, const nb::core::Vec2 &p3) const;
};

}}
