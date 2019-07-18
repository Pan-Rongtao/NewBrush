#include "gles/Sphere.h"
#include <vector>
#include <math.h>
#include <GLES2/gl2.h>

using namespace nb::core;
using namespace nb::gl;
//�򶥵��㷨��ַ��
//https://www.jianshu.com/p/123c5884f635;
//https://blog.csdn.net/martin20150405/article/details/53888204

constexpr int SphereVSlices						= 50;										//����ά�ȷֳɵ���Ƭ��
constexpr int SphereHSlices						= SphereVSlices / 2;						//����ѭ��Ϊγ����Ƭ����һ��
constexpr int SphereIndicesCountVertextCount	= (SphereHSlices + 1) * (SphereVSlices + 1);//������
constexpr int SphereIndicesCount				= SphereHSlices * SphereVSlices * 6;		//����������
constexpr auto SphereAngleStep					= NB_2PI / SphereVSlices;					//ÿ�����εĽǶ�

Sphere::Sphere(float x, float y, float z, float r, bool cartesian)
{
	std::vector<Vertex> vertexs;
	if (cartesian)
	{
		for (int i = 0; i < SphereHSlices + 1; ++i)
		{
			for (int j = 0; j < SphereVSlices + 1; ++j)
			{
				auto x = r * sin(SphereAngleStep * i) * sin(SphereAngleStep * j);
				auto y = r * cos(SphereAngleStep * i);
				auto z = r * sin(SphereAngleStep * i) * cos(SphereAngleStep * j);
				vertexs.push_back(Vertex(glm::vec3(x, y, z), glm::vec4(), glm::vec2((float)j / SphereVSlices, 1.0 - ((float)i / SphereHSlices))));
			}
		}
	}
	else
	{
		for (int i = SphereHSlices; i != -1; --i)
		{
			for (int j = SphereVSlices; j != -1; --j)
			{
				auto x = r * sin(SphereAngleStep * i) * sin(SphereAngleStep * j);
				auto y = r * cos(SphereAngleStep * i);
				auto z = r * sin(SphereAngleStep * i) * cos(SphereAngleStep * j);
				vertexs.push_back(Vertex(glm::vec3(x, y, z), glm::vec4(), glm::vec2((float)j / SphereVSlices, ((float)i / SphereHSlices))));
			}
		}
	}
	meshes().push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
	translate(x, y, z);
}

void Sphere::cullFace()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

std::vector<uint16_t> Sphere::getIndices() const
{
	int x = 0;
	std::vector<uint16_t> indices(SphereIndicesCount);
	for (int i = 0; i < SphereHSlices; i++)
	{
		for (int j = 0; j < SphereVSlices; j++)
		{
			indices[x++] = i * (SphereVSlices + 1) + j;
			indices[x++] = (i + 1) * (SphereVSlices + 1) + j;
			indices[x++] = (i + 1) * (SphereVSlices + 1) + (j + 1);
			indices[x++] = i * (SphereVSlices + 1) + j;
			indices[x++] = (i + 1) * (SphereVSlices + 1) + (j + 1);
			indices[x++] = i * (SphereVSlices + 1) + (j + 1);
		}
	}
	return indices;
}
