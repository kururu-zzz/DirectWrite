#ifndef __ANIMATION__
#define __ANIMATION__

#include <vector>
#include <memory>
#include <unordered_map>
#include <fbxsdk.h>
#include "../../System/Base/DXMath.h"


namespace fbx
{
	class Animation
	{
	private:
		std::shared_ptr<FbxAnimStack> _animStack;
		std::pair<FbxTime, FbxTime> _animationFrame;
		std::vector<std::vector<std::vector<DirectX::XMFLOAT4X4>>> matrixList;
		FbxTime _currentFrame;
	public:
		Animation(
			FbxScene* scene,
			const std::string& animationName,
			const int animationId,
			const std::unordered_map<int, DirectX::XMFLOAT4X4>& invBaseposeMatrixList,
			const std::unordered_map<std::string, int>& boneNodeNameList);
		void SetFrame(int frame);
		void MuteLayer(const int index, bool flag);
		int GetLayerNum(){ return _animStack->GetMemberCount<FbxAnimLayer>(); }
		void SetLayerWeight(const int index, float weight);
		float GetLayerWeight(const int index);
		void GetLayerName(const int index,std::string* name);
		const std::vector<DirectX::XMFLOAT4X4>& GetBoneMatrix(int meshId);
	};
}
#endif