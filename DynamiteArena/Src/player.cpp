//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(player.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "player.h"
#include "manager.h"
#include "bullet.h"
#include "camera.h"
#include "block.h"
#include "goal.h"
#include "explosion.h"
#include "wall.h"
#include "enemy.h"
#include <cmath>
#include "item.h"
#include "PlayerParam.h"

//*******************************************************************************************************************************************
// �R���X�g���N�^
//*******************************************************************************************************************************************
CPlayer::CPlayer(int nPriority):CObjectX(nPriority)
{
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
	
	m_InputKeyboard = nullptr;				// �L�[�{�[�h�̃|�C���^
	m_InputJoypad = nullptr;
	m_pCamera = nullptr;					// �J�����̃|�C���^
	m_pParamManager = nullptr;				// �p�����[�^�Ǘ��N���X�̃|�C���^

	m_bHit = false;							// �����������ǂ���(�v���C���[�ƕ�)
	m_bDamage = false;						// �����������ǂ���(�v���C���[�Ɣ��e)
	m_bDeath = false;						// �����������ǂ���(�v���C���[�ƓG)
	m_bGoal = false;						// �����������ǂ���(�v���C���[�ƃS�[���}�[�J�[)

	m_nCoolCount = 0;						// �N�[���_�E���J�E���g�p
	m_bHasFired = false;					// �ŏ��̒e���ǂ���
	m_nLife = 0;
	m_fShake = SHAKE_FRAME;					// �J������h�炷����

	m_bRot = true;
}

//*******************************************************************************************************************************************
// �f�X�g���N�^
//*******************************************************************************************************************************************
CPlayer::~CPlayer()
{
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���

	m_InputKeyboard = nullptr;				// �L�[�{�[�h�̃|�C���^
	m_InputJoypad = nullptr;
	m_pCamera = nullptr;					// �J�����̃|�C���^
	m_pParamManager = nullptr;				// �p�����[�^�Ǘ��N���X�̃|�C���^

	m_bHit = false;							// �����������ǂ���(�v���C���[�ƕ�)
	m_bDamage = false;						// �����������ǂ���(�v���C���[�Ɣ��e)
	m_bDeath = false;						// �����������ǂ���(�v���C���[�ƓG)
	m_bGoal = false;						// �����������ǂ���(�v���C���[�ƃS�[���}�[�J�[)

	m_nCoolCount = 0;						// �N�[���_�E���J�E���g�p
	m_bHasFired = false;					// �ŏ��̒e���ǂ���
	m_nLife = 0;
	m_fShake = SHAKE_FRAME;					// �J������h�炷����

}

//*******************************************************************************************************************************************
// ����������
//*******************************************************************************************************************************************
HRESULT CPlayer::Init()
{
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	m_InputKeyboard = manager.GetKeyboard();	// �L�[�{�[�h�̏��

	m_InputJoypad = manager.GetJoypad();		// �W���C�p�b�h�̏��
	
	m_pCamera = manager.GetCamera();			// �J�����̃|�C���^

	m_pParamManager = manager.GetParamManager();

	// X�t�@�C���I�u�W�F�N�g�̏���������
	CObjectX::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// �I������
//*******************************************************************************************************************************************
void CPlayer::Uninit()
{
	// X�t�@�C���I�u�W�F�N�g�̏I������
	CObjectX::Uninit();

	// �v���C���[�̔j��
	Release();

}

//*******************************************************************************************************************************************
// �X�V����
//*******************************************************************************************************************************************
void CPlayer::Update()
{
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();

	if (m_nLife > 0)
	{// �̗͂�����Ƃ�
		if (!m_bGoal)
		{
			// �ړ�����
			Move();

			// �U������
			Attack();

			if (m_bDamage)
			{
				m_nLife = 0;
			}

			if (m_bDeath)
			{
				m_nLife = 0;
			}

		}
		else
		{
			// �S�[�����o�̍X�V
			if (m_nCnt > 0)
			{
				D3DXVECTOR3 CurrentPos = GetPos();
				D3DXVECTOR3 CurrentRot = GetRot();

				CurrentPos.y += 1.0f;	// ��������y���W����������
				CurrentRot.y -= 0.3f;	// ��������]

				SetPos(CurrentPos);
				SetRot(CurrentRot);

				m_nCnt--; // �J�E���g�_�E��
			}
			else
			{
				manager.SetGoal(true);
			}
		}

		
	}
	else
	{// �̗͂��Ȃ��Ƃ�
		if (m_nDeathCnt > 0)
		{
			m_nDeathCnt--;	// �J�E���g�_�E��

			SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f,0.8f));	// �}�e���A���̐F�ύX
		}
		else
		{
			CPlayer::Uninit();

			manager.SetMode(CScene::MODE::MODE_FAILRESULT);
		}

	}

}

