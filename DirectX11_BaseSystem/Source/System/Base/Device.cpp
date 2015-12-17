#include "Device.h"

namespace DX11
{
	void Device::Init(HWND* hWnd){
		UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT; // BGRA テクスチャ有効
#ifndef NDEBUG
		flags |= D3D11_CREATE_DEVICE_DEBUG; // Debug ビルドならエラー報告を有効
#endif
		ID3D11Device* device;
		//デバイスの生成
		if (FAILED(D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flags,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&device,
			nullptr,
			nullptr)))
			throw;
		_device = std::shared_ptr<ID3D11Device>(device, [](ID3D11Device* p)
		{
			p->Release();
		});
		_hWnd = hWnd;
	}

	DXGI_SAMPLE_DESC Device::GetMSAA()
	{
		//使用可能なMSAAを取得
		DXGI_SAMPLE_DESC MSAA;
		for (int i = 0; i <= 1; i++){
			UINT Quality;
			if (SUCCEEDED(GetDevice()->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, i, &Quality))){
				if (0 < Quality){
					MSAA.Count = i;
					MSAA.Quality = Quality - 1;
				}
			}
		}
		return MSAA;
	};



	HRESULT Device::CreateBuffer(ID3D11Buffer** pBuffer, void* pData, size_t size, UINT CPUAccessFlag, D3D11_BIND_FLAG BindFlag){
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.ByteWidth = size;
		desc.Usage = (CPUAccessFlag == 0) ? D3D11_USAGE_DEFAULT : D3D11_USAGE_DYNAMIC;
		desc.BindFlags = BindFlag;
		desc.CPUAccessFlags = CPUAccessFlag;
		if (BindFlag == D3D11_BIND_STREAM_OUTPUT)
			desc.BindFlags |= D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(subData));
		subData.pSysMem = pData;
		subData.SysMemPitch = 0;
		subData.SysMemSlicePitch = 0;
		HRESULT hr;
		if (subData.pSysMem == NULL)
		{
			hr = _device->CreateBuffer(&desc, NULL, pBuffer);
		}
		else{
			hr = _device->CreateBuffer(&desc, &subData, pBuffer);
		}
		if (FAILED(hr))
			throw;

		return S_OK;
	}
}