#pragma once
#include "newbrush/core/DependencyObject.h"

namespace nb {

class NB_API Rotation3D : public DependencyObject
{
public:
	
};
using Rotation3DPtr = std::shared_ptr<Rotation3D>;

class NB_API AxisAngleRotation3D : public Rotation3D
{
public:
	static DependencyPropertyPtr AxisProperty();	//����������ԣ�glm::vec3��Ĭ��ֵ(0,1,0)��
	static DependencyPropertyPtr AngleProperty();	//�Ƕȵ��������ԣ�float,Ĭ��ֵ0.0)
};
using AxisAngleRotation3DPtr = std::shared_ptr<AxisAngleRotation3D>;

class NB_API QuaternionRotation3D : public Rotation3D
{
public:

};
using QuaternionRotation3DPtr = std::shared_ptr<QuaternionRotation3D>;

}