//*******************************************************************************************************************************************
// �`�揈��
//*******************************************************************************************************************************************
void CPlayer::Draw()
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//*******************************************************************************************************************************************
// ��������
//*******************************************************************************************************************************************
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer* pPlayer = new CPlayer();

	pPlayer->Init();											// ����������

	pPlayer->SetPos(pos);										// �ʒu�ݒ�

	pPlayer->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// �����ݒ�

	pPlayer->BindFileName("data\\MODEL\\PLAYER\\player000.x");	// �ǂݍ��ރ��f���ݒ�

	pPlayer->SetModelSize();									// ���f���̒��_���ݒ�

	pPlayer->SetType(CObject::OBJECTTYPE::TYPE_PLAYER);			// ���f���̎�ސݒ�

	pPlayer->m_nLife = 1;										// �v���C���[�̗̑�
	
	return nullptr;
}

//*******************************************************************************************************************************************
// �ړ�����
//*******************************************************************************************************************************************
void CPlayer::Move()
{
	//*******************************************************************************************
	// TPS���_�̃v���C���[�ړ�
	//*******************************************************************************************

	// ���[�J���ϐ��錾
	D3DXVECTOR3 CurrentPos = GetPos();						// �v���C���[�̌��݂̈ʒu
	D3DXVECTOR3 CurrentRot = GetRot();						// �v���C���[�̌��݂̌���
	// �v���C���[��1�O�̈ʒu�̎擾
	D3DXVECTOR3 CurrentPosOld = GetPosOld();

	// �v���C���[���f���̑傫���̎擾
	D3DXVECTOR3 CurrentSize = GetModelSize();

	D3DXVECTOR3 AdjustMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ��ʒ���
	D3DXVECTOR3 CameraRot = m_pCamera->GetRot();			// �J�����̌���

	float fCurrentSpeed = m_pParamManager->GetSpeed();

	float fLengthMove = 0.0f;								// �v���C���[�̈ړ����x

	//**************************************
	// �W���C�X�e�B�b�N�̈ړ�
	//**************************************
	m_Move.x += m_InputJoypad->GetLeftThumbX();
	m_Move.z += m_InputJoypad->GetLeftThumbY();

	// �ړ��ʂ̌v�Z
	if (m_Move.x != 0.0f || m_Move.z != 0.0f)
	{
		//CurrentRot.x = 0.0f;
		//CurrentRot.z = 0.0f;

		// �J�����̌�������Ɉړ��ʂ𒲐�
		float sinYaw = sinf(CameraRot.y);
		float cosYaw = cosf(CameraRot.y);

		// �J������ł̈ړ��x�N�g���̕ϊ�
		AdjustMove.x = m_Move.z * sinYaw + m_Move.x * cosYaw;
		AdjustMove.z = m_Move.z * cosYaw - m_Move.x * sinYaw;

		// �Ίp���̒������Z�o�����K��
		fLengthMove = sqrtf(AdjustMove.x * AdjustMove.x + AdjustMove.z * AdjustMove.z);
		AdjustMove.x /= fLengthMove;
		AdjustMove.z /= fLengthMove;

		// �ړ��ʂ��X�P�[������ (�K�v�Ȃ瑬�x���|����)
		AdjustMove.x *= fCurrentSpeed;
		AdjustMove.z *= fCurrentSpeed;

		// �ʒu�̍X�V
		CurrentPos += AdjustMove;

		// �����̍X�V (TPS���_�ł͈ړ������Ƀv���C���[�������ꍇ������)
		if (AdjustMove.x != 0.0f || AdjustMove.z != 0.0f)
		{
			CurrentRot.y = atan2f(-AdjustMove.x, -AdjustMove.z);
		}

		// �ړ��ʂ̃��Z�b�g
		m_Move.x = 0.0f;
		m_Move.z = 0.0f;
	}
	
	//Motion(CurrentRot);

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

					m_bHit = pBlock->CollisionBlock(&CurrentPos, &CurrentPosOld, CurrentSize,CObject::OBJECTTYPE::TYPE_PLAYER);

					if (m_bHit)
					{
						break;		// �㏑��h��
					}
				}
				else if (type == CObject::OBJECTTYPE::TYPE_GOAL)
				{
					CGoal* pGoal = (CGoal*)pObj;

					m_bGoal = pGoal->CollisionGoal(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_PLAYER);
				
					if (m_bGoal)
					{
						break;	// �㏑��h��
					}
				}
				else if (type == CObject::OBJECTTYPE::TYPE_EXPLOSION)
				{
					CExplosion* pExplosion = (CExplosion*)pObj;

					m_bDamage = pExplosion->CollisionExplosion(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_PLAYER);
				
					if (m_bDamage)
					{
						break;	// �㏑��h��
					}
				}
				else if (type == CObject::OBJECTTYPE::TYPE_BULLET)
				{
					CBullet* pBullet = (CBullet*)pObj;

					pBullet->CollisionBullet(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_PLAYER);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_NORMALWALL)
				{
					CWall* pWall = (CWall*)pObj;

					pWall->CollisionWall(&CurrentPos, &CurrentPosOld, CurrentSize,CObject::OBJECTTYPE::TYPE_NORMALWALL ,CObject::OBJECTTYPE::TYPE_PLAYER);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_SIDEWALL)
				{
					CWall* pWall = (CWall*)pObj;

					pWall->CollisionWall(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_SIDEWALL, CObject::OBJECTTYPE::TYPE_PLAYER);
				}
				else if (type == CObject::OBJECTTYPE::TYPE_ENEMY)
				{
					CEnemy* pEnemy = (CEnemy*)pObj;

					m_bDeath = pEnemy->CollisionEnemy(&CurrentPos, CurrentSize, CObject::OBJECTTYPE::TYPE_PLAYER);
				
					if (m_bDeath)
					{
						break;
					}
				}
				else if (type == CObject::OBJECTTYPE::TYPE_ITEM)
				{
					CItem* pItem = (CItem*)pObj;

					m_bHit = pItem->CollisionItem(&CurrentPos, CurrentSize, CObject::OBJECTTYPE::TYPE_PLAYER);

				}
			}
		}
	}

	m_pCamera->FollowCamera(CurrentPos);	// �J�����Ǐ]
	
	if (m_bDamage || m_bDeath)
	{// �_���[�W���o���Ԑݒ�
		Damage(DAMAGE_TIME);
	}

	if (m_bGoal)
	{// �S�[�����o���Ԑݒ�
		GoalParformance(GOAL_TIME);
	}

	SetPos(CurrentPos);		// �ʒu�̐ݒ�
	SetRot(CurrentRot);		// �����̐ݒ�
}

