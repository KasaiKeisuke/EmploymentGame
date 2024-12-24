//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(wall.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "wall.h"
#include "object.h"

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CWall::CWall(int nPriority):CObjectX(nPriority)
{

}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CWall::~CWall()
{

}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CWall::Init()
{
	// Xファイルオブジェクトの初期化処理
	CObjectX::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CWall::Uninit()
{
	// Xファイルオブジェクトの終了処理
	CObjectX::Uninit();

	// 壁の破棄
	Release();
}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CWall::Update()
{
	// Xファイルオブジェクトの更新処理
	CObjectX::Update();
}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CWall::Draw()
{
	// Xファイルオブジェクトの描画処理
	CObjectX::Draw();
}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
CWall* CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	CWall* pWall = new CWall();

	pWall->Init();	// 初期化処理

	pWall->SetPos(pos);	// 位置設定

	pWall->SetRot(rot);	// 向き設定

	switch (nType)
	{
	case 1:
		pWall->BindFileName("data\\MODEL\\WALL\\wall000.x");

		pWall->SetType(CObjectX::OBJECTTYPE::TYPE_NORMALWALL);		// オブジェクトの種類設定
		break;
	case 2:
		pWall->BindFileName("data\\MODEL\\WALL\\wall001.x");

		pWall->SetType(CObjectX::OBJECTTYPE::TYPE_SIDEWALL);		// オブジェクトの種類設定
		break;
	}

	pWall->SetModelSize();	// モデルの大きさ設定

	return nullptr;
}

//*******************************************************************************************************************************************
// 当たり判定
//*******************************************************************************************************************************************
bool CWall::CollisionWall(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size, int type, int nType)
{
	bool bHit = false;							// 当たったかどうか

	D3DXVECTOR3 CurrentPos = GetPos();			// ブロックの座標
	D3DXVECTOR3 CurrentMinVtx = GetMinVtx();	// ブロックの頂点の最小値
	D3DXVECTOR3 CurrentMaxVtx = GetMaxVtx();	// ブロックの頂点の最大値

	switch (type)
	{
	case CObject::OBJECTTYPE::TYPE_NORMALWALL:	// 壁の種類が通常壁の時
		switch (nType)
		{
		case CObject::OBJECTTYPE::TYPE_PLAYER:	// プレイヤーがぶつかってきたとき
			if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
				pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x)
			{// 壁の左側にプレイヤーが当たったとき
				pos->x = CurrentPos.x - NORMALWALL_WIDTH - PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
				pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x)
			{// 壁の右側にプレイヤーが当たったとき
				pos->x = CurrentPos.x + NORMALWALL_WIDTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
				pos->z - size.z / 2 <= CurrentPos.z + CurrentMaxVtx.z)
			{// 壁の奥側にプレイヤーが当たったとき
				pos->z = CurrentPos.z + NORMALWALL_DEPTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
				pos->z + size.z / 2 >= CurrentPos.z + CurrentMinVtx.z)
			{// 壁の手前側にプレイヤーが当たったとき
				pos->z = CurrentPos.z - NORMALWALL_DEPTH - PLAYER_SIZE / 2;
				bHit = true;
			}

			break;
		case CObject::OBJECTTYPE::TYPE_ENEMY:	// 敵がぶつかってきたとき
			if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
				pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x)
			{// 壁の左側にプレイヤーが当たったとき
				//pos->x = CurrentPos.x - NORMALWALL_WIDTH - PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
				pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x)
			{// 壁の右側にプレイヤーが当たったとき
				//pos->x = CurrentPos.x + NORMALWALL_WIDTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
				pos->z - size.z / 2 <= CurrentPos.z + CurrentMaxVtx.z)
			{// 壁の奥側にプレイヤーが当たったとき
				//pos->z = CurrentPos.z + NORMALWALL_DEPTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
				pos->z + size.z / 2 >= CurrentPos.z + CurrentMinVtx.z)
			{// 壁の手前側にプレイヤーが当たったとき
				//pos->z = CurrentPos.z - NORMALWALL_DEPTH - PLAYER_SIZE / 2;
				bHit = true;
			}

			break;

		}
		break;
	case CObject::OBJECTTYPE::TYPE_SIDEWALL:	// 壁の種類が側面壁の時
		switch (nType)
		{
		case CObject::OBJECTTYPE::TYPE_PLAYER:
			if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
				pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x)
			{// 壁の左側にプレイヤーが当たったとき
				pos->x = CurrentPos.x - SIDEWALL_WIDTH - PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
				pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x)
			{// 壁の右側にプレイヤーが当たったとき
				pos->x = CurrentPos.x + SIDEWALL_WIDTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
				pos->z - size.z / 2 <= CurrentPos.z + CurrentMaxVtx.z)
			{// 壁の奥側にプレイヤーが当たったとき
				pos->z = CurrentPos.z + SIDEWALL_DEPTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
				pos->z + size.z / 2 >= CurrentPos.z + CurrentMinVtx.z)
			{// 壁の手前側にプレイヤーが当たったとき
				pos->z = CurrentPos.z - SIDEWALL_DEPTH - PLAYER_SIZE / 2;
				bHit = true;
			}


			break;
		case CObject::OBJECTTYPE::TYPE_ENEMY:	// 敵がぶつかってきたとき
			if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
				pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x)
			{// 壁の左側にプレイヤーが当たったとき
				//pos->x = CurrentPos.x - NORMALWALL_WIDTH - PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
				pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x)
			{// 壁の右側にプレイヤーが当たったとき
				//pos->x = CurrentPos.x + NORMALWALL_WIDTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
				pos->z - size.z / 2 <= CurrentPos.z + CurrentMaxVtx.z)
			{// 壁の奥側にプレイヤーが当たったとき
				//pos->z = CurrentPos.z + NORMALWALL_DEPTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
				pos->z + size.z / 2 >= CurrentPos.z + CurrentMinVtx.z)
			{// 壁の手前側にプレイヤーが当たったとき
				//pos->z = CurrentPos.z - NORMALWALL_DEPTH - PLAYER_SIZE / 2;
				bHit = true;
			}

			break;

		}
		break;
	}
	return bHit;
}

//*******************************************************************************************************************************************
// ロード処理
//*******************************************************************************************************************************************
void CWall::Load()
{
	// ローカル変数宣言
	FILE* pFile = nullptr;	// ファイルポインタ
	char aString[128] = {};	// 読み込んだもの保存用
	char aSymbol[4] = {};	// ゴミ保存用
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置保存用
	D3DXVECTOR3 Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き保存用
	int nType = 0;										// 種類保存用

	pFile = fopen("data\\TXT\\WALL\\WallManager.txt", "r");

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

			if (strcmp(&aString[0], "WALL_SET") == 0)
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


					if (strcmp(&aString[0], "END_WALLSET") == 0)
					{
						CWall::Create(Pos, Rot, nType);
						break;
					}
				}
			}

		}
	}

}
