#pragma once
#include "gles/Model2D.h"

namespace nb{namespace gl{ namespace Gles{

class NB_EXPORT Triangle : public Model2D
{
public:
	//����һ�������Σ����������������궼��0.0��������ɫ��0.0
	Triangle();

	//����һ�������Σ�������������������(fisrtPosition, secondPosition, thirdPosition)��������ɫ��0.0
	Triangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition);

	//����һ�������Σ�������������������(fisrtPosition, secondPosition, thirdPosition)��
	//���������������ɫ����unifyColor
	Triangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition, const nb::Math::Vec4 &unifyColor);

	//����һ�������Σ�������������������
	Triangle(const nb::Math::Vec2 &fisrtPosition, const nb::Math::Vec2 &secondPosition, const nb::Math::Vec2 &thirdPosition,
		const nb::Math::Vec4 &fisrtColor, const nb::Math::Vec4 &secondColor, const nb::Math::Vec4 &thirdColor);

protected:
};

}}}
