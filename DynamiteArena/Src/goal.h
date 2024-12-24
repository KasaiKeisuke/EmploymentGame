//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(goal.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _GOAL_H_
#define _GOAL_H_

// include
#include "objectX.h"

// ゴールマーカークラスの定義
class CGoal : public CObjectX
{
public:
	CGoal(int nPriority = 3);																	// コンストラクタ
	~CGoal()override;																			// デストラクタ
	HRESULT Init()override;																		// 初期化処理
	void Uninit()override;																		// 終了処理
	void Update()override;																		// 更新処理
	void Draw()override;																		// 描画処理
	static CGoal* Create(D3DXVECTOR3 pos);														// 生成処理

	bool CollisionGoal(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size, int nType);		// 当たり判定
};
#endif