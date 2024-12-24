//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(wall.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _WALL_H_
#define _WALL_H_

// include 
#include "objectX.h"
#include <stdio.h>

// 壁クラスの定義
class CWall : public CObjectX
{
public:
	// 壁の種類の列挙型
	typedef enum
	{
		WALL_NONE = 0,
		WALL_NORMAL,	// 通常壁
		WALL_SIDE,		// 側面壁
		WALL_MAX
	}WALLTYPE;

	CWall(int nPriority = 3);																					// コンストラクタ
	~CWall()override;																							// デストラクタ
	HRESULT Init()override;																						// 初期化処理
	void Uninit()override;																						// 終了処理
	void Update()override;																						// 更新処理
	void Draw()override;																						// 描画処理
	static CWall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);											// 生成処理
	bool CollisionWall(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size,int type ,int nType);			// 当たり判定(当たってきたものの位置/当たってきたものの1つ前の位置/当たってきたものの大きさ/当たった壁の種類/当たってきたものの種類)
	static void Load();																							// ロード処理

private:
	static const int NORMALWALL_WIDTH = 50;																		// 通常壁の幅
	static const int NORMALWALL_DEPTH = 10;																		// 通常壁の奥行
	
	static const int SIDEWALL_WIDTH = 10;																		// 側面壁の幅
	static const int SIDEWALL_DEPTH = 51;																		// 側面壁の奥行

	static const int PLAYER_SIZE = 20;																			// プレイヤーの大きさ(直径)

};
#endif