#include "gles/Line.h"
#include <opengl/GLES2/gl2.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace nb;
using namespace nb::gl;

Line::Line()
	: Line(0.0f, 0.0f, 0.0f, 0.0f)
{
}

Line::Line(float x0, float y0, float x1, float y1)
{
	Model::mode = GL_LINES;

	auto center = glm::vec3((x1 - x0) / 2.0f, (y1 - y0) / 2.0f, 0.0f);
	std::vector<Vertex> vertexs{
		Vertex(glm::vec3(x0, y0, 0.0f) - center, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
		Vertex(glm::vec3(x1, y1, 0.0f)- center, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
	};
	meshes.push_back(Mesh(vertexs, { 0, 1 }));
	matrix = glm::translate(matrix, glm::vec3(center.x, center.y, center.z));
}
