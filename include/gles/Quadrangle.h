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
	//����һ�����Σ������ĸ��������궼Ϊ0.0����ɫΪ0.0
	Quadrangle();

	//����һ�����Σ������ĸ�����p0,p1,p2,p3
	//�����ĸ�������ɫ��Ϊ0.0
	Quadrangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3);

	//����һ�����Σ������ĸ�����p0,p1,p2,p3���սǻ�����radius
	Quadrangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, float radiusX, float radiusY);
	
private:
	glm::vec2	m_radius;
};

}}
