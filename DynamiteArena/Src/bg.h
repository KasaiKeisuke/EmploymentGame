//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(bg.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _BG_H_
#define _BG_H_

// include
#include "object2D.h"

// 画面背景クラスの定義
class CBg : public CObject2D
{
public:
	// 背景テクスチャ種類の列挙型
	typedef enum
	{
		TYPE_TITLE = 0,																	// タイトル画面
		TYPE_TUTORIAL,																	// チュートリアル画面
		TYPE_GAME,																		// ゲーム画面
		TYPE_CLEARRESULT,																// ゲームクリア画面
		TYPE_FAILRESULT,																// ゲームオーバー画面
		TYPE_MAX
	}TEXTYPE;

	CBg(int nPriority = 4);																// コンストラクタ
	~CBg()override;																		// デストラクタ
	HRESULT Init()override;																// 初期化処理
	void Uninit()override;																// 終了処理
	void Update()override;																// 更新処理
	void Draw()override;																// 描画処理
	static CBg* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, TEXTYPE type);		// 生成処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;												// テクスチャ
};
#endif