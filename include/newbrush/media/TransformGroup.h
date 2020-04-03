/*******************************************************
**	TransformGroup
**
*��ʾ������Transform������ɵĸ���Transform
**
********************************************************/

#pragma once
#include "newbrush/media/TransformCollection.h"

namespace nb {

	class NB_API TransformGroup : public Transform
	{
	public:
		TransformGroup();

		static DependencyProperty ChildrenProperty();

		virtual glm::mat4x4 value() override;

	};
}