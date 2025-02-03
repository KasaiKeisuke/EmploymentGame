//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(tutorial.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

// include 
#include "scene.h"
#include "input.h"

// チュートリアル画面クラスの定義
class CTutorial : public CScene
{
public:
	CTutorial();						// コンストラクタ
	~CTutorial();						// デストラクタ
	HRESULT Init();						// 初期化処理
	void Uninit();						// 終了処理
	void Update();						// 更新処理
	void Draw();						// 描画処理

private:
	CInputKeyboard* m_InputKeyboard;	// キーボードのポインタ
	CInputJoypad* m_InputJoypad;		// ジョイパッドのポインタ

	int m_nCnt;							// 画面遷移させるまでの時間

	static const int MAX_LAG = 5;		// 画面遷移させるタイミング
};
#endif