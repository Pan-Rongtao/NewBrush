/*******************************************************
**	Projection
**
**	ͶӰ
**		ͶӰ�����������ü��ռ�����ݽṹ
**
**		������
**
********************************************************/
#pragma once
#include "../core/Matrix4x4.h"

namespace nb{ namespace gl{

class NB_API Projection
{
public:
	//����
	nb::core::Matrix4x4 &matrix();
	const nb::core::Matrix4x4 &matrix() const;

	//����ͶӰ
	void ortho(float left, float right, float bottom, float top, float near, float far);

	//͸��ͶӰ
	void perspective(float fovy, float aspect, float near, float far);

	static std::shared_ptr<Projection> instance();

private:
	nb::core::Matrix4x4		m_matrix;
};

}}