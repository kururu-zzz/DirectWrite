#ifndef __SINGLETONMANAGER__
#define __SINGLETONMANAGER__

#include <Windows.h>
#include "Music.h"
#include "Device.h"

namespace SingletonManage
{
	HRESULT Initialize(HWND* hWnd)
	{
		DX11::InitDevice(hWnd);
		XACTInitialize();
		return S_OK;
	}
	void Destruction()
	{
		XACTDestroy();
	}
}

#endif