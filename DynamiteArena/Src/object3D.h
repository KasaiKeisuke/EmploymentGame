//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(object3D.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

// include
#include "object.h"
#include "renderer.h"

// 3Dポリゴンクラスの定義
class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 3);															// コンストラクタ
	~CObject3D()override;																	// デストラクタ
	HRESULT Init()override;																	// 初期化処理
	void Uninit()override;																	// 終了処理
	void Update()override;																	// 更新処理
	void Draw()override;																	// 描画処理

	static CObject3D* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth);	// 生成処理(位置/幅/高さ/奥行)

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);												// テクスチャ設定処理

	void SetObject3D(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth);			// 情報設定処理


	void SetPos(D3DXVECTOR3 pos);															// 位置設定処理
	D3DXVECTOR3 GetPos();																	// 位置取得処理

	void SetRot(D3DXVECTOR3 rot);															// 向き設定処理
	D3DXVECTOR3 GetRot();																	// 向き取得処理

	void DrawShadow();																		// 影の描画

	const static int MAX_OBJECT3D = 64;														// 3Dポリゴン最大数

private:
	LPDIRECT3DDEVICE9 m_pDevice;															// デバイスのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;														// 頂点バッファのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;															// テクスチャのポインタ
	D3DXVECTOR3 m_Pos;																		// 位置
	D3DXVECTOR3 m_Rot;																		// 向き
	D3DXCOLOR m_Col;																		// 色
	D3DXMATRIX m_mtxWorld;																	// ワールドマトリックス


	float m_fWidth;																			// 幅
	float m_fHeight;																		// 高さ
	float m_fDepth;																			// 奥行

	static CObject3D* m_apObject3D[MAX_OBJECT3D];											// 3Dポリゴンの数
};
#endif