//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(block.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "block.h"
#include "explosion.h"
#include "item.h"
#include "manager.h"
#include <stdio.h>
#include <random>

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CBlock::CBlock(int nPriority):CObjectX(nPriority),
m_bDeath(false),
m_nLife(0)
{
	m_pItemManager = nullptr;	// アイテムマネージャークラスのポインタ
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CBlock::~CBlock()
{
	m_bDeath = false;
	m_pItemManager = nullptr;	// アイテムマネージャークラスのポインタ
}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CBlock::Init()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	m_pItemManager = manager.GetItemManager();

	// Xファイルオブジェクトの初期化処理
	CObjectX::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CBlock::Uninit()
{
	// Xファイルオブジェクトの終了処理
	CObjectX::Uninit();

	// ブロックの破棄
	Release();
}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CBlock::Update()
{
	// Xファイルオブジェクトの更新処理
	CObjectX::Update();

	// 現在の位置の取得
	D3DXVECTOR3 CurrentPos = GetPos();

	// 弾の1つ前の位置の取得
	D3DXVECTOR3 CurrentPosOld = GetPosOld();

	// 弾モデルの大きさの取得
	D3DXVECTOR3 CurrentSize = GetModelSize();

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

				if (type == CObject::OBJECTTYPE::TYPE_EXPLOSION)
				{
					CExplosion* pExplosion = (CExplosion*)pObj;

					m_bDeath = pExplosion->CollisionExplosion(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_BLOCK);

				}


				if (m_Type == CBlock::BLOCKTYPE::TYPE_BREAK)
				{
					if (m_bDeath)
					{
						DecideToPlaceItem(CurrentPos);	// アイテムを配置するかどうか

						CBlock::Uninit();
					}
				}

			}
		}
	}

}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CBlock::Draw()
{
	// Xファイルオブジェクトの描画処理
	CObjectX::Draw();
}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
CBlock* CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type)
{
	CBlock* pBlock = new CBlock();

	pBlock->Init();	// 初期化処理

	pBlock->SetPos(pos);	// 位置設定

	pBlock->SetRot(rot);	// 向き設定

	pBlock->m_nLife = 1;	// 寿命設定

	switch (type)
	{
	case 1:
		pBlock->BindFileName("data\\MODEL\\BLOCK\\block000.x");

		pBlock->SetBlockType(CBlock::BLOCKTYPE::TYPE_NOTBREAK);

		pBlock->m_Type = CBlock::BLOCKTYPE::TYPE_NOTBREAK;
		
		break;
	case 2:
		pBlock->BindFileName("data\\MODEL\\BLOCK\\block001.x");

		pBlock->SetBlockType(CBlock::BLOCKTYPE::TYPE_BREAK);

		pBlock->m_Type = CBlock::BLOCKTYPE::TYPE_BREAK;

		break;
	}
	
	pBlock->SetModelSize();

	pBlock->SetType(CObjectX::OBJECTTYPE::TYPE_BLOCK);		// オブジェクトの種類設定

	return nullptr;
}

