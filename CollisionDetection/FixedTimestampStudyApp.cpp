#include "FixedTimestampStudyApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

FixedTimestampStudyApp::FixedTimestampStudyApp() {

}

FixedTimestampStudyApp::~FixedTimestampStudyApp() {

}

bool FixedTimestampStudyApp::startup() {
	
	// increase the 2d line count to maximize the number of obj we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);
	
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	// vs "../bin/font/consolas.ttf"
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -10)); // Gravity Control
	m_physicsScene->setTimeStep(0.01f);


	ball = new Sphere(glm::vec2(-20, 0), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 0, 0, 1));
	ball2 = new Sphere(glm::vec2(20, 0), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 0, 1));
	plane1 = new Plane(glm::vec2{ 0,-1 }, 50);

	
	m_physicsScene->addActor(ball);
	m_physicsScene->addActor(ball2);
	m_physicsScene->addActor(plane1); 

	ball->applyForce(glm::vec2(50, 20));
	ball2->applyForce(glm::vec2(-40, 20));
	

	return true;
}

void FixedTimestampStudyApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void FixedTimestampStudyApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
	{
		ball->applyForce(glm::vec2(10, 10));
	}
	
}

void FixedTimestampStudyApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, 
		-100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}