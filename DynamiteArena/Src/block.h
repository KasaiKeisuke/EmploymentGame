//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(block.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _BLOCK_H_
#define _BLOCK_H_

// include
#include "objectX.h"

// ブロッククラスの定義
class CBlock : public CObjectX
{
public:
	// ブロックの種類の列挙型
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_BREAK,			// 破壊できる
		TYPE_NOTBREAK,		// 破壊できない
	}BLOCKTYPE;

	CBlock(int nPriority = 2);																	// コンストラクタ
	~CBlock()override;																			// デストラクタ
	HRESULT Init()override;																		// 初期化処理
	void Uninit()override;																		// 終了処理
	void Update()override;																		// 更新処理
	void Draw()override;																		// 描画処理
	static CBlock* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type);							// 生成処理
	bool CollisionBlock(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size,int nType);		// 当たり判定(対象物の位置/対象物の1つ前の位置/対象物の大きさ/対象物の種類)

	static void Load();																			// ロード処理

	void SetBlockType(BLOCKTYPE type);															// ブロックの種類設定
	BLOCKTYPE GetType();																		// ブロックの種類取得

private:
	bool m_bDeath;																				// 破壊されたかどうか
	int m_nLife;																				// 耐久力
	BLOCKTYPE m_Type;																			// ブロックの種類

	static const int BLOCK_SIZE = 15;															// ブロックの大きさ(半径)
	static const int PLAYER_SIZE = 20;															// プレイヤーの大きさ(直径)
};

static const float ADJUST_HIT = 5.0f;		// 当たり判定調整用
#endif