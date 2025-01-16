//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(misobon.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _MISOBON_H_
#define _MISOBON_H_

// include
#include "objectX.h"

// みそボンクラスの定義
class CMisobon : public CObjectX
{
public:
	CMisobon(int nPriority = 3);											// コンストラクタ
	~CMisobon()override;													// デストラクタ
	HRESULT Init()override;													// 初期化処理
	void Uninit()override;													// 終了処理
	void Update()override;													// 更新処理
	void Draw()override;													// 描画処理
	static CMisobon* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);	// 生成処理

private:
	void Move();															// 移動処理

	int m_nType;															// 種類
	bool m_bMoveHorizon;													// 敵の横移動
	bool m_bMoveVertical;													// 敵の縦移動
};
#endif