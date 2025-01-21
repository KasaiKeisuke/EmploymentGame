//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(item.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "item.h"
#include "manager.h"
#include "explosion.h"
#include "block.h"
#include <stdio.h>

// 静的メンバ変数初期化
LPDIRECT3DTEXTURE9 CItem::m_pTexture = nullptr;	// テクスチャ

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CItem::CItem(int nPriority):CObject3D(nPriority)
{
	m_Type = TYPE_NONE;
	m_fWidth = 0.0f;	// 幅
	m_fDepth = 0.0f;	// 奥行

	m_bHit = false;		// 当たったかどうか
	m_bDeath = false;	// 使用されているかどうか
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CItem::~CItem()
{

}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CItem::Init()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();


	// 3Dオブジェクトの初期化処理
	CObject3D::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CItem::Uninit()
{
	// 3Dオブジェクトの終了処理
	CObject3D::Uninit();

	// アイテムの破棄
	Release();
}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CItem::Update()
{
	D3DXVECTOR3 CurrentPos = GetPos();

	if (!m_bDeath)
	{
		// 3Dオブジェクトの更新処理
		CObject3D::Update();

		for (int nCntPriority = 0; nCntPriority < DRAW_PRIORITY; nCntPriority++)
		{
			for (int nCntObj = 0; nCntObj < MAX_OBJECT3D; nCntObj++)
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

						m_bHit = pExplosion->CollisionExplosion(&CurrentPos, &CurrentPos, D3DXVECTOR3(m_fWidth, 0.0f, m_fDepth), CObject::OBJECTTYPE::TYPE_ITEM);
					}

				}

			}
		}
	}

	if (m_bHit)
	{
		m_bDeath = true;
	}

	if (m_bDeath)
	{
		CItem::Uninit();
	}
}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CItem::Draw()
{
	// 3Dオブジェクトの描画処理
	CObject3D::Draw();
}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
CItem* CItem::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth,int nType)
{
	CItem* pItem = new CItem();
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	pItem->Init();

	switch (nType)
	{
	case 1:
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(manager.GetRenderer()->GetDevice(), "data\\TEXTURE\\powerup000.png", &pItem->m_pTexture);
		pItem->m_Type = TYPE_POWERUP;
		break;
	case 2:
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(manager.GetRenderer()->GetDevice(), "data\\TEXTURE\\speedup000.png", &pItem->m_pTexture);
		pItem->m_Type = TYPE_SPEEDUP;
		break;
	case 3:
		//pItem->BindTexture();
		pItem->m_Type = TYPE_ENEMYKILL;
		break;
	}

	pItem->BindTexture(m_pTexture);

	pItem->SetObject3D(pos, fWidth, fHeight, fDepth);

	pItem->m_fWidth = fWidth;	// 変数に格納

	pItem->m_fDepth = fDepth;	// 変数に格納

	pItem->SetType(CObject::OBJECTTYPE::TYPE_ITEM);

	return pItem;
}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
bool CItem::CollisionItem(D3DXVECTOR3* pos, D3DXVECTOR3 size, int nType)
{
	bool bHit = false;
	D3DXVECTOR3 CurrentPos = GetPos();	// アイテムの位置
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	m_pParamManager = nullptr;

	m_pParamManager = manager.GetParamManager();
	switch (nType)
	{
	case CObject::OBJECTTYPE::TYPE_PLAYER:	// アイテムにプレイヤーがぶつかってきたとき
		if (pos->z + size.z / 2 >= CurrentPos.z - m_fDepth &&
			pos->z - size.z / 2 <= CurrentPos.z + m_fDepth &&
			pos->x + size.x / 2 >= CurrentPos.x - m_fWidth &&
			pos->x - size.x / 2 <= CurrentPos.x + m_fWidth)
		{
			m_bHit = true;

			bHit = true;

			switch (m_Type)
			{
			case TYPE_POWERUP:
				m_pParamManager->AddParam(600, TYPE_POWERUP);	// 強化時間10秒
				break;
			case TYPE_SPEEDUP:
				m_pParamManager->AddParam(300, TYPE_SPEEDUP);	// 強化時間5秒
				break;
			case TYPE_ENEMYKILL:
				// 特殊処理をここに追加可能
				break;
			}
		}
		break;
	}

	return bHit;
}

int CItem::GetItemType()
{
	return m_Type;
}

//*******************************************************************************************************************************************
// ロード処理
//*******************************************************************************************************************************************
void CItem::Load()
{
	FILE* pFile = nullptr;								// ファイルポインタ
	char aString[128] = {};								// 読み込んだもの保存用
	char aSymbol[4] = {};								// イコールなど保存用
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置保存用

	int nType = 0;										// 種類保存用

	pFile = fopen("data\\TXT\\ITEM\\ItemManager.txt", "r");

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
			
			if (strcmp(&aString[0], "ITEM_SET") == 0)
			{
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{
						fscanf(pFile, "%s %f %f %f",&aSymbol[0], &Pos.x, &Pos.y, &Pos.z);
					}
					else if (strcmp(&aString[0], "TYPE") == 0)
					{
						fscanf(pFile, "%s %d", &aSymbol[0],&nType);
					}

					if (strcmp(&aString[0], "END_ITEMSET") == 0)
					{
						CItem::Create(Pos, ITEM_WIDTH, ITEM_HEIGHT, ITEM_DEPTH, nType);

						break;
					}
				}
			}

		}
	}
}

