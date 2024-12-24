//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(field.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _FIELD_H_
#define _FIELD_H_

// include 
#include "object3D.h"

// 床クラスの定義
class CField : public CObject3D
{
public:
	CField(int nPriority = 2);																// コンストラクタ
	~CField()override;																		// デストラクタ
	HRESULT Init()override;																	// 初期化処理
	void Uninit()override;																	// 終了処理
	void Update()override;																	// 更新処理
	void Draw()override;																	// 描画処理
	static CField* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth);		// 生成処理

	static HRESULT Load();																	// テクスチャロード
	static void UnLoad();																	// テクスチャアンロード

private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;												// テクスチャ
};
#endif