#pragma once
#include "math/Matrix4x4.h"

namespace nb{ namespace gl{ namespace Gles {

class Camera
{
public:
	//����һ�������������λ��Ϊ(0.0, 0.0, 1.0)��Ŀ���Ϊ(0.0, 0.0, 0.0)����������Ϊ(0.0, 1.0, 0.0)
	Camera();
	
	//����һ�������������λ��Ϊposition��Ŀ���Ϊtarget����������ΪupVec
	Camera(const nb::Math::Vec3 &position, const nb::Math::Vec3 &target, const nb::Math::Vec3 &upVec);

	//��ȡ�۲����
	nb::Math::Matrix4x4 GetMatrix() const;

private:
	nb::Math::Matrix4x4		m_matrix;
};

}}}
