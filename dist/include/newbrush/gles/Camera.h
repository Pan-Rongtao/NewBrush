#pragma once
#include "../core/Matrix4x4.h"

namespace nb{ namespace gl{

class NB_API Camera
{
public:
	//����һ�������������λ��Ϊ(0.0, 0.0, 1.0)��Ŀ���Ϊ(0.0, 0.0, 0.0)����������Ϊ(0.0, 1.0, 0.0)
	Camera();

	static std::shared_ptr<Camera> instance();
		
	//��ȡ�۲����
	nb::core::Matrix4x4 &matrix();
	const nb::core::Matrix4x4 &matrix() const;

	//lookup
	void lookat(const nb::core::Vec3 &position, const nb::core::Vec3 &target, const nb::core::Vec3 &upVec);

private:
	nb::core::Matrix4x4		m_matrix;
};

}}
