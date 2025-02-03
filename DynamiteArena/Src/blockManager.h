//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(blockManager.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _BLOCKMANAGER_H_
#define _BLOCKMANAGER_H_

// include
#include "main.h"

// ブロックマネージャークラスの定義
class CBlockManager
{
public:
	CBlockManager();				// コンストラクタ
	~CBlockManager();				// デストラクタ
	HRESULT Init();					// 初期化処理
	void Uninit();					// 終了処理
	void Update();					// 更新処理
	void Draw();					// 描画処理

	void SetFlag(bool bFlag);
	bool GetFlag();
};
#endif