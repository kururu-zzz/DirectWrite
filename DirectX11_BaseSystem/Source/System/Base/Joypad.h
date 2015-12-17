#ifndef __JOYPAD__
#define __JOYPAD__

//初期化時につながれてるコントローラー台数とって動的生成したほうがいいな
//m_UserIndex消そう

#include <complex>

#include <array>
#include <windows.h>
#include <XInput.h>

#define MY_XINPUT_GAMEPAD_TRIGGER_THRESHOLD 300
#define MY_XINPUT_GAMEPAD_STICK_THRESHOLD 12000

class Joypad{
private:
	Joypad(){};
	Joypad(const Joypad& rhs);
	Joypad& operator=(const Joypad& rhs);
public:
	static Joypad* GetInstance(){
		static Joypad msp_instance;
		return &msp_instance;
	}
public:
	enum class Button{
		A = XINPUT_GAMEPAD_A,
		B = XINPUT_GAMEPAD_B,
		X = XINPUT_GAMEPAD_X,
		Y = XINPUT_GAMEPAD_Y,
		Up = XINPUT_GAMEPAD_DPAD_UP,
		Down = XINPUT_GAMEPAD_DPAD_DOWN,
		Left = XINPUT_GAMEPAD_DPAD_LEFT,
		Right = XINPUT_GAMEPAD_DPAD_RIGHT,
		Start = XINPUT_GAMEPAD_START,
		Back = XINPUT_GAMEPAD_BACK,
		LThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		RThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		LShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER
	};

	bool update(int userindex);
	bool isPushed(int userindex, Button button);
	bool isJustPushed(int userindex, Button button);
	bool vibrate(int userindex, double leftMotorSpeedByPercent, double rightMotorSpeedByPercent);
	bool isConnected(int userindex);
	double getLTrigger(int userindex, double thresholdByPercent =  MY_XINPUT_GAMEPAD_TRIGGER_THRESHOLD / (double)TriggerMax);
	double getRTrigger(int userindex, double thresholdByPercent =  MY_XINPUT_GAMEPAD_TRIGGER_THRESHOLD / (double)TriggerMax);
	bool isJustLTrigger(int userindex, double thresholdByPercent = MY_XINPUT_GAMEPAD_TRIGGER_THRESHOLD / (double)TriggerMax);
	bool isJustRTrigger(int userindex, double thresholdByPercent = MY_XINPUT_GAMEPAD_TRIGGER_THRESHOLD / (double)TriggerMax);
	std::complex<double> getLStick(int userindex, double thresholdByPercent = MY_XINPUT_GAMEPAD_STICK_THRESHOLD / (double)StickMax);
	std::complex<double> getRStick(int userindex, double thresholdByPercent = MY_XINPUT_GAMEPAD_STICK_THRESHOLD / (double)StickMax);
	bool isJustUpLStick(int userindex,    double thresholdByPercent = MY_XINPUT_GAMEPAD_STICK_THRESHOLD / (double)StickMax);
	bool isJustUpRStick(int userindex,    double thresholdByPercent = MY_XINPUT_GAMEPAD_STICK_THRESHOLD / (double)StickMax);
	bool isJustDownLStick(int userindex,  double thresholdByPercent = MY_XINPUT_GAMEPAD_STICK_THRESHOLD / (double)StickMax);
	bool isJustDownRStick(int userindex,  double thresholdByPercent = MY_XINPUT_GAMEPAD_STICK_THRESHOLD / (double)StickMax);
	bool isJustLeftLStick(int userindex,  double thresholdByPercent = MY_XINPUT_GAMEPAD_STICK_THRESHOLD / (double)StickMax);
	bool isJustLeftRStick(int userindex,  double thresholdByPercent = MY_XINPUT_GAMEPAD_STICK_THRESHOLD / (double)StickMax);
	bool isJustRightLStick(int userindex, double thresholdByPercent = MY_XINPUT_GAMEPAD_STICK_THRESHOLD / (double)StickMax);
	bool isJustRightRStick(int userindex, double thresholdByPercent = MY_XINPUT_GAMEPAD_STICK_THRESHOLD / (double)StickMax);

private:
	static const long TriggerMax = 255;
	static const long MotorSpeedMax = 65535;
	static const long StickMax = 32767;

	std::array<XINPUT_STATE,4> m_State;
	std::array<XINPUT_STATE, 4> m_prevState;
	std::array<bool,4> m_Connected;
};

inline bool JoypadUpdate(int userindex)
{
	return Joypad::GetInstance()->update(userindex);
}

inline bool isPushed(int userindex,Joypad::Button button)
{
	return Joypad::GetInstance()->isPushed(userindex, button);
}

inline bool isJustPushed(int userindex, Joypad::Button button)
{
	return Joypad::GetInstance()->isJustPushed(userindex, button);
}

inline std::complex<double> getLStick(int userindex)
{
	return Joypad::GetInstance()->getLStick(userindex);
}

inline std::complex<double> getRStick(int userindex)
{
	return Joypad::GetInstance()->getRStick(userindex);
}

inline double getLTrigger(int userindex)
{
	return Joypad::GetInstance()->getLTrigger(userindex);
}

inline double getRTrigger(int userindex)
{
	return Joypad::GetInstance()->getRTrigger(userindex);
}

inline bool isJustLTrigger(int userindex)
{
	return Joypad::GetInstance()->isJustLTrigger(userindex);
}

inline bool isJustRTrigger(int userindex)
{
	return Joypad::GetInstance()->isJustRTrigger(userindex);
}

inline bool isJustUpLStick(int userindex)
{
	return Joypad::GetInstance()->isJustUpLStick(userindex);
}

inline bool isJustUpRStick(int userindex)
{
	return Joypad::GetInstance()->isJustUpRStick(userindex);
}

inline bool isJustDownLStick(int userindex)
{
	return Joypad::GetInstance()->isJustDownLStick(userindex);
}

inline bool isJustDownRStick(int userindex)
{
	return Joypad::GetInstance()->isJustDownRStick(userindex);
}

inline bool isJustLeftLStick(int userindex)
{
	return Joypad::GetInstance()->isJustLeftLStick(userindex);
}

inline bool isJustLeftRStick(int userindex)
{
	return Joypad::GetInstance()->isJustLeftRStick(userindex);
}

inline bool isJustRightLStick(int userindex)
{
	return Joypad::GetInstance()->isJustRightLStick(userindex);
}

inline bool isJustRightRStick(int userindex)
{
	return Joypad::GetInstance()->isJustRightRStick(userindex);
}

#endif