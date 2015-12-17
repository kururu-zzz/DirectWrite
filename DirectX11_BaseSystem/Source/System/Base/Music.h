#ifndef __MUSIC__
#define __MUSIC__

#include <xact3.h>
#include <unordered_map>
#include <array>
#include <memory>
#include "ComUtil.h"

const std::array<std::string, 2> SoundKey = {
	"BGM",
	"SE",
};

typedef std::unordered_map<std::string, std::shared_ptr<IXACT3WaveBank>> um_WB;
typedef std::unordered_map<std::string, std::shared_ptr<IXACT3SoundBank>> um_SB;
typedef std::unordered_map<std::string, std::vector<std::shared_ptr<IXACT3Cue>>> um_Cue;
typedef std::unordered_map<std::string, std::shared_ptr<void>> um_void;

/**
*@brief XACT��p�������y�Ǘ��N���X
*
*�V���O���g��
*/
class Music{
	/*-----COM�̏�����(���������l������ԍŏ��ɐ錾)-----*/
	ComApartment com;
private:
	Music(){}
	Music(const Music& rhs);
	Music& operator=(const Music& rhs);
public:
	static Music* GetInstance(){
		static Music msp_instance;
		return &msp_instance;
	}
private:
	/*-----XACT�̕ϐ�-----*/

	std::shared_ptr<IXACT3Engine> Engine;
	um_void WBBuffer;///<������̓s����ABuffer�Q�͐�ɐ錾
	um_void SBBuffer;///<������̓s����ABuffer�Q�͐�ɐ錾
	um_WB WB;///<Buffer����ɐ錾
	um_SB SB;///<Buffer����ɐ錾
	um_Cue Cue;///<Buffer����ɐ錾
	bool MusicStop;
private:
	/*-----X3DAudio�̕ϐ�-----*/

	/*X3DAUDIO_HANDLE xact3dInstance;///<X3DAudio�̃n���h��
	X3DAUDIO_EMITTER m_Emitter;///<���𑗐M����ϐ�
	X3DAUDIO_LISTENER m_Listener;///<������M����ϐ�
	X3DAUDIO_DSP_SETTINGS DSPSettings;
	WAVEFORMATEXTENSIBLE format;*/

private:
	/*-----�ϐ������������֐��Q-----*/

	HRESULT CreateXACTEngine();///<Engine�̐���
	HRESULT CreateSoundBank();///<SoundBank�̐���
	HRESULT CreateWaveBank();///<WaveBank�̐���
	HRESULT Create3DSound();///<X3DAudio�ϐ��Q�̐���
	HRESULT CreateCue();///<Cue�̐���

public:
	/*-----����������֐��Q-----*/

	HRESULT Init();///<����������ԍŏ��ɐ�ΌĂԂ��ƁI�I
	void Destroy();///<�����������ԍŌ�ɐ�ΌĂԂ��ƁI�I

	/*-----X3DAudio�֐��Q-----*/
	/*void SetListenPos(XMFLOAT3 pos);///<Listener�̈ʒu��ݒ肷��
	void SetEmitPos(XMFLOAT3 pos);///<Emitter�̈ʒu��ݒ肷��
	*/
	/*-----XACT�֐��Q-----*/
	void Play(const std::string& CueName);///<�����Đ�
	void Stop(const std::string& CueName);///<�����X�g�b�v
	void Pause(const std::string& CueName);///<�����X�g�b�v
	void DoWork(){ Engine->DoWork(); }
	void SetCueVariable(const std::string& CueName, const std::string& VariableName, float Value);///<Cue�ϐ��ω�
	void SetGlobalVariable(const std::string& VariableName, float Value);///<XACT-Global�ϐ��ω�
	DWORD GetState(const std::string& CueName);
	void WorkNow(){ MusicStop = true; }
};

/**
*@brief XACT�̏��������s���֐��B�v���O�����̏��߂ɕK���ĂԂ��ƁB
*/
inline HRESULT XACTInitialize()
{
	return Music::GetInstance()->Init();
}
/**
*@brief XACT�̉���������s���֐��B�v���O�����̏I���ɕK���ĂԂ��ƁB
*/
inline void XACTDestroy()
{
	return Music::GetInstance()->Destroy();
}
/**
*@brief �����Đ�����֐��B�����ɁA�Ή�����Cue�̖��O��^���Ă��������B
*/
inline void PlayMusic(const std::string& CueName)
{
	Music::GetInstance()->Play(CueName);
}
/**
*@brief �����~����֐��B�����ɁA�Ή�����Cue�̖��O��^���Ă��������B
*/
inline void StopMusic(const std::string& CueName)
{
	Music::GetInstance()->Stop(CueName);
}
/**
*@brief �����ꎞ��~����֐��B�����ɁA�Ή�����Cue�̖��O��^���Ă��������B
*@brief PlayMusic�֐���Pause�����Ƃ��납��Đ����n�܂�܂��B
*/
inline void PauseMusic(const std::string& CueName)
{
	Music::GetInstance()->Pause(CueName);
}

/**
*@brief Cue�Ɋ��蓖�Ă��ϐ��ɒl��������֐��B
*@brief ��������Cue�̖��O�A��������Cue�ϐ��̖��O�A��O�����ɑ������l��^���Ă��������B
*/
inline void SetCueVariable(const std::string& CueName, const std::string& VariableName, float Value)
{
	Music::GetInstance()->SetCueVariable(CueName, VariableName, Value);
}

/**
*@brief XACT��Global�ȕϐ��ɒl��������֐��B
*@brief ��������Global�ϐ��̖��O�A�������ɑ������l��^���Ă��������B
*/
inline void SetGlobalVariable(const std::string& VariableName, float Value)
{
	Music::GetInstance()->SetGlobalVariable(VariableName, Value);
}

/*inline void Apply3DSound(const std::string& CueName, XMFLOAT3 ListenerPos, XMFLOAT3 EmitterPos)
{
	Music::GetInstance()->SetEmitPos(EmitterPos);
	Music::GetInstance()->SetListenPos(ListenerPos);
	Music::GetInstance()->Calculate3DSound();
	Music::GetInstance()->Apply3DSound(CueName);
}*/

inline DWORD GetMusicState(const std::string& CueName)
{
	return Music::GetInstance()->GetState(CueName);
}

inline void DoWork()
{
	Music::GetInstance()->DoWork();
}

inline void WorkNow()
{
	Music::GetInstance()->WorkNow();
}

#endif