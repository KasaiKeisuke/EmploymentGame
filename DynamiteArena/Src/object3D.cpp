//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(object3D.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "object3D.h"
#include "manager.h"

// 静的メンバ変数初期化
CObject3D* CObject3D::m_apObject3D[MAX_OBJECT3D] = {};

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CObject3D::CObject3D(int nPriority):CObject(nPriority)
{
	m_pDevice = nullptr;					// デバイスのポインタ
	m_pVtxBuff = nullptr;					// 頂点バッファのポインタ
	m_pTexture = nullptr;					// テクスチャのポインタ
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色
	m_mtxWorld = {};						// ワールドマトリックス
	m_fWidth = 0.0f;						// 幅
	m_fHeight = 0.0f;						// 高さ
	m_fDepth = 0.0f;						// 奥行

}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CObject3D::~CObject3D()
{
	m_pDevice = nullptr;					// デバイスのポインタ
	m_pVtxBuff = nullptr;					// 頂点バッファのポインタ
	m_pTexture = nullptr;					// テクスチャのポインタ
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_mtxWorld = {};						// ワールドマトリックス
	m_fWidth = 0.0f;						// 幅
	m_fHeight = 0.0f;						// 高さ
	m_fDepth = 0.0f;						// 奥行

}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CObject3D::Init()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	m_pDevice = manager.GetRenderer()->GetDevice();

	// 頂点バッファの生成
	m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし、頂点情報のポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CObject3D::Uninit()
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Release();
}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CObject3D::Update()
{
	// 頂点情報のポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f - m_fWidth, 0.0f, 0.0f + m_fDepth);
	pVtx[1].pos = D3DXVECTOR3(0.0f + m_fWidth, 0.0f, 0.0f + m_fDepth);
	pVtx[2].pos = D3DXVECTOR3(0.0f - m_fWidth, 0.0f, 0.0f - m_fDepth);
	pVtx[3].pos = D3DXVECTOR3(0.0f + m_fWidth, 0.0f, 0.0f - m_fDepth);

	// 法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CObject3D::Draw()
{
	// ローカル変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置の反映
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	m_pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	m_pDevice->SetFVF(FVF_VERTEX_3D);

	if (m_pTexture != nullptr)
	{
		// テクスチャの設定
		m_pDevice->SetTexture(0, m_pTexture);
	}

	// ポリゴンの描画
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
CObject3D* CObject3D::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth)
{
	for (int nCnt = 0; nCnt < MAX_OBJECT3D; nCnt++)
	{
		if (m_apObject3D[nCnt] == nullptr)
		{
			m_apObject3D[nCnt] = new CObject3D;

			m_apObject3D[nCnt]->Init();

			m_apObject3D[nCnt]->SetObject3D(pos, fWidth, fHeight, fDepth);

			return m_apObject3D[nCnt];
		}
	}
	return nullptr;
}

//*******************************************************************************************************************************************
// テクスチャ設定処理
//*******************************************************************************************************************************************
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//*******************************************************************************************************************************************
// 情報設定処理
//*******************************************************************************************************************************************
void CObject3D::SetObject3D(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth)
{
	m_Pos = pos;			// 位置
	m_fWidth = fWidth;		// 幅
	m_fHeight = fHeight;	// 高さ
	m_fDepth = fDepth;		// 奥行
}

//*******************************************************************************************************************************************
// 位置設定処理
//*******************************************************************************************************************************************
void CObject3D::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//*******************************************************************************************************************************************
// 位置取得処理
//*******************************************************************************************************************************************
D3DXVECTOR3 CObject3D::GetPos()
{
	return m_Pos;
}

//*******************************************************************************************************************************************
// 向き設定処理
//*******************************************************************************************************************************************
void CObject3D::SetRot(D3DXVECTOR3 rot)
{
	m_Rot = rot;
}

//*******************************************************************************************************************************************
// 向き取得処理
//*******************************************************************************************************************************************
D3DXVECTOR3 CObject3D::GetRot()
{
	return m_Rot;
}

//*******************************************************************************************************************************************
// 影の描画処理
//*******************************************************************************************************************************************
void CObject3D::DrawShadow()
{
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// 減算合成の設定
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置の反映
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	m_pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	m_pDevice->SetFVF(FVF_VERTEX_3D);

	if (m_pTexture != nullptr)
	{
		// テクスチャの設定
		m_pDevice->SetTexture(0, m_pTexture);
	}

	// ポリゴンの描画
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// 通常の合成に戻す
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

