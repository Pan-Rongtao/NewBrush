/*******************************************************
**	Quadrangle
**
**	������ģ��
**		Quadrangle������������ģ�͵����ݽṹ
**
**
**		������
**
********************************************************/
#pragma once
#include "Model.h"
#include "glm/glm.hpp"

namespace nb{ namespace gl{

class NB_API Quadrangle : public Model
{
public:
	//����һ�����Σ����Ŀ��Ϊ(0.0, 0.0)
	Quadrangle();

	//����һ�����Σ����Ŀ��Ϊ(width, height)
	Quadrangle(float width, float height);

	void setWidth(float width);
	void setHeight(float height);
	void setRadiuX(float radiusX);
	void setRadiuY(float radiusY);
	
private:
	void update();

	float	m_width;
	float	m_height;
	float	m_radiusX;
	float	m_radiusY;
};

}}
