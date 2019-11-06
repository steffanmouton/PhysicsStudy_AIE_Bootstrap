#include "RigidBody.h"


RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass):
	PhysicsObject()
{
	//TODO: Maybe this constructor is not good. Will check at run
	m_shapeID = shapeID;
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
}

RigidBody::~RigidBody()
{
}
