//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(item.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _ITEM_H_
#define _ITEM_H_

// include
#include "object3D.h"
#include "PlayerParam.h"

// アイテムクラスの定義
class CItem : public CObject3D
{
public:
	// アイテムの種類の列挙型
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_POWERUP,		// パワーアップ
		TYPE_SPEEDUP,		// スピードアップ
		TYPE_ENEMYKILL,		// みそボン撃破用
		TYPE_MAX
	}ITEMTYPE;

	CItem(int nPriority = 3);																		// コンストラクタ
	~CItem()override;																				// デストラクタ
	HRESULT Init()override;																			// 初期化処理
	void Uninit()override;																			// 終了処理
	void Update()override;																			// 更新処理
	void Draw()override;																			// 描画処理
	static CItem* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth,int nType);		// 生成処理

	bool CollisionItem(D3DXVECTOR3* pos, D3DXVECTOR3 size, int nType);								// 当たり判定

	void SetItemType(int nType);																	// アイテムの種類設定
	int GetItemType();																				// アイテムの種類取得

	static void Load();																				// ロード処理																							// アイテムのロード処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;															// テクスチャ

	CParamManager* m_pParamManager;																	// プレイヤーのパラメーター管理クラス

	ITEMTYPE m_Type;																				// アイテムの種類
	float m_fWidth;																					// 幅
	float m_fDepth;																					// 奥行

	bool m_bHit;																					// 当たったかどうか
	bool m_bDeath;																					// 使用されているかどうか

	int m_nLag;																						// アイテムが生成されてから当たり判定を発動させるまでの時間
};
static const float ITEM_WIDTH = 15.0f;																// アイテム用ポリゴンの幅
static const float ITEM_HEIGHT = 0.0f;																// アイテム用ポリゴンの高さ
static const float ITEM_DEPTH = 15.0f;																// アイテム用ポリゴンの奥行
#endif