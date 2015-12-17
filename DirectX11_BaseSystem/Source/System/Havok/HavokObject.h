#ifndef __HAVOK_OBJECT__
#define __HAVOK_OBJECT__

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
	class CollisionBox
	{
	public:
		std::shared_ptr<hkpBoxShape> _shape;
		std::shared_ptr<hkpRigidBody> _body;
	public:
		void Init(const hkVector4& pos, float weight, const hkVector4& boxShape, hkpMotion::MotionType motionType = hkpMotion::MOTION_BOX_INERTIA);
	};
}

#endif