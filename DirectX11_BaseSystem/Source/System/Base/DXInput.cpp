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
	{	//�L�[�{�[�h�f�o�C�X�̊J��
		m_pKeyDevice->Unacquire();
		m_pKeyDevice->Release();
	}
	if (m_pMouseDevice != NULL)
	{	//�}�E�X�f�o�C�X�̊J��
		m_pMouseDevice->Unacquire();
		m_pMouseDevice->Release();
	}

	// �W���C�p�b�h�f�o�C�X�̊J��----------------
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
	//�f�o�C�X�̍쐬
	if (FAILED(hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void **)&m_pInput, NULL)))
	{
		return hr;
	}
	//�L�[�{�[�h�̏�����
	if (FAILED(hr = SetupKeyboard(hWnd)))
	{
		return hr;
	}

	//�W���C�p�b�h�̏�����
	if (FAILED(hr = SetupJoypad(hWnd)))
	{
		return hr;
	}

	//�}�E�X�̏�����
	if (FAILED(hr = SetupMouse(hWnd)))
	{
		return hr;
	}

	return S_OK;
}

HRESULT DXInput::SetupKeyboard(HWND hWnd)
{
	HRESULT hr;

	//�f�o�C�X�̐���
	if (FAILED(hr = m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyDevice, NULL)))
	{
		return hr;
	}
	//�f�o�C�X���L�[�{�[�h�ɐݒ�
	if (FAILED(hr = m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}
	//�������x���̐ݒ�
	if (FAILED(hr = m_pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return hr;
	}
	//�f�o�C�X�̎擾
	m_pKeyDevice->Acquire();

	return hr;
}

HRESULT DXInput::SetupMouse(HWND hWnd)
{
	HRESULT hr;

	//�f�o�C�X�̍쐬
	if (FAILED(hr = m_pInput->CreateDevice(GUID_SysMouse, &m_pMouseDevice, NULL)))
	{
		return hr;
	}
	//�f�o�C�X���}�E�X�ɐݒ�
	if (FAILED(hr = m_pMouseDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		return hr;
	}
	//�������x���̐ݒ�
	if (FAILED(hr = m_pMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return hr;
	}
	//����J�n
	m_pMouseDevice->Acquire();

	return S_OK;
}


/**
*@brief	�W���C�p�b�h�̏�����
*@return
*@param	hWnd	�E�B���h�E�n���h��
*/
HRESULT DXInput::SetupJoypad(HWND hWnd)
{
	HRESULT hr;

	//�W���C�p�b�h�̗�
	if (FAILED(hr = m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL,
		(LPDIENUMDEVICESCALLBACK)GetJoyPadCallback, (VOID *)this, DIEDFL_ATTACHEDONLY)))
	{
		return hr;
	}
	//���o�ł������������[�v����
	long iLoopMax = m_iDetectJoypadCount > JOYPAD_MAX ? JOYPAD_MAX : m_iDetectJoypadCount;

	for (long i = 0; i < iLoopMax; ++i)
	{
		//�t�H�[�}�b�g�̐ݒ�
		if (FAILED(hr = m_pJoyPadDevice[i]->SetDataFormat(&c_dfDIJoystick2)))
		{
			return hr;
		}
		//�������x���̐ݒ�
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
		//�W���C�p�b�h����J�n
		m_pJoyPadDevice[i]->Acquire();
	}
	return hr;
}

/**
*@brief	�W���C�p�b�h�̎擾
*@return	DIENUM_STOP	:	�I�� DIENUM_CONTINUE : �p��
*@param	pDidIns
*@param	pCont	this�|�C���^
*/
BOOL CALLBACK DXInput::GetJoyPadCallback(DIDEVICEINSTANCE *pDidIns, void *pCont)
{
	DXInput *pThis = (DXInput *)pCont;

	//�f�o�C�X�̍쐬
	if (FAILED(pThis->m_pInput->CreateDevice(pDidIns->guidInstance,
		&(pThis->m_pJoyPadDevice[pThis->m_iDetectJoypadCount]), NULL)))
	{
		return DIENUM_STOP;
	}
	//�W���C�p�b�h�̐��𑝉�
	pThis->m_iDetectJoypadCount++;

	return DIENUM_CONTINUE;
}


/**
*@brief		�W���C�p�b�h�f�o�C�X�̗�
*@return	DIENUM_STOP : �񋓂̏I�� DIENUM_CONTINUE : �p��
*@param	pDidIns
*@param	pCont	this�|�C���^
*/
BOOL CALLBACK DXInput::EnumObjectCallback(DIDEVICEOBJECTINSTANCE *pDidIns, void *pCont)
{
	DXInput *pThis = (DXInput *)pCont;

	if (pDidIns->dwType & DIDFT_AXIS)
	{
		DIPROPRANGE	diprg;
		ZeroMemory(&diprg, sizeof(DIPROPRANGE));

		diprg.diph.dwSize = sizeof(DIPROPRANGE);	//�S�̂̃T�C�Y
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);	//�w�b�_�̃T�C�Y
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
	//�}�E�X�̍X�V
	UpdateMouseState();
	//�L�[�{�[�h�̍X�V
	UpdateKeyboardState();
	//�W���C�p�b�h�̍X�V
	UpdateJoypadState();
}

/**
*@brief	�L�[�{�[�h�̏�Ԃ��X�V
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
*@brief	�}�E�X�̏�Ԃ��X�V
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
*@brief	�W���C�p�b�h�̏�Ԃ��X�V
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
*@brief	�L�[�{�[�h���������ꂽ�����擾����
*@return	true : �������ꂽ
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
*@brief	�L�[�{�[�h���������ꂽ���ǂ������擾����
*@return	true : �������ꂽ
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
*@brief	�L�[�{�[�h��������Ă��邩�ǂ������擾����
*@return	true : ������Ă���
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
*@brief	�L�[�{�[�h��������Ă��邩�ǂ������擾����
*@return	true : ������Ă���
*/
bool DXInput::GetIsFreeKeyboard(unsigned char uDikCode)
{
	if ((m_KeyboardState[m_iStateIndex][uDikCode] & 0x80) == 0)
	{
		return true;
	}
	return false;
}

// i -->  0:���N���b�N 1:�E�N���b�N
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
*@brief	�W���C�p�b�h�̃{�^����������Ă��邩���擾����
*@return	true : ������Ă���
*@param	iPadID	�p�b�h�̂h�c
*@param	i	�{�^���h�c
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
*@brief	�W���C�p�b�h���������ꂽ���ǂ������擾����
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
*@brief	�W���C�p�b�h�̃{�^����������Ă��邩�ǂ������擾����
*@return	true : ������Ă���
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
*@brief	�W���C�p�b�h�̃{�^�����������ꂽ���ǂ������擾����
*@return	true : �������ꂽ
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
*@brief	�W���C�X�e�B�b�N�i���j
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
