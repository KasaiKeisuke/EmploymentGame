//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(explosion.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "explosion.h"
#include "manager.h"

// 静的メンバ変数初期化
char CExplosion::m_pFiletemp[FILE_PATH] = {};

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CExplosion::CExplosion(int nPriority):CObjectX(nPriority),
m_nCnt(0)
{
	m_bScale = true;	// 拡縮用フラグ
	m_nLag = 0;			// 拡縮を切り替えるまでの時間
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CExplosion::~CExplosion()
{

}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CExplosion::Init()
{
	// Xファイルオブジェクトの初期化処理
	CObjectX::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CExplosion::Uninit()
{
	// Xファイルオブジェクトの終了処理
	CObjectX::Uninit();

	// 爆発モデルの破棄
	Release();
}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CExplosion::Update()
{
	m_nCnt--;

	if (m_nCnt <= 0)
	{
		CExplosion::Uninit();
	}
	else
	{
		// 爆発のモーション
		Motion();

		// 回転
		//Turn();

		// Xファイルオブジェクトの更新処理
		CObjectX::Update();

	}

}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CExplosion::Draw()
{
	// Xファイルオブジェクトの描画処理
	CObjectX::Draw();
}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
CExplosion* CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion* pExplosion = new CExplosion();

	pExplosion->Init();

	pExplosion->SetPos(pos);

	pExplosion->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	if (m_pFiletemp != NULL)
	{
		pExplosion->BindFileName(m_pFiletemp);

	}

	pExplosion->SetModelSize();

	pExplosion->SetType(CObject::OBJECTTYPE::TYPE_EXPLOSION);

	pExplosion->m_nCnt = DRAW_COUNT;

	return pExplosion;
}

//*******************************************************************************************************************************************
// Xファイルロード
//*******************************************************************************************************************************************
HRESULT CExplosion::Load()
{
	const char FilePath[FILE_PATH] = "data\\MODEL\\EXPLOSION\\explosion000.x";

	//if (m_pFiletemp == NULL)
	//{
		strcpy(&m_pFiletemp[0], &FilePath[0]);

	//}
	return S_OK;
}

//*******************************************************************************************************************************************
// Xファイルアンロード
//*******************************************************************************************************************************************
void CExplosion::UnLoad()
{

}

//*******************************************************************************************************************************************
// 当たり判定
//*******************************************************************************************************************************************
bool CExplosion::CollisionExplosion(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size, int nType)
{
	// 爆発の詳細情報取得
	D3DXVECTOR3 CurrentPos = GetPos();
	D3DXVECTOR3 CurrentMinVtx = GetMinVtx();
	D3DXVECTOR3 CurrentMaxVtx = GetMaxVtx();
	D3DXVECTOR3 CurrentSize = GetModelSize();

	bool bHit = false;	// 当たったかどうか

	switch (nType)
	{
	case CObject::OBJECTTYPE::TYPE_PLAYER:	// プレイヤーと爆発の当たり判定
		if (pos->z + size.z / 2 >= CurrentPos.z - CurrentSize.z / 2 &&	// プレイヤーの奥と爆発の手前
			pos->z - size.z / 2 <= CurrentPos.z + CurrentSize.z / 2 &&	// プレイヤーの手前と爆発の奥
			pos->x - size.x / 2 <= CurrentPos.x + CurrentSize.x / 2 &&	// プレイヤーの左端と爆発の右端
			pos->x + size.x / 2 >= CurrentPos.x - CurrentSize.x / 2)	// プレイヤーの右端と爆発の左端
		{// プレイヤーの矩形が爆発の矩形の中にいるか
			bHit = true;
		}

		break;
	case CObject::OBJECTTYPE::TYPE_BLOCK:	// ブロックと爆発の当たり判定
		if (pos->z + size.z / 2 > CurrentPos.z - CurrentSize.z / 2 &&	// ブロックの奥と爆発の手前
			pos->z - size.z / 2 < CurrentPos.z + CurrentSize.z / 2 &&	// ブロックの手前と爆発の奥
			pos->x - size.x / 2 < CurrentPos.x + CurrentSize.x / 2 &&	// ブロックの左端と爆発の右端
			pos->x + size.x / 2 > CurrentPos.x - CurrentSize.x / 2)	// ブロックの右端と爆発の左端
		{// ブロックの矩形が爆発の矩形の中にいるか
			bHit = true;
		}
		break;
	case CObject::OBJECTTYPE::TYPE_ENEMY:
		if (pos->z + size.z / 2 >= CurrentPos.z - CurrentSize.z / 2 &&	// 敵の奥と爆発の手前
			pos->z - size.z / 2 <= CurrentPos.z + CurrentSize.z / 2 &&	// 敵の手前と爆発の奥
			pos->x - size.x / 2 <= CurrentPos.x + CurrentSize.x / 2 &&	// 敵の左端と爆発の右端
			pos->x + size.x / 2 >= CurrentPos.x - CurrentSize.x / 2)	// 敵の右端と爆発の左端
		{// 敵の矩形が爆発の矩形の中にいるか
			bHit = true;
		}
		break;
	case CObject::OBJECTTYPE::TYPE_ITEM:
		if (pos->z + size.z / 2 >= CurrentPos.z - CurrentSize.z / 2 &&	// アイテムの奥と爆発の手前
			pos->z - size.z / 2 <= CurrentPos.z + CurrentSize.z / 2 &&	// アイテムの手前と爆発の奥
			pos->x - size.x / 2 <= CurrentPos.x + CurrentSize.x / 2 &&	// アイテムの左端と爆発の右端
			pos->x + size.x / 2 >= CurrentPos.x - CurrentSize.x / 2)	// アイテムの右端と爆発の左端
		{// アイテムの矩形が爆発の矩形の中にいるか
			bHit = true;
		}
		break;
	}

	return bHit;
}

//*******************************************************************************************************************************************
// 回転処理
//*******************************************************************************************************************************************
void CExplosion::Turn()
{
	D3DXVECTOR3 CurrentRot = GetRot();

	CurrentRot.y += 0.1f;

	SetRot(CurrentRot);
}

//*******************************************************************************************************************************************
// モーション処理
//*******************************************************************************************************************************************
void CExplosion::Motion()
{
	D3DXVECTOR3 CurrentScale = GetScale();

	if (CurrentScale.x && CurrentScale.y && CurrentScale.z >= MAX_SCALE)
	{
		CurrentScale = D3DXVECTOR3(MAX_SCALE, MAX_SCALE, MAX_SCALE);	// 最大まで大きくしたら固定する
		m_nLag++;

		if (m_nLag >= TIME_LAG)
		{// 最大スケールになってから一定時間経過後フラグを切り替える
			m_bScale = false;
		}
	}

	if (m_bScale)
	{// 大きくする
		CurrentScale.x += ANIM_SPEEDFAST;
		CurrentScale.y += ANIM_SPEEDFAST;
		CurrentScale.z += ANIM_SPEEDFAST;
	}
	else if (!m_bScale)
	{// 小さくする
		m_nLag = 0;
		CurrentScale.x -= ANIM_SPEEDLATE;
		CurrentScale.y -= ANIM_SPEEDLATE;
		CurrentScale.z -= ANIM_SPEEDLATE;
	}

	SetScale(CurrentScale);

}
