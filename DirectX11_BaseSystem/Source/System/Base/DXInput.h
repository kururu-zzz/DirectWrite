#ifndef _DX_INPUT_H
#define _DX_INPUT_H

//#define SAFE_DELETE(p) {if(p) {delete (p); (p) = NULL;}}

#define DIRECTINPUT_VERSION 0x0800

#define	NC_DX_PROP_MIN	-1000
#define	NC_DX_PROP_MAX	1000

#define	PS2_Z	0 // △
#define	PS2_X	1 // ○
#define	PS2_C	2 // ×
#define	PS2_V	3 // □1
#define PS2_L2	4
#define PS2_R2	5
#define PS2_L1	6
#define PS2_R1	7
#define PS2_START	8
#define PS2_SELECT	9

#include "dinput.h"
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "DXGUID.LIB")
#pragma comment(lib, "winmm.lib")

//class DXCommand;

class DXInput
{
public:
	//friend class DXCommand;
	HRESULT		Setup(HINSTANCE hInst, HWND hWnd);
	void		Cleanup();
	void		Update();

	// キーボード
	bool		GetIsJustPressedKeyboard(unsigned char uDikCode);
	bool		GetIsJustPulledKeyboard(unsigned char uDikCode);
	bool		GetIsPressedKeyboard(unsigned char uDikCode);
	bool		GetIsFreeKeyboard(unsigned char uDikCode);

	// マウス
	bool		GetIsJustPressedMouse(long i);
	bool		GetIsJustPulledMouse(long i);
	bool		GetIsPressedMouse(long i);
	bool		GetIsFreeMouse(long i);

	// ジョイパッド
	bool		GetIsJustPressedJoypad(long iPadID, long i);
	bool		GetIsJustPulledJoypad(long iPadID, long i);
	bool		GetIsPressedJoypad(long iPadID, long i);
	bool		GetIsFreeJoypad(long iPadID, long i);

	// 左スティック
	bool		GetIsStickUp(long iPadID, long Sens = -300);
	bool		GetIsStickDown(long iPadID, long Sens = 300);
	bool		GetIsStickLeft(long iPadID, long Sens = -300);
	bool		GetIsStickRight(long iPadID, long Sens = 300);

	// ジョイパッド関連-----------------
	DIJOYSTATE2 *	GetJoypadState(long i)	{ return &m_JoypadState[i][m_iStateIndex]; }
	DIJOYSTATE2 *	GetPreJoypadState(long i){ return &m_JoypadState[i][1 - m_iStateIndex]; }

	long		GetStateIndex()	const{ return m_iStateIndex; }
	long		GetDetectJoypadCount(){ return m_iDetectJoypadCount; }
	// ----------------------------------

	DXInput();
	~DXInput();

	static DXInput *	GetInstance()	{ return m_spInstance; }

private:
	HRESULT		SetupKeyboard(HWND hWnd);
	HRESULT		SetupJoypad(HWND hWnd);
	HRESULT		SetupMouse(HWND hWnd);


	void		UpdateKeyboardState();
	void		UpdateMouseState();
	void		UpdateJoypadState();

	// ジョイパッド関連----------
	static BOOL CALLBACK	GetJoyPadCallback(DIDEVICEINSTANCE *pDidIns, void *pThis);
	static BOOL CALLBACK	EnumObjectCallback(DIDEVICEOBJECTINSTANCE *pDidIns, void *pThis);
	// --------------------------

	enum{ JOYPAD_MAX = 4 };
	LPDIRECTINPUT8			m_pInput;			//!<	デバイスへのポインタ
	LPDIRECTINPUTDEVICE8	m_pKeyDevice;		//!<	キーボードデバイス
	LPDIRECTINPUTDEVICE8	m_pMouseDevice;		//!<	マウスデバイス
	LPDIRECTINPUTDEVICE8	m_pJoyPadDevice[JOYPAD_MAX];	//!<	ジョイパッドデバイス

	long					m_iDetectJoypadCount;	//!<	検出したジョイパッドの数
	long					m_iSettingJoypad;		//!<	設定しているジョイパッド

	long					m_iStateIndex;			//!<	状態のインデックス

	DIMOUSESTATE2			m_MouseState[2];		//!<	マウスの状態
	DIJOYSTATE2				m_JoypadState[JOYPAD_MAX][2];//!<	ジョイパッドの状態
	unsigned char			m_KeyboardState[2][256];	 //!<	キーボードの状態


	static DXInput *m_spInstance;	//!<	インスタンス

};

inline DXInput * GetDXInput()
{
	return DXInput::GetInstance();
}

#endif
