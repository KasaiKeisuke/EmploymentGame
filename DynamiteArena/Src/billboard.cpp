//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(billboard.cpp)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "billboard.h"
#include "manager.h"

// �ÓI�����o�ϐ�������
CBillboard* CBillboard::m_apBillboard[MAX_BILLBOARD] = {};

//*******************************************************************************************************************************************
// �R���X�g���N�^
//*******************************************************************************************************************************************
CBillboard::CBillboard(int nPriority):CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pDevice = nullptr;
	m_mtxWorld = {};

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_fLength = 0.0f;
	m_Type = TYPE_NONE;
	m_nAnimFrame = 0;
	m_nAnimCount = 0;
}

//*******************************************************************************************************************************************
// �f�X�g���N�^
//*******************************************************************************************************************************************
CBillboard::~CBillboard()
{

}

//*******************************************************************************************************************************************
// ����������
//*******************************************************************************************************************************************
HRESULT CBillboard::Init()
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

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	// �e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*******************************************************************************************************************************************
// �I������
//*******************************************************************************************************************************************
void CBillboard::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//*******************************************************************************************************************************************
// �X�V����
//*******************************************************************************************************************************************
void CBillboard::Update()
{
	m_PosOld = m_Pos;	// �ʒu�̕ۑ�

	// ���_���̍X�V
	SetVtx(m_Type);
}

//*******************************************************************************************************************************************
// �`�揈��
//*******************************************************************************************************************************************
void CBillboard::Draw()
{
	// ���[�J���ϐ��錾
	D3DXMATRIX mtxTrans, mtxViex;

	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �r���[�}�g���b�N�X���擾
	m_pDevice->GetTransform(D3DTS_VIEW, &mtxViex);

	// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxViex);

	// �t�s������߂�
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	// �ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���C�g�𖳌��ɂ���
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̐ݒ�
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	m_pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	m_pDevice->SetTexture(0, m_pTexture);

	// �r���{�[�h�̕`��
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ���C�g��L���ɖ߂�
	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//*******************************************************************************************************************************************
// ��������
//*******************************************************************************************************************************************
CBillboard* CBillboard::Create()
{
	for (int nCntBillborad = 0; nCntBillborad < MAX_BILLBOARD; nCntBillborad++)
	{
		if (m_apBillboard[nCntBillborad] == nullptr)
		{
			m_apBillboard[nCntBillborad] = new CBillboard();

			m_apBillboard[nCntBillborad]->Init();

			return m_apBillboard[nCntBillborad];
		}
	}
	return nullptr;
}

//*******************************************************************************************************************************************
// �r���{�[�h���ݒ菈��
//*******************************************************************************************************************************************
void CBillboard::SetBillboard(D3DXVECTOR3 pos, float fWidth, float fHeight, int nDivision, BILLBOARDTYPE type)
{
	m_Pos = pos;						// �ʒu
	m_fWidth = fWidth;					// ��
	m_fHeight = fHeight;				// ����
	m_nTexDivision = nDivision;			// �e�N�X�`��������
	m_Type = type;						// ���
}

//*******************************************************************************************************************************************
// ���_���ݒ菈��
//*******************************************************************************************************************************************
void CBillboard::SetVtx(BILLBOARDTYPE type)
{
	int CurrentCount = GetAnimCount();

	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �Ίp���̒��������߂�
	m_fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight);

	// ���_���̐ݒ�
	pVtx[0].pos.x = -m_fLength;
	pVtx[0].pos.y = m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_fLength;
	pVtx[1].pos.y = m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -m_fLength;
	pVtx[2].pos.y = -m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_fLength;
	pVtx[3].pos.y = -m_fLength;
	pVtx[3].pos.z = 0.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[1].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[2].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[3].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / m_nTexDivision, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / m_nTexDivision, 1.0f);

	switch (type)
	{
	case CBillboard::BILLBOARDTYPE::TYPE_BULLET:


		break;
	case CBillboard::BILLBOARDTYPE::TYPE_EXPLOSION:

		m_nAnimFrame++;

		if (m_nAnimFrame % 6 == 0)
		{
			pVtx[0].tex.x += 0.125f;
			pVtx[1].tex.x += 0.125f;
			pVtx[2].tex.x += 0.125f;
			pVtx[3].tex.x += 0.125f;

			CurrentCount++;

		}
		SetAnimCount(CurrentCount);

		break;

	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//*******************************************************************************************************************************************
// �e�N�X�`���ݒ菈��
//*******************************************************************************************************************************************
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//*******************************************************************************************************************************************
// �ʒu�ݒ菈��
//*******************************************************************************************************************************************
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//*******************************************************************************************************************************************
// �ʒu�擾����
//*******************************************************************************************************************************************
D3DXVECTOR3 CBillboard::GetPos()
{
	return m_Pos;
}

//*******************************************************************************************************************************************
// �F�ݒ菈��
//*******************************************************************************************************************************************
void CBillboard::SetColor(D3DXCOLOR col)
{
	m_Col = col;
}

//*******************************************************************************************************************************************
// �F�擾����
//*******************************************************************************************************************************************
D3DXCOLOR CBillboard::GetColor()
{
	return m_Col;
}

//*******************************************************************************************************************************************
// �ʒu�擾����
//*******************************************************************************************************************************************
void CBillboard::SetAnimCount(int nCnt)
{
	m_nAnimCount = nCnt;
}

//*******************************************************************************************************************************************
// �A�j���[�V�����������񐔎擾����
//*******************************************************************************************************************************************
int CBillboard::GetAnimCount()
{
	return m_nAnimCount;
}
