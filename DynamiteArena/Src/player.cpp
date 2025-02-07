//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(player.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "player.h"
#include "manager.h"
#include "bullet.h"
#include "camera.h"
#include "block.h"
#include "goal.h"
#include "explosion.h"
#include "wall.h"
#include "enemy.h"
#include <cmath>
#include "item.h"
#include "PlayerParam.h"

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CPlayer::CPlayer(int nPriority):CObjectX(nPriority)
{
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量
	
	m_InputKeyboard = nullptr;				// キーボードのポインタ
	m_InputJoypad = nullptr;
	m_pCamera = nullptr;					// カメラのポインタ
	m_pParamManager = nullptr;				// パラメータ管理クラスのポインタ

	m_bHit = false;							// 当たったかどうか(プレイヤーと壁)
	m_bDamage = false;						// 当たったかどうか(プレイヤーと爆弾)
	m_bDeath = false;						// 当たったかどうか(プレイヤーと敵)
	m_bGoal = false;						// 当たったかどうか(プレイヤーとゴールマーカー)

	m_nCoolCount = 0;						// クールダウンカウント用
	m_bHasFired = false;					// 最初の弾かどうか
	m_nLife = 0;
	m_fShake = SHAKE_FRAME;					// カメラを揺らす時間

	m_bRot = true;
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CPlayer::~CPlayer()
{
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量

	m_InputKeyboard = nullptr;				// キーボードのポインタ
	m_InputJoypad = nullptr;
	m_pCamera = nullptr;					// カメラのポインタ
	m_pParamManager = nullptr;				// パラメータ管理クラスのポインタ

	m_bHit = false;							// 当たったかどうか(プレイヤーと壁)
	m_bDamage = false;						// 当たったかどうか(プレイヤーと爆弾)
	m_bDeath = false;						// 当たったかどうか(プレイヤーと敵)
	m_bGoal = false;						// 当たったかどうか(プレイヤーとゴールマーカー)

	m_nCoolCount = 0;						// クールダウンカウント用
	m_bHasFired = false;					// 最初の弾かどうか
	m_nLife = 0;
	m_fShake = SHAKE_FRAME;					// カメラを揺らす時間

}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CPlayer::Init()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	m_InputKeyboard = manager.GetKeyboard();	// キーボードの情報

	m_InputJoypad = manager.GetJoypad();		// ジョイパッドの情報
	
	m_pCamera = manager.GetCamera();			// カメラのポインタ

	m_pParamManager = manager.GetParamManager();

	// Xファイルオブジェクトの初期化処理
	CObjectX::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CPlayer::Uninit()
{
	// Xファイルオブジェクトの終了処理
	CObjectX::Uninit();

	// プレイヤーの破棄
	Release();

}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CPlayer::Update()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	// Xファイルオブジェクトの更新処理
	CObjectX::Update();

	if (m_nLife > 0)
	{// 体力があるとき
		if (!m_bGoal)
		{
			// 移動処理
			Move();

			// 攻撃処理
			Attack();

			if (m_bDamage)
			{
				m_nLife = 0;
			}

			if (m_bDeath)
			{
				m_nLife = 0;
			}

		}
		else
		{
			// ゴール演出の更新
			if (m_nCnt > 0)
			{
				D3DXVECTOR3 CurrentPos = GetPos();
				D3DXVECTOR3 CurrentRot = GetRot();

				CurrentPos.y += 1.0f;	// 少しずつy座標を高くする
				CurrentRot.y -= 0.3f;	// 少しずつ回転

				SetPos(CurrentPos);
				SetRot(CurrentRot);

				m_nCnt--; // カウントダウン
			}
			else
			{
				manager.SetGoal(true);
			}
		}

		
	}
	else
	{// 体力がないとき
		if (m_nDeathCnt > 0)
		{
			m_nDeathCnt--;	// カウントダウン

			SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f,0.8f));	// マテリアルの色変更
		}
		else
		{
			CPlayer::Uninit();

			manager.SetMode(CScene::MODE::MODE_FAILRESULT);
		}

	}

}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CPlayer::Draw()
{
	// Xファイルオブジェクトの描画処理
	CObjectX::Draw();
}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer* pPlayer = new CPlayer();

	pPlayer->Init();											// 初期化処理

	pPlayer->SetPos(pos);										// 位置設定

	pPlayer->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// 向き設定

	pPlayer->BindFileName("data\\MODEL\\PLAYER\\player000.x");	// 読み込むモデル設定

	pPlayer->SetModelSize();									// モデルの頂点情報設定

	pPlayer->SetType(CObject::OBJECTTYPE::TYPE_PLAYER);			// モデルの種類設定

	pPlayer->m_nLife = 1;										// プレイヤーの体力
	
	return nullptr;
}

