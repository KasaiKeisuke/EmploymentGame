//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(billboard.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "billboard.h"
#include "manager.h"

// 静的メンバ変数初期化
CBillboard* CBillboard::m_apBillboard[MAX_BILLBOARD] = {};

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CBillboard::CBillboard(int nPriority):CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pDevice = nullptr;
	m_mtxWorld = {};

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_fLength = 0.0f;
	m_Type = TYPE_NONE;
	m_nAnimFrame = 0;
	m_nAnimCount = 0;
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CBillboard::~CBillboard()
{

}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CBillboard::Init()
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

	// 頂点バッファをロックし、頂点情報へのポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	// 法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	// テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CBillboard::Uninit()
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CBillboard::Update()
{
	m_PosOld = m_Pos;	// 位置の保存

	// 頂点情報の更新
	SetVtx(m_Type);
}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CBillboard::Draw()
{
	// ローカル変数宣言
	D3DXMATRIX mtxTrans, mtxViex;

	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// ビューマトリックスを取得
	m_pDevice->GetTransform(D3DTS_VIEW, &mtxViex);

	// ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxViex);

	// 逆行列を求める
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	// 位置の反映
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ライトを無効にする
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの設定
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	m_pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	m_pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	m_pDevice->SetTexture(0, m_pTexture);

	// ビルボードの描画
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ライトを有効に戻す
	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
CBillboard* CBillboard::Create()
{
	for (int nCntBillborad = 0; nCntBillborad < MAX_BILLBOARD; nCntBillborad++)
	{
		if (m_apBillboard[nCntBillborad] == nullptr)
		{
			m_apBillboard[nCntBillborad] = new CBillboard();

			m_apBillboard[nCntBillborad]->Init();

			return m_apBillboard[nCntBillborad];
		}
	}
	return nullptr;
}

//*******************************************************************************************************************************************
// ビルボード情報設定処理
//*******************************************************************************************************************************************
void CBillboard::SetBillboard(D3DXVECTOR3 pos, float fWidth, float fHeight, int nDivision, BILLBOARDTYPE type)
{
	m_Pos = pos;						// 位置
	m_fWidth = fWidth;					// 幅
	m_fHeight = fHeight;				// 高さ
	m_nTexDivision = nDivision;			// テクスチャ分割数
	m_Type = type;						// 種類
}

//*******************************************************************************************************************************************
// 頂点情報設定処理
//*******************************************************************************************************************************************
void CBillboard::SetVtx(BILLBOARDTYPE type)
{
	int CurrentCount = GetAnimCount();

	// 頂点情報のポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 対角線の長さを求める
	m_fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight);

	// 頂点情報の設定
	pVtx[0].pos.x = -m_fLength;
	pVtx[0].pos.y = m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_fLength;
	pVtx[1].pos.y = m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -m_fLength;
	pVtx[2].pos.y = -m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_fLength;
	pVtx[3].pos.y = -m_fLength;
	pVtx[3].pos.z = 0.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[1].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[2].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[3].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / m_nTexDivision, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / m_nTexDivision, 1.0f);

	switch (type)
	{
	case CBillboard::BILLBOARDTYPE::TYPE_BULLET:


		break;
	case CBillboard::BILLBOARDTYPE::TYPE_EXPLOSION:

		m_nAnimFrame++;

		if (m_nAnimFrame % 6 == 0)
		{
			pVtx[0].tex.x += 0.125f;
			pVtx[1].tex.x += 0.125f;
			pVtx[2].tex.x += 0.125f;
			pVtx[3].tex.x += 0.125f;

			CurrentCount++;

		}
		SetAnimCount(CurrentCount);

		break;

	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//*******************************************************************************************************************************************
// テクスチャ設定処理
//*******************************************************************************************************************************************
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//*******************************************************************************************************************************************
// 位置設定処理
//*******************************************************************************************************************************************
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//*******************************************************************************************************************************************
// 位置取得処理
//*******************************************************************************************************************************************
D3DXVECTOR3 CBillboard::GetPos()
{
	return m_Pos;
}

//*******************************************************************************************************************************************
// 色設定処理
//*******************************************************************************************************************************************
void CBillboard::SetColor(D3DXCOLOR col)
{
	m_Col = col;
}

//*******************************************************************************************************************************************
// 色取得処理
//*******************************************************************************************************************************************
D3DXCOLOR CBillboard::GetColor()
{
	return m_Col;
}

//*******************************************************************************************************************************************
// 位置取得処理
//*******************************************************************************************************************************************
void CBillboard::SetAnimCount(int nCnt)
{
	m_nAnimCount = nCnt;
}

//*******************************************************************************************************************************************
// アニメーションさせた回数取得処理
//*******************************************************************************************************************************************
int CBillboard::GetAnimCount()
{
	return m_nAnimCount;
}
