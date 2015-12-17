
#include "btPhysicGhost.h"
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
	static DirectX::XMFLOAT4X4 btMatrixToXMFLOAT(const btMatrix3x3& mat)
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

	static float QuaternionToDegrees(btScalar axis,btScalar angle)
	{
		if (axis != 0)
			return DirectX::XMConvertToDegrees(asin(angle/axis))*axis;
		return 0;
	}

	template<typename T>
	void GhostObject<T>::Init(const DirectX::XMFLOAT3& pos, float weight, const DirectX::XMFLOAT3& shape,float friction) {
		_shape = CreateCollisionObject<T>(shape);
		auto body = new btGhostObject();
		_body = std::shared_ptr<btGhostObject>(body);
		_body->setCollisionShape(_shape.get());
		_body->setCollisionFlags(_body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}
	template<typename T>
	DirectX::XMFLOAT3 GhostObject<T>::GetTranslate() {
		auto translate = _body->getWorldTransform().getOrigin();
		return DirectX::XMFLOAT3(translate.getX(), translate.getY(), translate.getZ());
	}
	template<typename T>
	DirectX::XMFLOAT4X4 GhostObject<T>::GetRotate() {
		auto rotate = _body->getInterpolationWorldTransform().getBasis();
		return btMatrixToXMFLOAT(rotate);
	}
	template<typename T>
	DirectX::XMFLOAT3 GhostObject<T>::GetScale() {
		auto scale = _shape->getLocalScaling();
		return DirectX::XMFLOAT3(scale.getX(), scale.getY(), scale.getZ());
	}
	template<typename T>
	void GhostObject<T>::SetSize(const DirectX::XMFLOAT3& size)
	{
		_shape = CreateCollisionObject<T>(size);
		_body->setCollisionShape(_shape.get());
	}
	template<typename T>
	void GhostObject<T>::SetTranslate(const DirectX::XMFLOAT3& pos)
	{
		auto transform = _body->getWorldTransform();
		transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
		transform.setRotation(_body->getWorldTransform().getRotation());
		_body->setInterpolationWorldTransform(transform);
		_body->setWorldTransform(transform);
	}
	template<typename T>
	void GhostObject<T>::SetScale(const DirectX::XMFLOAT3& scale) {
		_shape->setLocalScaling(btVector3(scale.x, scale.y, scale.z));
	}
	template<typename T>
	void GhostObject<T>::SetRotate(const DirectX::XMFLOAT3& angle) {
		auto& transform = _body->getWorldTransform();
		transform.getBasis().setEulerZYX(angle.x, angle.y, angle.z);
	}
	template<typename T>
	void GhostObject<T>::AddTranslate(const DirectX::XMFLOAT3& pos)
	{
		auto& translate = _body->getWorldTransform().getOrigin();
		translate += btVector3(pos.x, pos.y, pos.z);
	}
	template class GhostObject<btBoxShape>;
	template class GhostObject<btSphereShape>;
	template class GhostObject<btCapsuleShape>;
}