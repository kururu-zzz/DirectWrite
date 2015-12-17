#include "HavokWorld.h"

namespace havok
{	
	void World::Init() 
	{

		hkpWorldCinfo info;
		info.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_CONTINUOUS;
		info.m_collisionTolerance = 0.001f;
		info.setBroadPhaseWorldSize(10000.0f);
		info.setupSolverInfo(hkpWorldCinfo::SOLVER_TYPE_8ITERS_HARD);
		info.m_gravity = hkVector4(0.0f, -9.8f, 0.0f);
		_world = std::make_shared<hkpWorld>(info);
	}

	void World::Update()
	{
		_world->stepDeltaTime(1.0f / 60.f);
	}
}