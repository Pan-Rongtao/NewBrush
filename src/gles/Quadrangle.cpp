#include "gles/Quadrangle.h"
#include <array>
#include <math.h>

using namespace nb;
using namespace nb::gl;

Quadrangle::Quadrangle()
	: Quadrangle(0.0f, 0.0f)
{
}

Quadrangle::Quadrangle(float width, float height)
	: m_width(width)
	, m_height(height)
	, m_radiusX(0.0f)
	, m_radiusY(0.0f)
{
	meshes.push_back(Mesh());
	update();
}

void Quadrangle::setWidth(float width)
{
	if (width != m_width)
	{
		m_width = width;
		update();
	}
}

void Quadrangle::setHeight(float height)
{
	if (height != m_height)
	{
		m_height = height;
		update();
	}
}

void Quadrangle::setRadiuX(float radiusX)
{
	if (radiusX != m_radiusX)
	{
		m_radiusX = radiusX;
		update();
	}
}

void Quadrangle::setRadiuY(float radiusY)
{
	if (radiusY != m_radiusY)
	{
		m_radiusY = radiusY;
		update();
	}
}

void Quadrangle::update()
{
	//�ĸ��ǵ�λ��
	auto &vertexs = meshes[0].vertexs;
	auto &indices = meshes[0].indices;
	bool radius = (m_width != 0.0f && m_height != 0.0f) && (m_radiusX != 0.0f && m_radiusY != 0.0f);			//�Ƿ���Ҫ����
	constexpr auto connerVertexSize = 20;							//ÿ�����εĶ�����
	constexpr auto connerIndicesSize = 3 * (connerVertexSize - 2);	//ÿ�����εĶ������д�С
	constexpr auto radianStep = M_PI_2 / (connerVertexSize - 2);	//���ε�λ����
	vertexs.resize(radius ? connerVertexSize * 4 : 4);				//���ж�����
	indices.resize(radius ? connerIndicesSize * 4 + 12 : 6);		//���ж������д�С=�ĸ����ȶ������� + ʮ���������ζ�������
	if (radius)
	{
		//�޶�Բ���ھ��ΰ볤/����
		auto radiusX = std::fabs(m_radiusX) <= m_width * 0.5f ? std::fabs(m_radiusX) : m_width * 0.5f;
		auto radiusY = std::fabs(m_radiusY) <= m_height * 0.5f ? std::fabs(m_radiusY) : m_height * 0.5f;

		auto fillConner = [&vertexs, &indices, &connerVertexSize, &connerIndicesSize, radiusX, &radiusY, &radianStep](const glm::vec3 &center, float radianSpan, int cornnerIndex) {
			auto beg = cornnerIndex * connerVertexSize;
			for (auto i = 0u; i < connerVertexSize; ++i)
			{
				//��䶥������
				if (i == 0)
				{
					vertexs[beg].position = center;
					vertexs[beg].color = vertexs[0].color;
				}
				else
				{
					auto radian = radianStep * (i - 1) + radianSpan;
					vertexs[beg + i].position = glm::vec3(radiusX * cos(radian), radiusY * sin(radian), 0.0) + center;
					vertexs[beg + i].color = vertexs[0].color;
					vertexs[beg + i].texCoord = glm::vec2(0.5 * cos(radian) + 0.5, 1.0 - (0.5 * sin(radian) + 0.5));
				}
				//��䶥������
				if(i >= 0 && i < connerVertexSize - 2)
				{
					int base = connerIndicesSize * cornnerIndex + (3 * i);
					indices[base] = beg;
					indices[base + 1] = beg + i + 1;
					indices[base + 2] = beg + i + 2;
				}
			}
		};
		//���Ͻǻ��Ρ����Ͻǻ��Ρ����½ǻ��Ρ����½ǻ���
		auto connerIndex = 0u;
		fillConner(glm::vec3{ radiusX - m_width * 0.5, radiusY - m_height * 0.5, 0.0f }, (float)M_PI, connerIndex++);
		fillConner(glm::vec3{ m_width * 0.5 - radiusX, radiusY - m_height * 0.5, 0.0f }, (float)M_PI * 1.5, connerIndex++);
		fillConner(glm::vec3{ m_width * 0.5 - radiusX, m_height * 0.5 - radiusY, 0.0f }, M_PI * 0.0, connerIndex++);
		fillConner(glm::vec3{ radiusX - m_width * 0.5, m_height * 0.5 - radiusY, 0.0f }, (float)M_PI * 0.5, connerIndex++);
		//�м�ʮ���������εĶ�������
		auto beg = indices.size() - 12;
		indices[beg++] = 1; indices[beg++] = connerVertexSize * 2 - 1; indices[beg++] = connerVertexSize * 2 + 1;
		indices[beg++] = 1; indices[beg++] = connerVertexSize * 2 + 1; indices[beg++] = connerVertexSize * 4 - 1;
		indices[beg++] = connerVertexSize - 1; indices[beg++] = connerVertexSize + 1; indices[beg++] = connerVertexSize * 3 - 1;
		indices[beg++] = connerVertexSize - 1; indices[beg++] = connerVertexSize * 3 - 1; indices[beg++] = connerVertexSize * 3 + 1;
	}
	else
	{
		vertexs[0].position = glm::vec3{ -m_width * 0.5, m_height * 0.5, 0.0f };	vertexs[0].texCoord = glm::vec2(0.0, 0.0);
		vertexs[1].position = glm::vec3{ m_width * 0.5, m_height * 0.5, 0.0f };	vertexs[1].texCoord = glm::vec2(1.0, 0.0);
		vertexs[2].position = glm::vec3{ m_width * 0.5, -m_height * 0.5, 0.0f };	vertexs[2].texCoord = glm::vec2(1.0, 1.0);
		vertexs[3].position = glm::vec3{ -m_width * 0.5, -m_height * 0.5, 0.0f };	vertexs[3].texCoord = glm::vec2(0.0, 1.0);
		indices = { 0, 1, 2, 0, 2, 3 };
	}
}
