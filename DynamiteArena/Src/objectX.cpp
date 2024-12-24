//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(objectX.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "objectX.h"
#include "manager.h"

// 静的メンバ変数初期化
CObjectX* CObjectX::m_apObjectX[DRAW_PRIORITY][MAX_OBJECTX] = {};

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CObjectX::CObjectX(int nPriority):CObject(nPriority)
{
	m_nNumVtx = 0;
	m_dwNumMat = 0;
	m_pBuffMat = NULL;
	m_pMesh = NULL;
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_pVtxBuffer = NULL;
	m_cFileName[0] = NULL;

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CObjectX::~CObjectX()
{
	if (m_pTexture != nullptr)
	{// テクスチャの破棄
		for (DWORD i = 0; i < m_dwNumMat; i++)
		{
			m_pTexture[i]->Release();
		}
		delete[]m_pTexture;
		m_pTexture = nullptr;
	}

	m_nNumVtx = 0;
	m_dwNumMat = 0;
	m_pBuffMat = NULL;
	m_pMesh = NULL;
	m_pVtxBuff = nullptr;
	m_pVtxBuffer = NULL;
	m_cFileName[0] = NULL;

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CObjectX::Init()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	m_pDevice = manager.GetRenderer()->GetDevice();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CObjectX::Uninit()
{
	// メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	// テクスチャの解放
	if (m_pTexture != nullptr)
	{
		for (DWORD i = 0; i < m_dwNumMat; i++)
		{
			if (m_pTexture[i] != nullptr)
			{
				m_pTexture[i]->Release();
				m_pTexture[i] = nullptr;
			}
		}
		delete[] m_pTexture;
		m_pTexture = nullptr;
	}

}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CObjectX::Update()
{
	m_PosOld = m_Pos;	// 位置の保存
}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CObjectX::Draw()
{
	// ローカル変数宣言
	D3DXMATRIX mtxRot, mtxTrans,mtxScale;		// 計算用マトリックス
	D3DMATERIAL9 matDef = {};					// 現在のマテリアル
	D3DXMATERIAL* pMat = nullptr;				// マテリアルのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// スケールを設定
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// 法線の正規化
	m_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// ワールドマトリックスの設定
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルの取得
	m_pDevice->GetMaterial(&matDef);

	//m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// マテリアルデータへのポインタ取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		pMat[nCntMat].MatD3D.Diffuse = m_Diffuse[nCntMat];
		
		// マテリアルの設定
		m_pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		m_pDevice->SetTexture(0, m_pTexture[nCntMat]);

		// モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	// 保存していたマテリアルを元に戻す
	m_pDevice->SetMaterial(&matDef);

	// 法線を元に戻す
	m_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
CObjectX* CObjectX::Create()
{
	for (int nCntPriority = 0; nCntPriority < DRAW_PRIORITY; nCntPriority++)
	{
		for (int nCntObjectX = 0; nCntObjectX < MAX_OBJECTX; nCntObjectX++)
		{
			if (m_apObjectX[nCntPriority][nCntObjectX] == nullptr)
			{
				m_apObjectX[nCntPriority][nCntObjectX] = new CObjectX;

				m_apObjectX[nCntPriority][nCntObjectX]->Init();	// 初期化処理

				return m_apObjectX[nCntPriority][nCntObjectX];
			}
		}
	}

	
	return nullptr;
}

//*******************************************************************************************************************************************
// 位置設定処理
//*******************************************************************************************************************************************
void CObjectX::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//*******************************************************************************************************************************************
// 位置取得処理
//*******************************************************************************************************************************************
D3DXVECTOR3 CObjectX::GetPos()
{
	return m_Pos;
}

//*******************************************************************************************************************************************
// 向き設定処理
//*******************************************************************************************************************************************
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_Rot = rot;
}

//*******************************************************************************************************************************************
// 向き取得処理
//*******************************************************************************************************************************************
D3DXVECTOR3 CObjectX::GetRot()
{
	return m_Rot;
}

//*******************************************************************************************************************************************
// ファイルパス設定処理
//*******************************************************************************************************************************************
void CObjectX::BindFileName(const char aPath[MAX_SENTENCE])
{
	strcpy(&m_cFileName[0], &aPath[0]);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(m_cFileName,
		D3DXMESH_SYSTEMMEM,
		m_pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	// マテリアル情報の取得
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	m_pTexture = new LPDIRECT3DTEXTURE9[m_dwNumMat];

	for (DWORD i = 0; i < m_dwNumMat; i++)
	{
		m_pTexture[i] = nullptr;

		if (pMat[i].pTextureFilename)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(m_pDevice, pMat[i].pTextureFilename, &m_pTexture[i]);

		}

		m_FormalDiffuse[i] = pMat[i].MatD3D.Diffuse;
		m_Diffuse[i] = pMat[i].MatD3D.Diffuse;

	}

}

//*******************************************************************************************************************************************
// モデルの大きさ設定処理
//*******************************************************************************************************************************************
void CObjectX::SetModelSize()
{
	// 頂点数の取得
	m_nNumVtx = m_pMesh->GetNumVertices();

	// 頂点フォーマットのサイズを取得
	m_sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// 頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuffer);

	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		// 頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuffer;

		// 頂点座標を比較してモデルの最小値・最大値を取得
		if (vtx.x < m_MinVtx.x)
		{
			m_MinVtx.x = vtx.x;
		}
		else if (vtx.x > m_MaxVtx.x)
		{
			m_MaxVtx.x = vtx.x;
		}

		if (vtx.y < m_MinVtx.y)
		{
			m_MinVtx.y = vtx.y;
		}
		else if (vtx.y > m_MaxVtx.y)
		{
			m_MaxVtx.y = vtx.y;
		}

		if (vtx.z < m_MinVtx.z)
		{
			m_MinVtx.z = vtx.z;
		}
		else if (vtx.z > m_MaxVtx.z)
		{
			m_MaxVtx.z = vtx.z;
		}

		// モデルのサイズを求める
		m_Size = m_MaxVtx - m_MinVtx;

		// 頂点フォーマットのサイズ分ポインタを進める
		m_pVtxBuffer += m_sizeFVF;
	}

	// 頂点バッファのアンロック
	m_pMesh->UnlockVertexBuffer();
}

//*******************************************************************************************************************************************
// モデルの大きさ取得処理
//*******************************************************************************************************************************************
D3DXVECTOR3 CObjectX::GetModelSize()
{
	return m_Size;
}

//***********************************************************************************************************************
// モデルの頂点の最小値取得処理
//***********************************************************************************************************************
D3DXVECTOR3 CObjectX::GetMinVtx()
{
	return m_MinVtx;
}

//***********************************************************************************************************************
// モデルの頂点の最大値取得処理
//***********************************************************************************************************************
D3DXVECTOR3 CObjectX::GetMaxVtx()
{
	return m_MaxVtx;
}

//***********************************************************************************************************************
// スケール設定処理
//***********************************************************************************************************************
void CObjectX::SetScale(D3DXVECTOR3 scale)
{
	m_Scale = scale;
}

//***********************************************************************************************************************
// スケール取得処理
//***********************************************************************************************************************
D3DXVECTOR3 CObjectX::GetScale()
{
	return m_Scale;
}

//*******************************************************************************************************************************************
// 色設定処理
//*******************************************************************************************************************************************
void CObjectX::SetColor(D3DXCOLOR col)
{
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		m_Diffuse[nCntMat] = col;
	}
}

//***********************************************************************************************************************
// 1つ前の位置の取得処理
//***********************************************************************************************************************
D3DXVECTOR3 CObjectX::GetPosOld()
{
	return m_PosOld;
}

