/*******************************************************
**	Triangle
**
**	������ģ��
**		Triangle������������ģ�͵����ݽṹ
**
**
**		������
**
********************************************************/
#pragma once
#include "Model.h"

namespace nb{namespace gl{

class NB_API Triangle : public Model
{
public:
	//����һ�������Σ����������������궼��0.0��������ɫ��0.0
	Triangle();

	//����һ�������Σ�������������������(p0, p1, p2)��������ɫ��0.0
	Triangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2);

	//����һ�������Σ�������������������(p0, p1, p2)��
	//���������������ɫ����color
	Triangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec4 &color);

	//����һ�������Σ�������������������(p0, p1, p2)�����������������ɫ����(color0, color1, color2)
	Triangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec4 &color0, const glm::vec4 &color1, const glm::vec4 &color2);

private:
	double distance(const glm::vec2 &p0, const glm::vec2 &p1) const;
	//����
	glm::vec2 center(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2) const;
};

}}
