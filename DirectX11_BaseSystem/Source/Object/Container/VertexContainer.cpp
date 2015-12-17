#include <vector>
#include <map>
#include <fbxsdk.h>

#include "VertexContainer.h"
#include "../Base/VertexData.h"
#include "../Container/ShaderResourceContainer.h"
#include "../../System/Base/Device.h"

using namespace DirectX;

namespace Vertex
{
	struct ModelBoneWeight
	{
		uint32_t boneIndex[4];
		DirectX::XMFLOAT4 boneWeight;
	};

	void EmplaceBufferMap(void* data, const size_t datasize, const std::string nodename, D3D11_BIND_FLAG flag, std::unordered_map<std::string, std::shared_ptr<ID3D11Buffer>>& bufferMap)
	{
		ID3D11Buffer* buffer;
		auto hr = DX11::CreateBuffer(&buffer, data, datasize, D3D11_CPU_ACCESS_WRITE, flag);
		assert(SUCCEEDED(hr));
		
		bufferMap.emplace(std::pair<std::string, std::shared_ptr<ID3D11Buffer>>(nodename, std::shared_ptr<ID3D11Buffer>(buffer, [](ID3D11Buffer* p){
			p->Release();
		})));
	}
	void CreateIndexList(const FbxMesh* fbxmesh,std::vector<int>* indexList)
	{
		auto polygonCount = fbxmesh->GetPolygonCount();

		indexList->reserve(polygonCount * 3);

		for (int i = 0; i < polygonCount; ++i) {
			indexList->emplace_back(fbxmesh->GetPolygonVertex(i, 0));
			indexList->emplace_back(fbxmesh->GetPolygonVertex(i, 1));
			indexList->emplace_back(fbxmesh->GetPolygonVertex(i, 2));
		}
	}

	void CreatePositionList(const FbxMesh* fbxmesh, const std::vector<int>* indexList, std::vector<XMFLOAT3>* positionList)
	{
		positionList->reserve(indexList->size());

		for (auto index : *indexList) {
			auto controlPoint = fbxmesh->GetControlPointAt(index);
			positionList->emplace_back(XMFLOAT3(static_cast<float>(controlPoint[0]), static_cast<float>(controlPoint[1]), static_cast<float>(controlPoint[2])));

			assert(static_cast<float>(controlPoint[3]) == 0.0);
		}
	}

	void CreateNormalList(const FbxMesh* fbxmesh, const std::vector<int>* indexList, std::vector<XMFLOAT3>* normalList)
	{
		auto elementCount = fbxmesh->GetElementNormalCount();

		// �@���v�f��1�̂ݑΉ�
		assert(elementCount == 1);

		auto element = fbxmesh->GetElementNormal();
		auto mappingMode = element->GetMappingMode();
		auto referenceMode = element->GetReferenceMode();
		const auto& indexArray = element->GetIndexArray();
		const auto& directArray = element->GetDirectArray();

		// eDirct��eIndexDirect�̂ݑΉ�
		assert((referenceMode == FbxGeometryElement::eDirect) || (referenceMode == FbxGeometryElement::eIndexToDirect));

		normalList->reserve(indexList->size());

		if (mappingMode == FbxGeometryElement::eByControlPoint)
		{
			// �R���g���[���|�C���g�Ń}�b�s���O
			for (auto index : *indexList)
			{
				auto normalIndex = (referenceMode == FbxGeometryElement::eDirect)
					? index
					: indexArray.GetAt(index);
				auto normal = directArray.GetAt(normalIndex);
				normalList->push_back(
					XMFLOAT3(
						static_cast<float>(normal[0]),
						static_cast<float>(normal[1]),
						static_cast<float>(normal[2])));

			}
		}
		else if (mappingMode == FbxGeometryElement::eByPolygonVertex)
		{
			// �|���S���o�[�e�b�N�X�i�C���f�b�N�X�j�Ń}�b�s���O
			auto indexByPolygonVertex = 0;
			auto polygonCount = fbxmesh->GetPolygonCount();
			for (int i = 0; i < polygonCount; ++i)
			{
				auto polygonSize = fbxmesh->GetPolygonSize(i);

				for (int j = 0; j < polygonSize; ++j)
				{
					auto normalIndex = (referenceMode == FbxGeometryElement::eDirect)
						? indexByPolygonVertex
						: indexArray.GetAt(indexByPolygonVertex);
					auto normal = directArray.GetAt(normalIndex);

					normalList->push_back(
						XMFLOAT3(
							static_cast<float>(normal[0]),
							static_cast<float>(normal[1]), 
							static_cast<float>(normal[2])));


					++indexByPolygonVertex;
				}

			}
		}
		else
		{
			// ����ȊO�̃}�b�s���O���[�h�ɂ͑Ή����Ȃ�
			assert(false);
		}
	}

