/*******************************************************
**	TransformGroup
**
*��ʾ������Transform������ɵĸ���Transform
**
********************************************************/

#pragma once
#include "newbrush/media/Transform3D.h"

namespace nb {
	
using TransformCollection = std::vector<Transform3DPtr>;
using TransformCollectionPtr = std::shared_ptr<TransformCollection>;

class NB_API Transform3DGroup : public Transform3D
{
public:
	Transform3DGroup() = default;

	static DependencyPropertyPtr ChildrenProperty();

	virtual glm::mat4x4 value() const override;

};
}