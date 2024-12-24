//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(timer.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _TIMER_H_
#define _TIMER_H_

// include
#include "number.h"
#include "GameManager.h"
#include "object.h"

// タイマークラスの定義
class CTimer : public CObject
{
public:
	CTimer(int nPriority = 4);					// コンストラクタ
	~CTimer()override;							// デストラクタ
	HRESULT Init()override;						// 初期化処理
	void Uninit()override;						// 終了処理
	void Update()override;						// 更新処理
	void Draw()override;						// 描画処理
	static CTimer* Create();					// 生成処理

	static void Sub(int nTime);					// タイマー減算処理

	static const int MAX_DIGIT = 3;				// 最大桁数
private:
	CGameManager* m_pGameManager;				// ゲームマネージャークラスのポインタ

	static CNumber* m_aNumber[MAX_DIGIT];		// 数字クラスの情報
	static int m_nTimer;						// タイマー格納用
};
#endif