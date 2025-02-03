//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(menu.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _MENU_H_
#define _MENU_H_

// include 
#include "object2D.h"
#include "manager.h"

// 選択肢クラスの定義
class CMenu : public CObject2D
{
public:
	// 画像の種類の列挙型
	typedef enum
	{
		MENU_NONE = 0,
		MENU_TUTORIAL,		// チュートリアル
		MENU_GAME,			// ゲーム
		MENU_MAX
	}MENUTYPE;

	CMenu(int nPriority = 4);																// コンストラクタ
	~CMenu()override;																		// デストラクタ
	HRESULT Init()override;																	// 初期化処理
	void Uninit()override;																	// 終了処理
	void Update()override;																	// 更新処理
	void Draw()override;																	// 描画処理
	static CMenu* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, MENUTYPE type);		// 生成処理

private:
	LPDIRECT3DTEXTURE9 m_pTexture;															// テクスチャのポインタ
	MENUTYPE m_Type;																		// テクスチャの種類
};
#endif