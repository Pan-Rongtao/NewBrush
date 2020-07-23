#pragma once
#include "newbrush/core/Def.h"
#include <glm/glm.hpp>

namespace nb{

class Light
{
public:
	glm::vec3	color;			//��ɫ
	glm::vec3	ambient;		//����
	glm::vec3	diffuse;		//������
	glm::vec3	specular;		//�߹�
};

struct DirectionalLight : public Light
{
public:
	glm::vec3	direction;		//����
	float		indensity;		//ǿ��
};

struct PointLight : public Light
{
public:
	glm::vec3	position;		//λ��
	float		constant;		//˥������
	float		linear;			//һ����
	float		quadratic;		//������
	float		indensity;		//ǿ��
};

struct SpotLight : public Light
{
	glm::vec3	position;		//λ��
	glm::vec3	direction;		//����
	float		cutoff;			//�й��
	float		constant;		//˥������
	float		linear;			//һ����
	float		quadratic;		//������
	float		indensity;		//ǿ��
};

}