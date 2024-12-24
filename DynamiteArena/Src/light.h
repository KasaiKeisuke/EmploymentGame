//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(light.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _LIGHT_H_
#define _LIGHT_H_

// include
#include "main.h"
#include "camera.h"

// ライトクラスの定義
class CLight
{
public:
	CLight();						// コンストラクタ
	~CLight();						// デストラクタ
	HRESULT Init();					// 初期化処理
	void Uninit();					// 終了処理
	void Update();					// 更新処理

	const static int MAX_LIGHT = 4;	// ライトの最大数
private:
	CCamera* m_pCamera;				// カメラのポインタ
	D3DLIGHT9 m_aLight[MAX_LIGHT];	// ライトの情報

	LPDIRECT3DDEVICE9 m_pDevice;	// デバイスのポインタ
};
#endif