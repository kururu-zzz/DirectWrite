#ifndef __DXRESOURCE__
#define __DXRESOURCE__

#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "dwrite.lib" )

#include <Windows.h>
#include <d3d11_4.h>
#include <d2d1_3.h>
#include <dwrite_3.h>
#include <memory>
#include <string>

#include "DXMath.h"

#include <vector>

namespace DX11
{
	namespace Resource
	{
		std::shared_ptr<ID3D11DeviceContext> CreateDeviceContext();
		std::shared_ptr<IDXGIDevice1> CreateDXGI();
		std::shared_ptr<IDXGIAdapter> CreateAdapter(IDXGIDevice1* DXGI);
		std::shared_ptr<IDXGIFactory2> CreateFactory(IDXGIAdapter* adapter);
		std::shared_ptr<IDXGISwapChain1> CreateSwapChain(IDXGIDevice1* device);
		std::shared_ptr<ID3D11Texture2D> CreateBackBuffer(IDXGISwapChain* swapChain);
		std::shared_ptr<ID3D11RenderTargetView> CreateRenderTargetView(ID3D11Texture2D* backBuffer);
		std::shared_ptr<ID3D11Texture2D> CreateDepthBuffer(const DirectX::XMFLOAT2& bufferSize, UINT Count = 1, UINT Quality = 0);
		std::shared_ptr<ID3D11Texture2D> CreateDepthBuffer(IDXGISwapChain* swapChain);
		std::shared_ptr<ID3D11DepthStencilView> CreateDepthStencilView(ID3D11Texture2D* depthBuffer);
		std::shared_ptr<ID3D11RasterizerState> CreateRasterizer();
		std::shared_ptr<ID3D11DepthStencilState> CreateDepthStensil();
		std::shared_ptr<ID3D11Texture2D> CreateRenderTargetBuffer(const DirectX::XMFLOAT2& size, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
		std::shared_ptr<ID3D11ShaderResourceView> CreateShaderResourceView(const std::string& filename);
		std::shared_ptr<ID3D11ShaderResourceView> CreateShaderResourceView(ID3D11Texture2D* resourceBuffer, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
		std::shared_ptr<ID3D11SamplerState> CreateSampler();
		std::shared_ptr<ID3DBlob> CompileShaderFromFile(const std::string& filename, const std::string& funcname, const std::string& shaderModel);
		std::shared_ptr<ID3D11VertexShader> CreateVertexShader(ID3DBlob* blob);
		std::shared_ptr<ID3D11GeometryShader> CreateGeometryShader(ID3DBlob* blob);
		std::shared_ptr<ID3D11PixelShader> CreatePixelShader(ID3DBlob* blob);
		std::shared_ptr<ID3D11InputLayout> CreateLayout(ID3DBlob* vertexBlob);
		std::shared_ptr<ID2D1Factory3> CreateD2DFactory();
		std::shared_ptr<ID2D1Device> CreateD2D_Device(IDXGIDevice1* dxgiDevice);
		std::shared_ptr<ID2D1DeviceContext> CreateD2D_DeviceContext(ID2D1Device* device);
		std::shared_ptr<ID2D1Bitmap1> CreateBitmap(ID2D1Device* d2dDevice, IDXGISwapChain* swapChain, ID2D1DeviceContext* context);
		std::shared_ptr<IDWriteFactory> CreateDWriteFactory();
		std::shared_ptr<IDWriteTextFormat> CreateTextFormat(const float fontSize);
	}
}

#endif