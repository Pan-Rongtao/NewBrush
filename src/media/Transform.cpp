#include "newbrush/media/Transform.h"

using namespace nb;

Transform Transform::m_identity;

Transform::Transform()
{}

Transform Transform::identity()
{
	return m_identity;
}

Transform Transform::inverse()
{
	return *this;
}

glm::mat4x4 Transform::value()
{
	glm::mat4x4 matrix = glm::mat4x4(1.0f);
	return matrix;
}

bool Transform::tryTransform(const Point &inPoint, Point &outPoint)
{
	outPoint = inPoint;
	return true;
}