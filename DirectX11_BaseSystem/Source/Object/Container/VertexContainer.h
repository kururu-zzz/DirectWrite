#ifndef __VERTEXCONTAINER__
#define __VERTEXCONTAINER__

#include <unordered_map>
#include <memory>
#include <string>
#include <d3d11.h>
#include "../../System/Base/DXMath.h" 


namespace Vertex
{
	class VertexContainer
	{
	private:
		std::unordered_map<std::string, std::shared_ptr<ID3D11Buffer>> _vertexBufferMap;
		std::unordered_map<std::string, std::shared_ptr<ID3D11Buffer>> _indexBufferMap;
	private:
		VertexContainer(){}
		VertexContainer(const VertexContainer& rhs);
		VertexContainer& operator=(const VertexContainer& rhs);
	public:
		static VertexContainer* GetInstance()
		{
			static VertexContainer msp_instance;
			return &msp_instance;
		}
		void CreateVertex(const FbxMesh* fbxmesh);
		ID3D11Buffer* GetVertexBuffer(const std::string BufferName){ return _vertexBufferMap.at(BufferName).get(); }
		ID3D11Buffer* GetIndexBuffer(const std::string BufferName){ return _indexBufferMap.at(BufferName).get(); }
		bool SearchVertex(const std::string& nodeName){ return _vertexBufferMap.find(nodeName) != _vertexBufferMap.end(); };
		bool FindIndex(const std::string& nodeName){ return _indexBufferMap.find(nodeName) != _indexBufferMap.end(); };
	};

	inline bool SearchVertex(const std::string& nodeName)
	{
		return VertexContainer::GetInstance()->SearchVertex(nodeName);
	}

	inline void CreateVertex(const FbxMesh* fbxmesh)
	{
		return VertexContainer::GetInstance()->CreateVertex(fbxmesh);
	}

	inline ID3D11Buffer* GetVertexBuffer(const std::string& bufferName){
		return VertexContainer::GetInstance()->GetVertexBuffer(bufferName);
	}

	inline ID3D11Buffer* GetIndexBuffer(const std::string& bufferName){
		return VertexContainer::GetInstance()->GetIndexBuffer(bufferName);
	}

}
#endif