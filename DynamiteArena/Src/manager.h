//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(manager.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _MANAGER_H_
#define _MANAGER_H_

// include
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "PlayerParam.h"
#include "GameManager.h"
#include "ItemManager.h"

// マネージャークラスの定義
class CManager
{
public:
	// シングルトンインスタンスを取得する
	static CManager& GetInstance()
	{
		static CManager instance;
		return instance;
	}

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	// 初期化処理
	void Uninit();												// 終了処理
	void Update();												// 更新処理
	void Draw();												// 描画処理

	CRenderer* GetRenderer();									// レンダラー取得処理
	CInputKeyboard* GetKeyboard();								// キーボード取得
	CInputJoypad* GetJoypad();									// ジョイパッド取得
	CCamera* GetCamera();										// カメラの取得処理
	CLight* GetLight();											// ライトの取得処理
	CParamManager* GetParamManager();							// パラメーター管理クラスのポインタ取得
	CGameManager* GetGameManager();								// ゲームマネージャー取得処理
	CItemManager* GetItemManager();								// アイテムマネージャークラスのポインタ取得

	void SetMode(CScene::MODE mode);							// モード設定処理

	void SetGoal(bool bGoal);									// ゴールフラグ設定処理
	bool GetGoal();												// ゴールフラグ取得処理

private:
	CManager();													// コンストラクタ
	~CManager();												// デストラクタ

	CManager(const CManager&) = delete;
	CManager& operator = (const CManager&) = delete;

	CRenderer* m_pRenderer;										// レンダラーのポインタ
	CInputKeyboard* m_InputKeyboard;							// キーボードのポインタ
	CInputJoypad* m_InputJoypad;								// ジョイパッドのポインタ
	CCamera* m_pCamera;											// カメラのポインタ
	CLight* m_pLight;											// ライトのポインタ	
	CScene* m_pScene;											// シーンのポインタ
	CParamManager* m_pParamManager;								// パラメーター管理クラスのポインタ		
	CGameManager* m_pGameManager;								// ゲームマネージャークラスのポインタ
	CItemManager* m_pItemManager;								// アイテムマネージャークラスのポインタ

	bool m_bGoal;												// ゴール判定用フラグ

};
#endif