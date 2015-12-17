#include "System/Base/Window.h"
#include "Sequence/Sequence.h"
#include "System/Base/SingletonManage.h"
#include "System/Base/DXInput.h"
#include "System\Base\DXResource.h"
#include "ComUtil.h"

static bool g_active = true;

// �E�B���h�E�v���V�[�W�� 
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KILLFOCUS:
		g_active = false;
		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	case WM_ACTIVATE:
		g_active = true;
		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	case WM_KEYUP:
		// �A�v���I�� 
		if (wParam == VK_ESCAPE)
			if(hWnd != NULL)
				::DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	default:
		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0L;
}


// ���C���֐� 
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE,
	LPTSTR,
	INT
){
	// �A�v���P�[�V�����̏�����
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// �A�v���P�[�V������ 
	TCHAR* AppName = _T("Lost Wishes");
	auto com = ComApartment();

	// �E�B���h�E�̍쐬
	HWND hWnd = InitWindow(AppName, hInstance, WndProc, 1200, 900);
	DXInput DirectInput;
	if (FAILED(DirectInput.Setup(hInstance, hWnd)))
	{
		return 0;
	}

	//�N���X�̏�����
	
	if (FAILED(SingletonManage::Initialize(&hWnd)))
	{
		SingletonManage::Destruction();
		return 0;
	}

	//����������
	auto Seed = timeGetTime();
	srand(Seed);

	std::shared_ptr<SeqManager> sManager = std::make_shared<SeqManager>();
	sManager->Init();
	

	::ShowWindow(hWnd, SW_SHOW);
	::UpdateWindow(hWnd);
	ShowCursor(FALSE);
	// ���b�Z�[�W���[�v 
	MSG msg = { 0 };
	do {
		if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}else {
			if (g_active)
			{
				DirectInput.Update();

				DoWork();

				if (!sManager->Update())
					break;

				sManager->Draw();
			}
		}
	} while (msg.message != WM_QUIT);

	sManager.reset();

	fbx::Resource::ClearResource();

	SingletonManage::Destruction();

	::UnregisterClass(AppName, hInstance);

	return msg.wParam;
}