#include "Light.h"
#include "../../System/Base/Device.h"
#include "../../System/Matrix/ConstantBufferManager.h"
#include "../../System/Base/DXInput.h"

using namespace DirectX;

namespace DX11
{
	Light::Light(){
	}
	void Light::Update(){
		XMFLOAT3 v;
		float spd = 5.f;
		v.x = ((GetDXInput()->GetIsPressedKeyboard(DIK_F) - GetDXInput()->GetIsPressedKeyboard(DIK_D))*spd);
		v.y = ((GetDXInput()->GetIsPressedKeyboard(DIK_R) - GetDXInput()->GetIsPressedKeyboard(DIK_C))*spd);
		v.z = ((GetDXInput()->GetIsPressedKeyboard(DIK_X) - GetDXInput()->GetIsPressedKeyboard(DIK_V))*spd);
		lightbuf.LightDirection.x += v.x;
		lightbuf.LightDirection.y += v.y;
		lightbuf.LightDirection.z += v.z;
		if (lightbuf.LightDirection.y <= 30.f)
			lightbuf.LightDirection.y = 30.f;
	}

	void Light::SetPos(const XMFLOAT3& lightPos)
	{
		lightbuf.LightDirection.x = lightPos.x;
		lightbuf.LightDirection.y = lightPos.y;
		lightbuf.LightDirection.z = lightPos.z;
	}

	const ConstantBuffer::cLightBuffer& Light::GetBuffer(){
		return lightbuf;
	}

	Light::~Light(){
	}
}