//*******************************************************************************************************************************************
// �U������
//*******************************************************************************************************************************************
void CPlayer::Attack()
{
	D3DXVECTOR3 CurrentPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 CurrentRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CurrentPos = GetPos();
	CurrentRot = GetRot();

	if (m_bHasFired)
	{// ���e�ȊO�J�E���g�����Z
		// �N�[���_�E���p�J�E���g�����Z
		m_nCoolCount++;
	}

	if (!m_bHasFired || m_nCoolCount >= COOLDOWN)
	{// �N�[���_�E�����Ԃ��o�߂�����
		if (m_InputJoypad->GetTrigger(CInputJoypad::JOYKEY_B))
		{// SPACE(�U��)�L�[�������ꂽ
			CBullet::Create(D3DXVECTOR3(CurrentPos.x,1.0f,CurrentPos.z), D3DXVECTOR3(sinf(CurrentRot.y + D3DX_PI) * 5.0f, 0.0f, cosf(CurrentRot.y + D3DX_PI) * 5.0f));
		
			m_nCoolCount = 0;

			m_bHasFired = true;
		}

	}
}

//*******************************************************************************************************************************************
// ��e����
//*******************************************************************************************************************************************
void CPlayer::Damage(int nCnt)
{
	m_nDeathCnt = nCnt;		// ���o���Ԃ�ݒ�
}

//*******************************************************************************************************************************************
// �S�[�����o����
//*******************************************************************************************************************************************
void CPlayer::GoalParformance(int nCnt)
{
	m_nCnt = nCnt;			// ���o���Ԃ�ݒ�
}

//*******************************************************************************************************************************************
// ���[�V��������
//*******************************************************************************************************************************************
void CPlayer::Motion(D3DXVECTOR3 &rot)
{
	if (rot.z <= -MAX_MOTIONROT)
	{
		m_bRot = false;
	}
	else if (rot.z >= MAX_MOTIONROT)
	{
		m_bRot = true;
	}

	if (m_bRot)
	{
		rot.z -= MOTION_SPEED;
	}
	else if (!m_bRot)
	{
		rot.z += MOTION_SPEED;
	}
}

