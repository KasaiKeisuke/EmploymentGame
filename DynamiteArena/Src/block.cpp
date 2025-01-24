//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(block.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "block.h"
#include "explosion.h"
#include "item.h"
#include "manager.h"
#include <stdio.h>
#include <random>

//*******************************************************************************************************************************************
// �R���X�g���N�^
//*******************************************************************************************************************************************
CBlock::CBlock(int nPriority):CObjectX(nPriority),
m_bDeath(false),
m_nLife(0)
{
	m_pItemManager = nullptr;	// �A�C�e���}�l�[�W���[�N���X�̃|�C���^
}

//*******************************************************************************************************************************************
// �f�X�g���N�^
//*******************************************************************************************************************************************
CBlock::~CBlock()
{
	m_bDeath = false;
	m_pItemManager = nullptr;	// �A�C�e���}�l�[�W���[�N���X�̃|�C���^
}

//*******************************************************************************************************************************************
// ����������
//*******************************************************************************************************************************************
HRESULT CBlock::Init()
{
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	m_pItemManager = manager.GetItemManager();

	// X�t�@�C���I�u�W�F�N�g�̏���������
	CObjectX::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// �I������
//*******************************************************************************************************************************************
void CBlock::Uninit()
{
	// X�t�@�C���I�u�W�F�N�g�̏I������
	CObjectX::Uninit();

	// �u���b�N�̔j��
	Release();
}

//*******************************************************************************************************************************************
// �X�V����
//*******************************************************************************************************************************************
void CBlock::Update()
{
	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();

	// ���݂̈ʒu�̎擾
	D3DXVECTOR3 CurrentPos = GetPos();

	// �e��1�O�̈ʒu�̎擾
	D3DXVECTOR3 CurrentPosOld = GetPosOld();

	// �e���f���̑傫���̎擾
	D3DXVECTOR3 CurrentSize = GetModelSize();

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

				if (type == CObject::OBJECTTYPE::TYPE_EXPLOSION)
				{
					CExplosion* pExplosion = (CExplosion*)pObj;

					m_bDeath = pExplosion->CollisionExplosion(&CurrentPos, &CurrentPosOld, CurrentSize, CObject::OBJECTTYPE::TYPE_BLOCK);

				}


				if (m_Type == CBlock::BLOCKTYPE::TYPE_BREAK)
				{
					if (m_bDeath)
					{
						DecideToPlaceItem(CurrentPos);	// �A�C�e����z�u���邩�ǂ���

						CBlock::Uninit();
					}
				}

			}
		}
	}

}

//*******************************************************************************************************************************************
// �`�揈��
//*******************************************************************************************************************************************
void CBlock::Draw()
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//*******************************************************************************************************************************************
// ��������
//*******************************************************************************************************************************************
CBlock* CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type)
{
	CBlock* pBlock = new CBlock();

	pBlock->Init();	// ����������

	pBlock->SetPos(pos);	// �ʒu�ݒ�

	pBlock->SetRot(rot);	// �����ݒ�

	pBlock->m_nLife = 1;	// �����ݒ�

	switch (type)
	{
	case 1:
		pBlock->BindFileName("data\\MODEL\\BLOCK\\block000.x");

		pBlock->SetBlockType(CBlock::BLOCKTYPE::TYPE_NOTBREAK);

		pBlock->m_Type = CBlock::BLOCKTYPE::TYPE_NOTBREAK;
		
		break;
	case 2:
		pBlock->BindFileName("data\\MODEL\\BLOCK\\block001.x");

		pBlock->SetBlockType(CBlock::BLOCKTYPE::TYPE_BREAK);

		pBlock->m_Type = CBlock::BLOCKTYPE::TYPE_BREAK;

		break;
	}
	
	pBlock->SetModelSize();

	pBlock->SetType(CObjectX::OBJECTTYPE::TYPE_BLOCK);		// �I�u�W�F�N�g�̎�ސݒ�

	return nullptr;
}

