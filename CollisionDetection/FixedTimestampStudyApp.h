#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <Gizmos.h>
#include "PhysicsScene.h"
#include <glm\ext.hpp>
#include "Sphere.h"
#include "Plane.h"

class FixedTimestampStudyApp : public aie::Application {
public:

	FixedTimestampStudyApp();
	virtual ~FixedTimestampStudyApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	Sphere* ball;
	Sphere* ball2;
	Plane* plane1;

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	PhysicsScene*		m_physicsScene;
};
