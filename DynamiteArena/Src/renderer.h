//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(randerer.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _RENDERER_H_
#define _RENDERER_H_

// include
#include "main.h"
#include "renderer.h"

// レンダラークラスの定義
class CRenderer
{
public:
	CRenderer();													// コンストラクタ
	~CRenderer();													// デストラクタ
	HRESULT Init(HWND hWnd, BOOL bWindow);							// 初期化処理
	void Uninit();													// 終了処理
	void Update();													// 更新処理
	void Draw();													// 描画処理
	LPDIRECT3DDEVICE9 GetDevice();									// デバイスの取得

private:
	LPDIRECT3D9 m_pD3D;												// オブジェクトのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;									// デバイスのポインタ
};

#endif 
