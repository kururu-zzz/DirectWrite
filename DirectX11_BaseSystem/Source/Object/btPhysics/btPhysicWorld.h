#ifndef BTPHYSIC_WORLD___
#define BTPHYSIC_WORLD___

#include <memory>
#define BT_NO_SIMD_OPERATOR_OVERLOADS //演算子のオーバーロードがdirectxmathと競合するので
#include <btBulletDynamicsCommon.h>

namespace btPhysics
{
	class World
	{
		std::shared_ptr<btDefaultCollisionConfiguration> _config;
		std::shared_ptr<btCollisionDispatcher> _dispatcher;
		std::shared_ptr<btDbvtBroadphase> _broadphase;
		std::shared_ptr<btSequentialImpulseConstraintSolver> _solver;
		std::shared_ptr<btDiscreteDynamicsWorld> _world;
		btClock _clock;
	public:
		World();
		void Update();
		void AddRigidBody(btRigidBody* rigidBody);
		void AddRigidBody(btRigidBody* rigidBody,short group,short mask);
		void RemoveRigidBody(btRigidBody* rigidBody);
		bool IsCollision(btCollisionObject* object1, btCollisionObject* object2);
		btDiscreteDynamicsWorld* GetWorld(){ return _world.get(); }
	};
}

#endif