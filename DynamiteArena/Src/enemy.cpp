//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(enemy.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "enemy.h"
#include "player.h"
#include "explosion.h"
#include "block.h"
#include "wall.h"
#include "bullet.h"
#include "score.h"
#include <stdio.h>

//*******************************************************************************************************************************************
// �R���X�g���N�^
//*******************************************************************************************************************************************
CEnemy::CEnemy(int nPriority):CObjectX(nPriority)
{
	m_nLife = 0;								// �̗�
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	m_bHit = false;								// ��e�������ǂ���
	m_bHitObstacle = false;						// ��Q���ɓ����������ǂ���(�u���b�N���)
	m_bMoveRot = false;							// �i�s��������p�t���O
	m_bRot = true;								// ���[�V�����p�t���O
	m_nCnt = 0;
}

//*******************************************************************************************************************************************
// �f�X�g���N�^
//*******************************************************************************************************************************************
CEnemy::~CEnemy()
{
	m_nLife = 0;								// �̗�
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	m_bHit = false;								// ��e�������ǂ���
	m_bHitObstacle = false;						// ��Q���ɓ����������ǂ���(�u���b�N���)
	m_bMoveRot = false;							// �i�s��������p�t���O
	m_bRot = true;								// ���[�V�����p�t���O
	m_nCnt = 0;
}

//*******************************************************************************************************************************************
// ����������
//*******************************************************************************************************************************************
HRESULT CEnemy::Init()
{
	// X�t�@�C���I�u�W�F�N�g�̏���������
	CObjectX::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// �I������
//*******************************************************************************************************************************************
void CEnemy::Uninit()
{
	// X�t�@�C���I�u�W�F�N�g�̏I������
	CObjectX::Uninit();

	Release();	// ���f���̔j��
}

//*******************************************************************************************************************************************
// �X�V����
//*******************************************************************************************************************************************
void CEnemy::Update()
{
	if (m_nLife > 0)
	{// �G�������Ă���Ƃ�
		// X�t�@�C���I�u�W�F�N�g�̍X�V����
		CObjectX::Update();

		Move();	// �ړ�����
	}
	else
	{// �G�����񂾂Ƃ�
		if (m_nCnt > 0)
		{// ���S���o��
			m_nCnt--;

			SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		}
		else
		{// ���S���o�I����
			CScore::Add(KILL_POINT);	// �X�R�A���Z

			CEnemy::Uninit();	// �I������
		}
	}

}

//*******************************************************************************************************************************************
// �`�揈��
//*******************************************************************************************************************************************
void CEnemy::Draw()
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//*******************************************************************************************************************************************
// ��������
//*******************************************************************************************************************************************
CEnemy* CEnemy::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move)
{
	CEnemy* pEnemy = new CEnemy();

	pEnemy->Init();												// ����������

	pEnemy->BindFileName("data\\MODEL\\ENEMY\\enemy000.x");		// �ǂݍ��ރ��f���ݒ�

	pEnemy->SetModelSize();										// ���f���̒��_���ݒ�

	pEnemy->SetPos(pos);										// �ʒu�ݒ菈��

	pEnemy->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// �����ݒ菈��

	pEnemy->SetType(CObject::OBJECTTYPE::TYPE_ENEMY);			// ��ސݒ�

	pEnemy->m_nLife = 1;										// �̗͐ݒ�

	pEnemy->m_Move = move;										// �ړ��ʐݒ�

	return pEnemy;
}

