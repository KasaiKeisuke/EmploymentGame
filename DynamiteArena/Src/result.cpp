//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(result.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "result.h"
#include "manager.h"

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CResult::CResult()
{
	m_InputKeyboard = nullptr;	// キーボードのポインタ
	m_InputJoypad = nullptr;	// ジョイパッドのポインタ
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CResult::~CResult()
{
	m_InputKeyboard = nullptr;	// キーボードのポインタ
	m_InputJoypad = nullptr;	// ジョイパッドのポインタ
}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CResult::Init()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	m_InputKeyboard = manager.GetKeyboard();

	m_InputJoypad = manager.GetJoypad();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CResult::Uninit()
{
	// シーン基底クラスの終了処理
	CScene::Uninit();
}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CResult::Update()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	if (m_InputKeyboard != nullptr && m_InputJoypad != nullptr)
	{
		if (m_InputJoypad->GetTrigger(CInputJoypad::JOYKEY_A))
		{// Aボタンが押されたらタイトル画面に移行
			manager.SetMode(CScene::MODE::MODE_TITLE);
		}
	}

}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CResult::Draw()
{

}
