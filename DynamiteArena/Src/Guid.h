//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(Guid.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _GUID_H_
#define _GUID_H_

// include
#include "object2D.h"
#include "manager.h"

// ガイドクラスの定義
class CGuid : public CObject2D
{
public:
	// テクスチャの種類の列挙型
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_STARTGAME,		// ゲームを始める用
		TYPE_RETURNTITLE,	// タイトル画面に戻る用
		TYPE_MAX
	}TEXTURETYPE;

	CGuid(int nPriority = 4);																	// コンストラクタ
	~CGuid()override;																			// デストラクタ
	HRESULT Init()override;																		// 初期化処理
	void Uninit()override;																		// 終了処理
	void Update()override;																		// 更新処理
	void Draw()override;																		// 描画処理
	static CGuid* Create(D3DXVECTOR3 pos, float fWidth, float fHeight,TEXTURETYPE type);		// 生成処理

private:
	LPDIRECT3DTEXTURE9 m_pTexture;																// テクスチャのポインタ
};
#endif