//*******************************************************************************************************************************************
// �����蔻��(�G�Ƒ��̃I�u�W�F�N�g)
//*******************************************************************************************************************************************
bool CEnemy::CollisionEnemy(D3DXVECTOR3* pos, D3DXVECTOR3 size, int nType)
{
	bool bHit = false;		// �����������ǂ���
	D3DXVECTOR3 CurrentPos = GetPos();			// ���݂̈ʒu�擾
	D3DXVECTOR3 CurrentSize = GetModelSize();	// ���f���̑傫���擾

	switch (nType)
	{
	case CObject::OBJECTTYPE::TYPE_PLAYER:	// �G���v���C���[�ƂԂ������Ƃ�
		if (pos->z + size.z / 2 >= CurrentPos.z - CurrentSize.z / 2 &&	// �v���C���[�̉��ƓG�̎�O
			pos->z - size.z / 2 <= CurrentPos.z + CurrentSize.z / 2 &&	// �v���C���[�̎�O�ƓG�̉�
			pos->x - size.x / 2 <= CurrentPos.x + CurrentSize.x / 2 &&	// �v���C���[�̍��[�ƓG�̉E�[
			pos->x + size.x / 2 >= CurrentPos.x - CurrentSize.x / 2)	// �v���C���[�̉E�[�ƓG�̍��[
		{// �v���C���[�̋�`���G�̋�`�̒��ɂ��邩
			bHit = true;
		}
		break;
	case CObject::OBJECTTYPE::TYPE_ENEMY:	// �G���v���C���[�ƂԂ������Ƃ�
		if (pos->z + size.z / 2 >= CurrentPos.z - CurrentSize.z / 2 &&	// �v���C���[�̉��ƓG�̎�O
			pos->z - size.z / 2 <= CurrentPos.z + CurrentSize.z / 2 &&	// �v���C���[�̎�O�ƓG�̉�
			pos->x - size.x / 2 <= CurrentPos.x + CurrentSize.x / 2 &&	// �v���C���[�̍��[�ƓG�̉E�[
			pos->x + size.x / 2 >= CurrentPos.x - CurrentSize.x / 2)	// �v���C���[�̉E�[�ƓG�̍��[
		{// �v���C���[�̋�`���G�̋�`�̒��ɂ��邩
			bHit = true;
		}
		break;
	default:
		break;
	}
	return bHit;
}

//*******************************************************************************************************************************************
// ���[�h����
//*******************************************************************************************************************************************
void CEnemy::Load()
{
	FILE* pFile = nullptr;
	char aString[MAX_WORD] = {};
	char aSymbol[MAX_SYMBOL] = {};

	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	D3DXVECTOR3 Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ����x

	if (pFile == nullptr)
	{
		pFile = fopen("data\\TXT\\ENEMY\\EnemyManager.txt", "r");
	}

	if (pFile != nullptr)
	{
		while (1)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "END_SCRIPT") == 0)
			{
				fclose(pFile);
				break;
			}

			if (strcmp(&aString[0],"ENEMY_SET") == 0)
			{
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aSymbol[0], &Pos.x, &Pos.y, &Pos.z);
					}
					else if (strcmp(&aString[0], "MOVE") == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aSymbol[0], &Move.x, &Move.y, &Move.z);
					}

					if (strcmp(&aString[0], "END_ENEMYSET") == 0)
					{
						CEnemy::Create(Pos, Move);

						break;
					}
				}
			}
		}
	}
}

