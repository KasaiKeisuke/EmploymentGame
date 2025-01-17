//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(bullet.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include 
#include "bullet.h"
#include "manager.h"
#include "caveat.h"
#include "block.h"
#include "wall.h"

//*******************************************************************************************************************************************
// �R���X�g���N�^
//*******************************************************************************************************************************************
CBullet::CBullet(int nPriority):CObjectX(nPriority),
m_Move(D3DXVECTOR3(0.0f,0.0f,0.0f)),
m_fGravity(9.8f),
m_fInitialYSpeed(3.0f),
m_bDeath(false),
m_bHitObstacle(false),
m_nLag(0)
{
	m_pParamManager = nullptr;	// �p�����[�^�[�Ǘ��N���X�̃|�C���^
	m_bScale = true;			// �g�k�p�X�P�[��(true�̎��ɑ傫������)
}

//*******************************************************************************************************************************************
// �f�X�g���N�^
//*******************************************************************************************************************************************
CBullet::~CBullet()
{

}

//*******************************************************************************************************************************************
// ����������
//*******************************************************************************************************************************************
HRESULT CBullet::Init()
{
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	m_pParamManager = manager.GetParamManager();

	// X�t�@�C���I�u�W�F�N�g�̏���������
	CObjectX::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// �I������
//*******************************************************************************************************************************************
void CBullet::Uninit()
{
	// X�t�@�C���I�u�W�F�N�g�̏I������
	CObjectX::Uninit();

	Release();
}

//*******************************************************************************************************************************************
// �X�V����
//*******************************************************************************************************************************************
void CBullet::Update()
{
	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();

	// �e�̈ړ�
	Move();

}

//*******************************************************************************************************************************************
// �`�揈��
//*******************************************************************************************************************************************
void CBullet::Draw()
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//*******************************************************************************************************************************************
// ��������
//*******************************************************************************************************************************************
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBullet* pBullet = new CBullet();

	pBullet->Init();

	// X�t�@�C���̐ݒ�
	pBullet->BindFileName("data\\MODEL\\BULLET\\bomb000.x");

	pBullet->SetModelSize();

	pBullet->SetPos(pos);

	pBullet->SetRot(D3DXVECTOR3(0.0f,D3DX_PI * 0.5f,0.0f));

	//**********************************************
	// �R�Ȃ�̏ꍇ
	//**********************************************
	pBullet->m_Move = move;
	pBullet->m_Move.y = pBullet->m_fInitialYSpeed;	// Y�������̂ݏ����x���ʂŐݒ�

	pBullet->m_nNotCollision = 20;					// ���e��u���Ă����莞�ԓ����蔻�肪�@�\���Ȃ�����
	
	pBullet->SetType(CObject::OBJECTTYPE::TYPE_BULLET);

	return pBullet;
}

//*******************************************************************************************************************************************
// �ړ�����
//*******************************************************************************************************************************************
void CBullet::Move()
{
	// ���݂̈ʒu�̎擾
	D3DXVECTOR3 CurrentPos = GetPos();

	// �e��1�O�̈ʒu�̎擾
	D3DXVECTOR3 CurrentPosOld = GetPosOld();

	// �e���f���̑傫���̎擾
	D3DXVECTOR3 CurrentSize = GetModelSize();

	// �d�͂��l������Y���̑��x�v�Z
	m_Move.y += -m_fGravity * 0.016f;	// 0.016�̓t���[���Ԃ̎���(60fps�O��)

	// �n�ʂɓ��B�����ꍇ�AY���̈ʒu�Ƒ��x�����Z�b�g
	if (CurrentPos.y <= 8.0f)
	{
		CurrentPos.y = 5.0f;	// �n�ʂ̍���
		m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		m_nLag++;

		if (m_nLag == UI_TIMING)
		{
			Death();				// ���S����
		}
		
		if (m_nLag >= DELETE_BULLET)
		{
			CBullet::Uninit();		// �I������
		}
		else if (m_nLag < DELETE_BULLET)
		{// �e���\������Ă����
			Motion();
		}

	}
	else
	{
		// ���ꂼ��̎��̈ړ�
		CurrentPos.x += m_Move.x;
		CurrentPos.y += m_Move.y;
		CurrentPos.z += m_Move.z;

	}

	for (int nCntPriority = 0; nCntPriority < DRAW_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECTX; nCntObj++)
		{
			// �I�u�W�F�N�g���擾
			CObject* pObj = nullptr;

			pObj = CObject::GetObjectInfo(nCntPriority, nCntObj);

			if (pObj != nullptr)
			{
				// ��ނ̎擾
				CObject::OBJECTTYPE type = pObj->GetType();

				if (type == CObject::OBJECTTYPE::TYPE_BLOCK)
				{
					CBlock* pBlock = (CBlock*)pObj;

					m_bHitObstacle = pBlock->CollisionBlock(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_BULLET);

				}
			}
		}
	}


	SetPos(CurrentPos);
}

