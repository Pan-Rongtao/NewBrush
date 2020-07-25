/*******************************************************
**	ScaleTransform
**
*�ڶ�ά x-y ����ϵ�����Ŷ���
**
********************************************************/

#pragma once
#include "newbrush/core/media/Transform.h"

namespace nb {

class NB_API ScaleTransform : public Transform
{
public:
	ScaleTransform();
	ScaleTransform(float scaleX, float scaleY);
	ScaleTransform(float scaleX, float scaleY, float centerX, float centerY);
	virtual ~ScaleTransform() = default;

	static DependencyPropertyPtr CenterXProperty();
	static DependencyPropertyPtr CenterYProperty();
	static DependencyPropertyPtr ScaleXProperty();
	static DependencyPropertyPtr ScaleYProperty();

	virtual glm::mat4x4 value() override;
};

using ScaleTransformPtr = std::shared_ptr<ScaleTransform>;
}
