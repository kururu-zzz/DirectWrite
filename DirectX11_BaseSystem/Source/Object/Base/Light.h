#ifndef _LIGHT
#define _LIGHT

#include <d3d11.h>
#include "../../System/Base/DXMath.h" 
#include <memory>

namespace DX11
{
	namespace ConstantBuffer
	{
		struct cLightBuffer
		{
			//ÉâÉCÉgÇÃèÓïÒ
			DirectX::XMFLOAT4 LightDirection;
			cLightBuffer()
			{
				LightDirection = DirectX::XMFLOAT4(0.f, 0.f, 0.f, 1.f);
			}
		};
	}

	class Light{
	private:
		std::shared_ptr<ID3D11Buffer> cb;
		ConstantBuffer::cLightBuffer lightbuf;
	public:
		Light();
		virtual ~Light();
		void Update();
		void SetPos(const DirectX::XMFLOAT3& LightPos);
		const ConstantBuffer::cLightBuffer& GetBuffer();
		const DirectX::XMFLOAT3 GetLightPos() const
		{
			return DirectX::XMFLOAT3(lightbuf.LightDirection.x, lightbuf.LightDirection.y, lightbuf.LightDirection.z);
		};
	};
}
#endif