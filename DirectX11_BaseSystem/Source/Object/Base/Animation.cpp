#include "Animation.h"
#include <assert.h>

namespace fbx
{
	//Convert FbxAMatrix to XMMMatrix
	static DirectX::XMMATRIX convertFbx2XM(const FbxAMatrix & fbxAMtx) {
		DirectX::XMFLOAT4X4 xmMtx;
		for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) xmMtx.m[i][j] = static_cast<float>(fbxAMtx[i][j]);
		return DirectX::XMLoadFloat4x4(&xmMtx);
	}
	void LoadAnimationFrame(const FbxTakeInfo* takeInfo,std::pair<FbxTime,FbxTime>* animationFrame)
	{
		auto importOffset = takeInfo->mImportOffset;
		auto startTime = takeInfo->mLocalTimeSpan.GetStart();
		auto stopTime = takeInfo->mLocalTimeSpan.GetStop();

		//Set AnimationFrame of Start and End
		animationFrame->first = (importOffset + startTime.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames24);
		animationFrame->second = (importOffset + stopTime.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames24);
	}

	void Animation::SetFrame(int frame){
		if ((frame >= _animationFrame.first.Get()) && (frame <= _animationFrame.second.Get()))
			_currentFrame.Set(FbxTime::GetOneFrameValue(FbxTime::eFrames24) * static_cast<FbxLongLong>(frame));
	}
	float Animation::GetLayerWeight(const int index)
	{
		if (index < _animStack->GetMemberCount<FbxAnimLayer>())
		{
			auto animLayer = _animStack->GetMember<FbxAnimLayer>(index);
			return static_cast<float>(animLayer->Weight);
		}
		return 0.f;
	}

	void Animation::SetLayerWeight(const int index,float weight)
	{
		if (index < _animStack->GetMemberCount<FbxAnimLayer>())
		{
			auto animLayer = _animStack->GetMember<FbxAnimLayer>(index);
			animLayer->Weight = weight;
		}
	}

	void Animation::MuteLayer(const int index,bool flag)
	{
		if (index < _animStack->GetMemberCount<FbxAnimLayer>())
		{
			auto animLayer = _animStack->GetMember<FbxAnimLayer>(index);
			animLayer->Mute = flag;
		}
	}

	void Animation::GetLayerName(const int index,std::string* name)
	{
		if (index < _animStack->GetMemberCount<FbxAnimLayer>())
		{
			auto animLayer = _animStack->GetMember<FbxAnimLayer>(index);
			*name = std::string(animLayer->GetName());
		}
	}

	const std::vector<DirectX::XMFLOAT4X4>& Animation::GetBoneMatrix(int meshId)
	{
		auto currentFrame = _currentFrame.Get() / FbxTime::GetOneFrameValue(FbxTime::eFrames24);
		return matrixList.at(meshId).at(currentFrame);
	}

	void CalcBoneMatrix(
		int meshId,
		FbxScene* scene,
		const FbxTime& currentFrame,
		const std::unordered_map<int, DirectX::XMFLOAT4X4>& invBaseposeMatrixList,
		const std::unordered_map<std::string, int>& boneNodeNameList,
		std::vector<DirectX::XMFLOAT4X4>* outMatrixList
		)
	{
		auto fbxmesh = scene->GetMember<FbxMesh>(meshId);
		auto skin = static_cast<FbxSkin*>(fbxmesh->GetDeformer(0, FbxDeformer::eSkin));
		auto skinCount = fbxmesh->GetDeformerCount(FbxDeformer::eSkin);
		if (skinCount == 0)
		{
			DirectX::XMFLOAT4X4 mat;
			DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixIdentity());
			outMatrixList->emplace_back(mat);
			return;
		}
		auto clusterCount = skin->GetClusterCount();

		DirectX::XMFLOAT4X4 out;
		for (int i = 0; i < clusterCount; ++i)
		{
			auto boneNodeId = boneNodeNameList.at(skin->GetCluster(i)->GetLink()->GetName());
			auto boneNode = scene->GetNode(boneNodeId);
			auto boneMatrix = boneNode->EvaluateGlobalTransform(currentFrame);

			DirectX::XMStoreFloat4x4(&out, XMMatrixTranspose(DirectX::XMLoadFloat4x4(&invBaseposeMatrixList.at(boneNodeId))*convertFbx2XM(boneMatrix)));

			outMatrixList->emplace_back(out);
		}
	}

	Animation::Animation(
		FbxScene* scene, 
		const std::string& animationName,
		const int animationId,
		const std::unordered_map<int, DirectX::XMFLOAT4X4>& invBaseposeMatrixList, 
		const std::unordered_map<std::string, int>& boneNodeNameList)
	{
		_animStack = std::shared_ptr<FbxAnimStack>(scene->GetSrcObject<FbxAnimStack>(animationId), [](FbxAnimStack* p) {});

		LoadAnimationFrame(scene->GetTakeInfo(animationName.c_str()), &_animationFrame);

		SetFrame(_animationFrame.first.Get());

		auto meshNum = scene->GetMemberCount<FbxMesh>();
		matrixList.resize(meshNum);
		scene->SetCurrentAnimationStack(_animStack.get());
		for (int i = 0; i < meshNum; ++i)
		{
			auto& vector = matrixList.at(i);
			auto endFrame = _animationFrame.second.Get();
			vector.resize(endFrame + 1);
			for (int j = 0; j <= endFrame; ++j)
			{
				auto& outMatrixList = vector.at(j);
				SetFrame(j);
				CalcBoneMatrix(i,scene,_currentFrame,invBaseposeMatrixList,boneNodeNameList, &outMatrixList);
			}
		}
	}
}