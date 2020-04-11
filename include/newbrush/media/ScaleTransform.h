/*******************************************************
**	ScaleTransform
**
*�ڶ�ά x-y ����ϵ�����Ŷ���
**
********************************************************/

#pragma once
#include "newbrush/media/Transform.h"

namespace nb {

	class NB_API ScaleTransform : public Transform
	{
	public:
		ScaleTransform();
		ScaleTransform(float scaleX, float scaleY);
		ScaleTransform(float scaleX, float scaleY, float centerX, float centerY);
		virtual ~ScaleTransform() = default;

		static DependencyProperty CenterXProperty();
		static DependencyProperty CenterYProperty();
		static DependencyProperty ScaleXProperty();
		static DependencyProperty ScaleYProperty();

		virtual glm::mat4x4 value() override;
	};
}