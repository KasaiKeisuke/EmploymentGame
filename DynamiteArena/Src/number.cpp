//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(number.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "number.h"
#include "manager.h"

// 静的メンバ変数初期化
LPDIRECT3DTEXTURE9 CNumber::m_pTextureTemp = nullptr;	// テクスチャのポインタ

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CNumber::CNumber(int nPriority) :CObject2D(nPriority)
{

}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CNumber::~CNumber()
{

}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CNumber::Init()
{
	// 2Dオブジェクトの初期化処理
	CObject2D::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CNumber::Uninit()
{
	// 2Dオブジェクトの終了処理
	CObject2D::Uninit();

	// UIの破棄
	Release();

}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CNumber::Update()
{
	// 2Dオブジェクトの更新処理
	CObject2D::Update();
}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CNumber::Draw()
{
	// 2Dオブジェクトの描画処理
	CObject2D::Draw();
}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
CNumber* CNumber::Create(D3DXVECTOR3 pos)
{
	CNumber* pNumber = new CNumber;

	pNumber->Init();	 // 初期化処理

	pNumber->SetObject2D(pos, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),30.0f, 30.0f);

	pNumber->BindTexture(m_pTextureTemp);

	pNumber->SetPolygonType(CObject2D::POLYGONTYPE::POLYGON_NUMBER);
	
	return pNumber;
}

//*******************************************************************************************************************************************
// テクスチャロード
//*******************************************************************************************************************************************
HRESULT CNumber::Load()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	if (m_pTextureTemp == nullptr)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(manager.GetRenderer()->GetDevice(),
			"data\\TEXTURE\\Number003.png",
			&m_pTextureTemp);

	}

	return S_OK;

}

//*******************************************************************************************************************************************
// テクスチャアンロード
//*******************************************************************************************************************************************
void CNumber::UnLoad()
{
	if (m_pTextureTemp != nullptr)
	{
		m_pTextureTemp->Release();

		m_pTextureTemp = nullptr;
	}
}

