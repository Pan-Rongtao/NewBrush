/*******************************************************
**	Transform
**
**��άƽ�����йر任�Ĺ��ܣ��任������ת (RotateTransform)������(ScaleTransform)��Ť�� (SkewTransform) ��ƽ�� (TranslateTransform)��
**
********************************************************/

#pragma once
#include "newbrush/core/DependencyObject.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

namespace nb {

	class NB_API Transform : public DependencyObject 
	{
	public:
		Transform();
		Transform(glm::mat4x4 mat);
		virtual ~Transform() = default;

		static Transform Identity();

		virtual Transform Inverse();
		virtual glm::mat4x4 Value();
		virtual bool TryTransform(const Point &inPoint, Point &outPoint);

	protected:
		glm::mat4x4 matrix;
	};
}