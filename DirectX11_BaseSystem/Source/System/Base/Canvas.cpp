#include "Canvas.h"
#include "DXResource.h"
#include "../Matrix/ConstantBufferManager.h"

using namespace DirectX;

namespace DX11
{
	namespace ConstantBuffer
	{
		struct viewportSetting
		{
			float viewportDrawable;
			float viewportNum;
			XMFLOAT2 space;
			viewportSetting()
			{
				viewportDrawable = 0.f;
				viewportDrawable = 1.f;
				space = XMFLOAT2(0.f, 0.f);
			}
		};
	}
	void Canvas::Init(const std::vector<XMFLOAT4>& viewportSetting){
		assert(viewportSetting.size() <= 5);

		_deviceContext = Resource::CreateDeviceContext();

		_dxgiDevice = Resource::CreateDXGI();

		_swapChain = Resource::CreateSwapChain(_dxgiDevice.get());

		_renderTargetView = Resource::CreateRenderTargetView(Resource::CreateBackBuffer(_swapChain.get()).get());

		_depthBuffer = Resource::CreateDepthBuffer(_swapChain.get());

		_depthStencilView = Resource::CreateDepthStencilView(_depthBuffer.get());

		_rasterizer = Resource::CreateRasterizer();

		_depthStencil = Resource::CreateDepthStensil();

		_d2dDevice = Resource::CreateD2D_Device(_dxgiDevice.get());

		_d2dContext = Resource::CreateD2D_DeviceContext(_d2dDevice.get());

		_textFormat = Resource::CreateTextFormat(48.f);

		_bitmap = Resource::CreateBitmap(_d2dDevice.get(), _swapChain.get(), _d2dContext.get());

		SetViewport(viewportSetting);

		_effectCanvas = std::make_shared<EffectCanvas>();
		_effectCanvas->Init(_deviceContext.get());

		for (auto setting : viewportSetting)
		{
			std::shared_ptr<Viewport> viewport = std::make_shared<Viewport>(XMFLOAT2(setting.x,setting.y));
			_viewport.emplace_back(viewport);
		}
	}
	void Canvas::Begin(){
		_deviceContext->RSSetState(_rasterizer.get());
		_deviceContext->OMSetDepthStencilState(_depthStencil.get(), 0);

		ID3D11RenderTargetView* renderTargetView = _renderTargetView.get();
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		_deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
		_deviceContext->ClearDepthStencilView(_depthStencilView.get(),D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		_deviceContext->OMSetRenderTargets(1, &renderTargetView, _depthStencilView.get());

		SetBlendState(BlendMode::Default);

		ConstantBuffer::SetBuffer(_deviceContext.get(),_viewport[0]->GetLight(0)->GetBuffer(), DX11::ConstantBuffer::cBufferSlot::Light,std::bitset<3>("111"));
		GetShaderManager()->SetLayout(_deviceContext.get());
	}

	void Canvas::End()
	{
		if(FAILED(_swapChain->Present(1, 0)))
			throw;
	}

	void Canvas::SetCameraBuffer()
	{
		std::array<ConstantBuffer::cCameraBuffer, 1> cambuf;
		for (unsigned int i = 0; i < _viewport.size(); ++i)
		{
			cambuf[i] = _viewport.at(i)->GetCamera()->GetBuffer();
		}
		ConstantBuffer::SetBuffer(_deviceContext.get(), cambuf, DX11::ConstantBuffer::cBufferSlot::Camera);
	}

	void Canvas::Reset()
	{
		_deviceContext->RSSetState(_rasterizer.get());
		_deviceContext->OMSetDepthStencilState(_depthStencil.get(), 0);
		SetBlendState(BlendMode::Default);
		GetShaderManager()->SetLayout(_deviceContext.get());
	}

	HRESULT Canvas::SetBlendState(BlendMode mode)
	{
		ID3D11BlendState* blendState = nullptr;

		D3D11_RENDER_TARGET_BLEND_DESC renderTarget;

		if (mode == BlendMode::Default)
		{
			renderTarget.BlendEnable = TRUE;
			renderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
			renderTarget.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			renderTarget.BlendOp = D3D11_BLEND_OP_ADD;
			renderTarget.SrcBlendAlpha = D3D11_BLEND_ZERO;
			renderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
			renderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
			renderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}
		else if (mode == BlendMode::Add)
		{
			renderTarget.BlendEnable = TRUE;
			renderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
			renderTarget.DestBlend = D3D11_BLEND_ONE;
			renderTarget.BlendOp = D3D11_BLEND_OP_ADD;
			renderTarget.SrcBlendAlpha = D3D11_BLEND_ZERO;
			renderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
			renderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
			renderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}

		D3D11_BLEND_DESC BlendDesc;
		::ZeroMemory(&BlendDesc, sizeof(BlendDesc));
		BlendDesc.AlphaToCoverageEnable = FALSE;
		// TRUEの場合、マルチレンダーターゲットで各レンダーターゲットのブレンドステートの設定を個別に設定できる
		// FALSEの場合、0番目のみが使用される
		BlendDesc.IndependentBlendEnable = FALSE;

		::CopyMemory(&BlendDesc.RenderTarget, &renderTarget, sizeof(D3D11_RENDER_TARGET_BLEND_DESC));

		if (FAILED(GetDevice()->CreateBlendState(&BlendDesc, &blendState)))
			throw;

		_deviceContext->OMSetBlendState(blendState, 0, 0xffffffff);

		blendState->Release();
		return S_OK;
	}
	void Canvas::SetViewport(const std::vector<XMFLOAT4>& viewportSetting){
		// ビューポートの設定
		std::vector<D3D11_VIEWPORT>	viewports;
		for (auto viewport : viewportSetting)
		{
			D3D11_VIEWPORT vp;
			vp.Width = viewport.x;
			vp.Height = viewport.y;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			vp.TopLeftX = viewport.z;
			vp.TopLeftY = viewport.w;
			viewports.emplace_back(vp);
		}
		_deviceContext->RSSetViewports(viewports.size(), viewports.data());
	}

	void Canvas::SetCulling(D3D11_CULL_MODE mode)
	{
		D3D11_RASTERIZER_DESC *rsDesc = nullptr;
		_rasterizer->GetDesc(rsDesc);
		rsDesc->CullMode = mode;
	}

	void Canvas::SetRenderTarget(Surface* surface)
	{
		surface->SetRenderTarget(_deviceContext.get());
	}
	void Canvas::SetDefaultRenderTarget()
	{
		_deviceContext->RSSetState(_rasterizer.get());
		_deviceContext->OMSetDepthStencilState(_depthStencil.get(), 0);
		ID3D11RenderTargetView* renderTargetView = _renderTargetView.get();
		_deviceContext->OMSetRenderTargets(1, &renderTargetView, _depthStencilView.get());
	}
	void Canvas::DrawSprite(Sprite* sprite, const ShaderSet& shader, const BlendMode& blend, const std::bitset<5> & drawable)
	{
		if (sprite != nullptr)
		{
			SetBlendState(blend);
			ConstantBuffer::viewportSetting vpSetting;
			vpSetting.viewportDrawable = static_cast<float>(drawable.to_ulong());
			vpSetting.viewportNum = static_cast<float>(_viewport.size());
			ConstantBuffer::SetBuffer(_deviceContext.get(), vpSetting, ConstantBuffer::cBufferSlot::Viewport, std::bitset<3>("010"));
			GetShaderManager()->SetShader(_deviceContext.get(), shader);
			sprite->Draw(_deviceContext.get());
			SetBlendState(BlendMode::Default);
		}
	}
	void Canvas::DrawModel(Model* model, const ShaderSet& shader, const BlendMode& blend, const std::bitset<5>& drawable)
	{
		if (model != nullptr)
		{
			ConstantBuffer::viewportSetting vpSetting;
			vpSetting.viewportDrawable = static_cast<float>(drawable.to_ulong());
			vpSetting.viewportNum = static_cast<float>(_viewport.size());
			GetShaderManager()->SetShader(_deviceContext.get(), shader);
			ConstantBuffer::SetBuffer(_deviceContext.get(), vpSetting, ConstantBuffer::cBufferSlot::Viewport, std::bitset<3>("010"));
			model->Draw(_deviceContext.get());
		}
	}
	void Canvas::DrawSurface(Surface* surface, const ShaderSet& shader, const BlendMode& blend, const std::bitset<5>& drawable)
	{
		if (surface != nullptr)
		{
			ConstantBuffer::viewportSetting vpSetting;
			vpSetting.viewportDrawable = static_cast<float>(drawable.to_ulong());
			vpSetting.viewportNum = static_cast<float>(_viewport.size());
			GetShaderManager()->SetShader(_deviceContext.get(), shader);
			ConstantBuffer::SetBuffer(_deviceContext.get(), vpSetting, ConstantBuffer::cBufferSlot::Viewport, std::bitset<3>("010"));
			surface->Draw(_deviceContext.get());
		}
	}
	void Canvas::DrawMultiModel(MultiModel* model, const ShaderSet& shader, const BlendMode& blend, const std::bitset<5>& drawable)
	{
		if (model != nullptr)
		{
			ConstantBuffer::viewportSetting vpSetting;
			vpSetting.viewportDrawable = static_cast<float>(drawable.to_ulong());
			vpSetting.viewportNum = static_cast<float>(_viewport.size());
			GetShaderManager()->SetShader(_deviceContext.get(), shader);
			ConstantBuffer::SetBuffer(_deviceContext.get(), vpSetting, ConstantBuffer::cBufferSlot::Viewport, std::bitset<3>("010"));
			model->Draw(_deviceContext.get());
		}
	}
	static bool startDrawEffect;
	void Canvas::DrawEffect(EffectObject* effect)
	{
		if (!startDrawEffect)
			startDrawEffect = _effectCanvas->BeginDrawEffect(*_viewport.at(0)->GetCamera(), _deviceContext.get());
		if(startDrawEffect)
			_effectCanvas->DrawEffect(effect);
	}
	void Canvas::EndEffect()
	{
		startDrawEffect = !_effectCanvas->EndDrawEffect(_deviceContext.get());
		Reset();
	}
	void Canvas::BeginCreateDepthTexture(VarianceShadowMap* variance)
	{
		variance->BeginDrawDepthMap(_deviceContext.get(), GetCamera(0), GetLight(0, 0)->GetLightPos());
		SetCameraBuffer();
	}
	void Canvas::EndCreateDepthTexture(VarianceShadowMap* variance, Surface* surface)
	{
		GetShaderManager()->SetShader(_deviceContext.get(), variance->GetShadowMap()->GetShader());
		variance->EndDrawDepthMap(_deviceContext.get(), 0,surface);
	}
	void Canvas::DrawText(const std::wstring& text)
	{
		HRESULT hr;
		static float el = 0.0f;
		el += 1.0f;
		if (el > 360.0f) el = 0.0f;

		// Direct2D

		D2D1_COLOR_F color;
		color = D2D1::ColorF(
			min(120.0f, max(0, 120.0f - el)) / 120.0f,
			min(120.0f, max(0, el - 120.0f)) / 120.0f,
			min(120.0f, max(0, 240.0f - el)) / 120.0f,
			1.0f);

		ID2D1SolidColorBrush *brush;
		_d2dContext->CreateSolidColorBrush(color, &brush);
		
		D2D1_RECT_F rect;
		rect = D2D1::RectF(0 + el, 500, 440 + el, 550);

		_d2dContext->BeginDraw();
		//_d2dContext->FillRectangle(&rect, brush);

		// DirectWrite

		rect = D2D1::RectF(0 + el, 200, 450 + el, 201);
		_d2dContext->DrawText(
			text.c_str(), text.size(), _textFormat.get(), &rect, brush);

		_d2dContext->EndDraw();
		brush->Release();
	}
}