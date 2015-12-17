#include "Joypad.h"

#include <algorithm>

#pragma comment(lib, "Xinput.lib")

#define COMPARISON(x,y,z) (((x) <= (y))&&((y) <= (z)))

bool Joypad::isPushed(int userindex, Button button) {
	if (COMPARISON(0, userindex, 3))
		return isConnected(userindex) && (m_State[userindex].Gamepad.wButtons & static_cast<int>(button));
	return false;
}

bool Joypad::isJustPushed(int userindex, Button button) {
	if (COMPARISON(0, userindex, 3))
		return isConnected(userindex) && (m_State[userindex].Gamepad.wButtons & static_cast<int>(button)) && !(m_prevState[userindex].Gamepad.wButtons & static_cast<int>(button));
	return false;
}

bool Joypad::isConnected(int userindex) {
	if (COMPARISON(0, userindex, 3))
		return m_Connected[userindex];
	return false;
}

bool Joypad::update(int userindex) {
	if (COMPARISON(0, userindex, 3)){
		m_prevState[userindex] = m_State[userindex];
		m_Connected[userindex] = (XInputGetState((DWORD)userindex, &m_State[userindex]) == ERROR_SUCCESS);
		return m_Connected[userindex];
	}
	return false;
}

std::complex<double> Joypad::getLStick(int userindex, double thresholdByPercent) {
	if (!isConnected(userindex)) return std::complex<double>(0, 0);
	auto y_abs = std::abs(m_State[userindex].Gamepad.sThumbLY) / (double)StickMax; // ïâÇÃäÑÇËéZÇÕèàóùåníËã`Ç»à◊
	auto y_sign = (m_State[userindex].Gamepad.sThumbLY < 0) ? -1 : 1;
	auto x_abs = std::abs(m_State[userindex].Gamepad.sThumbLX) / (double)StickMax;
	auto x_sign = (m_State[userindex].Gamepad.sThumbLX < 0) ? -1 : 1;

	return std::complex<double>(
		(x_abs < thresholdByPercent) ? 0 : x_abs * x_sign,
		(y_abs < thresholdByPercent) ? 0 : y_abs * y_sign
		);
}

std::complex<double> Joypad::getRStick(int userindex, double thresholdByPercent) {
	if (!isConnected(userindex)) return std::complex<double>(0, 0);
	auto y_abs = std::abs(m_State[userindex].Gamepad.sThumbRY) / (double)StickMax;
	auto y_sign = (m_State[userindex].Gamepad.sThumbRY < 0) ? -1 : 1;
	auto x_abs = std::abs(m_State[userindex].Gamepad.sThumbRX) / (double)StickMax;
	auto x_sign = (m_State[userindex].Gamepad.sThumbRX < 0) ? -1 : 1;

	return std::complex<double>(
		(x_abs < thresholdByPercent) ? 0 : x_abs * x_sign,
		(y_abs < thresholdByPercent) ? 0 : y_abs * y_sign
		);
}

bool Joypad::isJustUpLStick(int userindex, double thresholdByPercent)
{
	if (!isConnected(userindex)) return false;
	auto y_abs = std::abs(m_State[userindex].Gamepad.sThumbLY) / (double)StickMax;
	auto y_sign = (m_State[userindex].Gamepad.sThumbLY < 0) ? -1 : 1;
	auto old_y_abs = std::abs(m_prevState[userindex].Gamepad.sThumbLY) / (double)StickMax;
	auto old_y_sign = (m_prevState[userindex].Gamepad.sThumbLY < 0) ? -1 : 1;

	auto y = (y_abs < thresholdByPercent) ? 0:y_abs * y_sign;
	auto old_y = (old_y_abs < thresholdByPercent) ? 0 : old_y_abs * old_y_sign;

	return (old_y <= 0) && (y > 0);
}