//*******************************************************************************************************************************************
// 当たり判定
//*******************************************************************************************************************************************
bool CBlock::CollisionBlock(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size, int nType)
{
	bool bHit = false;							// 当たったかどうか
	bool bDraw = false;							// UIを消すかどうか

	D3DXVECTOR3 CurrentPos = GetPos();			// ブロックの座標
	D3DXVECTOR3 CurrentMinVtx = GetMinVtx();	// ブロックの頂点の最小値
	D3DXVECTOR3 CurrentMaxVtx = GetMaxVtx();	// ブロックの頂点の最大値
	D3DXVECTOR3 CurrentSize = GetModelSize();	// モデルのサイズ取得

	switch (nType)
	{
	case CObject::OBJECTTYPE::TYPE_PLAYER:	// ブロックにプレイヤーがぶつかってきたとき
		if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
			pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
			posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
			pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x)
		{// ブロックの左側にプレイヤーが当たったとき
			//pos->x = CurrentPos.x + CurrentMinVtx.x - size.x / 2;
			pos->x = CurrentPos.x - BLOCK_SIZE - PLAYER_SIZE / 2;
		}

		if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
			pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
			posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
			pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x)
		{// ブロックの右側にプレイヤーが当たったとき
			//pos->x = CurrentPos.x + CurrentMaxVtx.x + size.x / 2;
			pos->x = CurrentPos.x + BLOCK_SIZE + PLAYER_SIZE / 2;
		}

		if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
			pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
			posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
			pos->z - size.z / 2 <= CurrentPos.z + CurrentMaxVtx.z)
		{// ブロックの奥側にプレイヤーが当たったとき
			//pos->z = CurrentPos.z + CurrentMaxVtx.z + size.z / 2;
			pos->z = CurrentPos.z + BLOCK_SIZE + PLAYER_SIZE / 2;
		}

		if (pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x &&			
			pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x &&
			posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
			pos->z + size.z / 2 >= CurrentPos.z + CurrentMinVtx.z)
		{// ブロックの手前側にプレイヤーが当たったとき
			//pos->z = CurrentPos.z + CurrentMinVtx.z - size.z / 2;
			pos->z = CurrentPos.z - BLOCK_SIZE - PLAYER_SIZE / 2;
		}
		break;
	case CObject::OBJECTTYPE::TYPE_BULLET:
		if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
			pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
			posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
			pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x)
		{// ブロックの左側に弾が当たったとき
			pos->x = CurrentPos.x + CurrentMinVtx.x - size.x / 2;
			bHit = true;
		}

		if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
			pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
			posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
			pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x)
		{// ブロックの右側に弾が当たったとき
			pos->x = CurrentPos.x + CurrentMaxVtx.x + size.x / 2;
			bHit = true;
		}

		if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
			pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
			posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
			pos->z - size.z / 2 <= CurrentPos.z + CurrentMaxVtx.z)
		{// ブロックの奥側に弾が当たったとき
			pos->z = CurrentPos.z + CurrentMaxVtx.z + size.z / 2;
			bHit = true;
		}

		if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
			pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
			posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
			pos->z + size.z / 2 >= CurrentPos.z + CurrentMinVtx.z)
		{// ブロックの手前側に弾が当たったとき
			pos->z = CurrentPos.z + CurrentMinVtx.z - size.z / 2;
			bHit = true;
		}

		break;
	case CObject::OBJECTTYPE::TYPE_ENEMY:
		if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
			pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
			posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
			pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x)
		{// ブロックの左側に敵が当たったとき
			//pos->x = CurrentPos.x + CurrentMinVtx.x - size.x / 2;
			bHit = true;
		}

		if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
			pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
			posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
			pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x)
		{// ブロックの右側に敵が当たったとき
			//pos->x = CurrentPos.x + CurrentMaxVtx.x + size.x / 2;
			bHit = true;
		}

		if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
			pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
			posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
			pos->z - size.z / 2 <= CurrentPos.z + CurrentMaxVtx.z)
		{// ブロックの奥側に敵が当たったとき
			//pos->z = CurrentPos.z + CurrentMaxVtx.z + size.z / 2;
			bHit = true;
		}

		if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
			pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
			posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
			pos->z + size.z / 2 >= CurrentPos.z + CurrentMinVtx.z)
		{// ブロックの手前側に敵が当たったとき
			//pos->z = CurrentPos.z + CurrentMinVtx.z - size.z / 2;
			bHit = true;
		}

		break;
	}

	return bHit;
}

//*******************************************************************************************************************************************
// ロード処理
//*******************************************************************************************************************************************
void CBlock::Load()
{
	// ローカル変数宣言
	FILE* pFile = nullptr;	// ファイルポインタ
	char aString[128] = {};	// 読み込んだもの保存用
	char aSymbol[4] = {};	// ゴミ保存用
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置保存用
	D3DXVECTOR3 Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き保存用
	int nType = 0;										// 種類保存用

	pFile = fopen("data\\TXT\\BLOCK\\BlockManager.txt", "r");

	if (pFile != NULL)
	{
		while (1)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "END_SCRIPT") == 0)
			{
				fclose(pFile);
				break;
			}
			
			if (strcmp(&aString[0], "BLOCK_SET") == 0)
			{
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aSymbol[0], &Pos.x, &Pos.y, &Pos.z);
					}
					else if (strcmp(&aString[0], "ROT") == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aSymbol[0], &Rot.x, &Rot.y, &Rot.z);
					}
					else if (strcmp(&aString[0], "TYPE") == 0)
					{
						fscanf(pFile, "%s %d", &aSymbol[0], &nType);
					}


					if (strcmp(&aString[0], "END_BLOCKSET") == 0)
					{
						CBlock::Create(Pos, Rot, nType);
						break;
					}
				}
			}
			
		}
	}
}

//*******************************************************************************************************************************************
// ブロック種類設定
//*******************************************************************************************************************************************
void CBlock::SetBlockType(BLOCKTYPE type)
{
	m_Type = type;
}

//*******************************************************************************************************************************************
// ブロック種類取得
//*******************************************************************************************************************************************
CBlock::BLOCKTYPE CBlock::GetType()
{
	return m_Type;
}

//*******************************************************************************************************************************************
// アイテムを配置するかどうか
//*******************************************************************************************************************************************
void CBlock::DecideToPlaceItem(D3DXVECTOR3 pos)
{
	int nNumAppearItem = m_pItemManager->GetNumItem();	// 出現させたアイテムの個数取得

	if (nNumAppearItem >= 8)
	{// 一定個数出現したら処理を通さない
		return;
	}

	std::random_device rnd;  // 非決定的な乱数生成器
	std::mt19937 mt(rnd());  // メルセンヌツイスターの乱数生成器
	std::uniform_int_distribution<> rand(1, 2);  // 1か2のランダム

	int nRand = rand(mt);

	if (nRand == 1)
	{
		nNumAppearItem++;

		// アイテムの種類を決定
		std::uniform_int_distribution<> itemRand(1, ITEM_KIND);  // アイテムの種類のランダム
		int nKind = itemRand(mt);  // アイテムの種類

		// アイテムを作成
		CItem::Create(D3DXVECTOR3(pos.x, 0.1f, pos.z), ITEM_SIZE, 0.0f, ITEM_SIZE, nKind);

		m_pItemManager->SetNumItem(nNumAppearItem);
	}
}
