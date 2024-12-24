//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(object.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _OBJECT_H_
#define _OBJECT_H_

// include
#include "main.h"

// オブジェクトクラスの定義
class CObject
{
public:
	
	// オブジェクトの種類列挙型
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,		// プレイヤー
		TYPE_ENEMY,			// 敵
		TYPE_BLOCK,			// ブロック
		TYPE_NORMALWALL,	// 通常壁
		TYPE_SIDEWALL,		// 側面壁
		TYPE_BULLET,		// 弾
		TYPE_EXPLOSION,		// 爆発
		TYPE_GOAL,			// ゴールマーカー
		TYPE_ITEM,			// アイテム
		TYPE_MAX
	}OBJECTTYPE;

	CObject(int nPriority = 3);								// コンストラクタ
	virtual ~CObject();										// デストラクタ
	virtual HRESULT Init() = 0;								// 初期化処理
	virtual void Uninit() = 0;								// 終了処理
	virtual void Update() = 0;								// 更新処理
	virtual void Draw() = 0;								// 描画処理

	static void ReleaseAll();								// 全オブジェクト破棄
	static void UpdateAll();								// 全オブジェクト更新
	static void DrawAll();									// 全オブジェクト描画
	static CObject* GetObjectInfo(int nPriority, int nIdx);	// オブジェクト情報取得

	void SetType(OBJECTTYPE type);							// オブジェクトの種類設定処理
	OBJECTTYPE GetType();									// オブジェクトの種類取得処理

	static const int MAX_OBJECT = 512;						// オブジェクト最大数
	static const int DRAW_PRIORITY = 5;					// プライオリティ最大数

protected:
	void Release();											// オブジェクト破棄

private:
	static CObject* m_apObject[DRAW_PRIORITY][MAX_OBJECT];	// オブジェクトの情報
	static int m_nNumAll;									// オブジェクトの総数
	int m_nID;												// オブジェクトのID
	int m_nPriority;										// プライオリティ

	OBJECTTYPE m_Type;										// オブジェクトの種類
};

#endif