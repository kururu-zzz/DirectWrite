
#include "HavokObject.h"

namespace havok
{
	void RemoveReference(hkReferencedObject* p)
	{
		p->removeReference();
	}

	void CollisionBox::Init(const hkVector4& pos,float weight,const hkVector4& boxShape,hkpMotion::MotionType motionType) {

		auto shape = new hkpBoxShape;
		_shape = std::shared_ptr<hkpBoxShape>(shape,RemoveReference);


		hkMassProperties massProperties;
		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(_shape.get(), weight, massProperties);

		hkpRigidBodyCinfo bodyInfo;
		bodyInfo.m_mass = massProperties.m_mass;
		bodyInfo.m_centerOfMass = massProperties.m_centerOfMass;
		bodyInfo.m_inertiaTensor = massProperties.m_inertiaTensor;
		bodyInfo.m_shape = _shape.get();
		bodyInfo.m_motionType = motionType;

		auto body = new hkpRigidBody(bodyInfo);
		_body = std::shared_ptr<hkpRigidBody>(body, RemoveReference);
	}
}