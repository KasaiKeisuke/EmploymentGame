//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(score.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _SCORE_H_
#define _SCORE_H_

// include 
#include "object.h"
#include "number.h"
#include "GameManager.h"

// スコアクラスの定義
class CScore : public CObject
{
public:
	CScore(int nPriority = 4);				// コンストラクタ
	~CScore()override;						// デストラクタ
	HRESULT Init()override;					// 初期化処理
	void Uninit()override;					// 終了処理
	void Update()override;					// 更新処理
	void Draw()override;					// 描画処理
	static CScore* Create();				// 生成処理

	static void Add(int nScore);			// スコア加算処理

	static const int MAX_DIGIT = 8;			// スコアの桁数

private:
	static CNumber* m_aNumber[MAX_DIGIT];	// 数字の情報
	CGameManager* m_pGameManager;			// ゲームマネージャークラスのポインタ

	static int m_nScore;					//現在のスコア
};
#endif