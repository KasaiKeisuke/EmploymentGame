//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(enemy.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "enemy.h"
#include "player.h"
#include "explosion.h"
#include "block.h"
#include "wall.h"
#include "bullet.h"
#include "score.h"
#include <stdio.h>

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CEnemy::CEnemy(int nPriority):CObjectX(nPriority)
{
	m_nLife = 0;								// 体力
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
	m_bHit = false;								// 被弾したかどうか
	m_bHitObstacle = false;						// 障害物に当たったかどうか(ブロックや壁)
	m_bMoveRot = false;							// 進行方向判定用フラグ
	m_bRot = true;								// モーション用フラグ
	m_nCnt = 0;
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CEnemy::~CEnemy()
{
	m_nLife = 0;								// 体力
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
	m_bHit = false;								// 被弾したかどうか
	m_bHitObstacle = false;						// 障害物に当たったかどうか(ブロックや壁)
	m_bMoveRot = false;							// 進行方向判定用フラグ
	m_bRot = true;								// モーション用フラグ
	m_nCnt = 0;
}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CEnemy::Init()
{
	// Xファイルオブジェクトの初期化処理
	CObjectX::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CEnemy::Uninit()
{
	// Xファイルオブジェクトの終了処理
	CObjectX::Uninit();

	Release();	// モデルの破棄
}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CEnemy::Update()
{
	if (m_nLife > 0)
	{// 敵が生きているとき
		// Xファイルオブジェクトの更新処理
		CObjectX::Update();

		Move();	// 移動処理
	}
	else
	{// 敵が死んだとき
		if (m_nCnt > 0)
		{// 死亡演出中
			m_nCnt--;

			SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		}
		else
		{// 死亡演出終了後
			CScore::Add(KILL_POINT);	// スコア加算

			CEnemy::Uninit();	// 終了処理
		}
	}

}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CEnemy::Draw()
{
	// Xファイルオブジェクトの描画処理
	CObjectX::Draw();
}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
CEnemy* CEnemy::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move)
{
	CEnemy* pEnemy = new CEnemy();

	pEnemy->Init();												// 初期化処理

	pEnemy->BindFileName("data\\MODEL\\ENEMY\\enemy000.x");		// 読み込むモデル設定

	pEnemy->SetModelSize();										// モデルの頂点情報設定

	pEnemy->SetPos(pos);										// 位置設定処理

	pEnemy->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// 向き設定処理

	pEnemy->SetType(CObject::OBJECTTYPE::TYPE_ENEMY);			// 種類設定

	pEnemy->m_nLife = 1;										// 体力設定

	pEnemy->m_Move = move;										// 移動量設定

	return pEnemy;
}

//*******************************************************************************************************************************************
// 当たり判定(敵と他のオブジェクト)
//*******************************************************************************************************************************************
bool CEnemy::CollisionEnemy(D3DXVECTOR3* pos, D3DXVECTOR3 size, int nType)
{
	bool bHit = false;		// 当たったかどうか
	D3DXVECTOR3 CurrentPos = GetPos();			// 現在の位置取得
	D3DXVECTOR3 CurrentSize = GetModelSize();	// モデルの大きさ取得

	switch (nType)
	{
	case CObject::OBJECTTYPE::TYPE_PLAYER:	// 敵がプレイヤーとぶつかったとき
		if (pos->z + size.z / 2 >= CurrentPos.z - CurrentSize.z / 2 &&	// プレイヤーの奥と敵の手前
			pos->z - size.z / 2 <= CurrentPos.z + CurrentSize.z / 2 &&	// プレイヤーの手前と敵の奥
			pos->x - size.x / 2 <= CurrentPos.x + CurrentSize.x / 2 &&	// プレイヤーの左端と敵の右端
			pos->x + size.x / 2 >= CurrentPos.x - CurrentSize.x / 2)	// プレイヤーの右端と敵の左端
		{// プレイヤーの矩形が敵の矩形の中にいるか
			bHit = true;
		}
		break;
	case CObject::OBJECTTYPE::TYPE_ENEMY:	// 敵がプレイヤーとぶつかったとき
		if (pos->z + size.z / 2 >= CurrentPos.z - CurrentSize.z / 2 &&	// プレイヤーの奥と敵の手前
			pos->z - size.z / 2 <= CurrentPos.z + CurrentSize.z / 2 &&	// プレイヤーの手前と敵の奥
			pos->x - size.x / 2 <= CurrentPos.x + CurrentSize.x / 2 &&	// プレイヤーの左端と敵の右端
			pos->x + size.x / 2 >= CurrentPos.x - CurrentSize.x / 2)	// プレイヤーの右端と敵の左端
		{// プレイヤーの矩形が敵の矩形の中にいるか
			bHit = true;
		}
		break;
	default:
		break;
	}
	return bHit;
}

//*******************************************************************************************************************************************
// ロード処理
//*******************************************************************************************************************************************
void CEnemy::Load()
{
	FILE* pFile = nullptr;
	char aString[MAX_WORD] = {};
	char aSymbol[MAX_SYMBOL] = {};

	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	D3DXVECTOR3 Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動速度

	if (pFile == nullptr)
	{
		pFile = fopen("data\\TXT\\ENEMY\\EnemyManager.txt", "r");
	}

	if (pFile != nullptr)
	{
		while (1)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "END_SCRIPT") == 0)
			{
				fclose(pFile);
				break;
			}

			if (strcmp(&aString[0],"ENEMY_SET") == 0)
			{
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aSymbol[0], &Pos.x, &Pos.y, &Pos.z);
					}
					else if (strcmp(&aString[0], "MOVE") == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aSymbol[0], &Move.x, &Move.y, &Move.z);
					}

					if (strcmp(&aString[0], "END_ENEMYSET") == 0)
					{
						CEnemy::Create(Pos, Move);

						break;
					}
				}
			}
		}
	}
}

