#ifndef __CONTEXT__
#define __CONTEXT__

#include "../../Object/Base/Sprite.h"
#include "../../Object/Base/Model.h"
#include "../../Object/Base/MultiModel.h"
#include "../../Object/Base/Surface.h"
#include "../../Object/Effect/EffekseerManager.h"
#include "../../Object/Scene/VarianceShadow.h"
#include "../../System/Base/Shader.h"
#include "Camera.h"
#include "Viewport.h"
#include "../Matrix/ConstantBufferManager.h"

#include <dxgi1_5.h>
#include <d2d1_3.h>
#include <dwrite_3.h>
#include <memory>
#include <vector>
#include <bitset>

namespace DX11
{
	class Canvas{
	private:
		std::shared_ptr<ID3D11RenderTargetView> _renderTargetView = nullptr;
		std::shared_ptr<ID3D11Texture2D> _depthBuffer = nullptr;
		std::shared_ptr<ID3D11DepthStencilView> _depthStencilView = nullptr;

		std::shared_ptr<ID3D11RasterizerState> _rasterizer = nullptr;
		std::shared_ptr<ID3D11DepthStencilState> _depthStencil = nullptr;

		std::shared_ptr<IDXGIDevice1> _dxgiDevice = nullptr;
		std::shared_ptr<IDXGISwapChain1> _swapChain = nullptr;
		std::shared_ptr<ID3D11DeviceContext> _deviceContext = nullptr;

		std::shared_ptr<ID2D1Device> _d2dDevice = nullptr;
		std::shared_ptr<ID2D1DeviceContext> _d2dContext = nullptr;

		std::shared_ptr<IDWriteTextFormat> _textFormat = nullptr;
		std::shared_ptr<ID2D1Bitmap1> _bitmap = nullptr;

		std::vector<std::shared_ptr<Viewport>> _viewport;

		std::shared_ptr<EffectCanvas> _effectCanvas;
	private:
		Canvas(const Canvas& rhs);
		Canvas& operator=(const Canvas& rhs);
	public:
		Camera* GetCamera(const unsigned int viewportId)
		{
			return _viewport.at(viewportId)->GetCamera();
		}
		Light* GetLight(const unsigned int viewportId,const unsigned int lightId)
		{
			return _viewport.at(viewportId)->GetLight(lightId);
		}
		template<typename T>
		void SetConstantBuffer(const T& buffer,DX11::ConstantBuffer::cBufferSlot slotNum)
		{
			ConstantBuffer::SetBuffer(_deviceContext.get(), buffer, slotNum);
		}
	public:
		enum class BlendMode
		{
			Default,
			Add,
		};
		enum class CullingMode
		{
			Both_Side = 1,
			Reverse = 2,
			Normal = 3,
		};
	public:
		Canvas(){};
		void Init(const std::vector<DirectX::XMFLOAT4>& viewportSetting);
		HRESULT SetBlendState(BlendMode mode);
		void Begin();
		void End();
		void Reset();
		void SetViewport(const std::vector<DirectX::XMFLOAT4>& viewportSetting);
		void SetCulling(D3D11_CULL_MODE mode);
		void SetCameraBuffer();
		void SetDefaultRenderTarget();
		void SetRenderTarget(Surface* surface);
		const unsigned int GetViewportNum(){ return _viewport.size(); }

		void DrawSprite(Sprite* sprite, const ShaderSet& shader, const BlendMode& blend = BlendMode::Default, const std::bitset<5>& vpSetting = std::bitset<5>(1));
		void DrawModel(Model* model, const ShaderSet& shader, const BlendMode& blend = BlendMode::Default, const std::bitset<5>& vpSetting = std::bitset<5>(1));
		void DrawMultiModel(MultiModel* model, const ShaderSet& shader, const BlendMode& blend = BlendMode::Default, const std::bitset<5>& vpSetting = std::bitset<5>(1));
		void DrawSurface(Surface* surface, const ShaderSet& shader, const BlendMode& blend = BlendMode::Default, const std::bitset<5>& vpSetting = std::bitset<5>(1));
		void DrawEffect(EffectObject* effect);
		void DrawText(const std::wstring& text);
		void EndEffect();

		void BeginCreateDepthTexture(VarianceShadowMap* variance);
		void EndCreateDepthTexture(VarianceShadowMap* variance, Surface* surface);
	};
}

#endif