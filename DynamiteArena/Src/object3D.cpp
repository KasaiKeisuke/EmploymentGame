//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(object3D.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "object3D.h"
#include "manager.h"

// �ÓI�����o�ϐ�������
CObject3D* CObject3D::m_apObject3D[MAX_OBJECT3D] = {};

//*******************************************************************************************************************************************
// �R���X�g���N�^
//*******************************************************************************************************************************************
CObject3D::CObject3D(int nPriority):CObject(nPriority)
{
	m_pDevice = nullptr;					// �f�o�C�X�̃|�C���^
	m_pVtxBuff = nullptr;					// ���_�o�b�t�@�̃|�C���^
	m_pTexture = nullptr;					// �e�N�X�`���̃|�C���^
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	m_mtxWorld = {};						// ���[���h�}�g���b�N�X
	m_fWidth = 0.0f;						// ��
	m_fHeight = 0.0f;						// ����
	m_fDepth = 0.0f;						// ���s

}

//*******************************************************************************************************************************************
// �f�X�g���N�^
//*******************************************************************************************************************************************
CObject3D::~CObject3D()
{
	m_pDevice = nullptr;					// �f�o�C�X�̃|�C���^
	m_pVtxBuff = nullptr;					// ���_�o�b�t�@�̃|�C���^
	m_pTexture = nullptr;					// �e�N�X�`���̃|�C���^
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_mtxWorld = {};						// ���[���h�}�g���b�N�X
	m_fWidth = 0.0f;						// ��
	m_fHeight = 0.0f;						// ����
	m_fDepth = 0.0f;						// ���s

}

//*******************************************************************************************************************************************
// ����������
//*******************************************************************************************************************************************
HRESULT CObject3D::Init()
{
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	m_pDevice = manager.GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*******************************************************************************************************************************************
// �I������
//*******************************************************************************************************************************************
void CObject3D::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Release();
}

//*******************************************************************************************************************************************
// �X�V����
//*******************************************************************************************************************************************
void CObject3D::Update()
{
	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f - m_fWidth, 0.0f, 0.0f + m_fDepth);
	pVtx[1].pos = D3DXVECTOR3(0.0f + m_fWidth, 0.0f, 0.0f + m_fDepth);
	pVtx[2].pos = D3DXVECTOR3(0.0f - m_fWidth, 0.0f, 0.0f - m_fDepth);
	pVtx[3].pos = D3DXVECTOR3(0.0f + m_fWidth, 0.0f, 0.0f - m_fDepth);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//*******************************************************************************************************************************************
// �`�揈��
//*******************************************************************************************************************************************
void CObject3D::Draw()
{
	// ���[�J���ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	m_pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX_3D);

	if (m_pTexture != nullptr)
	{
		// �e�N�X�`���̐ݒ�
		m_pDevice->SetTexture(0, m_pTexture);
	}

	// �|���S���̕`��
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


}

//*******************************************************************************************************************************************
// ��������
//*******************************************************************************************************************************************
CObject3D* CObject3D::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth)
{
	for (int nCnt = 0; nCnt < MAX_OBJECT3D; nCnt++)
	{
		if (m_apObject3D[nCnt] == nullptr)
		{
			m_apObject3D[nCnt] = new CObject3D;

			m_apObject3D[nCnt]->Init();

			m_apObject3D[nCnt]->SetObject3D(pos, fWidth, fHeight, fDepth);

			return m_apObject3D[nCnt];
		}
	}
	return nullptr;
}

//*******************************************************************************************************************************************
// �e�N�X�`���ݒ菈��
//*******************************************************************************************************************************************
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//*******************************************************************************************************************************************
// ���ݒ菈��
//*******************************************************************************************************************************************
void CObject3D::SetObject3D(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth)
{
	m_Pos = pos;			// �ʒu
	m_fWidth = fWidth;		// ��
	m_fHeight = fHeight;	// ����
	m_fDepth = fDepth;		// ���s
}

//*******************************************************************************************************************************************
// �ʒu�ݒ菈��
//*******************************************************************************************************************************************
void CObject3D::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//*******************************************************************************************************************************************
// �ʒu�擾����
//*******************************************************************************************************************************************
D3DXVECTOR3 CObject3D::GetPos()
{
	return m_Pos;
}

//*******************************************************************************************************************************************
// �����ݒ菈��
//*******************************************************************************************************************************************
void CObject3D::SetRot(D3DXVECTOR3 rot)
{
	m_Rot = rot;
}

//*******************************************************************************************************************************************
// �����擾����
//*******************************************************************************************************************************************
D3DXVECTOR3 CObject3D::GetRot()
{
	return m_Rot;
}

//*******************************************************************************************************************************************
// �e�̕`�揈��
//*******************************************************************************************************************************************
void CObject3D::DrawShadow()
{
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���Z�����̐ݒ�
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	m_pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX_3D);

	if (m_pTexture != nullptr)
	{
		// �e�N�X�`���̐ݒ�
		m_pDevice->SetTexture(0, m_pTexture);
	}

	// �|���S���̕`��
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �ʏ�̍����ɖ߂�
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

