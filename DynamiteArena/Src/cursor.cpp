//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(cursor.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "cursor.h"

//*******************************************************************************************************************************************
// �R���X�g���N�^
//*******************************************************************************************************************************************
CCursor::CCursor(int nPriority):CObject2D(nPriority)
{
	m_pTexture = nullptr;		// �e�N�X�`���̃|�C���^
	m_nSelect = 0;				// �I�����i�[�p
	m_bCursorMove = false;		// �J�[�\���𓮂����Ă��邩�ǂ���
	m_InputKeyboard = nullptr;	// �L�[�{�[�h�̃|�C���^
	m_InputJoypad = nullptr;	// �W���C�p�b�h�̃|�C���^
	m_bScale = true;			// �|���S���̊g�k�p�t���O(true�̎��ɑ傫������)
}

//*******************************************************************************************************************************************
// �f�X�g���N�^
//*******************************************************************************************************************************************
CCursor::~CCursor()
{
	m_pTexture = nullptr;		// �e�N�X�`���̃|�C���^
	m_nSelect = 0;				// �I�����i�[�p
	m_bCursorMove = false;		// �J�[�\���𓮂����Ă��邩�ǂ���
	m_InputKeyboard = nullptr;	// �L�[�{�[�h�̃|�C���^
	m_InputJoypad = nullptr;	// �W���C�p�b�h�̃|�C���^
	m_bScale = true;			// �|���S���̊g�k�p�t���O(true�̎��ɑ傫������)
}

//*******************************************************************************************************************************************
// ����������
//*******************************************************************************************************************************************
HRESULT CCursor::Init()
{
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	m_InputKeyboard = manager.GetKeyboard();

	m_InputJoypad = manager.GetJoypad();

	m_nSelect = 1;
	
	// 2D�I�u�W�F�N�g�̏���������
	CObject2D::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// �I������
//*******************************************************************************************************************************************
void CCursor::Uninit()
{
	// 2D�I�u�W�F�N�g�̏I������
	CObject2D::Uninit();

	Release();
}

//*******************************************************************************************************************************************
// �X�V����
//*******************************************************************************************************************************************
void CCursor::Update()
{
	// 2D�I�u�W�F�N�g�̍X�V����
	CObject2D::Update();

	// �I������
	Select();

}

//*******************************************************************************************************************************************
// �`�揈��
//*******************************************************************************************************************************************
void CCursor::Draw()
{
	// 2D�I�u�W�F�N�g�̕`�揈��
	CObject2D::Draw();
}

//*******************************************************************************************************************************************
// ��������
//*******************************************************************************************************************************************
CCursor* CCursor::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	CCursor* pCursor = new CCursor();

	pCursor->Init();	// ����������

	pCursor->SetObject2D(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fWidth, fHeight);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(manager.GetRenderer()->GetDevice(), "data\\TEXTURE\\cursor000.png", &pCursor->m_pTexture);

	pCursor->BindTexture(pCursor->m_pTexture);

	return pCursor;
}

//*******************************************************************************************************************************************
// �I������
//*******************************************************************************************************************************************
void CCursor::Select()
{
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	D3DXVECTOR3 CurrentPos = GetPos();	// �ʒu�擾
	float CurrentWidth = GetWidth();	// ���擾
	float CurrentHeight = GetHeight();	// �����擾

	if (!m_InputKeyboard->GetPress(DIK_UP) && !m_InputKeyboard->GetPress(DIK_DOWN) || m_InputJoypad->GetPress(CInputJoypad::JOYKEY_UP) || m_InputJoypad->GetPress(CInputJoypad::JOYKEY_DOWN))
	{
		m_bCursorMove = false;
	}

	if (m_InputKeyboard->GetPress(DIK_UP) || m_InputKeyboard->GetPress(DIK_DOWN) || m_InputJoypad->GetRepeat(CInputJoypad::JOYKEY_UP) || m_InputJoypad->GetRepeat(CInputJoypad::JOYKEY_DOWN))
	{
		m_bCursorMove = true;
	}


	if (!m_bCursorMove)
	{// �J�[�\���������Ă��Ȃ��Ƃ�
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

	// ��ʑJ�ڏ���
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
