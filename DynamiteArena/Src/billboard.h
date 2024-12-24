//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(billboard.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

// include
#include "object.h"

// ビルボードクラスの定義
class CBillboard : public CObject
{
public:
	// ビルボードの種類の列挙型
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_BULLET,			// 弾
		TYPE_PARTICLE,			// パーティクル
		TYPE_EFFECT,			// エフェクト
		TYPE_EXPLOSION,			// 爆発
		TYPE_CAVEATUI,			// 警告表示UI
		TYPE_MAX
	}BILLBOARDTYPE;

	CBillboard(int nPriority = 3);																		// コンストラクタ
	~CBillboard()override;																				// デストラクタ
	HRESULT Init()override;																				// 初期化処理
	void Uninit()override;																				// 終了処理
	void Update()override;																				// 更新処理
	void Draw()override;																				// 描画処理
	static CBillboard* Create();																		// 生成処理

	void SetBillboard(D3DXVECTOR3 pos, float fWidth, float fHeight, int nDivision,BILLBOARDTYPE type);	// ビルボードの情報設定(位置/幅/高さ/テクスチャの分割数)
	void SetVtx(BILLBOARDTYPE type);																	// 頂点情報の設定

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);															// テクスチャの設定

	void SetPos(D3DXVECTOR3 pos);																		// 位置設定処理
	D3DXVECTOR3 GetPos();																				// 位置取得処理

	void SetColor(D3DXCOLOR col);																		// 色設定処理
	D3DXCOLOR GetColor();																				// 色取得処理

	void SetAnimCount(int nCnt);																		// アニメーションさせた回数設定処理
	int GetAnimCount();																					// アニメーションさせた回数取得処理

	static const int MAX_BILLBOARD = 512;																// ビルボードの最大数

private:
	LPDIRECT3DDEVICE9 m_pDevice;																		// デバイスのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;																	// 頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;																		// テクスチャのポインタ
	D3DXVECTOR3 m_Pos;																					// 位置
	D3DXVECTOR3 m_PosOld;																				// 1つ前の位置
	D3DXCOLOR m_Col;																					// 色
	D3DXMATRIX m_mtxWorld;																				// ワールドマトリックス

	int m_nTexDivision;																					// テクスチャの分割数
	int m_nAnimFrame;																					// アニメーションさせる時間間隔
	int m_nAnimCount;																					// アニメーションさせた回数

	float m_fWidth;																						// 幅
	float m_fHeight;																					// 高さ
	float m_fLength;																					// 対角線の長さ

	BILLBOARDTYPE m_Type;																				// ビルボードの種類

	static CBillboard* m_apBillboard[MAX_BILLBOARD];													// ビルボードの情報
};
#endif