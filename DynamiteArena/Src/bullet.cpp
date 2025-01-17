//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(bullet.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include 
#include "bullet.h"
#include "manager.h"
#include "caveat.h"
#include "block.h"
#include "wall.h"

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CBullet::CBullet(int nPriority):CObjectX(nPriority),
m_Move(D3DXVECTOR3(0.0f,0.0f,0.0f)),
m_fGravity(9.8f),
m_fInitialYSpeed(3.0f),
m_bDeath(false),
m_bHitObstacle(false),
m_nLag(0)
{
	m_pParamManager = nullptr;	// パラメーター管理クラスのポインタ
	m_bScale = true;			// 拡縮用スケール(trueの時に大きくする)
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CBullet::~CBullet()
{

}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CBullet::Init()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	m_pParamManager = manager.GetParamManager();

	// Xファイルオブジェクトの初期化処理
	CObjectX::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CBullet::Uninit()
{
	// Xファイルオブジェクトの終了処理
	CObjectX::Uninit();

	Release();
}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CBullet::Update()
{
	// Xファイルオブジェクトの更新処理
	CObjectX::Update();

	// 弾の移動
	Move();

}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CBullet::Draw()
{
	// Xファイルオブジェクトの描画処理
	CObjectX::Draw();
}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBullet* pBullet = new CBullet();

	pBullet->Init();

	// Xファイルの設定
	pBullet->BindFileName("data\\MODEL\\BULLET\\bomb000.x");

	pBullet->SetModelSize();

	pBullet->SetPos(pos);

	pBullet->SetRot(D3DXVECTOR3(0.0f,D3DX_PI * 0.5f,0.0f));

	//**********************************************
	// 山なりの場合
	//**********************************************
	pBullet->m_Move = move;
	pBullet->m_Move.y = pBullet->m_fInitialYSpeed;	// Y軸方向のみ初速度を個別で設定

	pBullet->m_nNotCollision = 20;					// 爆弾を置いてから一定時間当たり判定が機能しない時間
	
	pBullet->SetType(CObject::OBJECTTYPE::TYPE_BULLET);

	return pBullet;
}

//*******************************************************************************************************************************************
// 移動処理
//*******************************************************************************************************************************************
void CBullet::Move()
{
	// 現在の位置の取得
	D3DXVECTOR3 CurrentPos = GetPos();

	// 弾の1つ前の位置の取得
	D3DXVECTOR3 CurrentPosOld = GetPosOld();

	// 弾モデルの大きさの取得
	D3DXVECTOR3 CurrentSize = GetModelSize();

	// 重力を考慮したY軸の速度計算
	m_Move.y += -m_fGravity * 0.016f;	// 0.016はフレーム間の時間(60fps前提)

	// 地面に到達した場合、Y軸の位置と速度をリセット
	if (CurrentPos.y <= 8.0f)
	{
		CurrentPos.y = 5.0f;	// 地面の高さ
		m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		m_nLag++;

		if (m_nLag == UI_TIMING)
		{
			Death();				// 死亡判定
		}
		
		if (m_nLag >= DELETE_BULLET)
		{
			CBullet::Uninit();		// 終了処理
		}
		else if (m_nLag < DELETE_BULLET)
		{// 弾が表示されている間
			Motion();
		}

	}
	else
	{
		// それぞれの軸の移動
		CurrentPos.x += m_Move.x;
		CurrentPos.y += m_Move.y;
		CurrentPos.z += m_Move.z;

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
				{
					CBlock* pBlock = (CBlock*)pObj;

					m_bHitObstacle = pBlock->CollisionBlock(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_BULLET);

				}
			}
		}
	}


	SetPos(CurrentPos);
}