//*******************************************************************************************************************************************
// �x���\��UI�o������
//*******************************************************************************************************************************************
void CBullet::Death()
{	
	D3DXVECTOR3 CurrentPos = GetPos();	// �e�̈ʒu���擾
	int CurrentPower = m_pParamManager->GetPower();	// ���e�̔����͂̎擾

	CCaveat::Create(D3DXVECTOR3(CurrentPos.x, 0.1f, CurrentPos.z), 10.0f, 0.0f, 10.0f);	// �e�̈ʒu�Ɍx���\����UI�𐶐�

	// �c�����Ɖ������̐����ʒu���X�g
	D3DXVECTOR3 frontPositions[NUM_EXPLOSION];
	D3DXVECTOR3 backPositions[NUM_EXPLOSION];
	D3DXVECTOR3 leftPositions[NUM_EXPLOSION];
	D3DXVECTOR3 rightPositions[NUM_EXPLOSION];

	// �������鋗���̊Ԋu
	const float Interval = CAVEAT_SPAN;

	// ��O�����̐����ʒu���X�g
	for (int i = 0; i < CurrentPower; ++i)
	{
		float offset = -(i + 1) * Interval;  // ��O�͊�ʒu����}�C�i�X����
		frontPositions[i] = D3DXVECTOR3(CurrentPos.x, 0.1f, CurrentPos.z + offset);
	}

	// �������̐����ʒu���X�g
	for (int i = 0; i < CurrentPower; ++i)
	{
		float offset = (i + 1) * Interval;  // ���͊�ʒu����v���X����
		backPositions[i] = D3DXVECTOR3(CurrentPos.x, 0.1f, CurrentPos.z + offset);
	}

	// �������̐����ʒu���X�g
	for (int i = 0; i < CurrentPower; ++i)
	{
		float offset = -(i + 1) * Interval;  // ���͊�ʒu����}�C�i�X����
		leftPositions[i] = D3DXVECTOR3(CurrentPos.x + offset, 0.1f, CurrentPos.z);
	}

	// �E�����̐����ʒu���X�g
	for (int i = 0; i < CurrentPower; ++i)
	{
		float offset = (i + 1) * Interval;  // �E�͊�ʒu����v���X����
		rightPositions[i] = D3DXVECTOR3(CurrentPos.x + offset, 0.1f, CurrentPos.z);
	}

	// ��O�����̌x��UI����
	for (int i = 0; i < CurrentPower; ++i)
	{
		if (IsBlockPos(frontPositions[i], Interval, Interval))
		{
			break;  // ��O�����Ƀu���b�N������Έȍ~�̐������~
		}
		else
		{
			CCaveat::Create(frontPositions[i], POLYGON_SIZE, 0.0f, POLYGON_SIZE);
		}
	}

	// �������̌x��UI����
	for (int i = 0; i < CurrentPower; ++i)
	{
		if (IsBlockPos(backPositions[i], Interval, Interval))
		{
			break;  // �������Ƀu���b�N������Έȍ~�̐������~
		}
		else
		{
			CCaveat::Create(backPositions[i], POLYGON_SIZE, 0.0f, POLYGON_SIZE);
		}
	}

	// �������̌x��UI����
	for (int i = 0; i < CurrentPower; ++i)
	{
		if (IsBlockPos(leftPositions[i], Interval, Interval))
		{
			break;  // �������Ƀu���b�N������Έȍ~�̐������~
		}
		else
		{
			CCaveat::Create(leftPositions[i], POLYGON_SIZE, 0.0f, POLYGON_SIZE);
		}
	}

	// �E�����̌x��UI����
	for (int i = 0; i < CurrentPower; ++i)
	{
		if (IsBlockPos(rightPositions[i], Interval, Interval))
		{
			break;  // �E�����Ƀu���b�N������Έȍ~�̐������~
		}
		else
		{
			CCaveat::Create(rightPositions[i], POLYGON_SIZE, 0.0f, POLYGON_SIZE);
		}
	}
}

