//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(game.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include 
//*************************************************
// System
//*************************************************
#include "manager.h"

//*************************************************
// Scene
//*************************************************
#include "game.h"

//*************************************************
// Object
//*************************************************
#include "bullet.h"
#include "explosion.h"
#include "player.h"
#include "caveat.h"
#include "block.h"
#include "field.h"
#include "goal.h"
#include "wall.h"
#include "item.h"
#include "enemy.h"

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CGame::CGame()
{
	m_InputKeyboard = nullptr;	// キーボードのポインタ
	m_InputJoypad = nullptr;	// ジョイパッドのポインタ
	m_pParamManager = nullptr;	// パラメーター管理クラスのポインタ
	m_pGameManager = nullptr;	// ゲームマネージャークラスのポインタ
	m_pItemManager = nullptr;	// アイテムマネージャークラスのポインタ
	m_nTime = 0;
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CGame::~CGame()
{
	m_InputKeyboard = nullptr;	// キーボードのポインタ
	m_InputJoypad = nullptr;	// ジョイパッドのポインタ
	m_pParamManager = nullptr;	// パラメーター管理クラスのポインタ
	m_pGameManager = nullptr;	// ゲームマネージャークラスのポインタ
	m_pItemManager = nullptr;	// アイテムマネージャークラスのポインタ
	m_nTime = 0;
}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CGame::Init()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	m_InputKeyboard = manager.GetKeyboard();

	m_InputJoypad = manager.GetJoypad();

	m_pParamManager = manager.GetParamManager();

	m_pGameManager = manager.GetGameManager();

	m_pItemManager = manager.GetItemManager();

	// 警告表示Uiのテクスチャロード
	CCaveat::Load();

	// 床のテクスチャのロード
	CField::Load();

	// 爆発オブジェクトのロード
	CExplosion::Load();
	
	// ブロックのロード処理
	CBlock::Load();

	// 壁のロード処理
	CWall::Load();

	// 敵のロード処理
	CEnemy::Load();

	// 数字のテクスチャロード
	CNumber::Load();

	// パラメーター管理クラスの初期化処理
	if (m_pParamManager != nullptr)
	{
		m_pParamManager->Init();
	}

	// ゲームマネージャークラスの初期化処理
	if (m_pGameManager != nullptr)
	{
		m_pGameManager->Init();
	}

	// アイテムマネージャークラスの初期化処理
	if (m_pItemManager != nullptr)
	{
		m_pItemManager->Init();
	}

	// プレイヤーの生成
	CPlayer::Create(D3DXVECTOR3(-180.0f, 12.0f, -150.0f));

	// 床の生成
	CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 0.0f, 170.0f);

	// ゴールマーカーの生成
	CGoal::Create(D3DXVECTOR3(180.0f, 0.0f, 150.0f));


	// ゲーム2周目以降カメラの向きがバグらないように初期化
	manager.GetCamera()->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 制限時間の設定
	m_nTime = 180;

	// タイマーの設定
	m_pGameManager->SetTimer(m_nTime);

	// タイマーの生成
	CTimer::Create();

	// スコアの生成
	CScore::Create();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CGame::Uninit()
{
	// 床のテクスチャの破棄
	CField::UnLoad();

	// 警告表示UIテクスチャ破棄
	CCaveat::UnLoad();

	// シーン基底クラスの終了処理
	CScene::Uninit();

	// パラメーター管理クラスの終了処理
	if (m_pParamManager != nullptr)
	{
		m_pParamManager->Uninit();
	}

	// ゲームマネージャークラスの終了処理
	if (m_pGameManager != nullptr)
	{
		m_pGameManager->Uninit();
	}

	// アイテムマネージャークラスの終了処理
	if (m_pItemManager != nullptr)
	{
		m_pItemManager->Uninit();
	}
}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CGame::Update()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	bool bGameClear = manager.GetGoal();

	int nTime = m_pGameManager->GetTimer();

	if (bGameClear)
	{
		manager.SetMode(CScene::MODE::MODE_CLEARRESULT);
	
		manager.SetGoal(false);	// ゴールしたらフラグリセット
	}
	else
	{
		// タイマーの更新
		m_nTime--;

		if (m_nTime % 60 == 0)
		{
			CTimer::Sub(1);
		}


		//パラメーター管理クラスの更新処理
		if (m_pParamManager != nullptr)
		{
			m_pParamManager->Update();
		}

		// ゲームマネージャークラスの更新処理
		if (m_pGameManager != nullptr)
		{
			m_pGameManager->Update();
		}

		// アイテムマネージャークラスの更新処理
		if (m_pItemManager != nullptr)
		{
			m_pItemManager->Update();
		}

	}

	if (nTime <= 0)
	{
		manager.SetMode(CScene::MODE::MODE_FAILRESULT);
	}
}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CGame::Draw()
{

}