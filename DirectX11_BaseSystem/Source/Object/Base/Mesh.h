#ifndef _MESHCONTAINER
#define _MESHCONTAINER

#include <vector>
#include <fbxsdk.h>
#include <d3d11.h>

#include "../../System/Matrix/WorldMatrix.h"

namespace fbx
{
	namespace element
	{
		class Mesh : public DX11::WorldMatrix{
		public:
			Mesh(const DirectX::XMFLOAT3& pos, const FbxMesh* fbxMesh);
		private:
			std::string _nodeName;
			std::string _materialName;
			int _materialIndex;
			int _indexNum;
		public:
			void SetPos(const DirectX::XMFLOAT3& pos){ WorldMatrix::SetPos(pos); }
			void SetScale(const DirectX::XMFLOAT3& scale){ WorldMatrix::SetScale(scale); }
			void SetRotate(const DirectX::XMFLOAT3& angle){ WorldMatrix::SetRotate(angle); }
			void SetRotate(const DirectX::XMFLOAT4X4& angle){ WorldMatrix::SetRotate(angle); }

			const std::string& GetMaterialName() const{ return _materialName; }

			void Draw(ID3D11DeviceContext* deviceContext);
			void Draw(ID3D11DeviceContext* deviceContext,int instanceNum);
		};
	}
}
#endif