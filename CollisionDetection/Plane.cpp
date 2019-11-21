#include "Plane.h"


Plane::Plane() : PhysicsObject(ShapeType::PLANE)
{
	m_normal = glm::vec2(0, 1);
	m_distanceToOrigin = 0.f;
}

Plane::Plane(glm::vec2 normal, float distance) : PhysicsObject(ShapeType::PLANE)
{
	m_normal = normal;
	m_distanceToOrigin = distance;
}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{
}

void Plane::debug()
{
}

void Plane::makeGizmo()
{
	float lineSegmentLength = 300;
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	//easy to rotate normal through 90 degrees around z
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 color(1.f,1.f,1.f,1.f);
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);

	aie::Gizmos::add2DLine(start, end, color);
}

void Plane::resetPosition()
{
	m_normal = glm::vec2(0, 1);
	m_distanceToOrigin = 0.f;
}

Plane::~Plane()
{
}
