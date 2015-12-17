#include "CameraAnimation.h"
#include <assert.h>

namespace fbx
{
	//Convert FbxAMatrix to XMMMatrix
	static DirectX::XMMATRIX convertFbx2XM(const FbxAMatrix & fbxAMtx) {
		DirectX::XMFLOAT4X4 xmMtx;
		for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) xmMtx.m[i][j] = static_cast<float>(fbxAMtx[i][j]);
		return DirectX::XMLoadFloat4x4(&xmMtx);
	}
	static DirectX::XMVECTOR ConvertVectorFbxToXM(const FbxVector4& vec)
	{
		return DirectX::XMVectorSet(-vec[0], vec[1], vec[2], vec[3]);
	}
	static void LoadAnimationFrame(const FbxTakeInfo* takeInfo,std::pair<FbxTime,FbxTime>* animationFrame)
	{
		auto importOffset = takeInfo->mImportOffset;
		auto startTime = takeInfo->mLocalTimeSpan.GetStart();
		auto stopTime = takeInfo->mLocalTimeSpan.GetStop();

		//Set AnimationFrame of Start and End
		animationFrame->first = (importOffset + startTime.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames24);
		animationFrame->second = (importOffset + stopTime.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames24);
	}

	static void LoadCamera(FbxScene* fbxScene,std::shared_ptr<FbxCamera>* camera)
	{
		auto nodeCount = fbxScene->GetMemberCount<FbxNode>();
		for (int i = 0; i < nodeCount; ++i)
		{
			auto node = fbxScene->GetNode(i);
			if (node->GetNodeAttribute() != nullptr && node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eCamera)
			{
				*camera = std::shared_ptr<FbxCamera>(static_cast<FbxCamera*>(node->GetNodeAttribute()), [](FbxCamera* p)
				{
					//p->Destroy();
				});
			}
		}
	}

	static void CreateViewProjectionMatrix(FbxCamera* camera,DirectX::XMFLOAT4X4* matView, DirectX::XMFLOAT4X4* matProjection,const FbxTime& frame)
	{
		auto pos = camera->EvaluatePosition(frame);
		auto focus = camera->EvaluateLookAtPosition(frame);
		auto up = camera->UpVector.Get();

		XMStoreFloat4x4(matView, DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH
			(
			DirectX::XMVectorSet(-pos[0], pos[1], pos[2], pos[3]),
			DirectX::XMVectorSet(-focus[0], focus[1], focus[2], focus[3]),
			DirectX::XMVectorSet(up[0], up[1], up[2], up[3])
			)));

		auto near = camera->GetNearPlane();
		auto far = camera->GetFarPlane();
		double inch_mm = 25.4;    // インチ→ミリ

		double filmHeight = camera->FilmHeight.Get();   // フィルム高（インチ）
		double focalLength = camera->FocalLength.Get(); // 合焦距離（ミリ）
		double filmHeight_mm = inch_mm * filmHeight;
		double fovY = atan2(filmHeight_mm, 2.0 * focalLength);
		double fovY_Degree = fovY * 180 / 3.14159265358979;

		auto aspect = camera->AspectWidth / camera->AspectHeight;

		XMStoreFloat4x4(matProjection, DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(fovY, aspect, near, far)));
	}

	void CameraAnimation::Init(const std::shared_ptr<FbxScene>& scene)
	{
		_scene = scene;
		LoadCamera(scene.get(), &_camera);

		SetFrame(_animationFrame.first.Get());

		CreateViewProjectionMatrix(_camera.get(),&_matView,&_matProjection,_currentFrame);
	}

	void CameraAnimation::UpdateMatrix(int frame)
	{
		SetFrame(frame);
		CreateViewProjectionMatrix(_camera.get(), &_matView, &_matProjection, _currentFrame);
	}

	void CameraAnimation::GetCameraPos(DirectX::XMFLOAT3* pos)
	{
		DirectX::XMStoreFloat3(pos,ConvertVectorFbxToXM(_camera->EvaluatePosition(_currentFrame)));
	}

	void CameraAnimation::GetCameraFocus(DirectX::XMFLOAT3* focus)
	{
		DirectX::XMStoreFloat3(focus, ConvertVectorFbxToXM(_camera->EvaluateLookAtPosition(_currentFrame)));
	}

	void CameraAnimation::SetFrame(int frame){
		if (frame <= 0)
		{
			frame = 1;
		}
		_currentFrame.Set(FbxTime::GetOneFrameValue(FbxTime::eFrames24) * static_cast<FbxLongLong>(frame));
	}
}