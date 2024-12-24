//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(main.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include 
#include "main.h"
#include "manager.h"

// �v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam);
void ToggleFullscreen(HWND hWnd);	// �E�B���h�E���t���X�N���[���ɂ�����@

// �O���[�o���ϐ��錾
bool g_bIsFullScreen = false;
RECT g_windowRect;						// �E�B���h�E��؂�ւ��邽�߂̕ϐ�

//***********************************************************************************************************************
// ���C���֐�
//***********************************************************************************************************************
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					// WINDCLASSEX�̃T�C�Y
		CS_CLASSDC,							// �E�B���h�E�̃X�^�C��
		WindowProc,							// �E�B���h�E�v���V�[�W��
		0,									// 0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,									// 0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance,							// �C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),		// �^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),			// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			// �N���C�A���g�̈�̔w�i�F
		NULL,								// ���j���[�o�[
		CLASS_NAME,							// �E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)		// �t�@�C���̃A�C�R��
	};

	HWND hWnd;	// �E�B���h�E�n���h��(���ʎq)
	MSG  msg;   // ���b�Z�[�W���i�[����ϐ�

	RECT rect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };   // ��ʃT�C�Y�̑傫��

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);
	// �E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,				// �g���E�B���h�E�X�^�C��
		CLASS_NAME,							// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,						// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,				// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,						// �E�B���h�E�̍���X���W
		CW_USEDEFAULT,						// �E�B���h�E�̍���Y���W
		(rect.right - rect.left),			// �E�B���h�E�̕�
		(rect.bottom - rect.top),			// �E�B���h�E�̍���
		NULL,								// �e�E�B���h�E�̃n���h��
		NULL,								// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,							// �C���X�^���X�n���h��
		NULL);								// �E�B���h�E�쐬�f�[�^
	
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	if (FAILED(manager.Init(hInstance,hWnd, TRUE)))
	{// ������
		return -1;
	}

	ToggleFullscreen(hWnd);

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);	// �E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);			// �N���C�A���g�̈���X�V

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windows�̏���
			if (msg.message == WM_QUIT)
			{// WM_QUIT���b�Z�[�W���󂯎�����烋�[�v�𔲂���
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectX�̏���
			// �}�l�[�W���[�̍X�V����
			manager.Update();

			// �}�l�[�W���[�̕`�揈��
			manager.Draw();
		}
	}

	// �}�l�[�W���[�̏I������
	manager.Uninit();

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return (int)msg.wParam;

}

//***********************************************************************************************************************
// �E�B���h�E�v���V�[�W��
//***********************************************************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
	// ���[�J���ϐ��錾
	int nID;	// �Ԃ�l���i�[
	switch (uMsg)
	{
	case WM_DESTROY:	// �E�B���h�E�j���̃��b�Z�[�W
		// WM_QUIT�փ��b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	case WM_CLOSE:		// ����{�^�������̃��b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{// �͂��������ꂽ�ꍇ
			DestroyWindow(hWnd);	// �E�B���h�E�̔j��
		}
		else
		{// �������������ꂽ�ꍇ
			return 0;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:	// ESC�L�[�������ꂽ�Ƃ�
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{// �͂��������ꂽ�ꍇ
				DestroyWindow(hWnd);	// �E�B���h�E��j������
			}
			else
			{
				return 0;
			}
			break;
		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
	case WM_LBUTTONDOWN:	// �}�E�X���N���b�N�̃��b�Z�[�W

		SetFocus(hWnd);	// �E�B���h�E�Ƀt�H�[�J�X�����킹��

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, IParam);	// ����̏�����Ԃ�
}

//***********************************************************************************************************************
// �E�B���h�E���t���X�N���[���ɕς��鏈��
//***********************************************************************************************************************
void ToggleFullscreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_bIsFullScreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_bIsFullScreen = !g_bIsFullScreen;

}