//*******************************************************************************************************************************************
// �ړ�����
//*******************************************************************************************************************************************
void CEnemy::Move()
{
	D3DXVECTOR3 CurrentPos = GetPos();			// ���̈ʒu�擾
	D3DXVECTOR3 CurrentPosOld = GetPosOld();	// 1�O�̈ʒu�擾
	D3DXVECTOR3 CurrentRot = GetRot();			// ���̌����擾
	D3DXVECTOR3 CurrentSize = GetModelSize();	// ���f���̑傫���擾
	bool bProcessedHit = false;					// �Փ˔���̏����ς݃t���O��ǉ�

	// ���[�J���ϐ��錾
	D3DXVECTOR3 AdjustMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ����x�ۑ��p
	float fLengthMove = 0.0f;								// �ړ���

	if (m_bMoveRot)
	{
		AdjustMove += m_Move;
	}
	else if (!m_bMoveRot)
	{
		AdjustMove -= m_Move;
	}

	fLengthMove = sqrtf(AdjustMove.x * AdjustMove.x + AdjustMove.z * AdjustMove.z);

	AdjustMove.x /= fLengthMove;
	AdjustMove.z /= fLengthMove;

	// �ړ��ʂ��X�P�[������ (�K�v�Ȃ瑬�x���|����)
	AdjustMove.x *= ENEMY_SPEED;
	AdjustMove.z *= ENEMY_SPEED;

	// �ʒu�̍X�V
	CurrentPos += AdjustMove;


	// ���[�V��������
	Motion(CurrentRot);

	// �����̍X�V
	if (AdjustMove.x != 0.0f || AdjustMove.z != 0.0f)
	{
		CurrentRot.y = atan2f(-AdjustMove.x, -AdjustMove.z);
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
				{// �I�u�W�F�N�g�̎�ނ��u���b�N�̎�
					CBlock* pBlock = (CBlock*)pObj;

					m_bHitObstacle = pBlock->CollisionBlock(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_ENEMY);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_NORMALWALL)
				{// �I�u�W�F�N�g�̎�ނ��ʏ�ǂ̎�
					CWall* pWall = (CWall*)pObj;

					m_bHitObstacle = pWall->CollisionWall(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_NORMALWALL, CObject::OBJECTTYPE::TYPE_ENEMY);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_SIDEWALL)
				{// �I�u�W�F�N�g�̎�ނ����ʕǂ̎�
					CWall* pWall = (CWall*)pObj;

					m_bHitObstacle = pWall->CollisionWall(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_SIDEWALL, CObject::OBJECTTYPE::TYPE_ENEMY);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_EXPLOSION)
				{// �I�u�W�F�N�g�̎�ނ������̎�
					CExplosion* pExplosion = (CExplosion*)pObj;

					m_bHit = pExplosion->CollisionExplosion(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_ENEMY);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_BULLET)
				{// �I�u�W�F�N�g�̎�ނ��e�̎�
					CBullet* pBullet = (CBullet*)pObj;

					m_bHitObstacle = pBullet->CollisionBullet(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_ENEMY);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_ENEMY)
				{
					CEnemy* pOtherEnemy = (CEnemy*)pObj;

					if (pOtherEnemy != this)
					{
						m_bHitObstacle = pOtherEnemy->CollisionEnemy(&CurrentPos, CurrentSize, CObject::OBJECTTYPE::TYPE_ENEMY);
					}
				}

				// �Փ˂������ς݂łȂ��ꍇ�̂݃t���O��؂�ւ���
				if (m_bHitObstacle && !bProcessedHit)
				{
					m_bMoveRot = !m_bMoveRot; // �t���O��؂�ւ�
					bProcessedHit = true;    // �����ς݂ɐݒ�
				}

				if (m_bHit)
				{
					m_nLife--;	// �̗͂����炷
					Death(DEATH_COUNT);
				}
			}
		}

	}


	SetPos(CurrentPos);
	SetRot(CurrentRot);
}

//*******************************************************************************************************************************************
// ���S����
//*******************************************************************************************************************************************
void CEnemy::Death(int nCnt)
{
	m_nCnt = nCnt;
}

//*******************************************************************************************************************************************
// ���[�V��������
//*******************************************************************************************************************************************
void CEnemy::Motion(D3DXVECTOR3 &rot)
{
	if (rot.z <= -ENEMY_MOTIONROT)
	{
		m_bRot = false;
	}
	else if (rot.z >= ENEMY_MOTIONROT)
	{
		m_bRot = true;
	}

	if (m_bRot)
	{
		rot.z -= ENEMY_MOTIONSPEED;
	}
	else if (!m_bRot)
	{
		rot.z += ENEMY_MOTIONSPEED;
	}

}
