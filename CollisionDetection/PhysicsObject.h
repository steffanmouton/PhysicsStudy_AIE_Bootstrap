#pragma once
#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec4.hpp>
#include "Gizmos.h"

enum ShapeType
{
	PLANE = 0,
	SPHERE,
	BOX,
	SHAPE_COUNT
};

class PhysicsObject
{
protected:
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}
	PhysicsObject();

public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {};

	int getShapeID() const { return m_shapeID; }

protected:
	ShapeType m_shapeID;
};

