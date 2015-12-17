#include "Surface.h"
#include "../../System/Base/DXResource.h"

using namespace DirectX;

namespace DX11
{
	void Surface::Init(const XMFLOAT2& size, const DX11::ShaderSet& shader,DXGI_FORMAT format)
	{
		std::shared_ptr<ID3D11Texture2D> renderTargetBuffer = Resource::CreateRenderTargetBuffer(size,format);
		_renderTargetView = Resource::CreateRenderTargetView(renderTargetBuffer.get());
		_shaderResourceView = Resource::CreateShaderResourceView(renderTargetBuffer.get(),format);
		_sampler = Resource::CreateSampler();
		_depthStencilView = Resource::CreateDepthStencilView(Resource::CreateDepthBuffer(size).get());
		_shader = shader;
		_sprite.Init(XMFLOAT3(0.f, 0.f, 0.f), size, XMFLOAT4(0.f, 0.f, 1.f, 1.f), "");
		_sprite.SetAlpha(1.f);
		if (format != DXGI_FORMAT_R8G8B8A8_UNORM)
			shadowMap = true;
	}

	void Surface::SetRenderTarget(ID3D11DeviceContext* deviceContext)
	{
		ID3D11RenderTargetView* renderTargetView = _renderTargetView.get();
		if (!shadowMap)
			deviceContext->OMSetRenderTargets(1, &renderTargetView, _depthStencilView.get());
		else
			deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
		float clearColor[] = { 1.0f, 1.0f, 1.0f, 0.0f };
		deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
		if (!shadowMap)
		{
			deviceContext->ClearDepthStencilView(_depthStencilView.get(),
				D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		}
	}

	void Surface::SetTexture(ID3D11DeviceContext* deviceContext,unsigned int slotNum)
	{
		ID3D11ShaderResourceView* shaderResourceView = _shaderResourceView.get();
		ID3D11SamplerState* sampler = _sampler.get();
		deviceContext->PSSetShaderResources(slotNum, 1, &shaderResourceView);
		deviceContext->PSSetSamplers(slotNum, 1, &sampler);
	}
	void Surface::Draw(ID3D11DeviceContext* deviceContext)
	{
		SetTexture(deviceContext,1);
		_sprite.Draw(deviceContext);
	}
}