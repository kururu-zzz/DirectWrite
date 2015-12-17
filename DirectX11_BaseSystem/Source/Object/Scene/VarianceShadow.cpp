#include "VarianceShadow.h"
#include "../../System/Base/Shader.h"

HRESULT VarianceShadowMap::Init()
{
	DirectX::XMFLOAT2 Size(2400.f, 1800.f);
	 
	auto shader = DX11::ShaderSet("Blur", "RenderVS", "SHADER\\SPRITE.hlsl", "RenderGSSpriteViewport", "SHADER\\SPRITE.hlsl", "BlurShader", "SHADER\\BLUR.hlsl");
	//深度マップサーフェイス
	_shadowMap[0].Init(Size, shader, DXGI_FORMAT_R16G16_UNORM);
	_shadowMap[1].Init(Size, shader, DXGI_FORMAT_R16G16_UNORM);


	return S_OK;
}

void VarianceShadowMap::BeginDrawDepthMap(ID3D11DeviceContext* deviceContext,DX11::Camera* cam,const DirectX::XMFLOAT3& lightPos)
{
	cam->SetOrtho(lightPos,cam->GetFoc());
	_shadowMap[0].SetRenderTarget(deviceContext);
}

void VarianceShadowMap::EndDrawDepthMap(ID3D11DeviceContext* deviceContext,int blurNum,DX11::Surface* surface)
{
	int Count = 0;
	for (int i = 0; i < blurNum; ++i)
	{
		_shadowMap[(i + 1) % 2].SetRenderTarget(deviceContext);
		_shadowMap[i % 2].SetTexture(deviceContext,1);
		_shadowMap[i % 2].Draw(deviceContext);
		Count = i + 1;
	}
	surface->SetRenderTarget(deviceContext);
	_shadowMap[Count % 2].SetTexture(deviceContext,1);
}