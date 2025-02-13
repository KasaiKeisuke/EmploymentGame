//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(input.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "input.h"

// 静的メンバ変数初期化
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//*******************************************************************************************************************************************
// 入力基底クラス
//*******************************************************************************************************************************************

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CInput::CInput()
{
	m_pInput = nullptr;
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CInput::~CInput()
{
	if (m_pInput != nullptr)
	{
		m_pInput->Release();

		m_pInput = nullptr;
	}
}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{
		// DirectInputデバイスオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}

	}

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CInput::Uninit()
{
	// デバイスの破棄
	if (m_pDevice != nullptr)
	{
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	// ポインタの破棄
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//*******************************************************************************************************************************************
// キーボードクラス処理
//*******************************************************************************************************************************************

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CInputKeyboard::CInputKeyboard()
{
	m_nPressTime = 0;

	for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		m_aKeyState[nCntKey] = NULL;			// プレス情報
		m_aKeyStateTrigger[nCntKey] = NULL;		// トリガー情報
	}
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CInputKeyboard::~CInputKeyboard()
{
	for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		m_aKeyState[nCntKey] = NULL;			// プレス情報
		m_aKeyStateTrigger[nCntKey] = NULL;		// トリガー情報
	}

}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// デバイスの初期化
	CInput::Init(hInstance, hWnd);

	// 入力デバイス(キーボードの生成)
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマット
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CInputKeyboard::Uninit()
{
	CInput::Uninit();	// デバイスの終了処理

	XInputEnable(false);
}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CInputKeyboard::Update()
{
	// ローカル変数宣言
	BYTE aKeyState[MAX_KEY];	// キーボードの入力情報

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];	// キーボードのトリガー情報を保存
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	// キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();	// キーボードのアクセス権を獲得
	}
}

