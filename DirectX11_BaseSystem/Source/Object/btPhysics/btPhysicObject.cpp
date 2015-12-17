
#include "btPhysicObject.h"
#include <iostream>
#include <vector>
#include <typeinfo>

namespace btPhysics
{
	template<typename T>
	inline std::shared_ptr<T> CreateCollisionObject(const DirectX::XMFLOAT3& vec)
	{
		return nullptr;
	}
	template<>
	inline std::shared_ptr<btBoxShape> CreateCollisionObject<btBoxShape>(const DirectX::XMFLOAT3& vec)
	{
		auto shape = new btBoxShape(btVector3(btScalar(vec.x), btScalar(vec.y), btScalar(vec.z)));
		return std::shared_ptr<btBoxShape>(shape);
	}
	template<>
	inline std::shared_ptr<btSphereShape> CreateCollisionObject<btSphereShape>(const DirectX::XMFLOAT3& vec)
	{
		auto shape = new btSphereShape(btScalar(vec.x));
		return std::shared_ptr<btSphereShape>(shape);
	}
	template<>
	inline std::shared_ptr<btCapsuleShape> CreateCollisionObject<btCapsuleShape>(const DirectX::XMFLOAT3& vec)
	{
		auto shape = new btCapsuleShape(btScalar(vec.x), btScalar(vec.y));
		return std::shared_ptr<btCapsuleShape>(shape);
	}
	DirectX::XMFLOAT4X4 btMatrixToXMFLOAT(const btMatrix3x3& mat)
	{
		DirectX::XMFLOAT4X4 matrix;
		DirectX::XMStoreFloat4x4(&matrix, DirectX::XMMatrixIdentity());
		for (auto i : { 0, 1, 2 })
		{
			auto column = mat.getColumn(i);
			matrix.m[i][0] = column.getX();
			matrix.m[i][1] = column.getY();
			matrix.m[i][2] = column.getZ();
		}
		return matrix;
	}

	float QuaternionToDegrees(btScalar axis,btScalar angle)
	{
		if (axis != 0)
			return DirectX::XMConvertToDegrees(asin(angle/axis))*axis;
		return 0;
	}

	template<typename T>
	void CollisionBox<T>::Init(const DirectX::XMFLOAT3& pos, float weight, const DirectX::XMFLOAT3& shape,float friction, const DirectX::XMFLOAT3& correctionPos) {
		_correctionPos = correctionPos;
		_shape = CreateCollisionObject<T>(shape);
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(pos.x + _correctionPos.x, pos.y + _correctionPos.y, pos.z + _correctionPos.z));
		auto inertia = btVector3(0.f, 0.f, 0.f);
		if (weight != 0.f)
			_shape->calculateLocalInertia(btScalar(weight), inertia);
		auto motionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rb_cinfo(weight, motionState, _shape.get(), inertia);
		auto body = new btRigidBody(rb_cinfo);
		_body = std::shared_ptr<btRigidBody>(body, [](btRigidBody* body)
		{
			delete body->getMotionState();
		});
		_body->setFriction(btScalar(friction));
		_body->setSleepingThresholds(0.f, 0.f);
		if (weight == 0.f)
		{
			_body->setCollisionFlags(_body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
			_body->setActivationState(DISABLE_DEACTIVATION);
		}
	}
	template<typename T>
	DirectX::XMFLOAT3 CollisionBox<T>::GetTranslate() {
		auto translate = _body->getWorldTransform().getOrigin();
		return DirectX::XMFLOAT3(translate.getX() - _correctionPos.x, translate.getY() - _correctionPos.y, translate.getZ() - _correctionPos.z);
	}
	template<typename T>
	DirectX::XMFLOAT4X4 CollisionBox<T>::GetRotate() {
		auto rotate = _body->getWorldTransform().getBasis();
		return btMatrixToXMFLOAT(rotate);
	}
	template<typename T>
	DirectX::XMFLOAT3 CollisionBox<T>::GetScale() {
		auto scale = _shape->getLocalScaling();
		return DirectX::XMFLOAT3(scale.getX(), scale.getY(), scale.getZ());
	}
	template<typename T>
	DirectX::XMFLOAT3 CollisionBox<T>::GetVelocity() {
		auto velocity = _body->getLinearVelocity();
		return DirectX::XMFLOAT3(velocity.getX(), velocity.getY(), velocity.getZ());
	}
	template<typename T>
	void CollisionBox<T>::SetTranslate(const DirectX::XMFLOAT3& pos)
	{
		auto& transform = _body->getWorldTransform();
		transform.setOrigin(btVector3(pos.x + _correctionPos.x, pos.y + _correctionPos.y, pos.z +_correctionPos.z));
	}
	template<typename T>
	void CollisionBox<T>::SetScale(const DirectX::XMFLOAT3& scale) {
		_shape->setLocalScaling(btVector3(scale.x, scale.y, scale.z));
	}
	template<typename T>
	void CollisionBox<T>::SetRotate(const DirectX::XMFLOAT3& angle) {
		auto& transform = _body->getWorldTransform();
		transform.getBasis().setEulerZYX(angle.x,angle.y,angle.z);
	}
	template<typename T>
	void CollisionBox<T>::AddTranslate(const DirectX::XMFLOAT3& pos)
	{
		auto& translate = _body->getWorldTransform().getOrigin();
		translate += btVector3(pos.x,pos.y,pos.z);
	}
	template<typename T>
	void CollisionBox<T>::SetVelocity(const DirectX::XMFLOAT3& v)
	{
		_body->setLinearVelocity(btVector3(v.x, v.y, v.z));
	}
	template<typename T>
	void CollisionBox<T>::SetActive(bool flag)
	{
		_body->activate(flag);
	}
	template<typename T>
	void CollisionBox<T>::RemoveForce() {
		_body->clearForces();
	}
	template class CollisionBox<btBoxShape>;
	template class CollisionBox<btSphereShape>;
	template class CollisionBox<btCapsuleShape>;
}