//*******************************************************************************************************************************************
// ���[�V��������
//*******************************************************************************************************************************************
void CBullet::Motion()
{
	D3DXVECTOR3 CurrentScale = GetScale();

	if (CurrentScale.x && CurrentScale.y && CurrentScale.z <= MIN_BULLETSCALE)
	{
		m_bScale = true;
	}

	if (CurrentScale.x && CurrentScale.y && CurrentScale.z >= MAX_BULLETSCALE)
	{
		m_bScale = false;
	}

	if (m_nLag >= UI_TIMING)
	{// �������O�ɂȂ����烂�[�V�����̑��x�𑬂�����
		if (m_bScale)
		{
			CurrentScale.x += MOTION_SPEEDFAST;
			CurrentScale.y += MOTION_SPEEDFAST;
			CurrentScale.z += MOTION_SPEEDFAST;
		}
		else if (!m_bScale)
		{
			CurrentScale.x -= MOTION_SPEEDFAST;
			CurrentScale.y -= MOTION_SPEEDFAST;
			CurrentScale.z -= MOTION_SPEEDFAST;
		}

	}
	else
	{// ���e�u���Ă��炠�܂莞�Ԃ��o���Ă��Ȃ��Ƃ��̓��[�V�����̑��x��x������
		if (m_bScale)
		{
			CurrentScale.x += MOTION_SPEEDLATE;
			CurrentScale.y += MOTION_SPEEDLATE;
			CurrentScale.z += MOTION_SPEEDLATE;
		}
		else if (!m_bScale)
		{
			CurrentScale.x -= MOTION_SPEEDLATE;
			CurrentScale.y -= MOTION_SPEEDLATE;
			CurrentScale.z -= MOTION_SPEEDLATE;
		}

	}

	SetScale(CurrentScale);

}

//*******************************************************************************************************************************************
// �u���b�N�����邩�ǂ���
//*******************************************************************************************************************************************
bool CBullet::IsBlockPos(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	for (int nCntPriority = 0; nCntPriority < DRAW_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECTX; nCntObj++)
		{
			CObject* pObj = CObject::GetObjectInfo(nCntPriority, nCntObj);
			if (pObj != nullptr && pObj->GetType() == CObject::OBJECTTYPE::TYPE_BLOCK)
			{// �I�u�W�F�N�g�̎�ނ��u���b�N�Ȃ�
				CBlock* pBlock = (CBlock*)pObj;
				if (pBlock->GetType() == CBlock::BLOCKTYPE::TYPE_NOTBREAK)
				{// �󂹂Ȃ��u���b�N�Ȃ�
					// �u���b�N�̈ʒu�ƃT�C�Y���擾���Ĕ���
					D3DXVECTOR3 blockPos = pBlock->GetPos();
					D3DXVECTOR3 blockSize = pBlock->GetModelSize();
					// �����ʒu���u���b�N�Əd�Ȃ��Ă��邩���m�F
					if (pos.x + fWidth / 2 >= blockPos.x - blockSize.x / 2 &&
						pos.x - fWidth / 2 <= blockPos.x + blockSize.x / 2 &&
						pos.z + fDepth / 2 >= blockPos.z - blockSize.z / 2 &&
						pos.z - fDepth / 2 <= blockPos.z + blockSize.z / 2)
					{
						return true;  // �u���b�N������
					}

				}
				else if (pBlock->GetType() == CBlock::BLOCKTYPE::TYPE_BREAK)
				{
					// �u���b�N�̈ʒu�ƃT�C�Y���擾���Ĕ���
					D3DXVECTOR3 blockPos = pBlock->GetPos();
					D3DXVECTOR3 blockSize = pBlock->GetModelSize();
					// �����ʒu���u���b�N�Əd�Ȃ��Ă��邩���m�F
					if (pos.x + fWidth / 2 >= blockPos.x - blockSize.x / 2 &&
						pos.x - fWidth / 2 <= blockPos.x + blockSize.x / 2 &&
						pos.z + fDepth / 2 >= blockPos.z - blockSize.z / 2 &&
						pos.z - fDepth / 2 <= blockPos.z + blockSize.z / 2)
					{
						CCaveat::Create(pos, POLYGON_SIZE, 0.0f, POLYGON_SIZE);

						return true;  // �u���b�N������
					}

				}
			}

			if (pObj != nullptr)
			{
				if (pObj->GetType() == CObject::OBJECTTYPE::TYPE_NORMALWALL)
				{// �ʏ��
					CWall* pWall = (CWall*)pObj;
					// �ǂ̈ʒu�ƃT�C�Y���擾
					D3DXVECTOR3 WallPos = pWall->GetPos();
					D3DXVECTOR3 WallSize = pWall->GetModelSize();

					// �����ʒu���ǂƏd�Ȃ��Ă����琶�����Ȃ�
					if (pos.x + fWidth / 2 >= WallPos.x - WallSize.x / 2 &&
						pos.x - fWidth / 2 <= WallPos.x + WallSize.x / 2 &&
						pos.z + fDepth / 2 >= WallPos.z - WallSize.z / 2 &&
						pos.z - fDepth / 2 <= WallPos.z + WallSize.z / 2)
					{
						return true;
					}
				}
				else if (pObj->GetType() == CObject::OBJECTTYPE::TYPE_SIDEWALL)
				{// ���ʕ�
					CWall* pWall = (CWall*)pObj;
					// �ǂ̈ʒu�ƃT�C�Y���擾
					D3DXVECTOR3 WallPos = pWall->GetPos();
					D3DXVECTOR3 WallSize = pWall->GetModelSize();

					// �����ʒu���ǂƏd�Ȃ��Ă����琶�����Ȃ�
					if (pos.x + fWidth / 2 >= WallPos.x - WallSize.x / 2 &&
						pos.x - fWidth / 2 <= WallPos.x + WallSize.x / 2 &&
						pos.z + fDepth / 2 >= WallPos.z - WallSize.z / 2 &&
						pos.z - fDepth / 2 <= WallPos.z + WallSize.z / 2)
					{
						return true;
					}

				}
			}
		}
	}
	return false;  // �u���b�N���Ȃ�
}

