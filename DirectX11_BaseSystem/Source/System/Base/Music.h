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
*@brief XACTを用いた音楽管理クラス
*
*シングルトン
*/
class Music{
	/*-----COMの初期化(処理順を考慮し一番最初に宣言)-----*/
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
	/*-----XACTの変数-----*/

	std::shared_ptr<IXACT3Engine> Engine;
	um_void WBBuffer;///<解放順の都合上、Buffer群は先に宣言
	um_void SBBuffer;///<解放順の都合上、Buffer群は先に宣言
	um_WB WB;///<Bufferより後に宣言
	um_SB SB;///<Bufferより後に宣言
	um_Cue Cue;///<Bufferより後に宣言
	bool MusicStop;
private:
	/*-----X3DAudioの変数-----*/

	/*X3DAUDIO_HANDLE xact3dInstance;///<X3DAudioのハンドル
	X3DAUDIO_EMITTER m_Emitter;///<音を送信する変数
	X3DAUDIO_LISTENER m_Listener;///<音を受信する変数
	X3DAUDIO_DSP_SETTINGS DSPSettings;
	WAVEFORMATEXTENSIBLE format;*/

private:
	/*-----変数初期化生成関数群-----*/

	HRESULT CreateXACTEngine();///<Engineの生成
	HRESULT CreateSoundBank();///<SoundBankの生成
	HRESULT CreateWaveBank();///<WaveBankの生成
	HRESULT Create3DSound();///<X3DAudio変数群の生成
	HRESULT CreateCue();///<Cueの生成

public:
	/*-----初期化解放関数群-----*/

	HRESULT Init();///<初期化←一番最初に絶対呼ぶこと！！
	void Destroy();///<解放処理←一番最後に絶対呼ぶこと！！

	/*-----X3DAudio関数群-----*/
	/*void SetListenPos(XMFLOAT3 pos);///<Listenerの位置を設定する
	void SetEmitPos(XMFLOAT3 pos);///<Emitterの位置を設定する
	*/
	/*-----XACT関数群-----*/
	void Play(const std::string& CueName);///<音を再生
	void Stop(const std::string& CueName);///<音をストップ
	void Pause(const std::string& CueName);///<音をストップ
	void DoWork(){ Engine->DoWork(); }
	void SetCueVariable(const std::string& CueName, const std::string& VariableName, float Value);///<Cue変数変化
	void SetGlobalVariable(const std::string& VariableName, float Value);///<XACT-Global変数変化
	DWORD GetState(const std::string& CueName);
	void WorkNow(){ MusicStop = true; }
};

/**
*@brief XACTの初期化を行う関数。プログラムの初めに必ず呼ぶこと。
*/
inline HRESULT XACTInitialize()
{
	return Music::GetInstance()->Init();
}
/**
*@brief XACTの解放処理を行う関数。プログラムの終わりに必ず呼ぶこと。
*/
inline void XACTDestroy()
{
	return Music::GetInstance()->Destroy();
}
/**
*@brief 音を再生する関数。引数に、対応するCueの名前を与えてください。
*/
inline void PlayMusic(const std::string& CueName)
{
	Music::GetInstance()->Play(CueName);
}
/**
*@brief 音を停止する関数。引数に、対応するCueの名前を与えてください。
*/
inline void StopMusic(const std::string& CueName)
{
	Music::GetInstance()->Stop(CueName);
}
/**
*@brief 音を一時停止する関数。引数に、対応するCueの名前を与えてください。
*@brief PlayMusic関数でPauseしたところから再生が始まります。
*/
inline void PauseMusic(const std::string& CueName)
{
	Music::GetInstance()->Pause(CueName);
}

/**
*@brief Cueに割り当てた変数に値を代入する関数。
*@brief 第一引数にCueの名前、第二引数にCue変数の名前、第三引数に代入する値を与えてください。
*/
inline void SetCueVariable(const std::string& CueName, const std::string& VariableName, float Value)
{
	Music::GetInstance()->SetCueVariable(CueName, VariableName, Value);
}

/**
*@brief XACTのGlobalな変数に値を代入する関数。
*@brief 第一引数にGlobal変数の名前、第二引数に代入する値を与えてください。
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