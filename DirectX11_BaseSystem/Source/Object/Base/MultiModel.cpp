#include "MultiModel.h"
#include "../../System/Matrix/ConstantBufferManager.h"
#include "../../System/Base/Shader.h"

using namespace DirectX;

namespace DX11
{
	MultiModel::MultiModel()
	{
		Init();
	}

	//マップ全初期化
	void MultiModel::Init()
	{
		modelContainer.clear();
		modelIndexMap.clear();
		modelNumContainer.clear();
		modelPosContainer.clear();
	}

	void MultiModel::Insert(const XMFLOAT3& pos, const std::string& modelName)
	{
		if (modelIndexMap.find(modelName) != modelIndexMap.end())
		{
			int index = modelIndexMap.at(modelName);
			modelNumContainer.at(index) += 1;
			XMFLOAT4X4 mat;
			XMStoreFloat4x4(&mat, XMMatrixTranspose(XMMatrixTranslation(pos.x, pos.y, pos.z)));
			modelPosContainer.at(index).emplace_back(mat);
		}
		else
		{
			modelIndexMap.emplace(modelName, modelIndexMap.size());
			int index = modelIndexMap.at(modelName);
			modelContainer.emplace_back(std::make_shared<Model>());
			modelContainer.at(index)->Init(XMFLOAT3(0.f,0.f,0.f),modelName);
			modelNumContainer.emplace_back(1);
			XMFLOAT4X4 mat;
			XMStoreFloat4x4(&mat, XMMatrixTranspose(XMMatrixTranslation(pos.x, pos.y, pos.z)));
			modelPosContainer.emplace_back(std::vector<XMFLOAT4X4>());
			modelPosContainer.at(index).emplace_back(mat);
		}
	}

	void MultiModel::Draw(ID3D11DeviceContext* deviceContext)
	{
		for (auto it : modelIndexMap)
		{
			int index = it.second;
			assert(world_buf.matWorld.size() >= static_cast<unsigned int>(modelNumContainer.at(index)));
			std::copy(modelPosContainer.at(index).begin(), modelPosContainer.at(index).end(), world_buf.matWorld.begin());
			ConstantBuffer::SetBuffer(deviceContext,world_buf, ConstantBuffer::cBufferSlot::World);
			modelContainer.at(index)->Draw(deviceContext,modelNumContainer.at(index));
		}
	}

}