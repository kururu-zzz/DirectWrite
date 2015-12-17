#pragma once

#define BT_NO_SIMD_OPERATOR_OVERLOADS //演算子のオーバーロードがdirectxmathと競合するので
#include <btBulletDynamicsCommon.h>
#include <LinearMath/btIDebugDraw.h>
#include <memory>

class Physics
{
	std::shared_ptr<btDefaultCollisionConfiguration> _config;
	std::shared_ptr<btCollisionDispatcher> _dispatcher;
	std::shared_ptr<btDbvtBroadphase> _broadphase;
	std::shared_ptr<btSequentialImpulseConstraintSolver> _solver;

	btAlignedObjectArray<btCollisionShape*>	aCollisionShapes;
	btClock Clock;
public:
	Physics();
	~Physics();
public:
	void Init();
	void Exit();
};