	void CreateUVList(const FbxMesh* fbxmesh, const std::vector<int>* indexList, int UVNum, std::vector<XMFLOAT2>* uvList)
	{
		auto elementCount = fbxmesh->GetElementUVCount();
		if (UVNum + 1 > elementCount)
		{
			return;
		}

		auto element = fbxmesh->GetElementUV(UVNum);
		auto mappingMode = element->GetMappingMode();
		auto referenceMode = element->GetReferenceMode();
		const auto& indexArray = element->GetIndexArray();
		const auto& directArray = element->GetDirectArray();

		// eDirct��eIndexDirect�̂ݑΉ�
		assert((referenceMode == FbxGeometryElement::eDirect) || (referenceMode == FbxGeometryElement::eIndexToDirect));

		uvList->reserve(indexList->size());

		if (mappingMode == FbxGeometryElement::eByControlPoint)
		{
			// �R���g���[���|�C���g�Ń}�b�s���O
			for (auto index : *indexList)
			{
				auto uvIndex = (referenceMode == FbxGeometryElement::eDirect)
					? index
					: indexArray.GetAt(index);
				auto uv = directArray.GetAt(uvIndex);
				uvList->push_back(XMFLOAT2(static_cast<float>(uv[0]), static_cast<float>(uv[1])));
			}
		}
		else if (mappingMode == FbxGeometryElement::eByPolygonVertex)
		{
			// �|���S���o�[�e�b�N�X�i�C���f�b�N�X�j�Ń}�b�s���O
			auto indexByPolygonVertex = 0;
			auto polygonCount = fbxmesh->GetPolygonCount();
			for (int i = 0; i < polygonCount; ++i)
			{
				auto polygonSize = fbxmesh->GetPolygonSize(i);

				for (int j = 0; j < polygonSize; ++j)
				{
					auto uvIndex = (referenceMode == FbxGeometryElement::eDirect)
						? indexByPolygonVertex
						: indexArray.GetAt(indexByPolygonVertex);
					auto uv = directArray.GetAt(uvIndex);

					uvList->push_back(XMFLOAT2(static_cast<float>(uv[0]), static_cast<float>(uv[1])));

					++indexByPolygonVertex;
				}

			}
		}
		else
		{
			// ����ȊO�̃}�b�s���O���[�h�ɂ͑Ή����Ȃ�
			assert(false);
		}
	}
	void CreateWeightList(const FbxMesh* fbxmesh, const std::vector<int>* indexList, std::vector<ModelBoneWeight>* boneWeightList)
	{
		auto skinCount = fbxmesh->GetDeformerCount(FbxDeformer::eSkin);
		if (skinCount == 0)
		{
			return;
		}

		// �X�L����1�����Ή����Ȃ�
		assert(skinCount <= 1);

		auto controlPointsCount = fbxmesh->GetControlPointsCount();
		using TmpWeight = std::pair<int, float>;
		std::vector<std::vector<TmpWeight>> tmpBoneWeightList(controlPointsCount);

		auto skin = static_cast<FbxSkin*>(fbxmesh->GetDeformer(0, FbxDeformer::eSkin));
		auto clusterCount = skin->GetClusterCount();

		for (int i = 0; i < clusterCount; ++i)
		{
			auto cluster = skin->GetCluster(i);

			// eNormalize�����Ή����Ȃ�
			assert(cluster->GetLinkMode() == FbxCluster::eNormalize);

			auto indexCount = cluster->GetControlPointIndicesCount();
			auto indices = cluster->GetControlPointIndices();
			auto weights = cluster->GetControlPointWeights();

			for (int j = 0; j < indexCount; ++j)
			{
				auto controlPointIndex = indices[j];
				tmpBoneWeightList[controlPointIndex].push_back({ i, static_cast<float>(weights[j]) });
			}
		}

		// �R���g���[���|�C���g�ɑΉ������E�F�C�g���쐬
		std::vector<ModelBoneWeight> boneWeightListControlPoints;
		for (auto& tmpBoneWeight : tmpBoneWeightList)
		{
			if (tmpBoneWeight.size() > 0)
			{
				// �E�F�C�g�̑傫���Ń\�[�g
				std::sort(tmpBoneWeight.begin(), tmpBoneWeight.end(),
					[](const TmpWeight& weightA, const TmpWeight& weightB){ return weightA.second > weightB.second; }
				//[](const TmpWeight& weightA, const TmpWeight& weightB){ return weightA.second < weightB.second; }
				);

				// 1���_��4��葽���E�F�C�g������U���Ă���Ȃ�e�������Ȃ����͖̂�������
				while (tmpBoneWeight.size() > 4)
				{
					tmpBoneWeight.pop_back();
				}

				// 4�ɖ����Ȃ��ꍇ�̓_�~�[��}��
				while (tmpBoneWeight.size() < 4)
				{
					tmpBoneWeight.push_back({ 0, 0.0f });
				}

				ModelBoneWeight weight;
				float total = 0.0f;
				for (int i = 0; i < 4; ++i)
				{
					weight.boneIndex[i] = tmpBoneWeight[i].first;
					total += tmpBoneWeight[i].second;
				}
				weight.boneWeight.x = tmpBoneWeight[0].second / total;
				weight.boneWeight.y = tmpBoneWeight[1].second / total;
				weight.boneWeight.z = tmpBoneWeight[2].second / total;
				weight.boneWeight.w = tmpBoneWeight[3].second / total;

				boneWeightListControlPoints.push_back(weight);
			}
			else
			{
				ModelBoneWeight weight;
				for (auto i : {0,1,2,3})
					weight.boneIndex[i] = 0;
				weight.boneWeight = XMFLOAT4(0.f, 0.f, 0.f, 0.f);
				boneWeightListControlPoints.push_back(weight);
			}
		}
		// �C���f�b�N�X�œW�J
		for (auto index : *indexList)
		{
			boneWeightList->push_back(boneWeightListControlPoints[index]);
		}
	}

