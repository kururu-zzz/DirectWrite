#include "DXResource.h"
#include "Device.h"
#include "../Loader/WICTextureLoader.h"
using namespace DirectX;

#pragma comment( lib, "d3dcompiler.lib" )  // hlsl をコンパイルする
#include <D3Dcompiler.h>

#include <vector>

namespace DX11
{
	namespace Resource
	{
		void ReleaseIUnknown(IUnknown* p)
		{
			p->Release();
		}
		static DXGI_FORMAT TextureFormat2DepthStencilViewFormat(DXGI_FORMAT format)
		{
			switch (format) {
			case DXGI_FORMAT_R8_TYPELESS:
				return DXGI_FORMAT_R8_UNORM;
			case DXGI_FORMAT_R16_TYPELESS:
				return DXGI_FORMAT_D16_UNORM;
			case DXGI_FORMAT_R32_TYPELESS:
				return DXGI_FORMAT_D32_FLOAT;
			case DXGI_FORMAT_R24G8_TYPELESS:
				return DXGI_FORMAT_D24_UNORM_S8_UINT;
			default:
				return format;
			}
		}
		std::shared_ptr<ID3D11DeviceContext> CreateDeviceContext()
		{
			ID3D11DeviceContext* deviceContext;
			GetDevice()->GetImmediateContext(&deviceContext);

			return std::shared_ptr<ID3D11DeviceContext>(deviceContext, [](ID3D11DeviceContext* p){
				p->ClearState();
				p->Flush();
				p->Release();
			});
		}
		std::shared_ptr<IDXGIDevice1> CreateDXGI()
		{
			//インターフェース取得
			IDXGIDevice1* dxgiDevice = nullptr;
			if (FAILED(GetDevice()->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgiDevice)))
				throw;
			dxgiDevice->SetMaximumFrameLatency(1);
			return std::shared_ptr<IDXGIDevice1>(dxgiDevice, ReleaseIUnknown);
		}

		std::shared_ptr<ID2D1Factory3> CreateD2DFactory()
		{
			D2D1_FACTORY_OPTIONS option;
			ZeroMemory(&option, sizeof option);
			ID2D1Factory3 *factory;
			auto hr = D2D1CreateFactory(
				D2D1_FACTORY_TYPE_SINGLE_THREADED,
				__uuidof(ID2D1Factory3),
				&option,
				reinterpret_cast<void**>(&factory));
			if(FAILED(hr))
				throw;
			return std::shared_ptr<ID2D1Factory3>(factory, ReleaseIUnknown);
		}

		std::shared_ptr<ID2D1Device> CreateD2D_Device(IDXGIDevice1* dxgiDevice)
		{
			ID2D1Device* device;
			auto factory = CreateD2DFactory();
			// Direct2Dデバイスの作成
			auto hr = factory->CreateDevice(dxgiDevice, &device);
			if(FAILED(hr))
				throw;
			
			return std::shared_ptr<ID2D1Device>(device, ReleaseIUnknown);
		}

		std::shared_ptr<ID2D1DeviceContext> CreateD2D_DeviceContext(ID2D1Device* device)
		{
			ID2D1DeviceContext* context;
			// Direct2Dデバイスコンテクストの作成
			if(FAILED(device->CreateDeviceContext(
				D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
				&context)))
				throw;
			return std::shared_ptr<ID2D1DeviceContext>(context,ReleaseIUnknown);
		}

		std::shared_ptr<ID2D1Bitmap1> CreateBitmap(ID2D1Device* d2dDevice,IDXGISwapChain* swapChain,ID2D1DeviceContext* context)
		{
			float dpiX, dpiY;
			context->GetDpi(&dpiX,&dpiY);

			// レンダーターゲットの取得（DXGI）
			IDXGISurface *surface;
			if(FAILED(swapChain->GetBuffer(0, IID_PPV_ARGS(&surface))))
				throw;

			ID2D1Bitmap1* d2dBitmap;

			// Direct2Dの描画先となるビットマップを作成
			D2D1_BITMAP_PROPERTIES1 prop =
				D2D1::BitmapProperties1(
					D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
					D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
					dpiX,
					dpiY);
			auto hr = context->CreateBitmapFromDxgiSurface(
				surface, &prop, &d2dBitmap);
			if(FAILED(hr))
				throw;
			surface->Release();

			// 描画するDirect2Dビットマップの設定
			context->SetTarget(d2dBitmap);

			return std::shared_ptr<ID2D1Bitmap1>(d2dBitmap,ReleaseIUnknown);
		}

