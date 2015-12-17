/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_SOME_OBJECT_H
#define HK_SOME_OBJECT_H

extern const hkClass SomeObjectClass;
class SomeObject : public hkReferencedObject
{
	public:
		HK_DECLARE_REFLECTION();

		SomeObject(SomeObject* n=HK_NULL) : m_next(n) { ++m_numInstances; }
		SomeObject(hkFinishLoadedObjectFlag f) : hkReferencedObject(f) { if( f.m_finishing) { ++m_numInstances; } }
		virtual ~SomeObject() { --m_numInstances; }

		SomeObject* m_next;
		static int m_numInstances;
};

#endif // HK_SOME_OBJECT_H

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
