#ifndef __CAMERAANIMATION__
#define __CAMERAANIMATION__

#include <vector>
#include <memory>
#include <unordered_map>
#include <fbxsdk.h>
#include "../../System/Base/DXMath.h"


namespace fbx
{
	class CameraAnimation
	{
	private:
		std::shared_ptr<FbxScene> _scene;
		std::shared_ptr<FbxAnimStack> _animStack;
		std::shared_ptr<FbxCamera> _camera;
		std::pair<FbxTime, FbxTime> _animationFrame;
		DirectX::XMFLOAT4X4 _matView,_matProjection;
		FbxTime _currentFrame;
	public:
		void Init(const std::shared_ptr<FbxScene>& scene);
		void UpdateMatrix(int frame);
		void GetCameraPos(DirectX::XMFLOAT3* pos);
		void GetCameraFocus(DirectX::XMFLOAT3* focus);
		void GetViewMatrix(DirectX::XMFLOAT4X4* view){ *view = _matView; }
		void GetProjectionMatrix(DirectX::XMFLOAT4X4* projection){ *projection = _matProjection; };
		void SetFrame(int frame);
	};
}
#endif