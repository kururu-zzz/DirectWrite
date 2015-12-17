/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Physics2012/Dynamics/Entity/Util/hkpEntityCallbackUtil.h>
#include <Physics2012/Dynamics/World/Util/hkpWorldCallbackUtil.h>


void HK_CALL hkFireContactPointAddedCallback(hkpWorld* world, hkpEntity* entityA, hkpEntity* entityB, hkpContactPointAddedEvent& event)
{
	{
		hkpWorldCallbackUtil ::fireContactPointAdded( world,   event );
		hkpEntityCallbackUtil::fireContactPointAdded( entityA, event );
		hkpEntityCallbackUtil::fireContactPointAdded( entityB, event );
	}
}

void HK_CALL hkFireContactProcessCallback(hkpWorld* world, hkpEntity* entityA, hkpEntity* entityB, hkpContactProcessEvent& event)
{
	{
		hkpWorldCallbackUtil ::fireContactProcess( world,   event );
		hkpEntityCallbackUtil::fireContactProcess( entityA, event );
		hkpEntityCallbackUtil::fireContactProcess( entityB, event );
	}
}

void HK_CALL hkFireContactPointRemovedCallback(hkpWorld* world, hkpEntity* entityA, hkpEntity* entityB, hkpContactPointRemovedEvent& event)
{
	{
		hkpWorldCallbackUtil ::fireContactPointRemoved( world,   event );
		hkpEntityCallbackUtil::fireContactPointRemoved( entityA, event );
		hkpEntityCallbackUtil::fireContactPointRemoved( entityB, event );
	}
}

/*
 * Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20140907)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2014
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available at www.havok.com/tryhavok.
 * 
 */
