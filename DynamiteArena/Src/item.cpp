//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(item.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "item.h"
#include "manager.h"
#include "explosion.h"
#include "block.h"
#include <stdio.h>

// �ÓI�����o�ϐ�������
LPDIRECT3DTEXTURE9 CItem::m_pTexture = nullptr;	// �e�N�X�`��

//*******************************************************************************************************************************************
// �R���X�g���N�^
//*******************************************************************************************************************************************
CItem::CItem(int nPriority):CObject3D(nPriority)
{
	m_Type = TYPE_NONE;
	m_fWidth = 0.0f;	// ��
	m_fDepth = 0.0f;	// ���s

	m_bHit = false;		// �����������ǂ���
	m_bDeath = false;	// �g�p����Ă��邩�ǂ���
}

//*******************************************************************************************************************************************
// �f�X�g���N�^
//*******************************************************************************************************************************************
CItem::~CItem()
{

}

//*******************************************************************************************************************************************
// ����������
//*******************************************************************************************************************************************
HRESULT CItem::Init()
{
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();


	// 3D�I�u�W�F�N�g�̏���������
	CObject3D::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// �I������
//*******************************************************************************************************************************************
void CItem::Uninit()
{
	// 3D�I�u�W�F�N�g�̏I������
	CObject3D::Uninit();

	// �A�C�e���̔j��
	Release();
}

//*******************************************************************************************************************************************
// �X�V����
//*******************************************************************************************************************************************
void CItem::Update()
{
	D3DXVECTOR3 CurrentPos = GetPos();

	if (!m_bDeath)
	{
		// 3D�I�u�W�F�N�g�̍X�V����
		CObject3D::Update();

		for (int nCntPriority = 0; nCntPriority < DRAW_PRIORITY; nCntPriority++)
		{
			for (int nCntObj = 0; nCntObj < MAX_OBJECT3D; nCntObj++)
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

						m_bHit = pExplosion->CollisionExplosion(&CurrentPos, &CurrentPos, D3DXVECTOR3(m_fWidth, 0.0f, m_fDepth), CObject::OBJECTTYPE::TYPE_ITEM);
					}

				}

			}
		}
	}

	if (m_bHit)
	{
		m_bDeath = true;
	}

	if (m_bDeath)
	{
		CItem::Uninit();
	}
}

//*******************************************************************************************************************************************
// �`�揈��
//*******************************************************************************************************************************************
void CItem::Draw()
{
	// 3D�I�u�W�F�N�g�̕`�揈��
	CObject3D::Draw();
}

//*******************************************************************************************************************************************
// ��������
//*******************************************************************************************************************************************
CItem* CItem::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth,int nType)
{
	CItem* pItem = new CItem();
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	pItem->Init();

	switch (nType)
	{
	case 1:
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(manager.GetRenderer()->GetDevice(), "data\\TEXTURE\\powerup000.png", &pItem->m_pTexture);
		pItem->m_Type = TYPE_POWERUP;
		break;
	case 2:
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(manager.GetRenderer()->GetDevice(), "data\\TEXTURE\\speedup000.png", &pItem->m_pTexture);
		pItem->m_Type = TYPE_SPEEDUP;
		break;
	case 3:
		//pItem->BindTexture();
		pItem->m_Type = TYPE_ENEMYKILL;
		break;
	}

	pItem->BindTexture(m_pTexture);

	pItem->SetObject3D(pos, fWidth, fHeight, fDepth);

	pItem->m_fWidth = fWidth;	// �ϐ��Ɋi�[

	pItem->m_fDepth = fDepth;	// �ϐ��Ɋi�[

	pItem->SetType(CObject::OBJECTTYPE::TYPE_ITEM);

	return pItem;
}

//*******************************************************************************************************************************************
// ��������
//*******************************************************************************************************************************************
bool CItem::CollisionItem(D3DXVECTOR3* pos, D3DXVECTOR3 size, int nType)
{
	bool bHit = false;
	D3DXVECTOR3 CurrentPos = GetPos();	// �A�C�e���̈ʒu
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	m_pParamManager = nullptr;

	m_pParamManager = manager.GetParamManager();
	switch (nType)
	{
	case CObject::OBJECTTYPE::TYPE_PLAYER:	// �A�C�e���Ƀv���C���[���Ԃ����Ă����Ƃ�
		if (pos->z + size.z / 2 >= CurrentPos.z - m_fDepth &&
			pos->z - size.z / 2 <= CurrentPos.z + m_fDepth &&
			pos->x + size.x / 2 >= CurrentPos.x - m_fWidth &&
			pos->x - size.x / 2 <= CurrentPos.x + m_fWidth)
		{
			m_bHit = true;

			bHit = true;

			switch (m_Type)
			{
			case TYPE_POWERUP:
				m_pParamManager->AddParam(600, TYPE_POWERUP);	// ��������10�b
				break;
			case TYPE_SPEEDUP:
				m_pParamManager->AddParam(300, TYPE_SPEEDUP);	// ��������5�b
				break;
			case TYPE_ENEMYKILL:
				// ���ꏈ���������ɒǉ��\
				break;
			}
		}
		break;
	}

	return bHit;
}

int CItem::GetItemType()
{
	return m_Type;
}

//*******************************************************************************************************************************************
// ���[�h����
//*******************************************************************************************************************************************
void CItem::Load()
{
	FILE* pFile = nullptr;								// �t�@�C���|�C���^
	char aString[128] = {};								// �ǂݍ��񂾂��̕ۑ��p
	char aSymbol[4] = {};								// �C�R�[���ȂǕۑ��p
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu�ۑ��p

	int nType = 0;										// ��ޕۑ��p

	pFile = fopen("data\\TXT\\ITEM\\ItemManager.txt", "r");

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
			
			if (strcmp(&aString[0], "ITEM_SET") == 0)
			{
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{
						fscanf(pFile, "%s %f %f %f",&aSymbol[0], &Pos.x, &Pos.y, &Pos.z);
					}
					else if (strcmp(&aString[0], "TYPE") == 0)
					{
						fscanf(pFile, "%s %d", &aSymbol[0],&nType);
					}

					if (strcmp(&aString[0], "END_ITEMSET") == 0)
					{
						CItem::Create(Pos, ITEM_WIDTH, ITEM_HEIGHT, ITEM_DEPTH, nType);

						break;
					}
				}
			}

		}
	}
}

