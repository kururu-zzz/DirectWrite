#include "Mesh.h"
#include "../../System/Matrix/ConstantBufferManager.h"
#include "../Container/VertexContainer.h"
#include "VertexData.h"
#include <thread>

using namespace DirectX;

namespace fbx
{
	namespace element
	{

		Mesh::Mesh(const XMFLOAT3& pos, const FbxMesh* fbxmesh)
		{
			assert(fbxmesh != nullptr);

			SetPos(pos);
			_indexNum = fbxmesh->GetPolygonCount() * 3;

			auto node = fbxmesh->GetNode();

			_nodeName = std::string(node->GetName());
			_materialName = std::string(node->GetMaterial(0)->GetName());

			Vertex::CreateVertex(fbxmesh);
		}
		void Mesh::Draw(ID3D11DeviceContext* deviceContext){
			// VBのセット
			UINT SizeTbl[] = { sizeof(Vertex::SkinMeshVertex) };
			UINT OffsetTbl[] = { 0 };
			ID3D11Buffer* pBufferTbl[] = { Vertex::GetVertexBuffer(_nodeName) };
			deviceContext->IASetVertexBuffers(0, 1, pBufferTbl, SizeTbl, OffsetTbl);
			// IBのセット
			deviceContext->IASetIndexBuffer(Vertex::GetIndexBuffer(_nodeName), DXGI_FORMAT_R32_UINT, 0);

			deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			SetWorldBuffer(deviceContext);

			deviceContext->DrawIndexed(_indexNum, 0, 0);
		}

		void Mesh::Draw(ID3D11DeviceContext* deviceContext,int instanceNum){
			// VBのセット
			UINT SizeTbl[] = { sizeof(Vertex::SkinMeshVertex) };
			UINT OffsetTbl[] = { 0 };
			ID3D11Buffer* pBufferTbl[] = { Vertex::GetVertexBuffer(_nodeName) };
			deviceContext->IASetVertexBuffers(0, 1, pBufferTbl, SizeTbl, OffsetTbl);
			// IBのセット
			deviceContext->IASetIndexBuffer(Vertex::GetIndexBuffer(_nodeName), DXGI_FORMAT_R32_UINT, 0);

			deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			deviceContext->DrawIndexedInstanced(_indexNum, instanceNum, 0, 0, 0);
		}
	}
}