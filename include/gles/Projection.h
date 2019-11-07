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
#include "../core/Def.h"
#include "glm/glm.hpp"

namespace nb{ namespace gl{

class NB_API Projection
{
public:
	Projection();

	glm::mat4x4		matrix;

	//����ͶӰ
	void ortho(float left, float right, float bottom, float top, float near, float far);

	//͸��ͶӰ
	//fovy������
	void perspective(float fovy, float aspect, float near, float far);


};

}}