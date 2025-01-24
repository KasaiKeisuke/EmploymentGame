//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(explosion.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "explosion.h"
#include "manager.h"

// �ÓI�����o�ϐ�������
char CExplosion::m_pFiletemp[FILE_PATH] = {};

//*******************************************************************************************************************************************
// �R���X�g���N�^
//*******************************************************************************************************************************************
CExplosion::CExplosion(int nPriority):CObjectX(nPriority),
m_nCnt(0)
{
	m_bScale = true;	// �g�k�p�t���O
	m_nLag = 0;			// �g�k��؂�ւ���܂ł̎���
}

//*******************************************************************************************************************************************
// �f�X�g���N�^
//*******************************************************************************************************************************************
CExplosion::~CExplosion()
{

}

//*******************************************************************************************************************************************
// ����������
//*******************************************************************************************************************************************
HRESULT CExplosion::Init()
{
	// X�t�@�C���I�u�W�F�N�g�̏���������
	CObjectX::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// �I������
//*******************************************************************************************************************************************
void CExplosion::Uninit()
{
	// X�t�@�C���I�u�W�F�N�g�̏I������
	CObjectX::Uninit();

	// �������f���̔j��
	Release();
}

//*******************************************************************************************************************************************
// �X�V����
//*******************************************************************************************************************************************
void CExplosion::Update()
{
	m_nCnt--;

	if (m_nCnt <= 0)
	{
		CExplosion::Uninit();
	}
	else
	{
		// �����̃��[�V����
		Motion();

		// ��]
		//Turn();

		// X�t�@�C���I�u�W�F�N�g�̍X�V����
		CObjectX::Update();

	}

}

//*******************************************************************************************************************************************
// �`�揈��
//*******************************************************************************************************************************************
void CExplosion::Draw()
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//*******************************************************************************************************************************************
// ��������
//*******************************************************************************************************************************************
CExplosion* CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion* pExplosion = new CExplosion();

	pExplosion->Init();

	pExplosion->SetPos(pos);

	pExplosion->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	if (m_pFiletemp != NULL)
	{
		pExplosion->BindFileName(m_pFiletemp);

	}

	pExplosion->SetModelSize();

	pExplosion->SetType(CObject::OBJECTTYPE::TYPE_EXPLOSION);

	pExplosion->m_nCnt = DRAW_COUNT;

	return pExplosion;
}

//*******************************************************************************************************************************************
// X�t�@�C�����[�h
//*******************************************************************************************************************************************
HRESULT CExplosion::Load()
{
	const char FilePath[FILE_PATH] = "data\\MODEL\\EXPLOSION\\explosion000.x";

	//if (m_pFiletemp == NULL)
	//{
		strcpy(&m_pFiletemp[0], &FilePath[0]);

	//}
	return S_OK;
}

//*******************************************************************************************************************************************
// X�t�@�C���A�����[�h
//*******************************************************************************************************************************************
void CExplosion::UnLoad()
{

}