//*******************************************************************************************************************************************
// 警告表示UI出現判定
//*******************************************************************************************************************************************
void CBullet::Death()
{	
	D3DXVECTOR3 CurrentPos = GetPos();	// 弾の位置を取得
	int CurrentPower = m_pParamManager->GetPower();	// 爆弾の爆発力の取得

	CCaveat::Create(D3DXVECTOR3(CurrentPos.x, 0.1f, CurrentPos.z), 10.0f, 0.0f, 10.0f);	// 弾の位置に警告表示のUIを生成

	// 縦方向と横方向の生成位置リスト
	D3DXVECTOR3 frontPositions[NUM_EXPLOSION];
	D3DXVECTOR3 backPositions[NUM_EXPLOSION];
	D3DXVECTOR3 leftPositions[NUM_EXPLOSION];
	D3DXVECTOR3 rightPositions[NUM_EXPLOSION];

	// 生成する距離の間隔
	const float Interval = CAVEAT_SPAN;

	// 手前方向の生成位置リスト
	for (int i = 0; i < CurrentPower; ++i)
	{
		float offset = -(i + 1) * Interval;  // 手前は基準位置からマイナス方向
		frontPositions[i] = D3DXVECTOR3(CurrentPos.x, 0.1f, CurrentPos.z + offset);
	}

	// 奥方向の生成位置リスト
	for (int i = 0; i < CurrentPower; ++i)
	{
		float offset = (i + 1) * Interval;  // 奥は基準位置からプラス方向
		backPositions[i] = D3DXVECTOR3(CurrentPos.x, 0.1f, CurrentPos.z + offset);
	}

	// 左方向の生成位置リスト
	for (int i = 0; i < CurrentPower; ++i)
	{
		float offset = -(i + 1) * Interval;  // 左は基準位置からマイナス方向
		leftPositions[i] = D3DXVECTOR3(CurrentPos.x + offset, 0.1f, CurrentPos.z);
	}

	// 右方向の生成位置リスト
	for (int i = 0; i < CurrentPower; ++i)
	{
		float offset = (i + 1) * Interval;  // 右は基準位置からプラス方向
		rightPositions[i] = D3DXVECTOR3(CurrentPos.x + offset, 0.1f, CurrentPos.z);
	}

	// 手前方向の警告UI生成
	for (int i = 0; i < CurrentPower; ++i)
	{
		if (IsBlockPos(frontPositions[i], Interval, Interval))
		{
			break;  // 手前方向にブロックがあれば以降の生成を停止
		}
		else
		{
			CCaveat::Create(frontPositions[i], POLYGON_SIZE, 0.0f, POLYGON_SIZE);
		}
	}

	// 奥方向の警告UI生成
	for (int i = 0; i < CurrentPower; ++i)
	{
		if (IsBlockPos(backPositions[i], Interval, Interval))
		{
			break;  // 奥方向にブロックがあれば以降の生成を停止
		}
		else
		{
			CCaveat::Create(backPositions[i], POLYGON_SIZE, 0.0f, POLYGON_SIZE);
		}
	}

	// 左方向の警告UI生成
	for (int i = 0; i < CurrentPower; ++i)
	{
		if (IsBlockPos(leftPositions[i], Interval, Interval))
		{
			break;  // 左方向にブロックがあれば以降の生成を停止
		}
		else
		{
			CCaveat::Create(leftPositions[i], POLYGON_SIZE, 0.0f, POLYGON_SIZE);
		}
	}

	// 右方向の警告UI生成
	for (int i = 0; i < CurrentPower; ++i)
	{
		if (IsBlockPos(rightPositions[i], Interval, Interval))
		{
			break;  // 右方向にブロックがあれば以降の生成を停止
		}
		else
		{
			CCaveat::Create(rightPositions[i], POLYGON_SIZE, 0.0f, POLYGON_SIZE);
		}
	}
}

//*******************************************************************************************************************************************
// モーション処理
//*******************************************************************************************************************************************
void CBullet::Motion()
{
	D3DXVECTOR3 CurrentScale = GetScale();

	if (CurrentScale.x && CurrentScale.y && CurrentScale.z <= MIN_BULLETSCALE)
	{
		m_bScale = true;
	}

	if (CurrentScale.x && CurrentScale.y && CurrentScale.z >= MAX_BULLETSCALE)
	{
		m_bScale = false;
	}

	if (m_nLag >= UI_TIMING)
	{// 爆発直前になったらモーションの速度を速くする
		if (m_bScale)
		{
			CurrentScale.x += MOTION_SPEEDFAST;
			CurrentScale.y += MOTION_SPEEDFAST;
			CurrentScale.z += MOTION_SPEEDFAST;
		}
		else if (!m_bScale)
		{
			CurrentScale.x -= MOTION_SPEEDFAST;
			CurrentScale.y -= MOTION_SPEEDFAST;
			CurrentScale.z -= MOTION_SPEEDFAST;
		}

	}
	else
	{// 爆弾置いてからあまり時間が経っていないときはモーションの速度を遅くする
		if (m_bScale)
		{
			CurrentScale.x += MOTION_SPEEDLATE;
			CurrentScale.y += MOTION_SPEEDLATE;
			CurrentScale.z += MOTION_SPEEDLATE;
		}
		else if (!m_bScale)
		{
			CurrentScale.x -= MOTION_SPEEDLATE;
			CurrentScale.y -= MOTION_SPEEDLATE;
			CurrentScale.z -= MOTION_SPEEDLATE;
		}

	}

	SetScale(CurrentScale);

}

