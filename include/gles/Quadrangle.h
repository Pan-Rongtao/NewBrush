#pragma once
#include "math/Vec2.h"
#include "gles/Model2D.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT Quadrangle : public Model2D
{
public:
	//����һ�����Σ������ĸ��������궼Ϊ0.0����ɫΪ0.0
	Quadrangle();

	//����һ�����Σ������ĸ���������Ϊ(fisrtPosition, secondPosition, thirdPosition, fourthPosition)
	//�����ĸ�������ɫ��Ϊ0.0
	Quadrangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition, const nb::Math::Vec2 &fourthPosition);

	//����һ�����Σ������ĸ���������Ϊ(fisrtPosition, secondPosition, thirdPosition, fourthPosition)
	//�����ĸ�������ɫ��ΪunifyColor
	Quadrangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition, const nb::Math::Vec2 &fourthPosition, const nb::Math::Vec4 &unifyColor);

	//����һ�����Σ������ĸ���������Ϊ(fisrtPosition, secondPosition, thirdPosition, fourthPosition)
	//�����ĸ�������ɫΪ(fisrtColor, secondColor, thirdColor, fourthColor)
	Quadrangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition, const nb::Math::Vec2 &fourthPosition, 
		const nb::Math::Vec4 &fisrtColor, const nb::Math::Vec4 &secondColor, const nb::Math::Vec4 &thirdColor, const nb::Math::Vec4 &fourthColor);

protected:
	virtual IndicesSequece VertextsSequenceOverride() const;
};

}}}
