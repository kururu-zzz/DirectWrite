#ifndef __EFFECTOBJECT__
#define __EFFECTOBJECT__

#include "Effekseer.h"
#include "../../System/Base/DXMath.h" 
using namespace DirectX;
#include <string>

class EffectObject{
	std::string _effectName;
	::Effekseer::Handle	_handle = -1;
	::Effekseer::Vector3D _pos = ::Effekseer::Vector3D(0.f,0.f,0.f);
	::Effekseer::Vector3D _angle = ::Effekseer::Vector3D(0.f, 0.f, 0.f);
	::Effekseer::Vector3D _scale = ::Effekseer::Vector3D(1.f, 1.f, 1.f);
	float _playSpd = 1.f;
	bool _loopFlag = false;
	bool _playingFlag = false;
	bool _shownFlag = false;
	bool _pauseFlag = false;
public:
	EffectObject(const std::string& effectName) : _effectName(effectName){};
	void SetPos(const XMFLOAT3& pos);
	void SetRotate(const XMFLOAT3& angle);
	void SetScale(const XMFLOAT3& scale);
	void SetSpeed(const float speed);
	void SetFrame(const int frame);
	void SetLoop(bool loopFlag);//ÉãÅ[Évçƒê∂Ç∑ÇÈÇ©Çê›íË
	void ChangeEffect(const std::string& effectName){ _effectName = effectName; }
	XMFLOAT3 GetRotate(){ return XMFLOAT3(_angle.X, _angle.Y, _angle.Z ); }
	const std::string& GetEffectName(){ return _effectName; }
	void Draw(::Effekseer::Manager* manager, ::Effekseer::Effect* effect);
	bool IsPlay(){ return _playingFlag; }
	void Play();
	void Stop();
	void Pause(bool shownFlag);
	void PauseRelease() { _pauseFlag = false; _shownFlag = true; };
};

#endif