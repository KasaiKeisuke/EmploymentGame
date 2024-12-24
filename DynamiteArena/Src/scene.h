//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(scene.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _SCENE_H_
#define _SCENE_H_

// include
#include "main.h"

// シーン基底クラスの定義
class CScene
{
public:
	// 画面の種類
	typedef enum
	{
		MODE_TITLE = 0,		// タイトル画面
		MODE_TUTORIAL,		// チュートリアル画面
		MODE_GAME,			// ゲーム画面
		MODE_CLEARRESULT,	// ゲームクリア画面
		MODE_FAILRESULT,	// ゲームオーバー画面
		MODE_MAX
	}MODE;

	CScene();							// コンストラクタ
	~CScene();							// デストラクタ
	virtual HRESULT Init();				// 初期化処理
	virtual void Uninit();				// 終了処理
	virtual void Update();				// 更新処理
	virtual void Draw();				// 描画処理
	static CScene* Create(MODE mode);	// 生成処理
	void SetMode(MODE mode);			// モード設定処理
	MODE GetMode();						// モード取得処理

private:
	MODE m_Mode;						// 現在のモード
};
#endif