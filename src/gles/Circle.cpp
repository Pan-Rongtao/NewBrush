#include "gles/Circle.h"
#include <math.h>

using namespace nb;
using namespace nb::gl;

//��Բ�ĵ���㹫ʽΪ��x = a * cos(��); y = b * sin(��)
//����Խ��ԽԲ��
constexpr int CircleVertexCount			= 50;

Circle::Circle(float x, float y, float a, float b, bool cartesian)
{
	constexpr auto radianStep = 2 * M_PI / (CircleVertexCount - 2);
	std::vector<Vertex> vertexs{ Vertex(glm::vec3(), glm::vec4(), glm::vec2(0.5, 0.5)) };//���ĵ�
	//�Ƿ��ǵѿ�������ϵ��������������꽫��ͬ
	for (int i = 1; i != CircleVertexCount; ++i)
	{
		auto radian = radianStep * i;
		glm::vec2 texCoord(0.5 * cos(radian) + 0.5, cartesian ? 0.5 * sin(radian) + 0.5 : 1.0 - (0.5 * sin(radian) + 0.5));
		vertexs.push_back(Vertex(glm::vec3(a * cos(radian), b * sin(radian), 0.0), glm::vec4(), texCoord));
	}
	meshes().push_back(Mesh(vertexs, getIndices()));
	translate(x, y, 0.0f);
}

std::vector<uint16_t> Circle::getIndices() const
{
	constexpr auto count = 3 * (CircleVertexCount - 1);
	std::vector<uint16_t> indices(count);
	for (int i = 0; i != CircleVertexCount - 2; ++i)
	{
		int base = 3 * i;
		indices[base] = 0;
		indices[base + 1] = i + 1;
		indices[base + 2] = i + 2;
	}
	indices[count - 3] = 0;
	indices[count - 2] = CircleVertexCount - 1;
	indices[count - 1] = 1;
	return indices;
}
