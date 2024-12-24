//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(camera.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _CAMERA_H_
#define _CAMERA_H_

// include
#include "main.h"
#include "input.h"

// カメラクラスの定義
class CCamera
{
public:
	CCamera();												// コンストラクタ
	~CCamera();												// デストラクタ
	HRESULT Init();											// 初期化処理
	void Uninit();											// 終了処理
	void Update();											// 更新処理
	void SetCamera();										// カメラ設定処理

	void FollowCamera(D3DXVECTOR3 pos);						// カメラ追従処理									

	void SetRot(D3DXVECTOR3 rot);							// カメラの向き設定処理
	D3DXVECTOR3 GetRot();									// カメラの向き取得処理

	void SetPosV(D3DXVECTOR3 rot);							// カメラの視点設定
	D3DXVECTOR3 GetPosV();									// カメラの視点取得

	void SetPosR(D3DXVECTOR3 rot);							// カメラの注視点設定
	D3DXVECTOR3 GetPosR();									// カメラの注視点取得

	void SetShake(int nCnt, float fShake);					// カメラ揺らし処理
private:
	D3DXVECTOR3 m_PosV;										// カメラの視点
	D3DXVECTOR3 m_PosR;										// カメラの注視点
	D3DXVECTOR3 m_VecU;										// 上方向ベクトル
	D3DXVECTOR3 m_Rot;										// カメラの向き

	D3DXMATRIX m_mtxProjection;								// プロジェクション行列
	D3DXMATRIX m_MtxView;									// ビュー行列
	
	LPDIRECT3DDEVICE9 m_pDevice;							// デバイスのポインタ

	CInputKeyboard* m_InputKeyboard;						// キーボードのポインタ
	CInputJoypad* m_InputJoypad;							// ジョイパッドのポインタ

	int m_nCnt;												// 揺らすフレーム
	float m_fShake;											// 揺らす量
};

// 静的メンバ変数
static const float CameraLength = 100.0f;						// カメラの視点から注視点までの距離
static const float CAMERA_HEIGHT = 200.0f;						// カメラの視点の高さ

#endif