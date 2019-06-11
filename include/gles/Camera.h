/*******************************************************
**	Camera
**
**	�������
**		Camera�������۲��������ݽṹ
**	���ṩlookat�����Ծ�����б任��
**
**		������
**
********************************************************/
#pragma once
#include "../core/Def.h"
#include "glm/glm.hpp"

namespace nb{ namespace gl{

class NB_API Camera
{
public:
	//����һ�������������λ��Ϊ(0.0, 0.0, 1.0)��Ŀ���Ϊ(0.0, 0.0, 0.0)����������Ϊ(0.0, 1.0, 0.0)
	Camera();

	//��ȡ�۲����
	glm::mat4x4 &matrix();
	const glm::mat4x4 &matrix() const;

	//lookup
	void lookat(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &upVec);
	void lookat2D(double width, double height);

private:
	glm::mat4x4		m_matrix;
};

}}