//*******************************************************************************************************************************************
// 移動処理
//*******************************************************************************************************************************************
void CPlayer::Move()
{
	//*******************************************************************************************
	// TPS視点のプレイヤー移動
	//*******************************************************************************************

	// ローカル変数宣言
	D3DXVECTOR3 CurrentPos = GetPos();						// プレイヤーの現在の位置
	D3DXVECTOR3 CurrentRot = GetRot();						// プレイヤーの現在の向き
	// プレイヤーの1つ前の位置の取得
	D3DXVECTOR3 CurrentPosOld = GetPosOld();

	// プレイヤーモデルの大きさの取得
	D3DXVECTOR3 CurrentSize = GetModelSize();

	D3DXVECTOR3 AdjustMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量調整
	D3DXVECTOR3 CameraRot = m_pCamera->GetRot();			// カメラの向き

	float fCurrentSpeed = m_pParamManager->GetSpeed();

	float fLengthMove = 0.0f;								// プレイヤーの移動速度

	//**************************************
	// ジョイスティックの移動
	//**************************************
	m_Move.x += m_InputJoypad->GetLeftThumbX();
	m_Move.z += m_InputJoypad->GetLeftThumbY();

	// 移動量の計算
	if (m_Move.x != 0.0f || m_Move.z != 0.0f)
	{
		//CurrentRot.x = 0.0f;
		//CurrentRot.z = 0.0f;

		// カメラの向きを基準に移動量を調整
		float sinYaw = sinf(CameraRot.y);
		float cosYaw = cosf(CameraRot.y);

		// カメラ基準での移動ベクトルの変換
		AdjustMove.x = m_Move.z * sinYaw + m_Move.x * cosYaw;
		AdjustMove.z = m_Move.z * cosYaw - m_Move.x * sinYaw;

		// 対角線の長さを算出し正規化
		fLengthMove = sqrtf(AdjustMove.x * AdjustMove.x + AdjustMove.z * AdjustMove.z);
		AdjustMove.x /= fLengthMove;
		AdjustMove.z /= fLengthMove;

		// 移動量をスケール調整 (必要なら速度を掛ける)
		AdjustMove.x *= fCurrentSpeed;
		AdjustMove.z *= fCurrentSpeed;

		// 位置の更新
		CurrentPos += AdjustMove;

		// 向きの更新 (TPS視点では移動方向にプレイヤーが向く場合が多い)
		if (AdjustMove.x != 0.0f || AdjustMove.z != 0.0f)
		{
			CurrentRot.y = atan2f(-AdjustMove.x, -AdjustMove.z);
		}

		// 移動量のリセット
		m_Move.x = 0.0f;
		m_Move.z = 0.0f;
	}
	
	//Motion(CurrentRot);

	for (int nCntPriority = 0; nCntPriority < DRAW_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECTX; nCntObj++)
		{
			// オブジェクト情報取得
			CObject* pObj = nullptr;

			pObj = CObject::GetObjectInfo(nCntPriority, nCntObj);

			if (pObj != nullptr)
			{
				// 種類の取得
				CObject::OBJECTTYPE type = pObj->GetType();

				if (type == CObject::OBJECTTYPE::TYPE_BLOCK)
				{
					CBlock* pBlock = (CBlock*)pObj;

					m_bHit = pBlock->CollisionBlock(&CurrentPos, &CurrentPosOld, CurrentSize,CObject::OBJECTTYPE::TYPE_PLAYER);

					if (m_bHit)
					{
						break;		// 上書を防ぐ
					}
				}
				else if (type == CObject::OBJECTTYPE::TYPE_GOAL)
				{
					CGoal* pGoal = (CGoal*)pObj;

					m_bGoal = pGoal->CollisionGoal(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_PLAYER);
				
					if (m_bGoal)
					{
						break;	// 上書を防ぐ
					}
				}
				else if (type == CObject::OBJECTTYPE::TYPE_EXPLOSION)
				{
					CExplosion* pExplosion = (CExplosion*)pObj;

					m_bDamage = pExplosion->CollisionExplosion(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_PLAYER);
				
					if (m_bDamage)
					{
						break;	// 上書を防ぐ
					}
				}
				else if (type == CObject::OBJECTTYPE::TYPE_BULLET)
				{
					CBullet* pBullet = (CBullet*)pObj;

					pBullet->CollisionBullet(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_PLAYER);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_NORMALWALL)
				{
					CWall* pWall = (CWall*)pObj;

					pWall->CollisionWall(&CurrentPos, &CurrentPosOld, CurrentSize,CObject::OBJECTTYPE::TYPE_NORMALWALL ,CObject::OBJECTTYPE::TYPE_PLAYER);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_SIDEWALL)
				{
					CWall* pWall = (CWall*)pObj;

					pWall->CollisionWall(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_SIDEWALL, CObject::OBJECTTYPE::TYPE_PLAYER);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_ENEMY)
				{
					CEnemy* pEnemy = (CEnemy*)pObj;

					m_bDeath = pEnemy->CollisionEnemy(&CurrentPos, CurrentSize, CObject::OBJECTTYPE::TYPE_PLAYER);
				
					if (m_bDeath)
					{
						break;
					}
				}
				else if (type == CObject::OBJECTTYPE::TYPE_ITEM)
				{
					CItem* pItem = (CItem*)pObj;

					m_bHit = pItem->CollisionItem(&CurrentPos, CurrentSize, CObject::OBJECTTYPE::TYPE_PLAYER);

				}
			}
		}
	}

	m_pCamera->FollowCamera(CurrentPos);	// カメラ追従
	
	if (m_bDamage || m_bDeath)
	{// ダメージ演出時間設定
		Damage(DAMAGE_TIME);
	}

	if (m_bGoal)
	{// ゴール演出時間設定
		GoalParformance(GOAL_TIME);
	}

	SetPos(CurrentPos);		// 位置の設定
	SetRot(CurrentRot);		// 向きの設定
}

