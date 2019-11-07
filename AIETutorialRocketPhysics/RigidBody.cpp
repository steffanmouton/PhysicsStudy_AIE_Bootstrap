#include "RigidBody.h"


RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass):
	PhysicsObject(shapeID)
{
	m_shapeID = shapeID;
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	applyForce(gravity * m_mass * timeStep);
	m_position += m_velocity * timeStep;
	
}

void RigidBody::debug()
{
	char buffer[100];
	
	std::cout << "====DEBUG====";
	sprintf(buffer,"Position: %f , %f \n", m_position.x, m_position.y);
	std::cout << buffer;
	
	sprintf(buffer, "Velocity: %f , %f \n", m_velocity.x, m_velocity.y);
	std::cout << buffer;
	
	sprintf(buffer, "Mass: %f \n", m_mass);
	std::cout << buffer;
	
	sprintf(buffer, "Rotation: %f \n", m_position);
	std::cout << buffer;
}

void RigidBody::applyForce(glm::vec2 force)
{
	m_velocity += force/m_mass;
}

void RigidBody::applyForceToActor(RigidBody* actor2, glm::vec2 force)
{
	auto force_Actor2 = actor2->getMass() * actor2->getVelocity();

	// This object exerts force on the other, then receives the same back
	actor2->applyForce(force);
	applyForce(-force);


	// The other object exerts force on this object, then receives the same back
	applyForce(force_Actor2);
	actor2->applyForce(-force_Actor2);
}
