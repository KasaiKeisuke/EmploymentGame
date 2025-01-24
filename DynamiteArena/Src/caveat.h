//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(caveat.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _CAVEAT_H_
#define _CAVEAT_H_

// include 
#include "object3D.h"

// 警告表示UIクラスの定義
class CCaveat : public CObject3D
{
public:
	CCaveat(int nPriority = 4);																// コンストラクタ
	~CCaveat()override;																		// デストラクタ
	HRESULT Init()override;																	// 初期化処理
	void Uninit()override;																	// 終了処理
	void Update()override;																	// 更新処理
	void Draw()override;																	// 描画処理
	static CCaveat* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth);		// 生成処理

	static HRESULT Load();																	// テクスチャロード
	static void UnLoad();																	// テクスチャアンロード

	static const int DRAW_COUNT = 120;														// UIの表示時間
private:
	void Death();																			// 死亡判定

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;												// テクスチャ

	int m_nCnt;																				// UI表示時間
	bool m_bDeath;																			// 表示されているかどうか
	bool m_bDelete;																			// 描画させるかどうか
};
#endif