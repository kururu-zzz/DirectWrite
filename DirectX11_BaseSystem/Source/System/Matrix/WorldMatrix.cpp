#include "WorldMatrix.h"
#include "ConstantBufferManager.h"

using namespace DirectX;

namespace DX11
{
	WorldMatrix::WorldMatrix(){
		//ÉèÅ[ÉãÉhïœä∑çsóÒçÏê¨
		_scale = XMFLOAT3(1.f,1.f,1.f);
		_translate = XMFLOAT3(0.f, 0.f, 0.f);
		XMStoreFloat4x4(&_rotate, DirectX::XMMatrixIdentity());
	}

	void WorldMatrix::SetPos(const XMFLOAT3& pos){
		_translate = pos;
	}

	void WorldMatrix::SetRotate(const XMFLOAT3& angle){
		auto matRotateX = XMMatrixRotationX(XMConvertToRadians(angle.x));
		auto matRotateY = XMMatrixRotationY(XMConvertToRadians(angle.y));
		auto matRotateZ = XMMatrixRotationZ(XMConvertToRadians(angle.z));
		XMStoreFloat4x4(&_rotate, matRotateX*matRotateY*matRotateZ);
	}

	void WorldMatrix::SetRotate(const XMFLOAT4X4& angle)
	{
		_rotate = angle;
	}

	void WorldMatrix::SetScale(const XMFLOAT3& scale)
	{
		_scale = scale;
	}

	void WorldMatrix::SetWorldBuffer(ID3D11DeviceContext* deviceContext){
		auto matTranslate = XMMatrixTranslation(_translate.x, _translate.y, _translate.z);
		auto matScale = XMMatrixScaling(-_scale.x, _scale.y, _scale.z);
		auto matRotate = XMLoadFloat4x4(&_rotate);
		XMStoreFloat4x4(&_worldBuf.matWorld, XMMatrixTranspose(matScale*matRotate*matTranslate));
		ConstantBuffer::SetBuffer(deviceContext, _worldBuf, ConstantBuffer::cBufferSlot::World);
	}

	WorldMatrix::~WorldMatrix(){
	}
}