#include "DXInput.h"

DXInput * DXInput::m_spInstance = NULL;

DXInput::DXInput()
{
	m_pInput = NULL;
	m_pKeyDevice = NULL;
	m_pMouseDevice = NULL;


	for (long u = 0; u < JOYPAD_MAX; ++u)
	{
		m_pJoyPadDevice[u] = NULL;
	}

	m_iDetectJoypadCount = 0;
	m_iSettingJoypad = 0;


	m_iStateIndex = 0;

	m_spInstance = this;

	memset(m_KeyboardState, 0, sizeof(unsigned char)* 2 * 256);
	memset(m_MouseState, 0, sizeof(DIMOUSESTATE2)* 2);
	memset(m_JoypadState, 0, sizeof(DIJOYSTATE2)* 2 * JOYPAD_MAX);
}

void DXInput::Cleanup(){
	if (m_pKeyDevice != NULL)
	{	//キーボードデバイスの開放
		m_pKeyDevice->Unacquire();
		m_pKeyDevice->Release();
	}
	if (m_pMouseDevice != NULL)
	{	//マウスデバイスの開放
		m_pMouseDevice->Unacquire();
		m_pMouseDevice->Release();
	}

	// ジョイパッドデバイスの開放----------------
	for (long i = 0; i < JOYPAD_MAX; ++i)
	{
		if (m_pJoyPadDevice[i] != NULL)
		{
			m_pJoyPadDevice[i]->Unacquire();
			m_pJoyPadDevice[i]->Release();
		}
	}
	m_iDetectJoypadCount = 0;
	m_iSettingJoypad = 0;
	// ---------------
}

/**
*/
DXInput::~DXInput()
{
	Cleanup();

	m_spInstance = NULL;
}

HRESULT DXInput::Setup(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;
	//デバイスの作成
	if (FAILED(hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void **)&m_pInput, NULL)))
	{
		return hr;
	}
	//キーボードの初期化
	if (FAILED(hr = SetupKeyboard(hWnd)))
	{
		return hr;
	}

	//ジョイパッドの初期化
	if (FAILED(hr = SetupJoypad(hWnd)))
	{
		return hr;
	}

	//マウスの初期化
	if (FAILED(hr = SetupMouse(hWnd)))
	{
		return hr;
	}

	return S_OK;
}

