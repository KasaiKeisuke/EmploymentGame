//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(ItemManager.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _ITEMMANAGER_H_
#define _ITEMMANAGER_H_

// include 
#include "main.h"

// アイテムマネージャークラスの定義
class CItemManager
{
public:
	CItemManager();				// コンストラクタ
	~CItemManager();			// デストラクタ
	HRESULT Init();				// 初期化処理
	void Uninit();				// 終了処理
	void Update();				// 更新処理
	void Draw();				// 描画処理

	void SetNumItem(int nNum);	// アイテムの出現個数設定
	int GetNumItem();			// アイテムの出現個数取得

private:
	int m_nNumItem;				// アイテムの個数
};

#endif