//*******************************************************************************************************************************************
// �����蔻��
//*******************************************************************************************************************************************
bool CBullet::CollisionBullet(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size, int nType)
{
	D3DXVECTOR3 CurrentPos = GetPos();
	D3DXVECTOR3 CurrentMinVtx = GetMinVtx();
	D3DXVECTOR3 CurrentMaxVtx = GetMaxVtx();

	bool bHit = false;	// �����������ǂ���

	m_nNotCollision--;	// �J�E���g�����炷

	if (m_nNotCollision <= 0)
	{
		switch (nType)
		{
		case CObject::OBJECTTYPE::TYPE_PLAYER:
			if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x)
			{// �e�̍����Ƀv���C���[�����������Ƃ�
				pos->x = CurrentPos.x + CurrentMinVtx.x - size.x / 2;
				bHit = true;
			}

			if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
				pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x)
			{// �e�̉E���Ƀv���C���[�����������Ƃ�
				pos->x = CurrentPos.x + CurrentMaxVtx.x + size.x / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x  &&
				posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z)
			{// �e�̉����Ƀv���C���[�����������Ƃ�
				pos->z = CurrentPos.z + CurrentMaxVtx.z + size.z / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x  &&
				posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z)
			{// �e�̎�O���Ƀv���C���[�����������Ƃ�
				pos->z = CurrentPos.z + CurrentMinVtx.z - size.z / 2;
				bHit = true;
			}
			break;
		case CObject::OBJECTTYPE::TYPE_ENEMY:	// �G���Ԃ����Ă����Ƃ�
			if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x)
			{// �e�̍����ɓG�����������Ƃ�
				//pos->x = CurrentPos.x + CurrentMinVtx.x - size.x / 2;
				bHit = true;
			}

			if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
				pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x)
			{// �e�̉E���ɓG�����������Ƃ�
				//pos->x = CurrentPos.x + CurrentMaxVtx.x + size.x / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z)
			{// �e�̉����ɓG�����������Ƃ�
				//pos->z = CurrentPos.z + CurrentMaxVtx.z + size.z / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z)
			{// �e�̎�O���ɓG�����������Ƃ�
				//pos->z = CurrentPos.z + CurrentMinVtx.z - size.z / 2;
				bHit = true;
			}
			break;

		}
	}
	return bHit;
}
