#include "Camera.h"
#include "../Matrix/ConstantBufferManager.h"
#include "Device.h"
#include "../Loader/fbxResource.h"

using namespace DirectX;

namespace DX11
{
	void Camera::Init(const XMFLOAT3& pos,const XMFLOAT3& focus,const XMFLOAT2& screenSize)
	{
		_pos = pos;
		_focus = focus;

		_qua.x = _qua.z = 0;
		_qua.y = 1;

		RockOnFlag = false;

		screenAspect = screenSize.x / screenSize.y;

		XMStoreFloat4x4(&_cameraBuf.matView,
			XMMatrixTranspose(
			XMMatrixLookAtLH(
			XMLoadFloat3(&_pos),	//カメラの位置
			XMLoadFloat3(&_focus),	//カメラが注目する座標
			XMLoadFloat3(&_qua))));	//カメラの上向きを設定するベクトル

		XMStoreFloat4x4(&_cameraBuf.matProjection,
			XMMatrixTranspose(
			XMMatrixPerspectiveFovLH(
			XMConvertToRadians(ProjectionDegree),//画面の近さ
			screenAspect,		//画面の縦横比を設定
			10.0f,
			15000.0f)));

		_cameraBuf.matViewPort._11 = 2.f / screenSize.x;
		_cameraBuf.matViewPort._22 = -2.0f / screenSize.y;
		_cameraBuf.matViewPort._41 = -1.f;
		_cameraBuf.matViewPort._42 = 1.0f;

		XMStoreFloat4x4(&_cameraBuf.matViewPort, XMMatrixTranspose(XMLoadFloat4x4(&_cameraBuf.matViewPort)));

	}

	const ConstantBuffer::cCameraBuffer& Camera::GetBuffer(){
		_cameraBuf.eyePos = XMFLOAT4(_pos.x, _pos.y, _pos.z, 1.0f);
		return _cameraBuf;
	}

	void Camera::SetCam(const XMFLOAT3& pos, const XMFLOAT3& focus)
	{
		_pos = pos;
		_focus = focus;
		if ((_pos.x == _focus.x) && (_pos.y == _focus.y) && (_pos.z == _focus.z))//LookAtLH用の補正
			_pos.z += 0.01f;
		XMStoreFloat4x4(&_cameraBuf.matView,
			XMMatrixTranspose(
			XMMatrixLookAtLH(
			XMLoadFloat3(&_pos),	//カメラの位置
			XMLoadFloat3(&_focus),	//カメラが注目する座標
			XMLoadFloat3(&_qua))));	//カメラの上向きを設定するベクトル
	}



	void Camera::SetPos(const XMFLOAT3& pos)
	{
		_pos = pos;
		if ((_pos.x == _focus.x) && (_pos.y == _focus.y) && (_pos.z == _focus.z))//LookAtLH用の補正
			_pos.z += 0.01f;
		XMStoreFloat4x4(&_cameraBuf.matView,
			XMMatrixTranspose(
			XMMatrixLookAtLH(
			XMLoadFloat3(&_pos),	//カメラの位置
			XMLoadFloat3(&_focus),	//カメラが注目する座標
			XMLoadFloat3(&_qua))));	//カメラの上向きを設定するベクトル
	}

	void Camera::SetFocus(const XMFLOAT3& focus)
	{
		_focus = focus;
		if ((_pos.x == _focus.x) && (_pos.y == _focus.y) && (_pos.z == _focus.z))//LookAtLH用の補正
			_pos.z += 0.01f;
		XMStoreFloat4x4(&_cameraBuf.matView,
			XMMatrixTranspose(
			XMMatrixLookAtLH(
			XMLoadFloat3(&_pos),	//カメラの位置
			XMLoadFloat3(&_focus),	//カメラが注目する座標
			XMLoadFloat3(&_qua))));	//カメラの上向きを設定するベクトル
	}

	void Camera::SetOrtho(const XMFLOAT3& eyePos)
	{
		XMFLOAT4X4 matLightProjection,matLightView;
		XMStoreFloat4x4(&matLightProjection, XMMatrixIdentity());
		XMStoreFloat4x4(&matLightProjection, XMMatrixOrthographicLH(60.f, 45.f, 1.f, 1000.f));
		XMStoreFloat4x4(&matLightView, XMMatrixIdentity());
		//if (eyePos.z == 0)eyePos.z = 0.01f;
		XMStoreFloat4x4(&matLightView, XMMatrixLookAtLH(
			XMLoadFloat3(&XMFLOAT3(eyePos.x * 1.0f, eyePos.y * 1.0f, eyePos.z * 1.0f)),
			XMLoadFloat3(&XMFLOAT3(0, 0, 0)),
			XMLoadFloat3(&XMFLOAT3(0.f, 1.f, 0.f))));
		XMStoreFloat4x4(&_cameraBuf.matLVP, XMMatrixTranspose(XMLoadFloat4x4(&matLightView)*XMLoadFloat4x4(&matLightProjection)));
	}

	void Camera::SetOrtho(const XMFLOAT3& eyePos, const XMFLOAT3& focus)
	{
		XMFLOAT4X4 matLightProjection, matLightView;
		XMStoreFloat4x4(&matLightProjection, XMMatrixIdentity());
		XMStoreFloat4x4(&matLightProjection, XMMatrixOrthographicLH(1500.f, 1500.f, 1.f, 10000.f));
		XMStoreFloat4x4(&matLightView, XMMatrixIdentity());
		//if (eyePos.z == 0)eyePos.z = 0.01f;
		XMStoreFloat4x4(&matLightView, XMMatrixLookAtLH(
			XMLoadFloat3(&XMFLOAT3(eyePos.x, eyePos.y, eyePos.z)),
//			XMLoadFloat3(&XMFLOAT3(eyePos.x + focus.x, eyePos.y + focus.y, eyePos.z + focus.z)),
			XMLoadFloat3(&focus),
			XMLoadFloat3(&XMFLOAT3(0.f, 1.f, 0.f))));
		XMStoreFloat4x4(&_cameraBuf.matLVP, XMMatrixTranspose(XMLoadFloat4x4(&matLightView)*XMLoadFloat4x4(&matLightProjection)));
	}

	void Camera::RockOn(const XMFLOAT3& newFocus)
	{
		float rockSpd = 10.0f;
		XMFLOAT3 spd = XMFLOAT3(0.f,0.f,0.f);
		_pos = newFocus - _focus;
		spd.x /= rockSpd; spd.y /= rockSpd; spd.z /= rockSpd;
		_focus = _focus + spd;
	}
	bool Camera::CheckInScreen(const XMFLOAT3& pos)
	{
		XMFLOAT3 Out;
		XMStoreFloat3(&Out, XMVector3Transform(XMLoadFloat3(&pos), XMLoadFloat4x4(&_cameraBuf.matView)));
		XMStoreFloat3(&Out, XMVector3Transform(XMLoadFloat3(&Out), XMLoadFloat4x4(&_cameraBuf.matProjection)));
		Out.x /= Out.z; Out.y /= Out.z; Out.z /= Out.z;
		if ((fabs(Out.x) <= 1.2f) && (fabs(Out.y) <= 1.2f))
			return true;
		return false;
	}

}