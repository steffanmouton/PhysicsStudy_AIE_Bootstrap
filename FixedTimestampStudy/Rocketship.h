#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <Gizmos.h>
#include "PhysicsScene.h"
#include <glm\ext.hpp>
#include "Sphere.h"

class RocketShip : public aie::Application {
public:

	RocketShip();
	virtual ~RocketShip();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	Sphere* ball;
	Sphere* ball2;

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	PhysicsScene*		m_physicsScene;
};
