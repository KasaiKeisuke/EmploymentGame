//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(cursor.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _CURSOR_H_
#define _CURSOR_H_

// include 
#include "object2D.h"
#include "manager.h"
#include "input.h"

// カーソルクラスの定義
class CCursor : public CObject2D
{
public:
	CCursor(int nPriority = 4);													// コンストラクタ
	~CCursor()override;															// デストラクタ
	HRESULT Init()override;														// 初期化処理
	void Uninit()override;														// 終了処理
	void Update()override;														// 更新処理
	void Draw()override;														// 描画処理
	static CCursor* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);		// 生成処理

private:
	void Select();																// 選択処理

	static const int MAX_SELECT = 2;											// 選択肢の最大個数

	LPDIRECT3DTEXTURE9 m_pTexture;												// テクスチャのポインタ

	CInputKeyboard* m_InputKeyboard;											// キーボードのポインタ
	CInputJoypad* m_InputJoypad;												// ジョイパッドのポインタ

	int m_nSelect;																// 選択肢格納用

	bool m_bCursorMove;															// カーソルが動いているかどうか
	bool m_bScale;																// ポリゴンの拡縮用フラグ
};
static const float MIN_SCALE = 100.0f;											// 最小スケール
static const float MAX_SCALE = 120.0f;											// 最大スケール

#endif