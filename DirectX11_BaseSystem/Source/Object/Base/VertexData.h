#ifndef __VERTEXDATA__
#define __VERTEXDATA__

#include <array>
#include <algorithm>
#include <windef.h>

#include "../../System/Base/DXMath.h"

namespace Vertex
{
	struct SkinMeshVertex{
		DirectX::XMFLOAT3 pos;
		uint32_t color;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 texel;
		std::array<uint8_t,4> boneIndex;
		DirectX::XMFLOAT4 boneWeight;
		bool operator < (const SkinMeshVertex& v) const {
			return std::memcmp(this, &v, sizeof(SkinMeshVertex)) < 0;
		}
		SkinMeshVertex()
		{
			pos = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
			color = 0;
			normal = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
			texel = DirectX::XMFLOAT2(0.f, 0.f);
			std::for_each(boneIndex.begin(), boneIndex.end(), [](uint8_t i)
			{
				i = 0;
			});
			boneWeight = DirectX::XMFLOAT4(0.f, 0.f, 0.f, 0.f);
		}
	};
	struct DefaultVertex{
		DirectX::XMFLOAT3 pos;
		uint32_t color;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 texel;
		bool operator < (const DefaultVertex& v) const {
			return std::memcmp(this, &v, sizeof(DefaultVertex)) < 0;
		}
		DefaultVertex()
		{
			pos = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
			color = 0;
			normal = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
			texel = DirectX::XMFLOAT2(0.f, 0.f);
		}
	};
}

#endif