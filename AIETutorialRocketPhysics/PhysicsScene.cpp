#include "PhysicsScene.h"
#include <list>
#include "RigidBody.h"


PhysicsScene::PhysicsScene()
{
	setTimeStep(.01f);
	setGravity(glm::vec2(0, 0));
}


PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	int actorPos = -1;
	for(int i = 0; i < m_actors.size(); i++)
	{
		if (m_actors[i] == actor)
		{
			actorPos = i;
		}
	}

	if (actorPos != -1)
		m_actors.erase(m_actors.begin()+actorPos);
}

void PhysicsScene::update(float dt)
{
	static std::list<PhysicsObject*> dirty;

	
	//update physics at a fixed time step
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;

		dirty.clear();
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene()
{
	int count = 0;
	for (auto pActor : m_actors)
	{
		std::cout << count << " : ";
		pActor->debug();
		count++;
	}
}


