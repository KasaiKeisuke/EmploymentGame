//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(main.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include 
#include "main.h"
#include "manager.h"

// プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam);
void ToggleFullscreen(HWND hWnd);	// ウィンドウをフルスクリーンにする方法

// グローバル変数宣言
bool g_bIsFullScreen = false;
RECT g_windowRect;						// ウィンドウを切り替えるための変数

//***********************************************************************************************************************
// メイン関数
//***********************************************************************************************************************
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					// WINDCLASSEXのサイズ
		CS_CLASSDC,							// ウィンドウのスタイル
		WindowProc,							// ウィンドウプロシージャ
		0,									// 0にする(通常は使用しない)
		0,									// 0にする(通常は使用しない)
		hInstance,							// インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),		// タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),			// マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			// クライアント領域の背景色
		NULL,								// メニューバー
		CLASS_NAME,							// ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)		// ファイルのアイコン
	};

	HWND hWnd;	// ウィンドウハンドル(識別子)
	MSG  msg;   // メッセージを格納する変数

	RECT rect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };   // 画面サイズの大きさ

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);
	// ウィンドウを生成
	hWnd = CreateWindowEx(0,				// 拡張ウィンドウスタイル
		CLASS_NAME,							// ウィンドウクラスの名前
		WINDOW_NAME,						// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,				// ウィンドウスタイル
		CW_USEDEFAULT,						// ウィンドウの左上X座標
		CW_USEDEFAULT,						// ウィンドウの左上Y座標
		(rect.right - rect.left),			// ウィンドウの幅
		(rect.bottom - rect.top),			// ウィンドウの高さ
		NULL,								// 親ウィンドウのハンドル
		NULL,								// メニューハンドルまたは子ウィンドウID
		hInstance,							// インスタンスハンドル
		NULL);								// ウィンドウ作成データ
	
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	if (FAILED(manager.Init(hInstance,hWnd, TRUE)))
	{// 初期化
		return -1;
	}

	ToggleFullscreen(hWnd);

	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);	// ウィンドウの表示状態を設定
	UpdateWindow(hWnd);			// クライアント領域を更新

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windowsの処理
			if (msg.message == WM_QUIT)
			{// WM_QUITメッセージを受け取ったらループを抜ける
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectXの処理
			// マネージャーの更新処理
			manager.Update();

			// マネージャーの描画処理
			manager.Draw();
		}
	}

	// マネージャーの終了処理
	manager.Uninit();

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return (int)msg.wParam;

}

//***********************************************************************************************************************
// ウィンドウプロシージャ
//***********************************************************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
	// ローカル変数宣言
	int nID;	// 返り値を格納
	switch (uMsg)
	{
	case WM_DESTROY:	// ウィンドウ破棄のメッセージ
		// WM_QUITへメッセージを送る
		PostQuitMessage(0);
		break;
	case WM_CLOSE:		// 閉じるボタン押下のメッセージ
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{// はいが押された場合
			DestroyWindow(hWnd);	// ウィンドウの破棄
		}
		else
		{// いいえが押された場合
			return 0;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:	// ESCキーが押されたとき
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{// はいが押された場合
				DestroyWindow(hWnd);	// ウィンドウを破棄する
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
	case WM_LBUTTONDOWN:	// マウス左クリックのメッセージ

		SetFocus(hWnd);	// ウィンドウにフォーカスを合わせる

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, IParam);	// 既定の処理を返す
}

//***********************************************************************************************************************
// ウィンドウをフルスクリーンに変える処理
//***********************************************************************************************************************
void ToggleFullscreen(HWND hWnd)
{
	// 現在のウィンドウスタイルを取得
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_bIsFullScreen)
	{
		// ウィンドウモードに切り替え
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// フルスクリーンモードに切り替え
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_bIsFullScreen = !g_bIsFullScreen;

}

