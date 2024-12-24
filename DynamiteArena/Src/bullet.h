//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(bullet.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _BULLET_H_
#define _BULLET_H_

// include
#include "objectX.h"
#include "PlayerParam.h"

// 爆弾クラスの定義
class CBullet : public CObjectX
{
public:
	CBullet(int nPriority = 3);										// コンストラクタ
	~CBullet()override;												// デストラクタ
	HRESULT Init()override;											// 初期化処理
	void Uninit()override;											// 終了処理
	void Update()override;											// 更新処理
	void Draw()override;											// 描画処理
	static CBullet* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move);		// 生成処理

	bool IsBlockPos(D3DXVECTOR3 pos, float fWidth, float fDepth);	// ブロックがあるかどうか

	bool CollisionBullet(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size, int nType);	// 当たり判定

	static const int UI_TIMING = 120;								// UIを表示させるタイミング
	static const int DELETE_BULLET = 240;							// 弾の消すタイミング
	static const int NUM_EXPLOSION = 15;							// 爆発の生成個数(1方向)
	static const int FALL_INDEX = 2;								// 弾の落下地点のインデックス

private:
	void Move();													// 移動
	void Death();													// 警告表示UI出現判定
	void Motion();													// 弾のモーション

	CParamManager* m_pParamManager;									// パラメーター管理クラスのポインタ

	D3DXVECTOR3 m_Move;												// 移動量
	bool m_bDeath;													// 使用されているかどうか
	bool m_bScale;													// 拡縮用フラグ

	float m_fGravity;												// 弾の重力
	float m_fInitialYSpeed;											// Y軸方向の初速度

	bool m_bHitObstacle;											// 障害物に当たったかどうか

	int m_nLag;														// 地面についてから消えるまでの時間

	int m_nNotCollision;											// 当たり判定が機能しない時間
};

static const float BULLET_LIFE = 170.0f;							// 弾の寿命
static const float CAVEAT_SPAN = 15.0f;								// 警告表示UIの表示させる幅の間隔
static const float POLYGON_SIZE = 10.0f;							// 警告表示UIの大きさ(半径)

static const float MOTION_SPEEDFAST = 0.05f;						// モーション速度(速い)
static const float MOTION_SPEEDLATE = 0.01f;						// モーション速度(遅い)

static const float MIN_BULLETSCALE = 1.0f;								// 最小の大きさ
static const float MAX_BULLETSCALE = 1.5f;								// 最大の大きさ
#endif

