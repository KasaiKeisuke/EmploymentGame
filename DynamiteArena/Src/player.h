//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(player.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _PLAYER_H_
#define _PLAYER_H_

// include
#include "objectX.h"
#include "input.h"
#include "camera.h"
#include "PlayerParam.h"

// プレイヤークラスの定義
class CPlayer : public CObjectX
{
public:
	CPlayer(int nPriority = 3);					// コンストラクタ
	~CPlayer()override;							// デストラクタ
	HRESULT Init()override;						// 初期化処理
	void Uninit()override;						// 終了処理
	void Update()override;						// 更新処理
	void Draw()override;						// 描画処理
	static CPlayer* Create(D3DXVECTOR3 pos);	// 生成処理

	static const int COOLDOWN = 250;			// 弾発射のクールダウン

	static const int SHAKE_FRAME = 30;			// カメラを揺らす時間

	static const int DAMAGE_TIME = 80;			// ダメージ演出時間
	static const int GOAL_TIME = 100;			// ゴール演出時間

private:
	void Move();								// 移動
	void Attack();								// 攻撃
	void Damage(int nCnt);						// 被弾判定
	void GoalParformance(int nCnt);				// ゴール演出
	void Motion(D3DXVECTOR3 &rot);				// モーション処理

	CInputKeyboard* m_InputKeyboard;			// キーボードのポインタ
	CInputJoypad* m_InputJoypad;				// ジョイパッドのポインタ
	CCamera* m_pCamera;							// カメラのポインタ
	CParamManager* m_pParamManager;				// パラメーター管理クラスのポインタ

	D3DXVECTOR3 m_Move;							// 移動量
	
	int m_nLife;								// プレイヤーの体力
	bool m_bHit;								// 当たったかどうか(プレイヤーと壁)
	bool m_bDamage;								// 当たったかどうか(プレイヤーと爆弾)
	bool m_bDeath;								// 当たったかどうか(プレイヤーと敵)
	bool m_bGoal;								// 当たったかどうか(プレイヤーとゴール)

	int m_nCoolCount;							// クールダウンカウント用
	bool m_bHasFired;							// 1発目の弾かどうか

	int m_nCnt;									// ゴール演出の時間
	int m_nDeathCnt;							// 死亡演出の時間

	float m_fShake;								// カメラを揺らす時間

	bool m_bRot;								// モーション用フラグ
};

static const float CAMERA_SHAKE = 5.0f;			// カメラを揺らす量の最大値
static const float PLAYER_SPEED = 1.3f;			// プレイヤーの移動速度

static const float MAX_MOTIONROT = 0.5f;		// モーションで回転させる最大量
static const float MOTION_SPEED = 0.05f;		// モーション速度
#endif