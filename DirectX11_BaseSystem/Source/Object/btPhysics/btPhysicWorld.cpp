#include "btPhysicWorld.h"

#if _DEBUG
#pragma comment(lib,"BulletCollision_Debug.lib")
#pragma comment(lib,"BulletDynamics_Debug.lib")
#pragma comment(lib,"LinearMath_Debug.lib")
#else
#pragma comment(lib,"BulletCollision.lib")
#pragma comment(lib,"BulletDynamics.lib")
#pragma comment(lib,"LinearMath.lib")
#endif

namespace btPhysics
{
	bool World::IsCollision(btCollisionObject* object1,btCollisionObject* object2)
	{
		btCollisionObjectWrapper obj1(nullptr, object1->getCollisionShape(), object1, object1->getWorldTransform(), object1->getCompanionId(), object1->getUserIndex());
		btCollisionObjectWrapper obj2(nullptr, object2->getCollisionShape(), object2, object2->getWorldTransform(), object2->getCompanionId(), object2->getUserIndex());
		btCollisionAlgorithm* algo = _world->getCollisionWorld()->getDispatcher()->findAlgorithm(&obj1, &obj2);
		btManifoldResult result(&obj1, &obj2);
		algo->processCollision(&obj1, &obj2, _world->getCollisionWorld()->getDispatchInfo(), &result);
		auto mani = result.getPersistentManifold();
		bool collFlag = (mani->getNumContacts() != 0.f);
		_dispatcher->clearManifold(mani);
		_dispatcher->releaseManifold(mani);
		return collFlag;
	}
	World::World()
	{
		_config = std::make_shared<btDefaultCollisionConfiguration>();
		_dispatcher = std::make_shared<btCollisionDispatcher>(_config.get());
		_broadphase = std::make_shared<btDbvtBroadphase>();
		_solver = std::make_shared<btSequentialImpulseConstraintSolver>();
		_world = std::make_shared<btDiscreteDynamicsWorld>(_dispatcher.get(), _broadphase.get(), _solver.get(), _config.get());
		_world->setDebugDrawer(nullptr);
		_world->setGravity(btVector3(0, -300.f, 0));
		_world->applyGravity();
	}

	void World::Update()
	{
		_world->performDiscreteCollisionDetection();
		_world->clearForces();
		btScalar dt = (btScalar)_clock.getTimeMicroseconds();
		_clock.reset();
		_world->stepSimulation(dt / 1000000.f);
	}

	void World::AddRigidBody(btRigidBody* rigidBody)
	{
		_world->addRigidBody(rigidBody);
	}
	void World::AddRigidBody(btRigidBody* rigidBody,short group,short mask)
	{
		_world->addRigidBody(rigidBody,group,mask);
	}
	void World::RemoveRigidBody(btRigidBody* rigidBody)
	{
		_world->removeRigidBody(rigidBody);
		_world->removeCollisionObject(rigidBody);
	}
}