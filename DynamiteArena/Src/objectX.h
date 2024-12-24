//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(objectX.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _OBJECTX_H_
#define _OBJECTX_H_

// include 
#include "object.h"

// Xファイルクラスの定義
class CObjectX : public CObject
{
public:
	CObjectX(int nPriority = 3);								// コンストラクタ
	~CObjectX()override;										// デストラクタ
	HRESULT Init()override;										// 初期化処理
	void Uninit()override;										// 終了処理
	void Update()override;										// 更新処理
	void Draw()override;										// 描画処理

	static CObjectX* Create();									// 生成処理

	void SetPos(D3DXVECTOR3 pos);								// 位置設定処理
	D3DXVECTOR3 GetPos();										// 位置取得処理

	void SetRot(D3DXVECTOR3 rot);								// 向き設定処理
	D3DXVECTOR3 GetRot();										// 向き取得処理

	D3DXVECTOR3 GetPosOld();									// 1つ前の位置の取得

	const static int MAX_SENTENCE = 128;						// ファイルパスの文字数
	const static int MAX_OBJECTX = 256;							// Xファイルオブジェクトの最大個数
	const static int NUM_MATCOLOR = 20;							// マテリアルの数

	void BindFileName(const char aPath[MAX_SENTENCE]);			// ファイルパス設定処理

	void SetModelSize();										// モデルのサイズ設定
	D3DXVECTOR3 GetModelSize();									// モデルのサイズ取得

	D3DXVECTOR3 GetMinVtx();									// モデルの頂点の最小値取得		
	D3DXVECTOR3 GetMaxVtx();									// モデルの頂点の最大値取得

	void SetScale(D3DXVECTOR3 scale);							// スケール設定
	D3DXVECTOR3 GetScale();										// スケール取得

	void SetColor(D3DXCOLOR col);								// マテリアル色設定

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							// 頂点バッファのポインタ
	LPD3DXMESH m_pMesh;											// メッシュのポインタ
	LPD3DXBUFFER m_pBuffMat;									// マテリアルのポインタ
	DWORD m_dwNumMat;											// マテリアルの数
	LPDIRECT3DTEXTURE9* m_pTexture;								// テクスチャのポインタ
	char m_cFileName[MAX_SENTENCE];								// ファイルパス
	int m_nNumVtx;												// 頂点バッファ数
	DWORD m_sizeFVF;											// 頂点フォーマットのサイズ
	BYTE* m_pVtxBuffer;											// 頂点バッファのポインタ

	D3DXVECTOR3 m_Pos;											// 位置
	D3DXVECTOR3 m_PosOld;										// 1つ前の位置
	D3DXVECTOR3 m_Scale;										// サイズ

	D3DXVECTOR3 m_Rot;											// 向き
	D3DXMATRIX m_mtxWorld;										// ワールドマトリックス

	LPDIRECT3DDEVICE9 m_pDevice;								// デバイスのポインタ

	D3DXVECTOR3 m_MinVtx;										// 頂点の最小値
	D3DXVECTOR3 m_MaxVtx;										// 頂点の最大値
	D3DXVECTOR3 m_Size;											// モデルのサイズ

	D3DCOLORVALUE m_FormalDiffuse[MAX_OBJECTX];					// マテリアルの色合い(初期値)
	D3DCOLORVALUE m_Diffuse[MAX_OBJECTX];						// マテリアルの色合い(変更後)

	static CObjectX* m_apObjectX[DRAW_PRIORITY][MAX_OBJECTX];	// Xファイルオブジェクトの情報


};
#endif