//***********************************************************************************************************************
// プレス情報取得処理
//***********************************************************************************************************************
bool CInputKeyboard::GetPress(int nKey)
{
	return ((m_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

//***********************************************************************************************************************
// トリガー情報取得処理
//***********************************************************************************************************************
bool CInputKeyboard::GetTrigger(int nKey)
{
	return ((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}

//***********************************************************************************************************************
// リピート情報取得処理
//***********************************************************************************************************************
bool CInputKeyboard::GetRepeat(int nKey)
{
	if (GetPress(nKey))
	{
		if (GetTrigger(nKey))
		{
			m_nPressTime = 0;
			return true;
		}
		m_nPressTime++;

		if (m_nPressTime >= MAX_PRESSTIME)
		{// 押し続けて一定時間経ったら
			m_nPressTime = 0;

			return true;
		}
	}
	return false;
}

//***********************************************************************************************************************
// ジョイパッドクラス処理
//***********************************************************************************************************************

//***********************************************************************************************************************
// コンストラクタ
//***********************************************************************************************************************
CInputJoypad::CInputJoypad()
{
	m_pDevice = nullptr;

	memset(&m_JoykeyState, 0, sizeof(XINPUT_STATE));

	memset(&m_JoykeyStateTrigger, 0, sizeof(XINPUT_STATE));
}

//***********************************************************************************************************************
// デストラクタ
//***********************************************************************************************************************
CInputJoypad::~CInputJoypad()
{
	memset(&m_JoykeyState, 0, sizeof(XINPUT_STATE));

	memset(&m_JoykeyStateTrigger, 0, sizeof(XINPUT_STATE));

	m_JoykeyState = {};
	m_JoykeyStateTrigger = {};

	m_pDevice = nullptr;
}

//***********************************************************************************************************************
// 初期化処理
//***********************************************************************************************************************
HRESULT CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	// メモリのクリア
	memset(&m_JoykeyState, 0, sizeof(XINPUT_STATE));		// プレス情報

	// メモリのクリア
	memset(&m_JoykeyStateTrigger, 0, sizeof(XINPUT_STATE));	// トリガー情報

	// XInputのステートを設定(有効にする)
	XInputEnable(true);

	return S_OK;
}

//***********************************************************************************************************************
// 終了処理
//***********************************************************************************************************************
void CInputJoypad::Uninit()
{
	// メモリのクリア
	memset(&m_JoykeyState, 0, sizeof(XINPUT_STATE));		// プレス情報

	// メモリのクリア
	memset(&m_JoykeyStateTrigger, 0, sizeof(XINPUT_STATE));	// トリガー情報

	// XInputのステートを設定(無効にする)
	XInputEnable(false);
}

//***********************************************************************************************************************
// 更新処理
//***********************************************************************************************************************
void CInputJoypad::Update()
{
	// ローカル変数宣言
	XINPUT_STATE JoykeyState;			// ジョイパッドのプレス情報
	XINPUT_STATE JoykeyStateTrigger;	// ジョイパッドのトリガー情報

	// ジョイパッドの状態を取得
	if (XInputGetState(0, &JoykeyState) == ERROR_SUCCESS)
	{
		WORD Button = JoykeyState.Gamepad.wButtons;
		WORD OldButon = m_JoykeyState.Gamepad.wButtons;

		m_JoykeyStateTrigger.Gamepad.wButtons = ~OldButon & Button;
		m_JoykeyStateTrigger.Gamepad.bLeftTrigger = (m_JoykeyState.Gamepad.bLeftTrigger ^ JoykeyState.Gamepad.bLeftTrigger) & JoykeyState.Gamepad.bLeftTrigger;			// 左トリガー
		m_JoykeyStateTrigger.Gamepad.bRightTrigger = (m_JoykeyState.Gamepad.bRightTrigger ^ JoykeyState.Gamepad.bRightTrigger) & JoykeyState.Gamepad.bRightTrigger;		// 右トリガー

		m_JoykeyState = JoykeyState;	// ジョイパッドのプレス情報を保存
	}
	else
	{
		memset(&m_JoykeyStateTrigger, 0, sizeof(XINPUT_STATE));
	}
}

//***********************************************************************************************************************
// プレス情報取得処理
//***********************************************************************************************************************
bool CInputJoypad::GetPress(JOYKEY key)
{
	return((m_JoykeyState.Gamepad.wButtons) & (0x01 << key) ? true : false);
}

//***********************************************************************************************************************
// トリガー情報取得処理
//***********************************************************************************************************************
bool CInputJoypad::GetTrigger(JOYKEY key)
{
	return((m_JoykeyStateTrigger.Gamepad.wButtons) & (0x01 << key));
}

//***********************************************************************************************************************
// リピート情報取得処理(ジョイパッド)
//***********************************************************************************************************************
bool CInputJoypad::GetRepeat(JOYKEY key)
{
	if (GetPress(key))
	{
		if (GetTrigger(key))
		{
			m_nPressTime = 0;

			return true;
		}

		m_nPressTime++;

		if (m_nPressTime >= MAX_PRESSTIME)
		{// 押し続けて一定時間経ったら
			m_nPressTime = 0;

			return true;
		}

	}

	return false;
}

//***********************************************************************************************************************
// 左トリガーボタン取得処理
//***********************************************************************************************************************
bool CInputJoypad::GetLeftTrigger()
{
	return(m_JoykeyStateTrigger.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
}

//***********************************************************************************************************************
// 右トリガーボタン取得処理
//***********************************************************************************************************************
bool CInputJoypad::GetRightTrigger()
{
	return(m_JoykeyStateTrigger.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
}

//***********************************************************************************************************************
// 左スティックX軸処理
//***********************************************************************************************************************
float CInputJoypad::GetLeftThumbX()
{
	return static_cast<float>(m_JoykeyState.Gamepad.sThumbLX) / 32767.0f;
}

//***********************************************************************************************************************
// 左スティックY軸処理
//***********************************************************************************************************************
float CInputJoypad::GetLeftThumbY()
{
	return static_cast<float>(m_JoykeyState.Gamepad.sThumbLY) / 32767.0f;
}

//***********************************************************************************************************************
// 右スティックX軸処理
//***********************************************************************************************************************
float CInputJoypad::GetRightThumbX()
{
	return static_cast<float>(m_JoykeyState.Gamepad.sThumbRX) / 32000.0f;
}

//***********************************************************************************************************************
// 右スティックY軸処理
//***********************************************************************************************************************
float CInputJoypad::GetRightThumbY()
{
	return static_cast<float>(m_JoykeyState.Gamepad.sThumbRY) / 32000.0f;
}
