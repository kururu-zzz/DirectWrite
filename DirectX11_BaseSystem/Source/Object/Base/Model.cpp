#include "Model.h"
#include "../../System/Matrix/ConstantBufferManager.h"
#include "../Container/ShaderResourceContainer.h"
#include <array>
#include <algorithm>

using namespace DirectX;

namespace DX11
{
	struct MaterialParam
	{
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT4 emissive;
		XMFLOAT4 specular;
	};
	struct BoneMatrix
	{
		std::array<XMFLOAT4X4,90> boneMat;
		BoneMatrix()
		{
			std::for_each(boneMat.begin(), boneMat.end(), [](XMFLOAT4X4& mat)
			{
				XMStoreFloat4x4(&mat, XMMatrixIdentity());
			});
		}
	};

	static std::unordered_map<std::string, std::vector<std::shared_ptr<fbx::Animation>>> animContainers;
	static std::unordered_map<std::string, std::unordered_map<std::string, int>> animIndexTables;

	MaterialParam GetMaterialParam(const fbx::element::Material* material)
	{
		MaterialParam param;
		param.ambient = XMFLOAT4(material->ambient.x, material->ambient.y, material->ambient.z, 1.f);
		param.diffuse = XMFLOAT4(material->diffuse.x, material->diffuse.y, material->diffuse.z, 1.f);
		param.emissive = XMFLOAT4(material->emissive.x, material->emissive.y, material->emissive.z, 1.f);
		param.specular = XMFLOAT4(material->specular.x, material->specular.y, material->specular.z, 1.f);
		return param;
	}
	void LoadMaterial(
		FbxScene* scene,
		std::vector<std::shared_ptr<fbx::element::Material>>* _materialContainer,
		std::unordered_map<std::string,int>* materialIndexTable
		)
	{
		auto materialCount = scene->GetMaterialCount();
		_materialContainer->reserve(materialCount);
		for (int i = 0; i < materialCount; ++i) {
			auto _material = fbx::element::LoadMaterial(scene->GetMaterial(i));
			_materialContainer->emplace_back(_material);
			materialIndexTable->emplace(_material->materialName, i);
		}
	}

