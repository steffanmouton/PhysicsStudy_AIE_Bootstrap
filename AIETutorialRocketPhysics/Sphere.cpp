#include "Sphere.h"
#include <glm/detail/func_geometric.inl>


Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour)
: RigidBody(SPHERE, position, velocity, 0, mass)
{
	m_radius = radius;
	m_colour = colour;
}

Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 21, m_colour);
}

bool Sphere::checkCollision(PhysicsObject* pOther)
{
	auto spherePtr = dynamic_cast<Sphere*>(pOther);

	if (spherePtr != nullptr)
	{
		if (glm::distance(spherePtr->m_position, m_position) < m_radius + spherePtr->m_radius)
		{
			return true;
		}
	}

	return false;
}
