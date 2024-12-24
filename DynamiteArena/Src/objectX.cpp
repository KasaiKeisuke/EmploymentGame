//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(objectX.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "objectX.h"
#include "manager.h"

// �ÓI�����o�ϐ�������
CObjectX* CObjectX::m_apObjectX[DRAW_PRIORITY][MAX_OBJECTX] = {};

//*******************************************************************************************************************************************
// �R���X�g���N�^
//*******************************************************************************************************************************************
CObjectX::CObjectX(int nPriority):CObject(nPriority)
{
	m_nNumVtx = 0;
	m_dwNumMat = 0;
	m_pBuffMat = NULL;
	m_pMesh = NULL;
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_pVtxBuffer = NULL;
	m_cFileName[0] = NULL;

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

//*******************************************************************************************************************************************
// �f�X�g���N�^
//*******************************************************************************************************************************************
CObjectX::~CObjectX()
{
	if (m_pTexture != nullptr)
	{// �e�N�X�`���̔j��
		for (DWORD i = 0; i < m_dwNumMat; i++)
		{
			m_pTexture[i]->Release();
		}
		delete[]m_pTexture;
		m_pTexture = nullptr;
	}

	m_nNumVtx = 0;
	m_dwNumMat = 0;
	m_pBuffMat = NULL;
	m_pMesh = NULL;
	m_pVtxBuff = nullptr;
	m_pVtxBuffer = NULL;
	m_cFileName[0] = NULL;

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//*******************************************************************************************************************************************
// ����������
//*******************************************************************************************************************************************
HRESULT CObjectX::Init()
{
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	m_pDevice = manager.GetRenderer()->GetDevice();

	return S_OK;
}

//*******************************************************************************************************************************************
// �I������
//*******************************************************************************************************************************************
void CObjectX::Uninit()
{
	// ���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// �}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	// �e�N�X�`���̉��
	if (m_pTexture != nullptr)
	{
		for (DWORD i = 0; i < m_dwNumMat; i++)
		{
			if (m_pTexture[i] != nullptr)
			{
				m_pTexture[i]->Release();
				m_pTexture[i] = nullptr;
			}
		}
		delete[] m_pTexture;
		m_pTexture = nullptr;
	}

}

//*******************************************************************************************************************************************
// �X�V����
//*******************************************************************************************************************************************
void CObjectX::Update()
{
	m_PosOld = m_Pos;	// �ʒu�̕ۑ�
}

//*******************************************************************************************************************************************
// �`�揈��
//*******************************************************************************************************************************************
void CObjectX::Draw()
{
	// ���[�J���ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans,mtxScale;		// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef = {};					// ���݂̃}�e���A��
	D3DXMATERIAL* pMat = nullptr;				// �}�e���A���̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �X�P�[����ݒ�
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �@���̐��K��
	m_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// ���[���h�}�g���b�N�X�̐ݒ�
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A���̎擾
	m_pDevice->GetMaterial(&matDef);

	//m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// �}�e���A���f�[�^�ւ̃|�C���^�擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		pMat[nCntMat].MatD3D.Diffuse = m_Diffuse[nCntMat];
		
		// �}�e���A���̐ݒ�
		m_pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		m_pDevice->SetTexture(0, m_pTexture[nCntMat]);

		// ���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �ۑ����Ă����}�e���A�������ɖ߂�
	m_pDevice->SetMaterial(&matDef);

	// �@�������ɖ߂�
	m_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

}

//*******************************************************************************************************************************************
// ��������
//*******************************************************************************************************************************************
CObjectX* CObjectX::Create()
{
	for (int nCntPriority = 0; nCntPriority < DRAW_PRIORITY; nCntPriority++)
	{
		for (int nCntObjectX = 0; nCntObjectX < MAX_OBJECTX; nCntObjectX++)
		{
			if (m_apObjectX[nCntPriority][nCntObjectX] == nullptr)
			{
				m_apObjectX[nCntPriority][nCntObjectX] = new CObjectX;

				m_apObjectX[nCntPriority][nCntObjectX]->Init();	// ����������

				return m_apObjectX[nCntPriority][nCntObjectX];
			}
		}
	}

	
	return nullptr;
}

//*******************************************************************************************************************************************
// �ʒu�ݒ菈��
//*******************************************************************************************************************************************
void CObjectX::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//*******************************************************************************************************************************************
// �ʒu�擾����
//*******************************************************************************************************************************************
D3DXVECTOR3 CObjectX::GetPos()
{
	return m_Pos;
}

//*******************************************************************************************************************************************
// �����ݒ菈��
//*******************************************************************************************************************************************
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_Rot = rot;
}

//*******************************************************************************************************************************************
// �����擾����
//*******************************************************************************************************************************************
D3DXVECTOR3 CObjectX::GetRot()
{
	return m_Rot;
}

//*******************************************************************************************************************************************
// �t�@�C���p�X�ݒ菈��
//*******************************************************************************************************************************************
void CObjectX::BindFileName(const char aPath[MAX_SENTENCE])
{
	strcpy(&m_cFileName[0], &aPath[0]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(m_cFileName,
		D3DXMESH_SYSTEMMEM,
		m_pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	// �}�e���A�����̎擾
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	m_pTexture = new LPDIRECT3DTEXTURE9[m_dwNumMat];

	for (DWORD i = 0; i < m_dwNumMat; i++)
	{
		m_pTexture[i] = nullptr;

		if (pMat[i].pTextureFilename)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(m_pDevice, pMat[i].pTextureFilename, &m_pTexture[i]);

		}

		m_FormalDiffuse[i] = pMat[i].MatD3D.Diffuse;
		m_Diffuse[i] = pMat[i].MatD3D.Diffuse;

	}

}

//*******************************************************************************************************************************************
// ���f���̑傫���ݒ菈��
//*******************************************************************************************************************************************
void CObjectX::SetModelSize()
{
	// ���_���̎擾
	m_nNumVtx = m_pMesh->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	m_sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// ���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuffer);

	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		// ���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuffer;

		// ���_���W���r���ă��f���̍ŏ��l�E�ő�l���擾
		if (vtx.x < m_MinVtx.x)
		{
			m_MinVtx.x = vtx.x;
		}
		else if (vtx.x > m_MaxVtx.x)
		{
			m_MaxVtx.x = vtx.x;
		}

		if (vtx.y < m_MinVtx.y)
		{
			m_MinVtx.y = vtx.y;
		}
		else if (vtx.y > m_MaxVtx.y)
		{
			m_MaxVtx.y = vtx.y;
		}

		if (vtx.z < m_MinVtx.z)
		{
			m_MinVtx.z = vtx.z;
		}
		else if (vtx.z > m_MaxVtx.z)
		{
			m_MaxVtx.z = vtx.z;
		}

		// ���f���̃T�C�Y�����߂�
		m_Size = m_MaxVtx - m_MinVtx;

		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		m_pVtxBuffer += m_sizeFVF;
	}

	// ���_�o�b�t�@�̃A�����b�N
	m_pMesh->UnlockVertexBuffer();
}

//*******************************************************************************************************************************************
// ���f���̑傫���擾����
//*******************************************************************************************************************************************
D3DXVECTOR3 CObjectX::GetModelSize()
{
	return m_Size;
}

//***********************************************************************************************************************
// ���f���̒��_�̍ŏ��l�擾����
//***********************************************************************************************************************
D3DXVECTOR3 CObjectX::GetMinVtx()
{
	return m_MinVtx;
}

//***********************************************************************************************************************
// ���f���̒��_�̍ő�l�擾����
//***********************************************************************************************************************
D3DXVECTOR3 CObjectX::GetMaxVtx()
{
	return m_MaxVtx;
}

//***********************************************************************************************************************
// �X�P�[���ݒ菈��
//***********************************************************************************************************************
void CObjectX::SetScale(D3DXVECTOR3 scale)
{
	m_Scale = scale;
}

//***********************************************************************************************************************
// �X�P�[���擾����
//***********************************************************************************************************************
D3DXVECTOR3 CObjectX::GetScale()
{
	return m_Scale;
}

//*******************************************************************************************************************************************
// �F�ݒ菈��
//*******************************************************************************************************************************************
void CObjectX::SetColor(D3DXCOLOR col)
{
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		m_Diffuse[nCntMat] = col;
	}
}

//***********************************************************************************************************************
// 1�O�̈ʒu�̎擾����
//***********************************************************************************************************************
D3DXVECTOR3 CObjectX::GetPosOld()
{
	return m_PosOld;
}

