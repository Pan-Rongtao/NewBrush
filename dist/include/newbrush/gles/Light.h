#pragma once
#include "../core/Def.h"
#include "../core/Vec3.h"

namespace nb{ namespace gl {

struct DirectionalLight
{
public:
	nb::core::Vec3	direction;		//����
	nb::core::Vec3	color;			//��ɫ

	nb::core::Vec3	ambient;		//����
	nb::core::Vec3	diffuse;		//������
	nb::core::Vec3	specular;		//�߹�

	float			indensity;		//ǿ��
};

struct PointLight
{
public:
	nb::core::Vec3	position;		//λ��
	nb::core::Vec3	color;			//��ɫ

	nb::core::Vec3	ambient;		//����
	nb::core::Vec3	diffuse;		//������
	nb::core::Vec3	specular;		//�߹�

	float			constant;		//˥������
	float			linear;			//һ����
	float			quadratic;		//������

	float			indensity;		//ǿ��
};

struct SpotLight
{
	nb::core::Vec3	position;		//λ��
	nb::core::Vec3	direction;		//����
	nb::core::Vec3	color;			//��ɫ

	nb::core::Vec3	ambient;		//����
	nb::core::Vec3	diffuse;		//������
	nb::core::Vec3	specular;		//�߹�

	float			cutoff;			//�й��
	float			constant;		//˥������
	float			linear;			//һ����
	float			quadratic;		//������

	float			indensity;		//ǿ��
};

}}