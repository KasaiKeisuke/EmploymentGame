//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(TitleLogo.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

// include
#include "object2D.h"
#include "manager.h"

// タイトルロゴクラスの定義
class CTitleLogo : public CObject2D
{
public:
	CTitleLogo(int nPriority = 4);													// コンストラクタ
	~CTitleLogo()override;															// デストラクタ
	HRESULT Init()override;															// 初期化処理
	void Uninit()override;															// 終了処理
	void Update()override;															// 更新処理
	void Draw()override;															// 描画処理
	static CTitleLogo* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);		// 生成処理

private:
	void Animation();																// アニメーション処理

	LPDIRECT3DTEXTURE9 m_pTexture;													// テクスチャのポインタ

	bool m_bAnimation;																// アニメーション用フラグ
};
static const float MIN_COLOR = 0.1f;												// 色の最小値
static const float ANIM_SPEED = 0.01f;												// アニメーションの速度
#endif