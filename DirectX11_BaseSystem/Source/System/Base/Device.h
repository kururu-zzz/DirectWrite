#ifndef __DEVICE__
#define __DEVICE__

#include <d3d11.h>
#include <memory>

namespace DX11
{
	class Device{
	private:
		std::shared_ptr<ID3D11Device> _device = nullptr;
		HWND* _hWnd;
	private:
		Device(){};
		Device(const Device& rhs);
		Device& operator=(const Device& rhs);
	public:
		static Device* GetInstance(){
			static Device msp_instance;
			return &msp_instance;
		}
		ID3D11Device* GetDevice(){ return _device.get(); }
		HWND* GetHWND(){ return _hWnd; }
		DXGI_SAMPLE_DESC GetMSAA();

	public:
		void Init(HWND* hWnd);
		void Destroy();

		HRESULT CreateBuffer(ID3D11Buffer** pBuffer, void* pData, size_t size, UINT CPUAccessFlag, D3D11_BIND_FLAG BindFlag);
	};
	inline void InitDevice(HWND* hWnd)
	{
		DX11::Device::GetInstance()->Init(hWnd);
	}
	inline ID3D11Device* GetDevice(){
		return DX11::Device::GetInstance()->GetDevice();
	}
	inline HRESULT CreateBuffer(ID3D11Buffer** pBuffer, void* pData, size_t size, UINT CPUAccessFlag, D3D11_BIND_FLAG BindFlag){
		return DX11::Device::GetInstance()->CreateBuffer(pBuffer, pData, size, CPUAccessFlag, BindFlag);
	}
	inline HWND* GetHWND(){
		return DX11::Device::GetInstance()->GetHWND();
	}
	inline DXGI_SAMPLE_DESC GetMSAA(){
		return DX11::Device::GetInstance()->GetMSAA();
	}
}
#endif