#pragma once
#include "newbrush/core/Def.h"
#include <glm/glm.hpp>

namespace nb{

struct DirectionalLight
{
public:
	glm::vec3	direction;		//����
	glm::vec3	color;			//��ɫ
	glm::vec3	ambient;		//����
	glm::vec3	diffuse;		//������
	glm::vec3	specular;		//�߹�
	float		indensity;		//ǿ��
};

struct PointLight
{
public:
	glm::vec3	position;		//λ��
	glm::vec3	color;			//��ɫ
	glm::vec3	ambient;		//����
	glm::vec3	diffuse;		//������
	glm::vec3	specular;		//�߹�
	float		constant;		//˥������
	float		linear;			//һ����
	float		quadratic;		//������
	float		indensity;		//ǿ��
};

struct SpotLight
{
	glm::vec3	position;		//λ��
	glm::vec3	direction;		//����
	glm::vec3	color;			//��ɫ
	glm::vec3	ambient;		//����
	glm::vec3	diffuse;		//������
	glm::vec3	specular;		//�߹�
	float		cutoff;			//�й��
	float		constant;		//˥������
	float		linear;			//һ����
	float		quadratic;		//������
	float		indensity;		//ǿ��
};

}