//*******************************************************************************************************************************************
// �����蔻��
//*******************************************************************************************************************************************
bool CBlock::CollisionBlock(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size, int nType)
{
	bool bHit = false;							// �����������ǂ���
	bool bDraw = false;							// UI���������ǂ���

	D3DXVECTOR3 CurrentPos = GetPos();			// �u���b�N�̍��W
	D3DXVECTOR3 CurrentMinVtx = GetMinVtx();	// �u���b�N�̒��_�̍ŏ��l
	D3DXVECTOR3 CurrentMaxVtx = GetMaxVtx();	// �u���b�N�̒��_�̍ő�l
	D3DXVECTOR3 CurrentSize = GetModelSize();	// ���f���̃T�C�Y�擾

	switch (nType)
	{
	case CObject::OBJECTTYPE::TYPE_PLAYER:	// �u���b�N�Ƀv���C���[���Ԃ����Ă����Ƃ�
		if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
			pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
			posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
			pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x)
		{// �u���b�N�̍����Ƀv���C���[�����������Ƃ�
			//pos->x = CurrentPos.x + CurrentMinVtx.x - size.x / 2;
			pos->x = CurrentPos.x - BLOCK_SIZE - PLAYER_SIZE / 2;
		}

		if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
			pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
			posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
			pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x)
		{// �u���b�N�̉E���Ƀv���C���[�����������Ƃ�
			//pos->x = CurrentPos.x + CurrentMaxVtx.x + size.x / 2;
			pos->x = CurrentPos.x + BLOCK_SIZE + PLAYER_SIZE / 2;
		}

		if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
			pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
			posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
			pos->z - size.z / 2 <= CurrentPos.z + CurrentMaxVtx.z)
		{// �u���b�N�̉����Ƀv���C���[�����������Ƃ�
			//pos->z = CurrentPos.z + CurrentMaxVtx.z + size.z / 2;
			pos->z = CurrentPos.z + BLOCK_SIZE + PLAYER_SIZE / 2;
		}

		if (pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x &&			
			pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x &&
			posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
			pos->z + size.z / 2 >= CurrentPos.z + CurrentMinVtx.z)
		{// �u���b�N�̎�O���Ƀv���C���[�����������Ƃ�
			//pos->z = CurrentPos.z + CurrentMinVtx.z - size.z / 2;
			pos->z = CurrentPos.z - BLOCK_SIZE - PLAYER_SIZE / 2;
		}
		break;
	case CObject::OBJECTTYPE::TYPE_BULLET:
		if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
			pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
			posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
			pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x)
		{// �u���b�N�̍����ɒe�����������Ƃ�
			pos->x = CurrentPos.x + CurrentMinVtx.x - size.x / 2;
			bHit = true;
		}

		if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
			pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
			posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
			pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x)
		{// �u���b�N�̉E���ɒe�����������Ƃ�
			pos->x = CurrentPos.x + CurrentMaxVtx.x + size.x / 2;
			bHit = true;
		}

		if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
			pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
			posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
			pos->z - size.z / 2 <= CurrentPos.z + CurrentMaxVtx.z)
		{// �u���b�N�̉����ɒe�����������Ƃ�
			pos->z = CurrentPos.z + CurrentMaxVtx.z + size.z / 2;
			bHit = true;
		}

		if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
			pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
			posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
			pos->z + size.z / 2 >= CurrentPos.z + CurrentMinVtx.z)
		{// �u���b�N�̎�O���ɒe�����������Ƃ�
			pos->z = CurrentPos.z + CurrentMinVtx.z - size.z / 2;
			bHit = true;
		}

		break;
	case CObject::OBJECTTYPE::TYPE_ENEMY:
		if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
			pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
			posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
			pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x)
		{// �u���b�N�̍����ɓG�����������Ƃ�
			//pos->x = CurrentPos.x + CurrentMinVtx.x - size.x / 2;
			bHit = true;
		}

		if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
			pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
			posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
			pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x)
		{// �u���b�N�̉E���ɓG�����������Ƃ�
			//pos->x = CurrentPos.x + CurrentMaxVtx.x + size.x / 2;
			bHit = true;
		}

		if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
			pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
			posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
			pos->z - size.z / 2 <= CurrentPos.z + CurrentMaxVtx.z)
		{// �u���b�N�̉����ɓG�����������Ƃ�
			//pos->z = CurrentPos.z + CurrentMaxVtx.z + size.z / 2;
			bHit = true;
		}

		if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
			pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
			posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
			pos->z + size.z / 2 >= CurrentPos.z + CurrentMinVtx.z)
		{// �u���b�N�̎�O���ɓG�����������Ƃ�
			//pos->z = CurrentPos.z + CurrentMinVtx.z - size.z / 2;
			bHit = true;
		}

		break;
	}

	return bHit;
}

