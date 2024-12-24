//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(wall.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "wall.h"
#include "object.h"

//*******************************************************************************************************************************************
// �R���X�g���N�^
//*******************************************************************************************************************************************
CWall::CWall(int nPriority):CObjectX(nPriority)
{

}

//*******************************************************************************************************************************************
// �f�X�g���N�^
//*******************************************************************************************************************************************
CWall::~CWall()
{

}

//*******************************************************************************************************************************************
// ����������
//*******************************************************************************************************************************************
HRESULT CWall::Init()
{
	// X�t�@�C���I�u�W�F�N�g�̏���������
	CObjectX::Init();

	return S_OK;
}

//*******************************************************************************************************************************************
// �I������
//*******************************************************************************************************************************************
void CWall::Uninit()
{
	// X�t�@�C���I�u�W�F�N�g�̏I������
	CObjectX::Uninit();

	// �ǂ̔j��
	Release();
}

//*******************************************************************************************************************************************
// �X�V����
//*******************************************************************************************************************************************
void CWall::Update()
{
	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();
}

//*******************************************************************************************************************************************
// �`�揈��
//*******************************************************************************************************************************************
void CWall::Draw()
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//*******************************************************************************************************************************************
// ��������
//*******************************************************************************************************************************************
CWall* CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	CWall* pWall = new CWall();

	pWall->Init();	// ����������

	pWall->SetPos(pos);	// �ʒu�ݒ�

	pWall->SetRot(rot);	// �����ݒ�

	switch (nType)
	{
	case 1:
		pWall->BindFileName("data\\MODEL\\WALL\\wall000.x");

		pWall->SetType(CObjectX::OBJECTTYPE::TYPE_NORMALWALL);		// �I�u�W�F�N�g�̎�ސݒ�
		break;
	case 2:
		pWall->BindFileName("data\\MODEL\\WALL\\wall001.x");

		pWall->SetType(CObjectX::OBJECTTYPE::TYPE_SIDEWALL);		// �I�u�W�F�N�g�̎�ސݒ�
		break;
	}

	pWall->SetModelSize();	// ���f���̑傫���ݒ�

	return nullptr;
}

