//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(PlayerParam.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _PLAYERPARAM_H_
#define _PLAYERPARAM_H_

// include
#include "main.h"

// プレイヤーパラメーター管理クラスの定義
class CParamManager
{
public:
	CParamManager();								// コンストラクタ
	~CParamManager();								// デストラクタ
	HRESULT Init();									// 初期化処理
	void Uninit();									// 終了処理
	void Update();									// 更新処理

	void SetSpeed(float fSpeed);					// プレイヤーの移動速度設定
	float GetSpeed();								// プレイヤーの移動速度取得

	void SetPower(int nPower);						// 爆弾の爆発力設定処理
	int GetPower();									// 爆弾の爆発力取得処理

	int GetTime();									// パラメーターを強化する時間取得

	void AddParam(int nCnt, int nType);				// パラメーター強化処理
	void ResetParam();								// パラメーターリセット処理

private:


	int m_nCnt;										// パラメーターを強化する時間
	int m_nPower;									// 爆発力
	float m_fSpeed;									// 移動速度
};
#endif