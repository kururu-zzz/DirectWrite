#include "EffectObject.h"
#include "../../System/Base/Camera.h"

void EffectObject::SetPos(const XMFLOAT3& pos)
{
	_pos.X = pos.x;
	_pos.Y = pos.y;
	_pos.Z = pos.z;
}

void EffectObject::SetRotate(const XMFLOAT3& angle)
{
	_angle.X = angle.x;
	_angle.Y = angle.y;
	_angle.Z = angle.z;
}

void EffectObject::SetScale(const XMFLOAT3& scale)
{
	_scale.X = scale.x;
	_scale.Y = scale.y;
	_scale.Z = scale.z;
}

void EffectObject::SetSpeed(const float speed)
{
	_playSpd = speed;
}

void EffectObject::SetLoop(bool loopFlag)
{
	_loopFlag = loopFlag;
}

void EffectObject::Draw(::Effekseer::Manager* manager,::Effekseer::Effect* effect)
{
	if (_playingFlag)
	{
		if (_handle == -1 && !manager->Exists(_handle))
			_handle = manager->Play(effect, _pos.X, _pos.Y, _pos.Z);
		if (!_pauseFlag)
		{
			manager->BeginUpdate();
			manager->SetSpeed(_handle,_playSpd);
			manager->SetLocation(_handle, _pos);
			manager->SetRotation(_handle, XMConvertToRadians(_angle.X), XMConvertToRadians(_angle.Y), XMConvertToRadians(_angle.Z));
			manager->SetScale(_handle, _scale.X, _scale.Y, _scale.Z);
			manager->UpdateHandle(_handle);
			manager->EndUpdate();
		}
		manager->DrawHandle(_handle);
	}
	else
	{
		if (_handle != -1)
		{
			manager->StopEffect(_handle);
			_handle = -1;
		}
	}
	manager->SetShown(_handle, _playingFlag && _shownFlag);
	_playingFlag = manager->Exists(_handle);
	if (_loopFlag && !_playingFlag && _handle != -1)
	{
		_playingFlag = true;
		_handle = -1;
	}
}

void EffectObject::Play()
{
	_playingFlag = true;
	_shownFlag = true;
	_pauseFlag = false;
}

void EffectObject::Stop()
{
	_playingFlag = false;
}

void EffectObject::Pause(bool shownFlag)
{
	_shownFlag = shownFlag;
	_pauseFlag = true;
}