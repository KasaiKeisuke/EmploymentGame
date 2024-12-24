//***********************************************************************************************************************
//
// ダイナマイトアリーナ(number.h)
// Author : Kasai Keisuke
//
//***********************************************************************************************************************

#ifndef _NUMBER_H_
#define _NUMBER_H_

// include
#include "object2D.h"

// 数字クラスの定義
class CNumber : public CObject2D
{
public:
	CNumber(int nPriority = 4);					// コンストラクタ
	~CNumber()override;							// デストラクタ
	HRESULT Init()override;						// 初期化処理
	void Uninit()override;						// 終了処理
	void Update()override;						// 更新処理
	void Draw()override;						// 描画処理
	static CNumber* Create(D3DXVECTOR3 pos);	// 生成処理

	static HRESULT Load();						// テクスチャロード
	void UnLoad();								// テクスチャアンロード

private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;	// テクスチャのポインタ

};
#endif