HRESULT DXInput::SetupKeyboard(HWND hWnd)
{
	HRESULT hr;

	//デバイスの生成
	if (FAILED(hr = m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyDevice, NULL)))
	{
		return hr;
	}
	//デバイスをキーボードに設定
	if (FAILED(hr = m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}
	//協調レベルの設定
	if (FAILED(hr = m_pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return hr;
	}
	//デバイスの取得
	m_pKeyDevice->Acquire();

	return hr;
}

HRESULT DXInput::SetupMouse(HWND hWnd)
{
	HRESULT hr;

	//デバイスの作成
	if (FAILED(hr = m_pInput->CreateDevice(GUID_SysMouse, &m_pMouseDevice, NULL)))
	{
		return hr;
	}
	//デバイスをマウスに設定
	if (FAILED(hr = m_pMouseDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		return hr;
	}
	//協調レベルの設定
	if (FAILED(hr = m_pMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return hr;
	}
	//制御開始
	m_pMouseDevice->Acquire();

	return S_OK;
}


/**
*@brief	ジョイパッドの初期化
*@return
*@param	hWnd	ウィンドウハンドル
*/
HRESULT DXInput::SetupJoypad(HWND hWnd)
{
	HRESULT hr;

	//ジョイパッドの列挙
	if (FAILED(hr = m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL,
		(LPDIENUMDEVICESCALLBACK)GetJoyPadCallback, (VOID *)this, DIEDFL_ATTACHEDONLY)))
	{
		return hr;
	}
	//検出できた数だけループを回す
	long iLoopMax = m_iDetectJoypadCount > JOYPAD_MAX ? JOYPAD_MAX : m_iDetectJoypadCount;

	for (long i = 0; i < iLoopMax; ++i)
	{
		//フォーマットの設定
		if (FAILED(hr = m_pJoyPadDevice[i]->SetDataFormat(&c_dfDIJoystick2)))
		{
			return hr;
		}
		//協調レベルの設定
		if (FAILED(hr = m_pJoyPadDevice[i]->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
		{
			return hr;
		}
		if (FAILED(m_pJoyPadDevice[i]->EnumObjects(
			(LPDIENUMDEVICEOBJECTSCALLBACK)EnumObjectCallback, (VOID *)this, DIDFT_ALL)))
		{
			return hr;
		}
		m_iSettingJoypad++;
		//ジョイパッド制御開始
		m_pJoyPadDevice[i]->Acquire();
	}
	return hr;
}

/**
*@brief	ジョイパッドの取得
*@return	DIENUM_STOP	:	終了 DIENUM_CONTINUE : 継続
*@param	pDidIns
*@param	pCont	thisポインタ
*/
BOOL CALLBACK DXInput::GetJoyPadCallback(DIDEVICEINSTANCE *pDidIns, void *pCont)
{
	DXInput *pThis = (DXInput *)pCont;

	//デバイスの作成
	if (FAILED(pThis->m_pInput->CreateDevice(pDidIns->guidInstance,
		&(pThis->m_pJoyPadDevice[pThis->m_iDetectJoypadCount]), NULL)))
	{
		return DIENUM_STOP;
	}
	//ジョイパッドの数を増加
	pThis->m_iDetectJoypadCount++;

	return DIENUM_CONTINUE;
}


/**
*@brief		ジョイパッドデバイスの列挙
*@return	DIENUM_STOP : 列挙の終了 DIENUM_CONTINUE : 継続
*@param	pDidIns
*@param	pCont	thisポインタ
*/
BOOL CALLBACK DXInput::EnumObjectCallback(DIDEVICEOBJECTINSTANCE *pDidIns, void *pCont)
{
	DXInput *pThis = (DXInput *)pCont;

	if (pDidIns->dwType & DIDFT_AXIS)
	{
		DIPROPRANGE	diprg;
		ZeroMemory(&diprg, sizeof(DIPROPRANGE));

		diprg.diph.dwSize = sizeof(DIPROPRANGE);	//全体のサイズ
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);	//ヘッダのサイズ
		diprg.diph.dwHow = DIPH_BYID;
		diprg.diph.dwObj = pDidIns->dwType;
		diprg.lMin = NC_DX_PROP_MIN;
		diprg.lMax = NC_DX_PROP_MAX;

		if (FAILED(pThis->m_pJoyPadDevice[pThis->m_iSettingJoypad]->SetProperty(
			DIPROP_RANGE, &diprg.diph)))
		{
			return DIENUM_STOP;
		}
	}
	return DIENUM_CONTINUE;
}


void DXInput::Update()
{
	m_iStateIndex = 1 - m_iStateIndex;
	//マウスの更新
	UpdateMouseState();
	//キーボードの更新
	UpdateKeyboardState();
	//ジョイパッドの更新
	UpdateJoypadState();
}

/**
*@brief	キーボードの状態を更新
*@return
*/
void DXInput::UpdateKeyboardState()
{
	m_pKeyDevice->GetDeviceState(sizeof(m_KeyboardState[m_iStateIndex]), &m_KeyboardState[m_iStateIndex]);

	HRESULT hr;
	do
	{
		hr = m_pKeyDevice->Acquire();
	} while (hr == DIERR_INPUTLOST);
}

/**
*@brief	マウスの状態を更新
*@return
*/
void DXInput::UpdateMouseState()
{
	HRESULT hr;
	m_pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &m_MouseState[m_iStateIndex]);
	do
	{
		hr = m_pMouseDevice->Acquire();
	} while (hr == DIERR_INPUTLOST);
}

/**
*@brief	ジョイパッドの状態を更新
*@return
*/
void DXInput::UpdateJoypadState()
{
	long iLoopMax = m_iDetectJoypadCount > JOYPAD_MAX ? JOYPAD_MAX : m_iDetectJoypadCount;

	for (long i = 0; i < iLoopMax; ++i)
	{
		HRESULT hr;
		if (FAILED(m_pJoyPadDevice[i]->Poll()))
		{
			do
			{
				hr = m_pJoyPadDevice[i]->Acquire();
			} while (hr == DIERR_INPUTLOST);

			ZeroMemory(&m_JoypadState[i][m_iStateIndex], sizeof(m_JoypadState[i][m_iStateIndex]));

			return;
		}
		hr = m_pJoyPadDevice[i]->GetDeviceState(sizeof(DIJOYSTATE2), &m_JoypadState[i][m_iStateIndex]);
	}
}

/**
*@brief	キーボードが今押されたかを取得する
*@return	true : 今押された
*/
bool DXInput::GetIsJustPressedKeyboard(unsigned char uDikCode)
{
	if (m_KeyboardState[m_iStateIndex][uDikCode] & 0x80 &&
		((m_KeyboardState[1 - m_iStateIndex][uDikCode] & 0x80) == 0))
	{
		return true;
	}
	return false;
}

/**
*@brief	キーボードが今離されたかどうかを取得する
*@return	true : 今離された
*/
bool DXInput::GetIsJustPulledKeyboard(unsigned char uDikCode)
{
	if (((m_KeyboardState[m_iStateIndex][uDikCode] & 0x80) == 0) &&
		m_KeyboardState[1 - m_iStateIndex][uDikCode] & 0x80)
	{
		return true;
	}
	return false;
}

/**
*@brief	キーボードが押されているかどうかを取得する
*@return	true : 押されている
*/
bool DXInput::GetIsPressedKeyboard(unsigned char uDikCode)
{
	if (m_KeyboardState[m_iStateIndex][uDikCode] & 0x80)
	{
		return true;
	}
	return false;
}

/**
*@brief	キーボードが離されているかどうかを取得する
*@return	true : 離されている
*/
bool DXInput::GetIsFreeKeyboard(unsigned char uDikCode)
{
	if ((m_KeyboardState[m_iStateIndex][uDikCode] & 0x80) == 0)
	{
		return true;
	}
	return false;
}

// i -->  0:左クリック 1:右クリック
bool DXInput::GetIsPressedMouse(long i)
{
	if (m_MouseState[m_iStateIndex].rgbButtons[i] & 0x80)
	{
		return true;
	}
	return false;
}

bool DXInput::GetIsFreeMouse(long i)
{
	if ((m_MouseState[m_iStateIndex].rgbButtons[i] & 0x80) == 0)
	{
		return true;
	}
	return false;
}

bool DXInput::GetIsJustPressedMouse(long i)
{
	if (m_MouseState[m_iStateIndex].rgbButtons[i] & 0x80 &&
		(m_MouseState[1 - m_iStateIndex].rgbButtons[i] & 0x80) == 0)
	{
		return true;
	}
	return false;
}

bool DXInput::GetIsJustPulledMouse(long i)
{
	if ((m_MouseState[m_iStateIndex].rgbButtons[i] & 0x80) == 0 &&
		(m_MouseState[m_iStateIndex].rgbButtons[i] & 0x80))
	{
		return true;
	}
	return false;
}


/**
*@brief	ジョイパッドのボタンが押されているかを取得する
*@return	true : 押されている
*@param	iPadID	パッドのＩＤ
*@param	i	ボタンＩＤ
*/
bool DXInput::GetIsPressedJoypad(long iPadID, long i)
{
	if (m_JoypadState[iPadID][m_iStateIndex].rgbButtons[i] & 0x80)
	{
		return true;
	}
	return false;
}

/**
*@brief	ジョイパッドが今押されたかどうかを取得する
*@return	true :
*@param	iPadID
*@param	i
*/
bool DXInput::GetIsJustPressedJoypad(long iPadID, long i)
{
	if ((m_JoypadState[iPadID][m_iStateIndex].rgbButtons[i] & 0x80) &&
		((m_JoypadState[iPadID][1 - m_iStateIndex].rgbButtons[i] & 0x80) == 0))
	{
		return true;
	}
	return false;
}

/**
*@brief	ジョイパッドのボタンが離されているかどうかを取得する
*@return	true : 離されている
*@param	iPadID
*@param	i
*/
bool DXInput::GetIsFreeJoypad(long iPadID, long i)
{
	if (m_JoypadState[iPadID][m_iStateIndex].rgbButtons[i] & 0x80)
	{
		return false;
	}

	return true;
}

/**
*@brief	ジョイパッドのボタンが今離されたかどうかを取得する
*@return	true : 今離された
*@param	iPadID
*@param	i
*/
bool DXInput::GetIsJustPulledJoypad(long iPadID, long i)
{
	if (((m_JoypadState[iPadID][m_iStateIndex].rgbButtons[i] & 0x80) == 0) &&
		m_JoypadState[iPadID][1 - m_iStateIndex].rgbButtons[i] & 0x80)
	{
		return true;
	}
	return false;
}

/**
*@brief	ジョイスティック（左）
*/
bool DXInput::GetIsStickUp(long iPadID, long Sens)
{
	return m_JoypadState[iPadID][m_iStateIndex].lY < Sens ? true : false;
}

bool DXInput::GetIsStickDown(long iPadID, long Sens)
{
	return m_JoypadState[iPadID][m_iStateIndex].lY > Sens ? true : false;
}

bool DXInput::GetIsStickLeft(long iPadID, long Sens)
{
	return m_JoypadState[iPadID][m_iStateIndex].lX < Sens ? true : false;
}

bool DXInput::GetIsStickRight(long iPadID, long Sens)
{
	return m_JoypadState[iPadID][m_iStateIndex].lX > Sens ? true : false;
}
