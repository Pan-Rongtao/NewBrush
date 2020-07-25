/*******************************************************
**	TranslateTransform
**
*�� ��ά x-y ����ϵ��ƽ�ƣ��ƶ�������
**
********************************************************/

#pragma once
#include "newbrush/core/media/Transform.h"

namespace nb {

class NB_API TranslateTransform : public Transform
{
public:
	TranslateTransform();
	TranslateTransform(float offsetX, float offsetY);
	virtual ~TranslateTransform() = default;

	static DependencyPropertyPtr XProperty();
	static DependencyPropertyPtr YProperty();

	virtual glm::mat4x4 value() override;

};

using TranslateTransformPtr = std::shared_ptr<TranslateTransform>;
}
