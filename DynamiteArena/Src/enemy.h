//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(enemy.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _ENEMY_H_
#define _ENEMY_H_

// include
#include "objectX.h"

// 敵クラスの定義
class CEnemy : public CObjectX
{
public:
	CEnemy(int nPriority = 3);																	// コンストラクタ
	~CEnemy()override;																			// デストラクタ
	HRESULT Init()override;																		// 初期化処理
	void Uninit()override;																		// 終了処理
	void Update()override;																		// 更新処理
	void Draw()override;																		// 描画処理
	static CEnemy* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move);									// 生成処理
	
	bool CollisionEnemy(D3DXVECTOR3* pos, D3DXVECTOR3 size, int nType);							// 当たり判定(敵と他のオブジェクト)

	static void Load();																			// ロード処理
private:
	void Move();																				// 移動処理
	void Death(int nCnt);																		// 死亡判定
	void Motion(D3DXVECTOR3 &rot);																// モーション処理

	int m_nCnt;

	int m_nLife;																				// 寿命
	D3DXVECTOR3 m_Move;																			// 移動量

	bool m_bHit;																				// 被弾したかどうか
	bool m_bHitObstacle;																		// 障害物に当たったかどうか(ブロックや壁)
	bool m_bMoveRot;																			// 進行方向判定用フラグ
	bool m_bRot;																				// モーション用フラグ
};

static const float ENEMY_SPEED = 0.5f;															// 敵の移動速度
static const float ENEMY_MOTIONROT = 0.5f;														// モーションの角度
static const float ENEMY_MOTIONSPEED = 0.01f;													// モーション速度
#endif