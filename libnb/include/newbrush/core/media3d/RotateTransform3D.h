#pragma once
#include "newbrush/core/media3d/Transform3D.h"
#include "newbrush/core/media3d/Rotation3D.h"
#include "newbrush/core/base/Point.h"

namespace nb {

class RotateTransform3D : public Transform3D
{
public:
	RotateTransform3D();
	RotateTransform3D(Rotation3DPtr rotation);
	RotateTransform3D(Rotation3DPtr rotation, const Point3D &center);
	RotateTransform3D(Rotation3DPtr rotation, float centerX, float centerY, float centerZ);

	static DependencyPropertyPtr CenterXProperty();	//���ĵ�X��������������(float, 0.0)
	static DependencyPropertyPtr CenterYProperty();	//���ĵ�Y��������������(float, 0.0)
	static DependencyPropertyPtr CenterZProperty();	//���ĵ�Z��������������(float, 0.0)
	static DependencyPropertyPtr RotationProperty();//��תֵ����������(Rotation3DPtr, nullptr)

	virtual glm::mat4x4 value() const;

};

}