//*******************************************************************************************************************************************
// ���[�h����
//*******************************************************************************************************************************************
void CBlock::Load()
{
	// ���[�J���ϐ��錾
	FILE* pFile = nullptr;	// �t�@�C���|�C���^
	char aString[128] = {};	// �ǂݍ��񂾂��̕ۑ��p
	char aSymbol[4] = {};	// �S�~�ۑ��p
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu�ۑ��p
	D3DXVECTOR3 Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����ۑ��p
	int nType = 0;										// ��ޕۑ��p

	pFile = fopen("data\\TXT\\BLOCK\\BlockManager.txt", "r");

	if (pFile != NULL)
	{
		while (1)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "END_SCRIPT") == 0)
			{
				fclose(pFile);
				break;
			}
			
			if (strcmp(&aString[0], "BLOCK_SET") == 0)
			{
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aSymbol[0], &Pos.x, &Pos.y, &Pos.z);
					}
					else if (strcmp(&aString[0], "ROT") == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aSymbol[0], &Rot.x, &Rot.y, &Rot.z);
					}
					else if (strcmp(&aString[0], "TYPE") == 0)
					{
						fscanf(pFile, "%s %d", &aSymbol[0], &nType);
					}


					if (strcmp(&aString[0], "END_BLOCKSET") == 0)
					{
						CBlock::Create(Pos, Rot, nType);
						break;
					}
				}
			}
			
		}
	}
}

//*******************************************************************************************************************************************
// �u���b�N��ސݒ�
//*******************************************************************************************************************************************
void CBlock::SetBlockType(BLOCKTYPE type)
{
	m_Type = type;
}

//*******************************************************************************************************************************************
// �u���b�N��ގ擾
//*******************************************************************************************************************************************
CBlock::BLOCKTYPE CBlock::GetType()
{
	return m_Type;
}

//*******************************************************************************************************************************************
// �A�C�e����z�u���邩�ǂ���
//*******************************************************************************************************************************************
void CBlock::DecideToPlaceItem(D3DXVECTOR3 pos)
{
	int nNumAppearItem = m_pItemManager->GetNumItem();	// �o���������A�C�e���̌��擾

	if (nNumAppearItem >= 8)
	{// �����o�������珈����ʂ��Ȃ�
		return;
	}

	std::random_device rnd;  // �񌈒�I�ȗ���������
	std::mt19937 mt(rnd());  // �����Z���k�c�C�X�^�[�̗���������
	std::uniform_int_distribution<> rand(1, 2);  // 1��2�̃����_��

	int nRand = rand(mt);

	if (nRand == 1)
	{
		nNumAppearItem++;

		// �A�C�e���̎�ނ�����
		std::uniform_int_distribution<> itemRand(1, ITEM_KIND);  // �A�C�e���̎�ނ̃����_��
		int nKind = itemRand(mt);  // �A�C�e���̎��

		// �A�C�e�����쐬
		CItem::Create(D3DXVECTOR3(pos.x, 0.1f, pos.z), ITEM_SIZE, 0.0f, ITEM_SIZE, nKind);

		m_pItemManager->SetNumItem(nNumAppearItem);
	}
}