bool Joypad::isJustUpRStick(int userindex, double thresholdByPercent)
{
	if (!isConnected(userindex)) return false;
	auto y_abs = std::abs(m_State[userindex].Gamepad.sThumbRY) / (double)StickMax;
	auto y_sign = (m_State[userindex].Gamepad.sThumbRY < 0) ? -1 : 1;
	auto old_y_abs = std::abs(m_prevState[userindex].Gamepad.sThumbRY) / (double)StickMax;
	auto old_y_sign = (m_prevState[userindex].Gamepad.sThumbRY < 0) ? -1 : 1;

	auto y = (y_abs < thresholdByPercent) ? 0 : y_abs * y_sign;
	auto old_y = (old_y_abs < thresholdByPercent) ? 0 : old_y_abs * old_y_sign;

	return (old_y <= 0) && (y > 0);
}

bool Joypad::isJustDownLStick(int userindex, double thresholdByPercent)
{
	if (!isConnected(userindex)) return false;
	auto y_abs = std::abs(m_State[userindex].Gamepad.sThumbLY) / (double)StickMax;
	auto y_sign = (m_State[userindex].Gamepad.sThumbLY < 0) ? -1 : 1;
	auto old_y_abs = std::abs(m_prevState[userindex].Gamepad.sThumbLY) / (double)StickMax;
	auto old_y_sign = (m_prevState[userindex].Gamepad.sThumbLY < 0) ? -1 : 1;

	auto y = (y_abs < thresholdByPercent) ? 0 : y_abs * y_sign;
	auto old_y = (old_y_abs < thresholdByPercent) ? 0 : old_y_abs * old_y_sign;

	return (old_y >= 0) && (y < 0);
}

bool Joypad::isJustDownRStick(int userindex, double thresholdByPercent)
{
	if (!isConnected(userindex)) return false;
	auto y_abs = std::abs(m_State[userindex].Gamepad.sThumbRY) / (double)StickMax;
	auto y_sign = (m_State[userindex].Gamepad.sThumbRY < 0) ? -1 : 1;
	auto old_y_abs = std::abs(m_prevState[userindex].Gamepad.sThumbRY) / (double)StickMax;
	auto old_y_sign = (m_prevState[userindex].Gamepad.sThumbRY < 0) ? -1 : 1;

	auto y = (y_abs < thresholdByPercent) ? 0 : y_abs * y_sign;
	auto old_y = (old_y_abs < thresholdByPercent) ? 0 : old_y_abs * old_y_sign;

	return (old_y >= 0) && (y < 0);
}

bool Joypad::isJustRightLStick(int userindex, double thresholdByPercent)
{
	if (!isConnected(userindex)) return false;
	auto y_abs = std::abs(m_State[userindex].Gamepad.sThumbLX) / (double)StickMax;
	auto y_sign = (m_State[userindex].Gamepad.sThumbLX < 0) ? -1 : 1;
	auto old_y_abs = std::abs(m_prevState[userindex].Gamepad.sThumbLX) / (double)StickMax;
	auto old_y_sign = (m_prevState[userindex].Gamepad.sThumbLX < 0) ? -1 : 1;

	auto y = (y_abs < thresholdByPercent) ? 0 : y_abs * y_sign;
	auto old_y = (old_y_abs < thresholdByPercent) ? 0 : old_y_abs * old_y_sign;

	return (old_y <= 0) && (y > 0);
}

bool Joypad::isJustRightRStick(int userindex, double thresholdByPercent)
{
	if (!isConnected(userindex)) return false;
	auto y_abs = std::abs(m_State[userindex].Gamepad.sThumbRX) / (double)StickMax;
	auto y_sign = (m_State[userindex].Gamepad.sThumbRX < 0) ? -1 : 1;
	auto old_y_abs = std::abs(m_prevState[userindex].Gamepad.sThumbRX) / (double)StickMax;
	auto old_y_sign = (m_prevState[userindex].Gamepad.sThumbRX < 0) ? -1 : 1;

	auto y = (y_abs < thresholdByPercent) ? 0 : y_abs * y_sign;
	auto old_y = (old_y_abs < thresholdByPercent) ? 0 : old_y_abs * old_y_sign;

	return (old_y <= 0) && (y > 0);
}

