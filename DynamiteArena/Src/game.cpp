//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(game.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include 
//*************************************************
// System
//*************************************************
#include "manager.h"

//*************************************************
// Scene
//*************************************************
#include "game.h"

//*************************************************
// Object
//*************************************************
#include "bullet.h"
#include "explosion.h"
#include "player.h"
#include "caveat.h"
#include "block.h"
#include "field.h"
#include "goal.h"
#include "wall.h"
#include "item.h"
#include "enemy.h"

//*******************************************************************************************************************************************
// �R���X�g���N�^
//*******************************************************************************************************************************************
CGame::CGame()
{
	m_InputKeyboard = nullptr;	// �L�[�{�[�h�̃|�C���^
	m_InputJoypad = nullptr;	// �W���C�p�b�h�̃|�C���^
	m_pParamManager = nullptr;	// �p�����[�^�[�Ǘ��N���X�̃|�C���^
	m_pGameManager = nullptr;	// �Q�[���}�l�[�W���[�N���X�̃|�C���^
	m_nTime = 0;
}

//*******************************************************************************************************************************************
// �f�X�g���N�^
//*******************************************************************************************************************************************
CGame::~CGame()
{
	m_InputKeyboard = nullptr;	// �L�[�{�[�h�̃|�C���^
	m_InputJoypad = nullptr;	// �W���C�p�b�h�̃|�C���^
	m_pParamManager = nullptr;	// �p�����[�^�[�Ǘ��N���X�̃|�C���^
	m_pGameManager = nullptr;	// �Q�[���}�l�[�W���[�N���X�̃|�C���^
	m_nTime = 0;
}

//*******************************************************************************************************************************************
// ����������
//*******************************************************************************************************************************************
HRESULT CGame::Init()
{
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	m_InputKeyboard = manager.GetKeyboard();

	m_InputJoypad = manager.GetJoypad();

	m_pParamManager = manager.GetParamManager();

	m_pGameManager = manager.GetGameManager();

	// �x���\��Ui�̃e�N�X�`�����[�h
	CCaveat::Load();

	// ���̃e�N�X�`���̃��[�h
	CField::Load();

	// �����I�u�W�F�N�g�̃��[�h
	CExplosion::Load();
	
	// �u���b�N�̃��[�h����
	CBlock::Load();

	// �ǂ̃��[�h����
	CWall::Load();

	// �A�C�e���̃��[�h����
	CItem::Load();

	// �G�̃��[�h����
	CEnemy::Load();

	// �����̃e�N�X�`�����[�h
	CNumber::Load();

	// �p�����[�^�[�Ǘ��N���X�̏���������
	if (m_pParamManager != nullptr)
	{
		m_pParamManager->Init();
	}

	// �Q�[���}�l�[�W���[�N���X�̏���������
	if (m_pGameManager != nullptr)
	{
		m_pGameManager->Init();
	}

	// �v���C���[�̐���
	CPlayer::Create(D3DXVECTOR3(-180.0f, 12.0f, -150.0f));

	// ���̐���
	CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 0.0f, 170.0f);

	// �S�[���}�[�J�[�̐���
	CGoal::Create(D3DXVECTOR3(180.0f, 0.0f, 150.0f));

	//*****************************
	// �e�X�g�z�u
	//*****************************
	//CWall::Create(D3DXVECTOR3(-150.0f, 13.0f, 130.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);

	// �Q�[��2���ڈȍ~�J�����̌������o�O��Ȃ��悤�ɏ�����
	manager.GetCamera()->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �������Ԃ̐ݒ�
	m_nTime = 180;

	// �^�C�}�[�̐ݒ�
	m_pGameManager->SetTimer(m_nTime);

	// �^�C�}�[�̐���
	CTimer::Create();

	// �X�R�A�̐���
	CScore::Create();

	return S_OK;
}

//*******************************************************************************************************************************************
// �I������
//*******************************************************************************************************************************************
void CGame::Uninit()
{
	// ���̃e�N�X�`���̔j��
	CField::UnLoad();

	// �x���\��UI�e�N�X�`���j��
	CCaveat::UnLoad();

	// �V�[�����N���X�̏I������
	CScene::Uninit();

	// �p�����[�^�[�Ǘ��N���X�̏I������
	if (m_pParamManager != nullptr)
	{
		m_pParamManager->Uninit();
	}

	// �Q�[���}�l�[�W���[�N���X�̏I������
	if (m_pGameManager != nullptr)
	{
		m_pGameManager->Uninit();
	}
}

//*******************************************************************************************************************************************
// �X�V����
//*******************************************************************************************************************************************
void CGame::Update()
{
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	bool bGameClear = manager.GetGoal();

	int nTime = m_pGameManager->GetTimer();

	if (bGameClear)
	{
		manager.SetMode(CScene::MODE::MODE_CLEARRESULT);
	
		manager.SetGoal(false);	// �S�[��������t���O���Z�b�g
	}
	else
	{
		// �^�C�}�[�̍X�V
		m_nTime--;

		if (m_nTime % 60 == 0)
		{
			CTimer::Sub(1);
		}
	}

	//�p�����[�^�[�Ǘ��N���X�̍X�V����
	if (m_pParamManager != nullptr)
	{
		m_pParamManager->Update();
	}

	// �Q�[���}�l�[�W���[�N���X�̍X�V����
	if (m_pGameManager != nullptr)
	{
		m_pGameManager->Update();
	}


	if (nTime <= 0)
	{
		manager.SetMode(CScene::MODE::MODE_FAILRESULT);
	}
}

//*******************************************************************************************************************************************
// �`�揈��
//*******************************************************************************************************************************************
void CGame::Draw()
{

}