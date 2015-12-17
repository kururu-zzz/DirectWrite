/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_HKREFERENCEDOBJECT_H
#define HKBASE_HKREFERENCEDOBJECT_H

extern HK_EXPORT_COMMON const hkClass hkReferencedObjectClass;

#include <Common/Base/Object/hkBaseObject.h>
#include <Common/Base/Thread/Atomic/hkAtomicPrimitives.h>

class hkCriticalSection;
class hkVtableClassRegistry;

/// Base for all classes in the Havok SDK.
/// All core SDK objects that can be owned by multiple owners inherit from this class -
/// rigid bodies, constraints, and actions are all hkReferencedObjects
/// and any object that is memory managed by Havok also inherits from it.
class HK_EXPORT_COMMON hkReferencedObject : public hkBaseObject
{
		//+hk.ReflectedFile("BaseObject")

	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE_CLASS);
		HK_DECLARE_REFLECTION();

			/// Creates a new referenced object with an initial reference count of 1.
		HK_FORCE_INLINE hkReferencedObject();

			/// Copy constructor, any default subclass's copy constructor will correctly initialize reference count to 1.
		HK_FORCE_INLINE hkReferencedObject( const hkReferencedObject& originalObject );

			/// Serialization constructor
		hkReferencedObject( class hkFinishLoadedObjectFlag flag ) {}

			/// Empty assignment operator - the reference count of this will remain unchanged.
		HK_FORCE_INLINE void operator=( const hkReferencedObject& originalObject );

			/// Destroy this object.
		HK_NOSPU_VIRTUAL ~hkReferencedObject() { }

			/// Returns the size of this object.
			/// A memory size of 0 is a special case and indicates
			/// that the object should not be freed (as it has
			/// probably been read in from a packed file for instance)
			/// or is embedded in another structure
		HK_FORCE_INLINE int getAllocatedSize() const;

			/// Returns the current reference count. Used for debugging only.
		HK_FORCE_INLINE int getReferenceCount() const;

			/// Sets the reference count
		inline void setReferenceCount(int newRefCount);

			/// Returns the memory size and flags
		HK_FORCE_INLINE int getMemorySizeAndFlags() const;

			/// Sets the memory size and flags
		inline void setMemorySizeAndFlags(int newMemSizeAndFlags);

			/// Sets the memory size, flags and reference count
		inline void setMemorySizeFlagsAndReferenceCount(int newMemSizeAndFlags, int newRefCount);

			/// Adds a reference to the object - this increments the reference count.
			/// ###ACCESS_CHECKS###( [(&hkReferencedObjectLock::getInstance()),HK_ACCESS_RW] );
		inline void addReference() const;

			/// Removes a reference to the object - this decrements the last reference count.
			/// ###ACCESS_CHECKS###( [(&hkReferencedObjectLock::getInstance()),HK_ACCESS_RW] );
		inline void removeReference() const;

			/// Adds the references of a full array of referenced, this will call lockAll internally.
		static void HK_CALL addReferences( const hkReferencedObject*const* objects, int numObjects, int pointerStriding );

			/// Adds the references of a full array of referenced, this will call lockAll internally.
		template<typename T>
		static void HK_CALL addReferences( const T*const* objects, int numObjects, int pointerStriding = sizeof(T*) )	{ addReferences( reinterpret_cast<const hkReferencedObject*const*>(objects), numObjects, pointerStriding ) ; HK_ON_DEBUG(numObjects > 0 && objects[0]->iMustBeDerivedFromReferencedObject()); }

			/// Removes the references of a full array of referenced, this will call lockAll internally.
		static void HK_CALL removeReferences( const hkReferencedObject*const* objects, int numObjects, int pointerStriding );

			/// Removes the references of a full array of referenced, this will call lockAll internally.
		template<typename T>
		static void HK_CALL removeReferences( const T*const* objects, int numObjects, int pointerStriding = sizeof(T*) ){ removeReferences( reinterpret_cast<const hkReferencedObject*const*>(objects), numObjects, pointerStriding ); HK_ON_DEBUG(numObjects > 0 && objects[0]->iMustBeDerivedFromReferencedObject()); }

			/// Mode which defines the locking policy, see setLockMode
		enum LockMode
		{
			//+reflected(False)
				/// no checking, no locking, good for single threaded applications
			LOCK_MODE_NONE,

				/// automatic locking of references, using lockAll is optional and will only improve performance
			LOCK_MODE_AUTO,

				/// manual locking of references, using lockAll is required.
				/// this mode should only be used when you debug to define performance bottlenecks
			LOCK_MODE_MANUAL
		};

			/// Sets the current lock policy.
			/// In a multithreaded environment, incrementing and decrementing reference counters must be thread safe.
			/// In a typical usage of Havok, calls to addReference() and removeReference() happen in groups, as a result
			/// we did not implement addReferences() using atomic operations but rely on explicit locks:
			///     - In a single threaded application you can simply forget about locking and call setLockMode(LOCK_MODE_NONE)
			///     - If you want automatic locking of references use setLockMode(LOCK_MODE_AUTO); this will be the slowest option, but works out of the box.
			///     - If you care about performance and want to find all potential performance bottlenecks,
			///       you can use setLockMode(LOCK_MODE_MANUAL) in a debug build.
			///       In this case you explicitly have to call hkReferencedObject::lockAll/unlockAll()
			///       and you get an error if you fail to do so. Typically you call lock/unlock around a bunch of add/removeReferences().
			///
			/// Also for convenience hkpWorld::lock() calls hkReferencedObject::lockAll().
		static void HK_CALL setLockMode(LockMode mode);

			/// Returns the current lock mode, see setLockMode
		static LockMode HK_CALL getLockMode();

			/// Lock access to all referenceCounts.
			/// Typically you do this at the beginning of your single threaded section. If your mode is set to \p LOCK_MODE_AUTO,
			/// this will still be useful as a group of add/remove reference calls will only perform a single lock.
			/// Note that recursive calls to lockAll() are allowed and very fast.
		static void HK_CALL lockAll();

			/// Unlock access to all referenceCounts
		static void HK_CALL unlockAll();

			/// Get the internal critical section used for locking reference counts
		static hkCriticalSection* HK_CALL getLockCriticalSection();

			/// Create the hkReferencedObjectLock singleton if it hasn't been created before.
			/// Either way initialize the lock mode.
		static void HK_CALL lockInit(LockMode lockMode);

			/// Returns the address of the lockAll pointer
		static hkUint32* HK_CALL getLockAllPtr();

			/// For internal use, initialize the referenced object lock singleton
		static void HK_CALL initializeLock();

			/// For internal use, deinitialize the referenced object lock singleton
		static void HK_CALL deinitializeLock();

			/// Return the type of this object. Returns HK_NULL if not known.
        virtual const hkClass* getClassType() const;

	protected:

		/// Deletes this object (i.e. roughly equivalent to "delete this;")
		/// Derived objects may customize this behavior, for instance objects may be
		/// queued for deletion rather than deleted immediately.
		HK_NOSPU_VIRTUAL void deleteThisReferencedObject() const;

	private:

		/// Memory size, flags, and reference count, packed into a 32-bit integer for atomic access.
		/// The MemSizeFlagsAndRefCount union is used to access its fields. Do not access directly! Use the provided accessor functions. 
		hkUint32 m_memSizeAndRefCount;	//+nosave
};

#include <Common/Base/Object/hkReferencedObject.inl>

#endif // HKBASE_HKREFERENCEDOBJECT_H

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
