#ifndef __BTPHYSICS_OBJECT__
#define __BTPHYSICS_OBJECT__

#include <memory>

#define BT_NO_SIMD_OPERATOR_OVERLOADS
#include <btBulletDynamicsCommon.h>
#include <LinearMath/btIDebugDraw.h>
#include <DirectXMath.h>

namespace btPhysics
{
	template<typename T>
	class CollisionBox
	{
	private:
		std::shared_ptr<btConvexInternalShape> _shape;
		std::shared_ptr<btRigidBody> _body;
	private:
		DirectX::XMFLOAT3 _correctionPos;
	public:
		/**
		*@brief Initialize object of BulletPhysics for Collision
		*@param pos:position
		*@param weight:weight of object
		*		weight == 0:static
		*		weight >  0:dynamic
		*@param shape:shape of object
		*Type name		:description of param
		*btBoxShape		:x,y,z is width,height,depth
		*btSphereShape	:x is radius of sphere
		*btCapsuleShape	:x is radius,y is height
		*/
		void Init(const DirectX::XMFLOAT3& pos, float weight, const DirectX::XMFLOAT3& shape,float friction,const DirectX::XMFLOAT3& correctionPos = DirectX::XMFLOAT3(0.f,0.f,0.f));
		DirectX::XMFLOAT3 GetTranslate();
		DirectX::XMFLOAT4X4 GetRotate();
		DirectX::XMFLOAT3 GetScale();
		DirectX::XMFLOAT3 GetVelocity();
		void SetTranslate(const DirectX::XMFLOAT3& pos);
		void SetScale(const DirectX::XMFLOAT3& scale);
		void SetRotate(const DirectX::XMFLOAT3& angle);
		void AddTranslate(const DirectX::XMFLOAT3& pos);
		void SetVelocity(const DirectX::XMFLOAT3& velocity);
		void SetActive(bool flag);
		btRigidBody* GetRigidBody(){ return _body.get(); }
		void RemoveForce();
	};
}

#endif