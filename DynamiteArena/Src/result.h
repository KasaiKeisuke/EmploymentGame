//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(result.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _RESULT_H_
#define _RESULT_H_

// include
#include "scene.h"
#include "input.h"

// リザルト画面クラスの定義
class CResult : public CScene
{
public:
	CResult();							// コンストラクタ
	~CResult();							// デストラクタ
	HRESULT Init()override;				// 初期化処理
	void Uninit()override;				// 終了処理
	void Update()override;				// 更新処理
	void Draw()override;				// 描画処理

private:
	CInputKeyboard* m_InputKeyboard;	// キーボードのポインタ
	CInputJoypad* m_InputJoypad;		// ジョイパッドのポインタ
};
#endif