//*******************************************************************************************************************************************
// �����蔻��
//*******************************************************************************************************************************************
bool CWall::CollisionWall(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size, int type, int nType)
{
	bool bHit = false;							// �����������ǂ���

	D3DXVECTOR3 CurrentPos = GetPos();			// �u���b�N�̍��W
	D3DXVECTOR3 CurrentMinVtx = GetMinVtx();	// �u���b�N�̒��_�̍ŏ��l
	D3DXVECTOR3 CurrentMaxVtx = GetMaxVtx();	// �u���b�N�̒��_�̍ő�l

	switch (type)
	{
	case CObject::OBJECTTYPE::TYPE_NORMALWALL:	// �ǂ̎�ނ��ʏ�ǂ̎�
		switch (nType)
		{
		case CObject::OBJECTTYPE::TYPE_PLAYER:	// �v���C���[���Ԃ����Ă����Ƃ�
			if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
				pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x)
			{// �ǂ̍����Ƀv���C���[�����������Ƃ�
				pos->x = CurrentPos.x - NORMALWALL_WIDTH - PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
				pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x)
			{// �ǂ̉E���Ƀv���C���[�����������Ƃ�
				pos->x = CurrentPos.x + NORMALWALL_WIDTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
				pos->z - size.z / 2 <= CurrentPos.z + CurrentMaxVtx.z)
			{// �ǂ̉����Ƀv���C���[�����������Ƃ�
				pos->z = CurrentPos.z + NORMALWALL_DEPTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
				pos->z + size.z / 2 >= CurrentPos.z + CurrentMinVtx.z)
			{// �ǂ̎�O���Ƀv���C���[�����������Ƃ�
				pos->z = CurrentPos.z - NORMALWALL_DEPTH - PLAYER_SIZE / 2;
				bHit = true;
			}

			break;
		case CObject::OBJECTTYPE::TYPE_ENEMY:	// �G���Ԃ����Ă����Ƃ�
			if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
				pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x)
			{// �ǂ̍����Ƀv���C���[�����������Ƃ�
				//pos->x = CurrentPos.x - NORMALWALL_WIDTH - PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
				pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x)
			{// �ǂ̉E���Ƀv���C���[�����������Ƃ�
				//pos->x = CurrentPos.x + NORMALWALL_WIDTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
				pos->z - size.z / 2 <= CurrentPos.z + CurrentMaxVtx.z)
			{// �ǂ̉����Ƀv���C���[�����������Ƃ�
				//pos->z = CurrentPos.z + NORMALWALL_DEPTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
				pos->z + size.z / 2 >= CurrentPos.z + CurrentMinVtx.z)
			{// �ǂ̎�O���Ƀv���C���[�����������Ƃ�
				//pos->z = CurrentPos.z - NORMALWALL_DEPTH - PLAYER_SIZE / 2;
				bHit = true;
			}

			break;

		}
		break;
	case CObject::OBJECTTYPE::TYPE_SIDEWALL:	// �ǂ̎�ނ����ʕǂ̎�
		switch (nType)
		{
		case CObject::OBJECTTYPE::TYPE_PLAYER:
			if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
				pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x)
			{// �ǂ̍����Ƀv���C���[�����������Ƃ�
				pos->x = CurrentPos.x - SIDEWALL_WIDTH - PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
				pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x)
			{// �ǂ̉E���Ƀv���C���[�����������Ƃ�
				pos->x = CurrentPos.x + SIDEWALL_WIDTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
				pos->z - size.z / 2 <= CurrentPos.z + CurrentMaxVtx.z)
			{// �ǂ̉����Ƀv���C���[�����������Ƃ�
				pos->z = CurrentPos.z + SIDEWALL_DEPTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
				pos->z + size.z / 2 >= CurrentPos.z + CurrentMinVtx.z)
			{// �ǂ̎�O���Ƀv���C���[�����������Ƃ�
				pos->z = CurrentPos.z - SIDEWALL_DEPTH - PLAYER_SIZE / 2;
				bHit = true;
			}


			break;
		case CObject::OBJECTTYPE::TYPE_ENEMY:	// �G���Ԃ����Ă����Ƃ�
			if (pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				posOld->x + size.x / 2 <= CurrentPos.x + CurrentMinVtx.x &&
				pos->x + size.x / 2 >= CurrentPos.x + CurrentMinVtx.x)
			{// �ǂ̍����Ƀv���C���[�����������Ƃ�
				//pos->x = CurrentPos.x - NORMALWALL_WIDTH - PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->z - size.z / 2 < CurrentPos.z + CurrentMaxVtx.z &&
				pos->z + size.z / 2 > CurrentPos.z + CurrentMinVtx.z &&
				posOld->x - size.x / 2 >= CurrentPos.x + CurrentMaxVtx.x &&
				pos->x - size.x / 2 <= CurrentPos.x + CurrentMaxVtx.x)
			{// �ǂ̉E���Ƀv���C���[�����������Ƃ�
				//pos->x = CurrentPos.x + NORMALWALL_WIDTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z - size.z / 2 >= CurrentPos.z + CurrentMaxVtx.z &&
				pos->z - size.z / 2 <= CurrentPos.z + CurrentMaxVtx.z)
			{// �ǂ̉����Ƀv���C���[�����������Ƃ�
				//pos->z = CurrentPos.z + NORMALWALL_DEPTH + PLAYER_SIZE / 2;
				bHit = true;
			}

			if (pos->x - size.x / 2 < CurrentPos.x + CurrentMaxVtx.x &&
				pos->x + size.x / 2 > CurrentPos.x + CurrentMinVtx.x &&
				posOld->z + size.z / 2 <= CurrentPos.z + CurrentMinVtx.z &&
				pos->z + size.z / 2 >= CurrentPos.z + CurrentMinVtx.z)
			{// �ǂ̎�O���Ƀv���C���[�����������Ƃ�
				//pos->z = CurrentPos.z - NORMALWALL_DEPTH - PLAYER_SIZE / 2;
				bHit = true;
			}

			break;

		}
		break;
	}
	return bHit;
}

//*******************************************************************************************************************************************
// ���[�h����
//*******************************************************************************************************************************************
void CWall::Load()
{
	// ���[�J���ϐ��錾
	FILE* pFile = nullptr;	// �t�@�C���|�C���^
	char aString[128] = {};	// �ǂݍ��񂾂��̕ۑ��p
	char aSymbol[4] = {};	// �S�~�ۑ��p
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu�ۑ��p
	D3DXVECTOR3 Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����ۑ��p
	int nType = 0;										// ��ޕۑ��p

	pFile = fopen("data\\TXT\\WALL\\WallManager.txt", "r");

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

			if (strcmp(&aString[0], "WALL_SET") == 0)
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


					if (strcmp(&aString[0], "END_WALLSET") == 0)
					{
						CWall::Create(Pos, Rot, nType);
						break;
					}
				}
			}

		}
	}

}
