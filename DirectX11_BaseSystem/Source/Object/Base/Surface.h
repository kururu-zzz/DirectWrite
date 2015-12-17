#ifndef _SURFACE
#define _SURFACE

#include <d3d11.h>
#include <memory>

#include "Sprite.h"
#include "../../System/Base/Shader.h"
#include "../../System/Base/DXMath.h"


namespace DX11
{
	class Surface{
	private:
		std::shared_ptr<ID3D11ShaderResourceView> _shaderResourceView;
		std::shared_ptr<ID3D11SamplerState> _sampler;
		std::shared_ptr<ID3D11RenderTargetView> _renderTargetView;
		std::shared_ptr<ID3D11DepthStencilView> _depthStencilView;
		Sprite _sprite;
		DX11::ShaderSet _shader;
		bool shadowMap = false;
	public:
		void Init(const DirectX::XMFLOAT2& size, const DX11::ShaderSet& shader, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
		void SetRenderTarget(ID3D11DeviceContext* deviceContext);
		void SetAlpha(float alpha){ _sprite.SetAlpha(alpha); }
		void SetDepth(float depth){ _sprite.SetPos(DirectX::XMFLOAT3(_sprite.GetPos().x, _sprite.GetPos().y,depth)); }
		void SetTexture(ID3D11DeviceContext* deviceContext,unsigned int slotNum = 0);
		void SetShader(const DX11::ShaderSet& shader){ _shader = shader; }
		const DX11::ShaderSet& GetShader(){ return _shader; }
		Sprite* GetSprite() { return &_sprite; }
		void Draw(ID3D11DeviceContext* deviceContext);
	};
}

#endif