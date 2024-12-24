//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(game.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _GAME_H_
#define _GAME_H_

// include
#include "scene.h"
#include "input.h"
#include "PlayerParam.h"
#include "GameManager.h"
#include "timer.h"
#include "score.h"

// ゲーム画面クラスの定義
class CGame : public CScene
{
public:
	CGame();							// コンストラクタ
	~CGame();							// デストラクタ
	HRESULT Init()override;				// 初期化処理
	void Uninit()override;				// 終了処理
	void Update()override;				// 更新処理
	void Draw()override;				// 描画処理

private:
	CInputKeyboard* m_InputKeyboard;	// キーボードのポインタ
	CInputJoypad* m_InputJoypad;		// ジョイパッドのポインタ
	CParamManager* m_pParamManager;		// パラメーター管理クラスのポインタ
	CGameManager* m_pGameManager;		// ゲームマネージャークラスのポインタ

	static const int FIELD_SIZE = 500;	// 床の大きさ

	int m_nTime;						// 制限時間
};
#endif