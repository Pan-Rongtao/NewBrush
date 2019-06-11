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

	//����һ�����Σ��������ĵ���centerPoint�����Ϊwidth, height
	//�����ĸ�������ɫ��Ϊ0.0
	Quadrangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3);

	//����һ�����Σ��������ĵ���centerPoint�����Ϊwidth, height
	//�����ĸ�������ɫ��ΪunifyColor
	Quadrangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, const glm::vec4 &color);

	//����һ�����Σ��������ĵ���centerPoint�����Ϊwidth, height
	//�����ĸ�������ɫΪ(color0, color1, color2, color3)
	Quadrangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, const glm::vec4 &color0, const glm::vec4 &color1, const glm::vec4 &color2, const glm::vec4 &color3);

private:
	std::vector<uint16_t> getIndices() const;
	glm::vec3 getCenter(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3) const;
};

}}