		std::shared_ptr<IDWriteFactory> CreateDWriteFactory() {
			// DirectWriteのファクトリの作成
			IDWriteFactory* dwriteFactory;
			if(FAILED(DWriteCreateFactory(
				DWRITE_FACTORY_TYPE_SHARED,
				__uuidof(dwriteFactory),
				reinterpret_cast<IUnknown**>(&dwriteFactory))))
				throw;
			return std::shared_ptr<IDWriteFactory>(dwriteFactory,ReleaseIUnknown);
		}
		std::shared_ptr<IDWriteTextFormat> CreateTextFormat(const float fontSize){
			auto dwriteFactory = CreateDWriteFactory();

			IDWriteTextFormat* textFormat;
			// テキストフォーマットの作成
			if(FAILED(dwriteFactory->CreateTextFormat(
				L"Meiryo UI", nullptr,
				DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
				fontSize, L"", &textFormat)))
				throw;

			if(FAILED(textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER)))
				throw;

			// パラグラフの指定
			if(FAILED(textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR)))
				throw;

			return std::shared_ptr<IDWriteTextFormat>(textFormat,ReleaseIUnknown);
		}

		std::shared_ptr<IDXGIAdapter> CreateAdapter(IDXGIDevice1* DXGI)
		{
			//アダプター取得
			IDXGIAdapter* adapter = nullptr;
			if (FAILED(DXGI->GetAdapter(&adapter)))
				throw;
			return std::shared_ptr<IDXGIAdapter>(adapter, ReleaseIUnknown);
		}
		std::shared_ptr<IDXGIFactory2> CreateFactory(IDXGIAdapter* adapter)
		{
			//ファクトリー取得
			IDXGIFactory2* DXGIFactory = nullptr;
			if (FAILED(adapter->GetParent(__uuidof(IDXGIFactory2), (void**)&DXGIFactory)))
				throw;
			return std::shared_ptr<IDXGIFactory2>(DXGIFactory, ReleaseIUnknown);
		}

		std::shared_ptr<IDXGISwapChain1> CreateSwapChain(IDXGIDevice1* device)
		{
			auto DXGIFactory = CreateFactory(CreateAdapter(device).get());
			IDXGISwapChain1* swapchain;
			DXGI_SWAP_CHAIN_DESC1 scDesc;
			//スワップチェイン作成
			// 解像度
			scDesc.Width = 1200;
			scDesc.Height = 900;
			// バックバッファのテクスチャフォーマット
			scDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			// スケール方法
			scDesc.Scaling = DXGI_SCALING_STRETCH;
			// 立体視
			scDesc.Stereo = 0;
			// 半透明モード
			scDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

			// 使用方法
			scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			// バックバッファの数
			scDesc.BufferCount = 2;
			// 描画後のバッファの扱い
			scDesc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
			// MSAA
			scDesc.SampleDesc.Count = 1;
			scDesc.SampleDesc.Quality = 0;
			// フラグ
			scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // 解像度変更が有効
			if (FAILED(DXGIFactory->CreateSwapChainForHwnd(GetDevice(),*GetHWND(), &scDesc, nullptr,nullptr,&swapchain)))
				throw;

			return std::shared_ptr<IDXGISwapChain1>(swapchain, [](IDXGISwapChain1* p)
			{
				BOOL FullScreen;
				p->GetFullscreenState(&FullScreen, nullptr);
				if (FullScreen == TRUE) p->SetFullscreenState(FALSE, nullptr);
				p->Release();
			});
		}

		std::shared_ptr<ID3D11Texture2D> CreateBackBuffer(IDXGISwapChain* swapChain)
		{
			ID3D11Texture2D* backbuffer;

			if (FAILED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
				reinterpret_cast<void**>(&backbuffer))))
				throw;
			return std::shared_ptr<ID3D11Texture2D>(backbuffer, ReleaseIUnknown);
		}

		std::shared_ptr<ID3D11RenderTargetView> CreateRenderTargetView(ID3D11Texture2D* backBuffer)
		{
			ID3D11RenderTargetView* renderTarget;

			// RenderTargetViewの作成
			if (FAILED(GetDevice()->CreateRenderTargetView(backBuffer, nullptr, &renderTarget)))
				throw;
			return std::shared_ptr<ID3D11RenderTargetView>(renderTarget, ReleaseIUnknown);
		}

		std::shared_ptr<ID3D11Texture2D> CreateDepthBuffer(const XMFLOAT2& bufferSize, UINT Count, UINT Quality)
		{
			ID3D11Texture2D* depthBuffer;

			// デプステクスチャの作成
			D3D11_TEXTURE2D_DESC depthDesc;
			ZeroMemory(&depthDesc, sizeof(depthDesc));
			depthDesc.Width = static_cast<UINT>(bufferSize.x);
			depthDesc.Height = static_cast<UINT>(bufferSize.y);
			depthDesc.MipLevels = 1;
			depthDesc.ArraySize = 1;
			depthDesc.Format = DXGI_FORMAT_R32_TYPELESS;
			depthDesc.SampleDesc.Count = Count;
			depthDesc.SampleDesc.Quality = Quality;
			depthDesc.Usage = D3D11_USAGE_DEFAULT;
			depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
			depthDesc.CPUAccessFlags = 0;
			depthDesc.MiscFlags = 0;
			if (FAILED(GetDevice()->CreateTexture2D(&depthDesc, nullptr, &depthBuffer)))
				throw;

			return std::shared_ptr<ID3D11Texture2D>(depthBuffer, ReleaseIUnknown);
		}

		std::shared_ptr<ID3D11Texture2D> CreateDepthBuffer(IDXGISwapChain* swapChain)
		{
			DXGI_SWAP_CHAIN_DESC chainDesc;
			if (FAILED(swapChain->GetDesc(&chainDesc)))
				throw;

			return CreateDepthBuffer(XMFLOAT2((float)chainDesc.BufferDesc.Width, (float)chainDesc.BufferDesc.Height), chainDesc.SampleDesc.Count, chainDesc.SampleDesc.Quality);
		}

		std::shared_ptr<ID3D11DepthStencilView> CreateDepthStencilView(ID3D11Texture2D* depthBuffer)
		{
			D3D11_TEXTURE2D_DESC depthDesc;
			depthBuffer->GetDesc(&depthDesc);
			ID3D11DepthStencilView* depthstencilview;

			// 深度ステンシルビュー設定
			D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
			::ZeroMemory(&descDSV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
			descDSV.Format = TextureFormat2DepthStencilViewFormat(depthDesc.Format);
			descDSV.ViewDimension = (depthDesc.SampleDesc.Count > 1) ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
			descDSV.Texture2D.MipSlice = 0;
			if (FAILED(GetDevice()->CreateDepthStencilView(depthBuffer, &descDSV, &depthstencilview)))
				throw;

			return std::shared_ptr<ID3D11DepthStencilView>(depthstencilview, ReleaseIUnknown);
		}

		std::shared_ptr<ID3D11RasterizerState> CreateRasterizer()
		{
			ID3D11RasterizerState* rasterizer;

			D3D11_RASTERIZER_DESC rsDesc;
			ZeroMemory(&rsDesc, sizeof(D3D11_RASTERIZER_DESC));
			rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
			rsDesc.FillMode = D3D11_FILL_SOLID;
			rsDesc.FrontCounterClockwise = FALSE;
			rsDesc.DepthClipEnable = TRUE;
			if (FAILED(GetDevice()->CreateRasterizerState(&rsDesc, &rasterizer)))
				throw;

			return std::shared_ptr<ID3D11RasterizerState>(rasterizer, ReleaseIUnknown);

		}
		std::shared_ptr<ID3D11DepthStencilState> CreateDepthStensil()
		{
			ID3D11DepthStencilState* depthStencil;

			D3D11_DEPTH_STENCIL_DESC dsDesc;
			ZeroMemory(&dsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
			dsDesc.DepthEnable = TRUE;
			dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
			dsDesc.StencilEnable = FALSE;
			if (FAILED(GetDevice()->CreateDepthStencilState(&dsDesc, &depthStencil)))
				throw;

			return std::shared_ptr<ID3D11DepthStencilState>(depthStencil, ReleaseIUnknown);

			return S_OK;
		}

		std::shared_ptr<ID3D11Texture2D> CreateRenderTargetBuffer(const XMFLOAT2& size,DXGI_FORMAT format){
			ID3D11Texture2D* buffer; //テクスチャ

			// レンダリングテクスチャを作成する
			D3D11_TEXTURE2D_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Width = (UINT)size.x;
			desc.Height = (UINT)size.y;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = format;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;

			if (FAILED(GetDevice()->CreateTexture2D(&desc, nullptr, &buffer)))
				throw;
			return std::shared_ptr<ID3D11Texture2D>(buffer, ReleaseIUnknown);
		}

		std::shared_ptr<ID3D11ShaderResourceView> CreateShaderResourceView(const std::string& filename)
		{
			ID3D11ShaderResourceView* shaderResourceView;
			WCHAR	sNewPath[100];
			//文字コード変換
			MultiByteToWideChar(CP_ACP, 0, filename.c_str(), -1, sNewPath, MAX_PATH);

			if (FAILED(CreateWICTextureFromFile(GetDevice(), sNewPath, nullptr, &shaderResourceView, 0)))
				throw;
			return std::shared_ptr<ID3D11ShaderResourceView>(shaderResourceView, ReleaseIUnknown);
		}

		std::shared_ptr<ID3D11ShaderResourceView> CreateShaderResourceView(ID3D11Texture2D* resourceBuffer,DXGI_FORMAT format)
		{
			ID3D11ShaderResourceView* shaderResourceView;
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			ZeroMemory(&srvDesc, sizeof(srvDesc));
			srvDesc.Format = format;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels = 1;

			if (FAILED(GetDevice()->CreateShaderResourceView(resourceBuffer, &srvDesc, &shaderResourceView)))
				throw;
			return std::shared_ptr<ID3D11ShaderResourceView>(shaderResourceView, ReleaseIUnknown);
		}

		std::shared_ptr<ID3D11SamplerState> CreateSampler()
		{
			ID3D11SamplerState* sampler;
			// サンプラを作成する
			D3D11_SAMPLER_DESC samDesc;
			ZeroMemory(&samDesc, sizeof(samDesc));
			samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
			samDesc.AddressU = samDesc.AddressV = samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			samDesc.BorderColor[0] = samDesc.BorderColor[1] = samDesc.BorderColor[2] = samDesc.BorderColor[3] = 1.0f;
			samDesc.MipLODBias = 0.f;
			samDesc.MaxAnisotropy = 0;
			samDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
			samDesc.MinLOD = 0;
			samDesc.MaxLOD = D3D11_FLOAT32_MAX;

			if (FAILED(GetDevice()->CreateSamplerState(&samDesc, &sampler)))
				throw;
			return std::shared_ptr<ID3D11SamplerState>(sampler, ReleaseIUnknown);
		}

		std::shared_ptr<ID3D11InputLayout> CreateLayout(ID3DBlob* vertexBlob){
			ID3D11InputLayout* layout;
			D3D11_INPUT_ELEMENT_DESC layout_desc[] = {
				{ "IN_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "IN_COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "IN_NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "IN_TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "IN_BONEINDEX", 0, DXGI_FORMAT_R8G8B8A8_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "IN_BONEWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			if (FAILED(GetDevice()->CreateInputLayout(layout_desc,
				_countof(layout_desc),
				vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), &layout)))
				throw;
			return std::shared_ptr<ID3D11InputLayout>(layout, ReleaseIUnknown);
		}
		std::shared_ptr<ID3DBlob> CompileShaderFromFile(const std::string& filename, const std::string& funcname,
			const std::string& shaderModel)
		{
			ID3DBlob* blob;

			WCHAR	sNewPath[100];
			//文字コード変換
			MultiByteToWideChar(CP_ACP, 0, filename.c_str(), -1, sNewPath, MAX_PATH);

			HRESULT hr = S_OK;
			// 行列を列優先で設定し、古い形式の記述を許可しないようにする
			UINT flag1 = D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_ENABLE_STRICTNESS;
			// 最適化レベルを設定する
#if defined(DEBUG) || defined(_DEBUG)
			flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL0;
#else
			flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif

			if (FAILED(D3DCompileFromFile(
				sNewPath, nullptr, nullptr, funcname.c_str(), shaderModel.c_str(), flag1, 0, &blob, nullptr)))
				throw;
			return std::shared_ptr<ID3DBlob>(blob, ReleaseIUnknown);
		}
		std::shared_ptr<ID3D11VertexShader> CreateVertexShader(ID3DBlob* blob)
		{
			ID3D11VertexShader* vs;

			if (FAILED(GetDevice()->CreateVertexShader((BYTE*)blob->GetBufferPointer(),
				blob->GetBufferSize(), NULL, &vs)))
				throw;
			return std::shared_ptr<ID3D11VertexShader>(vs, ReleaseIUnknown);
		}
		std::shared_ptr<ID3D11GeometryShader> CreateGeometryShader(ID3DBlob* blob)
		{
			ID3D11GeometryShader* gs;

			if (FAILED(GetDevice()->CreateGeometryShader((BYTE*)blob->GetBufferPointer(),
				blob->GetBufferSize(), NULL, &gs)))
				throw;
			return std::shared_ptr<ID3D11GeometryShader>(gs, ReleaseIUnknown);
		}
		std::shared_ptr<ID3D11PixelShader> CreatePixelShader(ID3DBlob* blob)
		{
			ID3D11PixelShader* ps;

			if (FAILED(GetDevice()->CreatePixelShader((BYTE*)blob->GetBufferPointer(),
				blob->GetBufferSize(), NULL, &ps)))
				throw;
			return std::shared_ptr<ID3D11PixelShader>(ps, ReleaseIUnknown);
		}
	}
}