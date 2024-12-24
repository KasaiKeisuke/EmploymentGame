//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(object2D.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "object2D.h"
#include "manager.h"

// 静的メンバ変数初期化
CObject2D* CObject2D::m_apObject2D[MAX_OBJECT] = {};

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CObject2D::CObject2D(int nPriority):CObject(nPriority)
{
	m_pDevice = nullptr;					// デバイスのポインタ
	m_pVtxBuff = nullptr;					// 頂点バッファのポインタ
	m_pTexture = nullptr;					// テクスチャのポインタ
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_fWidth = 0.0f;						// 幅
	m_fHeight = 0.0f;						// 高さ
	m_Type = POLYGONTYPE::POLYGON_NORMAL;	// ポリゴンの種類
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CObject2D::~CObject2D()
{
	m_pDevice = nullptr;					// デバイスのポインタ
	m_pVtxBuff = nullptr;					// 頂点バッファのポインタ
	m_pTexture = nullptr;					// テクスチャのポインタ
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_fWidth = 0.0f;						// 幅
	m_fHeight = 0.0f;						// 高さ
}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CObject2D::Init()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	m_pDevice = manager.GetRenderer()->GetDevice();

	// 頂点バッファの生成
	m_pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点情報のポインタ
	VERTEX_2D* pVtx;
	
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CObject2D::Uninit()
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
void CObject2D::Update()
{
	VERTEX_2D* pVtx;	// 頂点情報のポインタ

	switch (m_Type)
	{
	case CObject2D::POLYGONTYPE::POLYGON_NORMAL:
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y - m_fHeight, m_Pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y - m_fHeight, m_Pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y + m_fHeight, m_Pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y + m_fHeight, m_Pos.z);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
		pVtx[1].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
		pVtx[2].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
		pVtx[3].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点バッファをアンロックする
		m_pVtxBuff->Unlock();

		break;
	case CObject2D::POLYGONTYPE::POLYGON_NUMBER:
		break;
	case CObject2D::POLYGONTYPE::POLYGON_BLINK:

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y - m_fHeight, m_Pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y - m_fHeight, m_Pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y + m_fHeight, m_Pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y + m_fHeight, m_Pos.z);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
		pVtx[1].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
		pVtx[2].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
		pVtx[3].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点バッファをアンロックする
		m_pVtxBuff->Unlock();

		break;
	}
}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CObject2D::Draw()
{
	// 頂点バッファをデータストリームに設定
	m_pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	m_pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	m_pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
CObject2D* CObject2D::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if (m_apObject2D[nCnt] == nullptr)
		{
			m_apObject2D[nCnt] = new CObject2D;

			m_apObject2D[nCnt]->Init();

			//*********************************
			// 引数の値の設定
			//*********************************
			m_apObject2D[nCnt]->m_Pos = pos;

			m_apObject2D[nCnt]->m_fWidth = fWidth;

			m_apObject2D[nCnt]->m_fHeight = fHeight;

			return m_apObject2D[nCnt];
		}
	}

	return nullptr;
}

//*******************************************************************************************************************************************
// テクスチャ設定処理
//*******************************************************************************************************************************************
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//*******************************************************************************************************************************************
// 2Dオブジェクト情報設定処理
//*******************************************************************************************************************************************
void CObject2D::SetObject2D(D3DXVECTOR3 pos,D3DXCOLOR col, float fWidth, float fHeight)
{
	m_Pos = pos;			// 位置
	m_Col = col;			// 色
	m_fWidth = fWidth;		// 幅
	m_fHeight = fHeight;	// 高さ
}

//*******************************************************************************************************************************************
// ポリゴンの種類設定処理
//*******************************************************************************************************************************************
void CObject2D::SetPolygonType(POLYGONTYPE type)
{
	m_Type = type;
}

//*******************************************************************************************************************************************
// ポリゴンの頂点設定処理
//*******************************************************************************************************************************************
void CObject2D::SetVtxAnimPolygon(float fWidth, float fHeight, float TexPos)
{
	float fheightTex = 1.0f / fHeight;

	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y + m_fHeight, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[1].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[2].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[3].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + TexPos * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(((1 / fWidth) + TexPos * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + TexPos * 0.1f, fheightTex);
	pVtx[3].tex = D3DXVECTOR2(((1 / fWidth) + TexPos * 0.1f), fheightTex);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//*******************************************************************************************************************************************
// ポリゴンの頂点設定処理
//*******************************************************************************************************************************************
void CObject2D::SetColor(D3DXCOLOR col)
{
	m_Col = col;
}

//*******************************************************************************************************************************************
// ポリゴンの頂点設定処理
//*******************************************************************************************************************************************
D3DXCOLOR CObject2D::GetColor()
{
	return m_Col;
}
