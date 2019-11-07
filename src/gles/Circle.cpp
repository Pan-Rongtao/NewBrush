#include "gles/Circle.h"
#include <math.h>

using namespace nb;
using namespace nb::gl;

//��Բ�ĵ���㹫ʽΪ��x = a * cos(��); y = b * sin(��)
//����Խ��ԽԲ��
constexpr int vertexCount = 50;

Circle::Circle()
	: Circle(0.0f, 0.0f, 0.0f, 0.0f, false)
{
}

Circle::Circle(float x, float y, float a, float b, bool cartesian)
{
	auto getIndices = []()->std::vector<uint16_t> {
		constexpr auto count = 3 * (vertexCount - 1);
		std::vector<uint16_t> indices(count);
		for (int i = 0; i != vertexCount - 2; ++i)
		{
			int base = 3 * i;
			indices[base] = 0;
			indices[base + 1] = i + 1;
			indices[base + 2] = i + 2;
		}
		indices[count - 3] = 0;
		indices[count - 2] = vertexCount - 1;
		indices[count - 1] = 1;
		return indices;
	};
	Mesh mesh(std::vector<Vertex>(vertexCount), getIndices());
	meshes.push_back(mesh);
	set(x, y, a, b, cartesian);
}

void Circle::set(float x, float y, float a, float b, bool cartesian)
{
	auto &vertexs = meshes[0].vertexs;
	//���ĵ�
	vertexs[0].position = glm::vec3();
	vertexs[0].texCoord = glm::vec2(0.5, 0.5);
	//�Ƿ��ǵѿ�������ϵ��������������꽫��ͬ
	constexpr auto radianStep = 2 * M_PI / (vertexCount - 2);
	for (int i = 1; i != vertexCount; ++i)
	{
		auto radian = radianStep * i;
		vertexs[i].position = glm::vec3(a * cos(radian), b * sin(radian), 0.0);
		vertexs[i].texCoord = glm::vec2(0.5 * cos(radian) + 0.5, cartesian ? 0.5 * sin(radian) + 0.5 : 1.0 - (0.5 * sin(radian) + 0.5));
	}
	translate(x, y, 0.0f);
}