//*******************************************************************************************************************************************
// 攻撃処理
//*******************************************************************************************************************************************
void CPlayer::Attack()
{
	D3DXVECTOR3 CurrentPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 CurrentRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CurrentPos = GetPos();
	CurrentRot = GetRot();

	if (m_bHasFired)
	{// 初弾以外カウントを加算
		// クールダウン用カウントを加算
		m_nCoolCount++;
	}

	if (!m_bHasFired || m_nCoolCount >= COOLDOWN)
	{// クールダウン時間を経過したら
		if (m_InputJoypad->GetTrigger(CInputJoypad::JOYKEY_B))
		{// SPACE(攻撃)キーが押された
			CBullet::Create(D3DXVECTOR3(CurrentPos.x,1.0f,CurrentPos.z), D3DXVECTOR3(sinf(CurrentRot.y + D3DX_PI) * 5.0f, 0.0f, cosf(CurrentRot.y + D3DX_PI) * 5.0f));
		
			m_nCoolCount = 0;

			m_bHasFired = true;
		}

	}
}

//*******************************************************************************************************************************************
// 被弾処理
//*******************************************************************************************************************************************
void CPlayer::Damage(int nCnt)
{
	m_nDeathCnt = nCnt;		// 演出時間を設定
}

//*******************************************************************************************************************************************
// ゴール演出処理
//*******************************************************************************************************************************************
void CPlayer::GoalParformance(int nCnt)
{
	m_nCnt = nCnt;			// 演出時間を設定
}

//*******************************************************************************************************************************************
// モーション処理
//*******************************************************************************************************************************************
void CPlayer::Motion(D3DXVECTOR3 &rot)
{
	if (rot.z <= -MAX_MOTIONROT)
	{
		m_bRot = false;
	}
	else if (rot.z >= MAX_MOTIONROT)
	{
		m_bRot = true;
	}

	if (m_bRot)
	{
		rot.z -= MOTION_SPEED;
	}
	else if (!m_bRot)
	{
		rot.z += MOTION_SPEED;
	}
}