//*******************************************************************************************************************************************
// 移動処理
//*******************************************************************************************************************************************
void CEnemy::Move()
{
	D3DXVECTOR3 CurrentPos = GetPos();			// 今の位置取得
	D3DXVECTOR3 CurrentPosOld = GetPosOld();	// 1つ前の位置取得
	D3DXVECTOR3 CurrentRot = GetRot();			// 今の向き取得
	D3DXVECTOR3 CurrentSize = GetModelSize();	// モデルの大きさ取得
	bool bProcessedHit = false;					// 衝突判定の処理済みフラグを追加

	// ローカル変数宣言
	D3DXVECTOR3 AdjustMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動速度保存用
	float fLengthMove = 0.0f;								// 移動量

	if (m_bMoveRot)
	{
		AdjustMove += m_Move;
	}
	else if (!m_bMoveRot)
	{
		AdjustMove -= m_Move;
	}

	fLengthMove = sqrtf(AdjustMove.x * AdjustMove.x + AdjustMove.z * AdjustMove.z);

	AdjustMove.x /= fLengthMove;
	AdjustMove.z /= fLengthMove;

	// 移動量をスケール調整 (必要なら速度を掛ける)
	AdjustMove.x *= ENEMY_SPEED;
	AdjustMove.z *= ENEMY_SPEED;

	// 位置の更新
	CurrentPos += AdjustMove;


	// モーション処理
	Motion(CurrentRot);

	// 向きの更新
	if (AdjustMove.x != 0.0f || AdjustMove.z != 0.0f)
	{
		CurrentRot.y = atan2f(-AdjustMove.x, -AdjustMove.z);
	}

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
				{// オブジェクトの種類がブロックの時
					CBlock* pBlock = (CBlock*)pObj;

					m_bHitObstacle = pBlock->CollisionBlock(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_ENEMY);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_NORMALWALL)
				{// オブジェクトの種類が通常壁の時
					CWall* pWall = (CWall*)pObj;

					m_bHitObstacle = pWall->CollisionWall(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_NORMALWALL, CObject::OBJECTTYPE::TYPE_ENEMY);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_SIDEWALL)
				{// オブジェクトの種類が側面壁の時
					CWall* pWall = (CWall*)pObj;

					m_bHitObstacle = pWall->CollisionWall(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_SIDEWALL, CObject::OBJECTTYPE::TYPE_ENEMY);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_EXPLOSION)
				{// オブジェクトの種類が爆発の時
					CExplosion* pExplosion = (CExplosion*)pObj;

					m_bHit = pExplosion->CollisionExplosion(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_ENEMY);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_BULLET)
				{// オブジェクトの種類が弾の時
					CBullet* pBullet = (CBullet*)pObj;

					m_bHitObstacle = pBullet->CollisionBullet(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_ENEMY);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_ENEMY)
				{
					CEnemy* pOtherEnemy = (CEnemy*)pObj;

					if (pOtherEnemy != this)
					{
						m_bHitObstacle = pOtherEnemy->CollisionEnemy(&CurrentPos, CurrentSize, CObject::OBJECTTYPE::TYPE_ENEMY);
					}
				}

				// 衝突を処理済みでない場合のみフラグを切り替える
				if (m_bHitObstacle && !bProcessedHit)
				{
					m_bMoveRot = !m_bMoveRot; // フラグを切り替え
					bProcessedHit = true;    // 処理済みに設定
				}

				if (m_bHit)
				{
					m_nLife--;	// 体力を減らす
					Death(DEATH_COUNT);
				}
			}
		}

	}


	SetPos(CurrentPos);
	SetRot(CurrentRot);
}

//*******************************************************************************************************************************************
// 死亡処理
//*******************************************************************************************************************************************
void CEnemy::Death(int nCnt)
{
	m_nCnt = nCnt;
}

//*******************************************************************************************************************************************
// モーション処理
//*******************************************************************************************************************************************
void CEnemy::Motion(D3DXVECTOR3 &rot)
{
	if (rot.z <= -ENEMY_MOTIONROT)
	{
		m_bRot = false;
	}
	else if (rot.z >= ENEMY_MOTIONROT)
	{
		m_bRot = true;
	}

	if (m_bRot)
	{
		rot.z -= ENEMY_MOTIONSPEED;
	}
	else if (!m_bRot)
	{
		rot.z += ENEMY_MOTIONSPEED;
	}

}
