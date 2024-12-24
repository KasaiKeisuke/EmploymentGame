//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(object2D.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

// include
#include "renderer.h"
#include "object.h"

// 2Dポリゴン管理クラス
class CObject2D : public CObject
{
public:
	// ポリゴンの種類の列挙型
	typedef enum
	{
		POLYGON_NONE = 0,
		POLYGON_NORMAL,		// 普通のポリゴン
		POLYGON_NUMBER,		// 数字を扱うポリゴン
		POLYGON_BLINK,		// 点滅させるポリゴン
	}POLYGONTYPE;

	CObject2D(int nPriority = 3);											// コンストラクタ
	~CObject2D()override;													// デストラクタ
	HRESULT Init()override;													// 初期化処理
	void Uninit()override;													// 終了処理
	void Update()override;													// 更新処理
	void Draw()override;													// 描画処理

	static CObject2D* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// 生成処理

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);

	void SetObject2D(D3DXVECTOR3 pos,D3DXCOLOR col, float fWidth, float fHeight);			// 情報設定処理

	void SetPolygonType(POLYGONTYPE type);									// ポリゴンの種類設定

	void SetVtxAnimPolygon(float fWidth, float fHeight, float TexPos);		// 頂点設定処理

	void SetColor(D3DXCOLOR col);											// 色設定処理
	D3DXCOLOR GetColor();													// 色取得処理

	const static int MAX_OBJECT = 128;										// オブジェクト最大数

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;										// 頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;											// テクスチャのポインタ
	LPDIRECT3DDEVICE9 m_pDevice;											// デバイスのポインタ

	D3DXVECTOR3 m_Pos;														// 位置
	D3DXCOLOR m_Col;

	float m_fWidth;															// 幅
	float m_fHeight;														// 高さ

	static CObject2D* m_apObject2D[MAX_OBJECT];								// 2Dポリゴンの数

	POLYGONTYPE m_Type;														// ポリゴンの種類
};
#endif