	void VertexContainer::CreateVertex(const FbxMesh* fbxmesh)
	{
		// �C���f�b�N�X�o�b�t�@�擾
		std::vector<int> indexList;
		CreateIndexList(fbxmesh, &indexList);

		// �S�ēW�J������Ԃ̒��_�擾
		std::vector<XMFLOAT3> positionList;
		CreatePositionList(fbxmesh, &indexList, &positionList);

		std::vector<XMFLOAT3> normalList;
		CreateNormalList(fbxmesh, &indexList, &normalList);

		std::vector<XMFLOAT2> uv0List;
		CreateUVList(fbxmesh, &indexList, 0, &uv0List);

		std::vector<ModelBoneWeight> boneWeightList;
		CreateWeightList(fbxmesh, &indexList, &boneWeightList);

		// �O�̂��߃T�C�Y�`�F�b�N
		assert(indexList.size() == positionList.size());
		assert(indexList.size() == normalList.size());
		//assert((indexList.size() == boneWeightList.size()) || (boneWeightList.size() == 0));

		// ���_���C���^�[���[�u�h�A���C��
		std::vector<SkinMeshVertex> VertexList;
		for (unsigned int i = 0; i < indexList.size(); ++i) {
			SkinMeshVertex vertex;
			vertex.pos = positionList[i];
			vertex.normal = normalList[i];
			vertex.color = 0xffffffff;
			vertex.texel = (uv0List.size() == 0) ? XMFLOAT2(0.0f, 0.0f) : XMFLOAT2(uv0List[i].x, -uv0List[i].y);

			if (boneWeightList.size() > 0) {
				for (int j = 0; j < 4; ++j)
					vertex.boneIndex[j] = boneWeightList[i].boneIndex[j];
				vertex.boneWeight = boneWeightList[i].boneWeight;
			}
			else
			{
				for (int j = 0; j < 4; ++j)
					vertex.boneIndex[j] = 0;
				vertex.boneWeight = XMFLOAT4(0, 0, 0, 0);
			}

			VertexList.emplace_back(vertex);
		}

		// �d�����_�������ăC���f�b�N�X�쐬
		std::vector<SkinMeshVertex> modelVertexList;
		modelVertexList.reserve(VertexList.size());
		std::vector<int> modelIndexList;
		modelIndexList.reserve(indexList.size());

		std::map<SkinMeshVertex, int> exist; // �����������p
		for (auto& vertex : VertexList) {
			if (exist.count(vertex) == 0) {
				modelIndexList.emplace_back(modelVertexList.size());

				exist.emplace(vertex, modelVertexList.size());
				modelVertexList.emplace_back(vertex);
			}
			else {
				modelIndexList.emplace_back(exist[vertex]);
			}
		}

		auto nodeName = std::string(fbxmesh->GetNode()->GetName());
		EmplaceBufferMap((void*)modelVertexList.data(), sizeof(SkinMeshVertex)*modelVertexList.size(), nodeName, D3D11_BIND_VERTEX_BUFFER, _vertexBufferMap);///<���_�o�b�t�@�쐬
		EmplaceBufferMap((void*)modelIndexList.data(), sizeof(uint32_t)*modelIndexList.size(), nodeName, D3D11_BIND_INDEX_BUFFER, _indexBufferMap);///<�C���f�b�N�X�o�b�t�@�쐬
	}
}