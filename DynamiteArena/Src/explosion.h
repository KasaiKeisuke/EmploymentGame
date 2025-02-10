//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(explosion.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

// include 
#include "objectX.h"

// 爆発クラスの定義
class CExplosion : public CObjectX
{
public:
	CExplosion(int nPriority = 3);																	// コンストラクタ
	~CExplosion()override;																			// デストラクタ
	HRESULT Init()override;																			// 初期化処理
	void Uninit()override;																			// 終了処理
	void Update()override;																			// 更新処理
	void Draw()override;																			// 描画処理
	static CExplosion* Create(D3DXVECTOR3 pos);														// 生成処理

	static HRESULT Load();																			// Xファイルロード
	static void UnLoad();																			// Xファイルアンロード

	bool CollisionExplosion(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size, int nType);	// 当たり判定

	static const int DRAW_COUNT = 60;																// 表示させる時間
	static const int FILE_PATH = 256;																// ファイルパス
	static const int TIME_LAG = 25;																	// モーションを切り替えるまでの時間
	static const int EXPLOSION_SIZE = 20;															// 爆発の大きさ

private:
	void Turn();																					// 回転処理
	void Motion();																					// モーション処理

	static char m_pFiletemp[FILE_PATH];																// ファイルパス
	int m_nCnt;																						// 表示させる時間

	int m_nLag;																						// 拡縮を切り替えるまでの時間
	bool m_bScale;																					// 拡縮用フラグ
};

static const float MAX_SCALE = 1.6f;																// モデルの最大スケール
static const float ANIM_SPEEDFAST = 0.5f;															// アニメーション速度(速い)
static const float ANIM_SPEEDLATE = 0.05f;															// アニメーション速度(遅い)

#endif