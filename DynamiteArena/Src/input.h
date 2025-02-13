//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(input.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _INPUT_H_
#define _INPUT_H_

// include
#include "main.h"
#include "renderer.h"

// マクロ定義
#define MAX_KEY	(256)	// キーの最大数

//******************************************
// 入力基底クラス(DirectInputの管理)の定義
//******************************************
class CInput
{
public:
	CInput();												// コンストラクタ
	~CInput();												// デストラクタ
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	virtual void Uninit();									// 終了処理
	virtual void Update() = 0;								// 更新処理(入力端末ごとに必要)

	const static int MAX_PRESSTIME = 5;						// 最大の長押し時間	
protected:
	static LPDIRECTINPUT8 m_pInput;							// DirectInputオブジェクトへのポインタ
	LPDIRECTINPUTDEVICE8 m_pDevice;							// 入力デバイスのポインタ
	int m_nPressTime;										// キーやボタンを押し続けた時間
};

//******************************************
// キーボードクラスの定義
//******************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();										// コンストラクタ
	~CInputKeyboard();										// デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;	// 初期化処理
	void Uninit()override;									// 終了処理
	void Update()override;									// 更新処理

	bool GetPress(int nKey);								// プレス情報取得
	bool GetTrigger(int nKey);								// トリガー情報
	bool GetRepeat(int nKey);								// リピート情報

private:
	BYTE m_aKeyState[MAX_KEY];
	BYTE m_aKeyStateTrigger[MAX_KEY];
};

//******************************************
// ジョイパッドクラスの定義
//******************************************
class CInputJoypad : public CInput
{
public:
	// ジョイパッドのボタン配置
	typedef enum
	{
		JOYKEY_UP = 0,											// 十字キー(上)
		JOYKEY_DOWN,											// 十字キー(下)
		JOYKEY_LEFT,											// 十字キー(左)
		JOYKEY_RIGHT,											// 十字キー(右)
		JOYKEY_START,											// スタートボタン
		JOYKEY_BACK,											// バックボタン
		JOYKEY_LEFT_THUMB,										// 左スティック(押し込み)
		JOYKEY_RIGHT_THUMB,										// 右スティック(押し込み)
		JOYKEY_LEFT_SHOULDER,									// LBボタン
		JOYKEY_RIGHT_SHOULDER,									// RBボタン
		JOYKEY_AUTO,											// オートボタン
		JOYKEY_CLEAR,											// クリアボタン
		JOYKEY_A,												// Aボタン
		JOYKEY_B,												// Bボタン
		JOYKEY_X,												// Xボタン
		JOYKEY_Y,												// Yボタン
		JOYKEY_ZR,												// RTボタン
		JOYKEY_ZL,												// LTボタン
		JOYKEY_MAX
	}JOYKEY;

	CInputJoypad();												// コンストラクタ
	~CInputJoypad();											// デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;		// 初期化処理
	void Uninit()override;										// 終了処理
	void Update()override;										// 更新処理

	bool GetPress(JOYKEY key);									// プレス情報取得
	bool GetTrigger(JOYKEY key);								// トリガー情報取得
	bool GetRepeat(JOYKEY key);									// リピート情報

	bool GetLeftTrigger();										// 左トリガーボタン
	bool GetRightTrigger();										// 右トリガーボタン

	float GetLeftThumbX();										// 左スティックのX軸
	float GetLeftThumbY();										// 左スティックのY軸
	float GetRightThumbX();										// 右スティックのX軸
	float GetRightThumbY();										// 右スティックのY軸 

private:
	XINPUT_STATE m_JoykeyState;									// ジョイパッドのプレス情報
	XINPUT_STATE m_JoykeyStateTrigger;							// ジョイパッドのトリガー情報


};
#endif