//*******************************************************************************************************************************************
// �����蔻��
//*******************************************************************************************************************************************
bool CExplosion::CollisionExplosion(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size, int nType)
{
	// �����̏ڍ׏��擾
	D3DXVECTOR3 CurrentPos = GetPos();
	D3DXVECTOR3 CurrentMinVtx = GetMinVtx();
	D3DXVECTOR3 CurrentMaxVtx = GetMaxVtx();
	D3DXVECTOR3 CurrentSize = GetModelSize();

	bool bHit = false;	// �����������ǂ���

	switch (nType)
	{
	case CObject::OBJECTTYPE::TYPE_PLAYER:	// �v���C���[�Ɣ����̓����蔻��
		if (pos->z + size.z / 2 >= CurrentPos.z - CurrentSize.z / 2 &&	// �v���C���[�̉��Ɣ����̎�O
			pos->z - size.z / 2 <= CurrentPos.z + CurrentSize.z / 2 &&	// �v���C���[�̎�O�Ɣ����̉�
			pos->x - size.x / 2 <= CurrentPos.x + CurrentSize.x / 2 &&	// �v���C���[�̍��[�Ɣ����̉E�[
			pos->x + size.x / 2 >= CurrentPos.x - CurrentSize.x / 2)	// �v���C���[�̉E�[�Ɣ����̍��[
		{// �v���C���[�̋�`�������̋�`�̒��ɂ��邩
			bHit = true;
		}

		break;
	case CObject::OBJECTTYPE::TYPE_BLOCK:	// �u���b�N�Ɣ����̓����蔻��
		if (pos->z + size.z / 2 > CurrentPos.z - CurrentSize.z / 2 &&	// �u���b�N�̉��Ɣ����̎�O
			pos->z - size.z / 2 < CurrentPos.z + CurrentSize.z / 2 &&	// �u���b�N�̎�O�Ɣ����̉�
			pos->x - size.x / 2 < CurrentPos.x + CurrentSize.x / 2 &&	// �u���b�N�̍��[�Ɣ����̉E�[
			pos->x + size.x / 2 > CurrentPos.x - CurrentSize.x / 2)	// �u���b�N�̉E�[�Ɣ����̍��[
		{// �u���b�N�̋�`�������̋�`�̒��ɂ��邩
			bHit = true;
		}
		break;
	case CObject::OBJECTTYPE::TYPE_ENEMY:
		if (pos->z + size.z / 2 >= CurrentPos.z - CurrentSize.z / 2 &&	// �G�̉��Ɣ����̎�O
			pos->z - size.z / 2 <= CurrentPos.z + CurrentSize.z / 2 &&	// �G�̎�O�Ɣ����̉�
			pos->x - size.x / 2 <= CurrentPos.x + CurrentSize.x / 2 &&	// �G�̍��[�Ɣ����̉E�[
			pos->x + size.x / 2 >= CurrentPos.x - CurrentSize.x / 2)	// �G�̉E�[�Ɣ����̍��[
		{// �G�̋�`�������̋�`�̒��ɂ��邩
			bHit = true;
		}
		break;
	case CObject::OBJECTTYPE::TYPE_ITEM:
		if (pos->z + size.z / 2 >= CurrentPos.z - CurrentSize.z / 2 &&	// �A�C�e���̉��Ɣ����̎�O
			pos->z - size.z / 2 <= CurrentPos.z + CurrentSize.z / 2 &&	// �A�C�e���̎�O�Ɣ����̉�
			pos->x - size.x / 2 <= CurrentPos.x + CurrentSize.x / 2 &&	// �A�C�e���̍��[�Ɣ����̉E�[
			pos->x + size.x / 2 >= CurrentPos.x - CurrentSize.x / 2)	// �A�C�e���̉E�[�Ɣ����̍��[
		{// �A�C�e���̋�`�������̋�`�̒��ɂ��邩
			bHit = true;
		}
		break;
	}

	return bHit;
}

//*******************************************************************************************************************************************
// ��]����
//*******************************************************************************************************************************************
void CExplosion::Turn()
{
	D3DXVECTOR3 CurrentRot = GetRot();

	CurrentRot.y += 0.1f;

	SetRot(CurrentRot);
}

//*******************************************************************************************************************************************
// ���[�V��������
//*******************************************************************************************************************************************
void CExplosion::Motion()
{
	D3DXVECTOR3 CurrentScale = GetScale();

	if (CurrentScale.x && CurrentScale.y && CurrentScale.z >= MAX_SCALE)
	{
		CurrentScale = D3DXVECTOR3(MAX_SCALE, MAX_SCALE, MAX_SCALE);	// �ő�܂ő傫��������Œ肷��
		m_nLag++;

		if (m_nLag >= TIME_LAG)
		{// �ő�X�P�[���ɂȂ��Ă����莞�Ԍo�ߌ�t���O��؂�ւ���
			m_bScale = false;
		}
	}

	if (m_bScale)
	{// �傫������
		CurrentScale.x += ANIM_SPEEDFAST;
		CurrentScale.y += ANIM_SPEEDFAST;
		CurrentScale.z += ANIM_SPEEDFAST;
	}
	else if (!m_bScale)
	{// ����������
		m_nLag = 0;
		CurrentScale.x -= ANIM_SPEEDLATE;
		CurrentScale.y -= ANIM_SPEEDLATE;
		CurrentScale.z -= ANIM_SPEEDLATE;
	}

	SetScale(CurrentScale);

}
