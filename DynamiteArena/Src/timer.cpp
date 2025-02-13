//*******************************************************************************************************************************************
//
// ダイナマイトアリーナ(timer.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "timer.h"
#include "manager.h"

//*******************************************************************************************************************************************
// 静的メンバ変数初期化
//*******************************************************************************************************************************************
CNumber* CTimer::m_aNumber[MAX_DIGIT] = {};
int CTimer::m_nTimer = 0;

//*******************************************************************************************************************************************
// コンストラクタ
//*******************************************************************************************************************************************
CTimer::CTimer(int nPriority):CObject(nPriority)
{
	m_pGameManager = nullptr;
}

//*******************************************************************************************************************************************
// デストラクタ
//*******************************************************************************************************************************************
CTimer::~CTimer()
{
	m_pGameManager = nullptr;
}

//*******************************************************************************************************************************************
// 初期化処理
//*******************************************************************************************************************************************
HRESULT CTimer::Init()
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();
	m_pGameManager = manager.GetGameManager();

	if (m_pGameManager != nullptr)
	{
		m_nTimer = m_pGameManager->GetTimer();
	}

	// 桁数分の数字の生成
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_aNumber[nCnt] = CNumber::Create(D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (40.0f * nCnt), 50.0f, 0.0f));
	}

	return S_OK;
}

//*******************************************************************************************************************************************
// 終了処理
//*******************************************************************************************************************************************
void CTimer::Uninit()
{
	// タイマーの桁数分の終了処理
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_aNumber[nCnt]->Uninit();
	}

	// タイマーの破棄
	Release();
}

//*******************************************************************************************************************************************
// 更新処理
//*******************************************************************************************************************************************
void CTimer::Update()
{
	int aTime[MAX_DIGIT];	// 各桁の数字保存用

	int nTime = m_pGameManager->GetTimer();

	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		// 桁数の分解
		aTime[nCnt] = nTime % 10;
		nTime /= 10;

	}

	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_aNumber[nCnt]->SetVtxAnimPolygon(10.0f, 1.0f, (float)aTime[nCnt]);
	
		m_aNumber[nCnt]->Update();
	}
}

//*******************************************************************************************************************************************
// 描画処理
//*******************************************************************************************************************************************
void CTimer::Draw()
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_aNumber[nCnt]->Draw();
	}
}

//*******************************************************************************************************************************************
// 生成処理
//*******************************************************************************************************************************************
CTimer* CTimer::Create()
{
	CTimer* pTimer = new CTimer();

	pTimer->Init();

	return pTimer;
}

//*******************************************************************************************************************************************
// タイマー減算処理
//*******************************************************************************************************************************************
void CTimer::Sub(int nTime)
{
	// シングルトンインスタンスの取得
	CManager& manager = CManager::GetInstance();

	m_nTimer = manager.GetGameManager()->GetTimer();

	m_nTimer -= nTime;

	manager.GetGameManager()->SetTimer(m_nTimer);
}

