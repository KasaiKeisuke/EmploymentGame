//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(GameManager.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

// include
#include "main.h"

// ゲームマネージャークラスの定義
class CGameManager
{
public:
	CGameManager();				// コンストラクタ
	~CGameManager();			// デストラクタ
	HRESULT Init();				// 初期化処理
	void Uninit();				// 終了処理
	void Update();				// 更新処理

	void SetTimer(int nTime);	// 制限時間設定
	int GetTimer();				// 制限時間取得

	void SetScore(int nScore);	// スコア設定
	int GetScore();				// スコア取得

private:
	int m_nTime;				// 制限時間格納用
	int m_nScore;				// スコア格納用
};
#endif // !_GAMEMANAGER_H_
