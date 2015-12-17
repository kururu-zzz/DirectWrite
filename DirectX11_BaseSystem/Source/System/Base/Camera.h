#ifndef __CAMERA__
#define __CAMERA__

#include "../Base/DXMath.h" 
#include "../../Object/Base/CameraAnimation.h"
#include <unordered_map>

namespace DX11
{
	namespace ConstantBuffer
	{
		struct cCameraBuffer
		{
			DirectX::XMFLOAT4X4	matView;
			DirectX::XMFLOAT4X4	matProjection;
			DirectX::XMFLOAT4X4  matViewPort;
			DirectX::XMFLOAT4X4	matLVP;
			DirectX::XMFLOAT4 eyePos;
			cCameraBuffer()
			{
				DirectX::XMStoreFloat4x4(&matProjection, DirectX::XMMatrixIdentity());
				DirectX::XMStoreFloat4x4(&matView, DirectX::XMMatrixIdentity());
				DirectX::XMStoreFloat4x4(&matViewPort, DirectX::XMMatrixIdentity());
				DirectX::XMStoreFloat4x4(&matLVP, DirectX::XMMatrixIdentity());
				eyePos = DirectX::XMFLOAT4(0.f, 0.f, 0.f, 0.f);
			}
		};
	}

	class Camera{
	private:
		ConstantBuffer::cCameraBuffer _cameraBuf;
		DirectX::XMFLOAT3 _pos;
		DirectX::XMFLOAT3 _focus;
		DirectX::XMFLOAT3 _qua;

		bool RockOnFlag;

		const float ProjectionDegree = 45.f;
		float screenAspect = 0.f;
	public:
		void Init(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& focus, const DirectX::XMFLOAT2& screenSize);
		void SetPos(const DirectX::XMFLOAT3& pos);
		void SetFocus(const DirectX::XMFLOAT3& focus);
		void SetCam(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& focus);
		void SetOrtho(const DirectX::XMFLOAT3& eyePos);
		void SetOrtho(const DirectX::XMFLOAT3& eyePos, const DirectX::XMFLOAT3& focus);
		void RockOn(const DirectX::XMFLOAT3& newFocus);
		bool CheckInScreen(const DirectX::XMFLOAT3& pos);

		const ConstantBuffer::cCameraBuffer& GetBuffer();

		const DirectX::XMFLOAT3& GetPos() const{
			return _pos;
		};
		const DirectX::XMFLOAT3& GetFoc() const{
			return _focus;
		};
	};
}

#endif