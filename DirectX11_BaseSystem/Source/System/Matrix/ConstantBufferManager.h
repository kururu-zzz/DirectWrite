#ifndef __CONSTANTBUFFERMANAGER__
#define __CONSTANTBUFFERMANAGER__

#include "../Base/Device.h"
#include <d3d11.h>
#include <bitset>

namespace DX11
{
	namespace ConstantBuffer
	{
		enum class cBufferSlot
		{
			World,
			Camera,
			Material,
			Light,
			Viewport,
			Bone,
			Variable,
		};
		template<typename T_n>
		std::shared_ptr<ID3D11Buffer> CreateConstantBuffer()
		{
			static std::shared_ptr<ID3D11Buffer> cbuf;
			if(cbuf==nullptr){
				ID3D11Buffer* cb;
				CreateBuffer(&cb, nullptr, sizeof(T_n), D3D11_CPU_ACCESS_WRITE, D3D11_BIND_CONSTANT_BUFFER);
				cbuf = std::shared_ptr<ID3D11Buffer>(cb, [](ID3D11Buffer* p){ p->Release(); });
			}
			return cbuf;
		}

		template<typename T_n>
		void SetBuffer(ID3D11DeviceContext* deviceContext, T_n data, cBufferSlot slotNum, const std::bitset<3>& setShaderBit = std::bitset<3>("111"))
		{
			ID3D11Buffer* cb = CreateConstantBuffer<T_n>().get();
			D3D11_MAPPED_SUBRESOURCE resource;
			auto hr = deviceContext->Map(cb, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
			if (SUCCEEDED(hr)) {
				auto param = (T_n*)(resource.pData);
				*param = data;

				deviceContext->Unmap(cb, 0);
			}
			auto setShaderFlagSet = setShaderBit.to_ulong();
			if ((setShaderFlagSet & 0x001) == 0x001)
				deviceContext->VSSetConstantBuffers(static_cast<int>(slotNum), 1, &cb);
			if ((setShaderFlagSet & 0x002) == 0x002)
				deviceContext->GSSetConstantBuffers(static_cast<int>(slotNum), 1, &cb);
			if ((setShaderFlagSet & 0x004) == 0x004)
				deviceContext->PSSetConstantBuffers(static_cast<int>(slotNum), 1, &cb);
		}
	}
}

#endif