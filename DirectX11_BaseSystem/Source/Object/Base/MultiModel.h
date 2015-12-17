#ifndef __MULTIMODEL__
#define __MULTIMODEL__

#include <unordered_map>
#include <map>
#include <memory>
#include <array>
#include <vector>
#include <d3d11.h>

#include "Model.h"

namespace DX11
{
	namespace ConstantBuffer
	{
		const int instanceMax = 500;
		struct cMultiWorldBuffer
		{
			std::array<DirectX::XMFLOAT4X4, instanceMax> matWorld;
			cMultiWorldBuffer()
			{
				std::for_each(matWorld.begin(), matWorld.end(), [](DirectX::XMFLOAT4X4 mat)
				{
					DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixIdentity());
				});
			}
		};
	}

	class MultiModel
	{
	private:
		ConstantBuffer::cMultiWorldBuffer world_buf;
		std::unordered_map<std::string, int> modelIndexMap;
		std::vector<std::shared_ptr<Model>> modelContainer;
		std::vector<int> modelNumContainer;
		std::vector<std::vector<DirectX::XMFLOAT4X4>> modelPosContainer;
	public:
		MultiModel();
		void Init();
		void Insert(const DirectX::XMFLOAT3& pos, const std::string& modelname);
		void Draw(ID3D11DeviceContext* deviceContext);
	};

}

#endif