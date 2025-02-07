//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(scene.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "scene.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "bg.h"
#include "TitleLogo.h"
#include "cursor.h"
#include "menu.h"
#include "Guid.h"

#include "manager.h"

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CScene::CScene()
{

}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CScene::~CScene()
{

}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CScene::Init()
{
	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CScene::Uninit()
{
	CObject2D::ReleaseAll();
}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CScene::Update()
{

}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CScene::Draw()
{

}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = nullptr;

	switch (mode)
	{
	case MODE_TITLE:
		pScene = new CTitle();

		//******************************************
		// 背景
		//******************************************
		CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CBg::TEXTYPE::TYPE_TITLE);

		//******************************************
		// 選択肢
		//******************************************
		CMenu::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 150.0f, 0.0f), 150.0f, 100.0f, CMenu::MENUTYPE::MENU_TUTORIAL);

		CMenu::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f + 150.0f, 0.0f), 150.0f, 100.0f, CMenu::MENUTYPE::MENU_GAME);

		//******************************************
		// タイトルロゴ
		//******************************************
		CTitleLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 370.0f, 0.0f), 500.0f, 100.0f);

		//******************************************
		// カーソル
		//******************************************
		CCursor::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 250.0f, SCREEN_HEIGHT / 2.0f - 150.0f, 0.0f), 50.0f, 50.0f);

		//******************************************
		// ガイド
		//******************************************
		CGuid::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 400.0f, SCREEN_HEIGHT / 2.0f + 400.0f, 0.0f), 150.0f, 150.0f, CGuid::TEXTURETYPE::TYPE_STARTGAME);

		break;
	case MODE_TUTORIAL:
		pScene = new CTutorial();

		//******************************************
		// 背景
		//******************************************
		CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CBg::TEXTYPE::TYPE_TUTORIAL);
	
		//******************************************
		// ガイド
		//******************************************
		CGuid::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 600.0f, SCREEN_HEIGHT / 2.0f + 400.0f, 0.0f), 250.0f, 150.0f, CGuid::TEXTURETYPE::TYPE_RETURNTITLE);

		break;
	case MODE_GAME:
		pScene = new CGame();

		break;
	case MODE_CLEARRESULT:
		pScene = new CResult();

		//******************************************
		// 背景
		//******************************************
		CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CBg::TEXTYPE::TYPE_CLEARRESULT);

		//******************************************
		// ガイド
		//******************************************
		CGuid::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 400.0f, SCREEN_HEIGHT / 2.0f + 400.0f, 0.0f), 200.0f, 150.0f, CGuid::TEXTURETYPE::TYPE_RETURNTITLE);

		break;
	case MODE_FAILRESULT:
		pScene = new CResult();

		//******************************************
		// 背景
		//******************************************
		CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CBg::TEXTYPE::TYPE_FAILRESULT);

		//******************************************
		// ガイド
		//******************************************
		CGuid::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 400.0f, SCREEN_HEIGHT / 2.0f + 400.0f, 0.0f), 200.0f, 150.0f, CGuid::TEXTURETYPE::TYPE_RETURNTITLE);

		break;
	}

	pScene->SetMode(mode);

	if (pScene != nullptr)
	{
		pScene->Init();

		return pScene;
	}

	return nullptr;
}

//*******************************************************************************************************************************************
// モード設定処理
//*******************************************************************************************************************************************
void CScene::SetMode(MODE mode)
{
	m_Mode = mode;
}

//*******************************************************************************************************************************************
// モード取得
//*******************************************************************************************************************************************
CScene::MODE CScene::GetMode()
{
	return m_Mode;
}
