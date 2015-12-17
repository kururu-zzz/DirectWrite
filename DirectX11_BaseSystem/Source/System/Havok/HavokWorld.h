#ifndef __HAVOK_WORLD__
#define __HAVOK_WORLD__

#include <memory>

// Math and base includes
#include <Common/Base/keycode.cxx>
#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>

#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBodyCinfo.h>
#include <Physics2012/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>
#include <Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics2012/Collide/Dispatch/hkpAgentRegisterUtil.h>

namespace havok
{
	class World
	{
		std::shared_ptr<hkpWorld> _world;
	public:
		void Init();
		void Update();
	};
}

#endif