	void LoadMesh(
		FbxScene* scene, 
		const XMFLOAT3& pos,
		std::vector<std::shared_ptr<fbx::element::Mesh>> *_meshContainer,
		std::map<std::string,int>* meshIndexTable
		)
	{
		auto meshCount = scene->GetMemberCount<FbxMesh>();
		_meshContainer->reserve(meshCount);
		for (int i = 0; i < meshCount; ++i) {
			_meshContainer->emplace_back(
				std::make_shared<fbx::element::Mesh>(pos, scene->GetMember<FbxMesh>(i))
				);
			auto meshName = scene->GetMember<FbxMesh>(i)->GetNode()->GetName();
			meshIndexTable->emplace(meshName,i);
		}
	}
	static DirectX::XMMATRIX convertFbx2XM(const FbxAMatrix & fbxAMtx) {
		DirectX::XMFLOAT4X4 xmMtx;
		for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) xmMtx.m[i][j] = static_cast<float>(fbxAMtx[i][j]);
		return DirectX::XMLoadFloat4x4(&xmMtx);
	}
	void CreateBaseposeMatrix(FbxScene* fbxScene, std::unordered_map<int, DirectX::XMFLOAT4X4>* invBaseposeMatrixList, std::unordered_map<std::string, int>* boneNodeNameList)
	{
		auto nodeCount = fbxScene->GetMemberCount<FbxNode>();
		for (int i = 0; i < nodeCount; ++i)
		{
			auto node = fbxScene->GetNode(i);
			if (node->GetNodeAttribute() != nullptr && node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
			{
				boneNodeNameList->emplace(node->GetName(), i);
				DirectX::XMFLOAT4X4 matrix;

				auto baseposeMatrix = node->EvaluateGlobalTransform().Inverse();
				DirectX::XMStoreFloat4x4(&matrix, convertFbx2XM(baseposeMatrix));
				invBaseposeMatrixList->emplace(i, matrix);
			}
		}
	}
	void LoadAnimation(
		std::shared_ptr<FbxScene>* scene,
		std::vector<std::shared_ptr<fbx::Animation>>* animContainer,
		std::unordered_map<std::string,int>* animIndexTable,
		std::unordered_map<int, DirectX::XMFLOAT4X4>* invBaseposeMatrixList, 
		std::unordered_map<std::string, int>* boneNodeNameList,
		const std::string& modelName
		)
	{
		if (animContainers.find(modelName) == animContainers.end())
		{
			auto animCount = (*scene)->GetMemberCount<FbxAnimStack>();
			auto animLayerCount = (*scene)->GetMemberCount<FbxAnimLayer>();
			if (animCount == 0)
				return;
			else
			{
				CreateBaseposeMatrix(scene->get(), invBaseposeMatrixList, boneNodeNameList);
			}
			std::vector<std::shared_ptr<fbx::Animation>> anims;
			std::unordered_map<std::string,int> animIndexes;
			anims.reserve(animCount);
			for (int i = 0; i < animCount; ++i)
			{
				auto animationName = (*scene)->GetMember<FbxAnimStack>(i)->GetName();
				animIndexes.emplace(std::pair<std::string, int>(animationName, i));
				anims.emplace_back(std::make_shared<fbx::Animation>(scene->get(),animationName,i,*invBaseposeMatrixList,*boneNodeNameList));
			}
			animContainers.emplace(modelName, anims);
			animIndexTables.emplace(modelName, animIndexes);
		}
		*animIndexTable = animIndexTables.at(modelName);
		*animContainer = animContainers.at(modelName);
	}

	void Model::Init(const XMFLOAT3& pos, const std::string& modelName){
		_pos = pos;

		auto scene = fbx::Resource::LoadModel(modelName);

		LoadMaterial(scene.get(), &_materialContainer,&_materialIndexTable);///< シーンに含まれるマテリアルの解析

		LoadMesh(scene.get(), pos, &_meshContainer,&_meshIndexTable);///< シーンに含まれるメッシュの解析

		LoadAnimation(&scene, &_animContainer, &_animIndexTable,&_invBaseposeMatrixList,&_boneNodeNameList,modelName);

		if (_animContainer.size() != 0)
		_currentAnimationName = _animIndexTable.begin()->first;
	}

	void Model::SetPos(const XMFLOAT3& pos){
		_pos = pos;
		for (auto& it : _meshContainer){
			it->SetPos(_pos);
		}
	}

	void Model::MovePos(const XMFLOAT3& spd)
	{
		_pos.x += spd.x;
		_pos.y += spd.y;
		_pos.z += spd.z;
		for (auto& it : _meshContainer){
			it->SetPos(_pos);
		}
	}

	void Model::SetScale(const XMFLOAT3& scale)
	{
		for (auto& it : _meshContainer){
			it->SetScale(scale);
		}
	}

	void Model::SetRotate(const XMFLOAT3& angle){
		_angle = angle;
		for (auto& it : _meshContainer)
			it->SetRotate(angle);
	}

	void Model::SetRotate(const XMFLOAT4X4& angle){
		for (auto& it : _meshContainer)
			it->SetRotate(angle);
	}

	std::shared_ptr<fbx::Animation> Model::AccessAnimation(const std::string& animationName)
	{
		auto animIndex = _animIndexTable.at(animationName);
		return AccessAnimation(animIndex);
	}

	std::shared_ptr<fbx::Animation> Model::AccessAnimation(int animIndex)
	{
		if (animIndex < _animContainer.size())
			return _animContainer.at(animIndex);
		return nullptr;
	}

	void Model::ApplyAnimation(const std::string& animationName)
	{
		_currentAnimationName = animationName;
	}

	void Model::ChangeTexture(const std::string& fileName)
	{
		CreateTexture(fileName);
		for (auto& meshInfo : _meshIndexTable)
		{
			auto meshId = meshInfo.second;
			auto& mesh = _meshContainer.at(meshId);
			auto& material = _materialContainer.at(_materialIndexTable.at(mesh->GetMaterialName()));
			material->diffuseTextureName = fileName;
		}
	}

	void Model::Draw(ID3D11DeviceContext* deviceContext)
	{
		std::shared_ptr<fbx::Animation> currentAnim;
		if (_animContainer.size() != 0)
			currentAnim = _animContainer.at(_animIndexTable.at(_currentAnimationName));

		for (auto& meshInfo : _meshIndexTable)
		{
			auto meshId = meshInfo.second;
			auto& mesh = _meshContainer.at(meshId);
			if (currentAnim != nullptr)
			{
				auto boneMat = currentAnim->GetBoneMatrix(meshId);
				static BoneMatrix out;
				std::copy(boneMat.begin(), boneMat.end(), out.boneMat.begin());
				DX11::ConstantBuffer::SetBuffer(deviceContext, out, ConstantBuffer::cBufferSlot::Bone);
			}
			auto& material = _materialContainer.at(_materialIndexTable.at(mesh->GetMaterialName()));
			DX11::ConstantBuffer::SetBuffer(deviceContext, GetMaterialParam(material.get()), DX11::ConstantBuffer::cBufferSlot::Material);
			SetTexture(deviceContext,material->diffuseTextureName);
			mesh->Draw(deviceContext);
		}
	}

	void Model::Draw(ID3D11DeviceContext* deviceContext,int InstanceNum)
	{
		auto currentAnim = _animContainer.at(_animIndexTable.at(_currentAnimationName));

		for (auto mesh : _meshContainer)
		{
			auto material = _materialContainer.at(_materialIndexTable.at(mesh->GetMaterialName()));
			//std::vector<XMFLOAT4X4> boneMat;
			//currentAnim->GetBoneMatrix(,,&boneMat);
			DX11::ConstantBuffer::SetBuffer(deviceContext, GetMaterialParam(material.get()), DX11::ConstantBuffer::cBufferSlot::Material);
			SetTexture(deviceContext,material->diffuseTextureName);
			mesh->Draw(deviceContext,InstanceNum);
		}
	}

	Model::~Model(){
	}
}