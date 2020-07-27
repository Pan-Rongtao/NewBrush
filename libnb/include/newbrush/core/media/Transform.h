/*******************************************************
**	Transform
**
**��άƽ�����йر任�Ĺ��ܣ��任������ת (RotateTransform)������(ScaleTransform)��Ť�� (SkewTransform) ��ƽ�� (TranslateTransform)��
**
********************************************************/

#pragma once
#include "newbrush/core/DependencyObject.h"
#include "newbrush/core/base/Point.h"
#include "glm/glm.hpp"

namespace nb {

class NB_API Transform : public DependencyObject 
{
public:
	Transform();
	virtual ~Transform() = default;

	static Transform identity();

	virtual Transform inverse();
	virtual glm::mat4x4 value();
	virtual bool tryTransform(const Point &inPoint, Point &outPoint);

private:
	static Transform m_identity;
};

using TransformPtr = std::shared_ptr<Transform>;
}