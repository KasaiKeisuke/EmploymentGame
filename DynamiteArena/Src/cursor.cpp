//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(cursor.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "cursor.h"

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CCursor::CCursor(int nPriority):CObject2D(nPriority)
{
	m_pTexture = nullptr;		// テクスチャのポインタ
	m_nSelect = 0;				// 選択肢格納用
	m_bCursorMove = false;		// カーソルを動かしているかどうか
	m_InputKeyboard = nullptr;	// キーボードのポインタ
	m_InputJoypad = nullptr;	// ジョイパッドのポインタ
	m_bScale = true;			// ポリゴンの拡縮用フラグ(trueの時に大きくする)
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CCursor::~CCursor()
{
	m_pTexture = nullptr;		// テクスチャのポインタ
	m_nSelect = 0;				// 選択肢格納用
	m_bCursorMove = false;		// カーソルを動かしているかどうか
	m_InputKeyboard = nullptr;	// キーボードのポインタ
	m_InputJoypad = nullptr;	// ジョイパッドのポインタ
	m_bScale = true;			// ポリゴンの拡縮用フラグ(trueの時に大きくする)
}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CCursor::Init()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	m_InputKeyboard = manager.GetKeyboard();

	m_InputJoypad = manager.GetJoypad();

	m_nSelect = 1;
	
	// 2Dオブジェクトの初期化処理
	CObject2D::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CCursor::Uninit()
{
	// 2Dオブジェクトの終了処理
	CObject2D::Uninit();

	Release();
}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CCursor::Update()
{
	// 2Dオブジェクトの更新処理
	CObject2D::Update();

	// 選択処理
	Select();

}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CCursor::Draw()
{
	// 2Dオブジェクトの描画処理
	CObject2D::Draw();
}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
CCursor* CCursor::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	CCursor* pCursor = new CCursor();

	pCursor->Init();	// 初期化処理

	pCursor->SetObject2D(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fWidth, fHeight);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(manager.GetRenderer()->GetDevice(), "data\\TEXTURE\\cursor000.png", &pCursor->m_pTexture);

	pCursor->BindTexture(pCursor->m_pTexture);

	return pCursor;
}

//*******************************************************************************************************************************************
// 選択処理
//*******************************************************************************************************************************************
void CCursor::Select()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	D3DXVECTOR3 CurrentPos = GetPos();	// 位置取得
	float CurrentWidth = GetWidth();	// 幅取得
	float CurrentHeight = GetHeight();	// 高さ取得

	if (!m_InputKeyboard->GetPress(DIK_UP) && !m_InputKeyboard->GetPress(DIK_DOWN) || m_InputJoypad->GetPress(CInputJoypad::JOYKEY_UP) || m_InputJoypad->GetPress(CInputJoypad::JOYKEY_DOWN))
	{
		m_bCursorMove = false;
	}

	if (m_InputKeyboard->GetPress(DIK_UP) || m_InputKeyboard->GetPress(DIK_DOWN) || m_InputJoypad->GetRepeat(CInputJoypad::JOYKEY_UP) || m_InputJoypad->GetRepeat(CInputJoypad::JOYKEY_DOWN))
	{
		m_bCursorMove = true;
	}


	if (!m_bCursorMove)
	{// カーソルが動いていないとき
		if (CurrentWidth <= MIN_SCALE && CurrentHeight <= MIN_SCALE)
		{
			m_bScale = true;
		}

		if (CurrentWidth >= MAX_SCALE && CurrentHeight >= MAX_SCALE)
		{
			m_bScale = false;
		}

		if (m_bScale)
		{
			CurrentWidth += 1.0f;
			CurrentHeight += 1.0f;
		}
		else if (!m_bScale)
		{
			CurrentWidth -= 1.0f;
			CurrentHeight -= 1.0f;
		}

		SetSize(CurrentWidth, CurrentHeight);
	}
	else if (m_bCursorMove)
	{
		if (m_InputKeyboard->GetRepeat(DIK_UP) || m_InputJoypad->GetRepeat(CInputJoypad::JOYKEY_UP))
		{
			m_nSelect--;
		}

		if (m_InputKeyboard->GetRepeat(DIK_DOWN) || m_InputJoypad->GetRepeat(CInputJoypad::JOYKEY_DOWN))
		{
			m_nSelect++;
		}

		if (m_nSelect < 1)
		{
			m_nSelect = MAX_SELECT;
		}
		else if (m_nSelect > MAX_SELECT)
		{
			m_nSelect = 1;
		}

		switch (m_nSelect)
		{
		case 1:
			CurrentPos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 250.0f, SCREEN_HEIGHT / 2.0f - 150.0f, 0.0f);

			break;
		case 2:
			CurrentPos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 250.0f, SCREEN_HEIGHT / 2.0f + 150.0f, 0.0f);

			break;
		}


		SetPos(CurrentPos);
	}

	// 画面遷移処理
	if (m_InputKeyboard->GetTrigger(DIK_RETURN) || m_InputJoypad->GetTrigger(CInputJoypad::JOYKEY_A))
	{
		switch (m_nSelect)
		{
		case 1:
			manager.SetMode(CScene::MODE::MODE_TUTORIAL);

			break;
		case 2:
			manager.SetMode(CScene::MODE::MODE_GAME);

			break;
		}
	}

}