bool Joypad::isJustLeftLStick(int userindex, double thresholdByPercent)
{
	if (!isConnected(userindex)) return false;
	auto y_abs = std::abs(m_State[userindex].Gamepad.sThumbLX) / (double)StickMax;
	auto y_sign = (m_State[userindex].Gamepad.sThumbLX < 0) ? -1 : 1;
	auto old_y_abs = std::abs(m_prevState[userindex].Gamepad.sThumbLX) / (double)StickMax;
	auto old_y_sign = (m_prevState[userindex].Gamepad.sThumbLX < 0) ? -1 : 1;

	auto y = (y_abs < thresholdByPercent) ? 0 : y_abs * y_sign;
	auto old_y = (old_y_abs < thresholdByPercent) ? 0 : old_y_abs * old_y_sign;

	return (old_y >= 0) && (y < 0);
}

bool Joypad::isJustLeftRStick(int userindex, double thresholdByPercent)
{
	if (!isConnected(userindex)) return false;
	auto y_abs = std::abs(m_State[userindex].Gamepad.sThumbRX) / (double)StickMax;
	auto y_sign = (m_State[userindex].Gamepad.sThumbRX < 0) ? -1 : 1;
	auto old_y_abs = std::abs(m_prevState[userindex].Gamepad.sThumbRX) / (double)StickMax;
	auto old_y_sign = (m_prevState[userindex].Gamepad.sThumbRX < 0) ? -1 : 1;

	auto y = (y_abs < thresholdByPercent) ? 0 : y_abs * y_sign;
	auto old_y = (old_y_abs < thresholdByPercent) ? 0 : old_y_abs * old_y_sign;

	return (old_y >= 0) && (y < 0);
}

double Joypad::getLTrigger(int userindex, double thresholdByPercent) {
	if (!isConnected(userindex)) return 0;
	auto t = m_State[userindex].Gamepad.bLeftTrigger / (double)TriggerMax;
	return (t < thresholdByPercent) ? 0 : t;
}

double Joypad::getRTrigger(int userindex, double thresholdByPercent) {
	if (!isConnected(userindex)) return 0;
	auto t = m_State[userindex].Gamepad.bRightTrigger / (double)TriggerMax;
	return (t < thresholdByPercent) ? 0 : t;
}

bool Joypad::isJustLTrigger(int userindex, double thresholdByPercent) {
	if (!isConnected(userindex)) return false;
	auto t = m_State[userindex].Gamepad.bLeftTrigger / (double)TriggerMax;
	auto old_t = m_prevState[userindex].Gamepad.bLeftTrigger / (double)TriggerMax;
	return (old_t != t) && (t > 0);
}

bool Joypad::isJustRTrigger(int userindex, double thresholdByPercent) {
	if (!isConnected(userindex)) return false;
	auto t = m_State[userindex].Gamepad.bRightTrigger / (double)TriggerMax;
	auto old_t = m_prevState[userindex].Gamepad.bRightTrigger / (double)TriggerMax;
	return (old_t != t) && (t > 0);
}

bool Joypad::vibrate(int userindex, double leftMotorSpeedByPercent, double rightMotorSpeedByPercent) {
	if (COMPARISON(0, userindex, 3))
	{
		XINPUT_VIBRATION vib;
		vib.wLeftMotorSpeed = static_cast<WORD>(leftMotorSpeedByPercent * MotorSpeedMax);
		vib.wRightMotorSpeed = static_cast<WORD>(rightMotorSpeedByPercent * MotorSpeedMax);
		return XInputSetState(userindex, &vib) == ERROR_SUCCESS;
	}
	return false;
}