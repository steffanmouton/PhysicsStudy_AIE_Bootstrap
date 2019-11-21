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

		// check for collisions
		for (auto pActor : m_actors)
		{
			for (auto pOther: m_actors)
			{
				if (pActor == pOther)
					continue;
				if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
					std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
					continue;

				RigidBody* pRigid = dynamic_cast<RigidBody*>(pActor);
				if (pRigid->checkCollision(pOther) == true)
				{
					pRigid->applyForceToActor(
						dynamic_cast<RigidBody*>(pOther),
						pRigid->getVelocity() * pRigid->getMass());
					dirty.push_back(pRigid);
					dirty.push_back(pOther);
				}
			}
		}
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

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere,
	PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere,
};

void PhysicsScene::checkForCollision()
{
	int actorCount = m_actors.size();
	
	//need to check for collisions against all objects except this one
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeId1 = object1->getShapeID();
			int shapeId2 = object2->getShapeID();

			//using function pointers
			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];

			if (collisionFunctionPtr != nullptr)
			{
				//did a collision occur?
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