//*******************************************************************************************************************************************
// ブロックがあるかどうか
//*******************************************************************************************************************************************
bool CBullet::IsBlockPos(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	for (int nCntPriority = 0; nCntPriority < DRAW_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECTX; nCntObj++)
		{
			CObject* pObj = CObject::GetObjectInfo(nCntPriority, nCntObj);
			if (pObj != nullptr && pObj->GetType() == CObject::OBJECTTYPE::TYPE_BLOCK)
			{// オブジェクトの種類がブロックなら
				CBlock* pBlock = (CBlock*)pObj;
				if (pBlock->GetType() == CBlock::BLOCKTYPE::TYPE_NOTBREAK)
				{// 壊せないブロックなら
					// ブロックの位置とサイズを取得して判定
					D3DXVECTOR3 blockPos = pBlock->GetPos();
					D3DXVECTOR3 blockSize = pBlock->GetModelSize();
					// 生成位置がブロックと重なっているかを確認
					if (pos.x + fWidth / 2 >= blockPos.x - blockSize.x / 2 &&
						pos.x - fWidth / 2 <= blockPos.x + blockSize.x / 2 &&
						pos.z + fDepth / 2 >= blockPos.z - blockSize.z / 2 &&
						pos.z - fDepth / 2 <= blockPos.z + blockSize.z / 2)
					{
						return true;  // ブロックがある
					}

				}
				else if (pBlock->GetType() == CBlock::BLOCKTYPE::TYPE_BREAK)
				{
					// ブロックの位置とサイズを取得して判定
					D3DXVECTOR3 blockPos = pBlock->GetPos();
					D3DXVECTOR3 blockSize = pBlock->GetModelSize();
					// 生成位置がブロックと重なっているかを確認
					if (pos.x + fWidth / 2 >= blockPos.x - blockSize.x / 2 &&
						pos.x - fWidth / 2 <= blockPos.x + blockSize.x / 2 &&
						pos.z + fDepth / 2 >= blockPos.z - blockSize.z / 2 &&
						pos.z - fDepth / 2 <= blockPos.z + blockSize.z / 2)
					{
						CCaveat::Create(pos, POLYGON_SIZE, 0.0f, POLYGON_SIZE);

						return true;  // ブロックがある
					}

				}
			}

			if (pObj != nullptr)
			{
				if (pObj->GetType() == CObject::OBJECTTYPE::TYPE_NORMALWALL)
				{// 通常壁
					CWall* pWall = (CWall*)pObj;
					// 壁の位置とサイズを取得
					D3DXVECTOR3 WallPos = pWall->GetPos();
					D3DXVECTOR3 WallSize = pWall->GetModelSize();

					// 生成位置が壁と重なっていたら生成しない
					if (pos.x + fWidth / 2 >= WallPos.x - WallSize.x / 2 &&
						pos.x - fWidth / 2 <= WallPos.x + WallSize.x / 2 &&
						pos.z + fDepth / 2 >= WallPos.z - WallSize.z / 2 &&
						pos.z - fDepth / 2 <= WallPos.z + WallSize.z / 2)
					{
						return true;
					}
				}
				else if (pObj->GetType() == CObject::OBJECTTYPE::TYPE_SIDEWALL)
				{// 側面壁
					CWall* pWall = (CWall*)pObj;
					// 壁の位置とサイズを取得
					D3DXVECTOR3 WallPos = pWall->GetPos();
					D3DXVECTOR3 WallSize = pWall->GetModelSize();

					// 生成位置が壁と重なっていたら生成しない
					if (pos.x + fWidth / 2 >= WallPos.x - WallSize.x / 2 &&
						pos.x - fWidth / 2 <= WallPos.x + WallSize.x / 2 &&
						pos.z + fDepth / 2 >= WallPos.z - WallSize.z / 2 &&
						pos.z - fDepth / 2 <= WallPos.z + WallSize.z / 2)
					{
						return true;
					}

				}
			}
		}
	}
	return false;  // ブロックがない
}

//*******************************************************************************************************************************************
// 当たり判定
//*******************************************************************************************************************************************
bool CBullet::CollisionBullet(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size, int nType)
{
	D3DXVECTOR3 CurrentPos = GetPos();
	D3DXVECTOR3 CurrentMinVtx = GetMinVtx();
	D3DXVECTOR3 CurrentMaxVtx = GetMaxVtx();

	bool bHit = false;	// 当たったかどうか

	m_nNotCollision--;	// カウントを減らす

	if (m_nNotCollision <= 0)
	{
		switch (nType)
		{
		case CObject::OBJECTTYPE::TYPE_PLAYER:
			if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x)
			{// 弾の左側にプレイヤーが当たったとき
				pos->x = CurrentPos.x + CurrentMinVtx.x - size.x / 2;
				bHit = true;
			}

			if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
				pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x)
			{// 弾の右側にプレイヤーが当たったとき
				pos->x = CurrentPos.x + CurrentMaxVtx.x + size.x / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x  &&
				posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z)
			{// 弾の奥側にプレイヤーが当たったとき
				pos->z = CurrentPos.z + CurrentMaxVtx.z + size.z / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x  &&
				posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z)
			{// 弾の手前側にプレイヤーが当たったとき
				pos->z = CurrentPos.z + CurrentMinVtx.z - size.z / 2;
				bHit = true;
			}
			break;
		case CObject::OBJECTTYPE::TYPE_ENEMY:	// 敵がぶつかってきたとき
			if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x)
			{// 弾の左側に敵が当たったとき
				//pos->x = CurrentPos.x + CurrentMinVtx.x - size.x / 2;
				bHit = true;
			}

			if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
				pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x)
			{// 弾の右側に敵が当たったとき
				//pos->x = CurrentPos.x + CurrentMaxVtx.x + size.x / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z)
			{// 弾の奥側に敵が当たったとき
				//pos->z = CurrentPos.z + CurrentMaxVtx.z + size.z / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z)
			{// 弾の手前側に敵が当たったとき
				//pos->z = CurrentPos.z + CurrentMinVtx.z - size.z / 2;
				bHit = true;
			}
			break;

		}
	}
	return bHit;
}
