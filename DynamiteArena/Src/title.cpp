//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(title.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "scene.h"
#include "title.h"
#include "manager.h"

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CTitle::CTitle()
{
	m_InputKeyboard = nullptr;	// キーボードのポインタ
	m_InputJoypad = nullptr;	// ジョイパッドのポインタ
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CTitle::~CTitle()
{
	m_InputKeyboard = nullptr;	// キーボードのポインタ
	m_InputJoypad = nullptr;	// ジョイパッドのポインタ
}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CTitle::Init()
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
void CTitle::Uninit()
{
	// シーン基底クラスの終了処理
	CScene::Uninit();
}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CTitle::Update()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	if (m_InputKeyboard != nullptr && m_InputJoypad != nullptr)
	{
		if (m_InputKeyboard->GetTrigger(DIK_RETURN) || m_InputJoypad->GetTrigger(CInputJoypad::JOYKEY_A))
		{// ENTERキー or Aボタンが押されたらゲーム画面に移行
			manager.SetMode(CScene::MODE::MODE_TUTORIAL);
		}
	}

}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CTitle::Draw()
{

}
