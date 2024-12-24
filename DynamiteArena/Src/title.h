//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(title.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _TITLE_H_
#define _TITLE_H_

// include
#include "scene.h"
#include "input.h"

// タイトル画面クラスの定義
class CTitle : public CScene
{
public:
	CTitle();							// コンストラクタ
	~CTitle();							// デストラクタ
	HRESULT Init()override;				// 初期化処理
	void Uninit()override;				// 終了処理
	void Update()override;				// 更新処理
	void Draw()override;				// 描画処理

private:
	CInputKeyboard* m_InputKeyboard;	// キーボードのポインタ
	CInputJoypad* m_InputJoypad;		// ジョイパッドのポインタ
};
#endif