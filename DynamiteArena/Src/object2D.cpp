//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(object2D.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

// include
#include "object2D.h"
#include "manager.h"

// �ÓI�����o�ϐ�������
CObject2D* CObject2D::m_apObject2D[MAX_OBJECT] = {};

//*******************************************************************************************************************************************
// �R���X�g���N�^
//*******************************************************************************************************************************************
CObject2D::CObject2D(int nPriority):CObject(nPriority)
{
	m_pDevice = nullptr;					// �f�o�C�X�̃|�C���^
	m_pVtxBuff = nullptr;					// ���_�o�b�t�@�̃|�C���^
	m_pTexture = nullptr;					// �e�N�X�`���̃|�C���^
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_fWidth = 0.0f;						// ��
	m_fHeight = 0.0f;						// ����
	m_Type = POLYGONTYPE::POLYGON_NORMAL;	// �|���S���̎��
}

//*******************************************************************************************************************************************
// �f�X�g���N�^
//*******************************************************************************************************************************************
CObject2D::~CObject2D()
{
	m_pDevice = nullptr;					// �f�o�C�X�̃|�C���^
	m_pVtxBuff = nullptr;					// ���_�o�b�t�@�̃|�C���^
	m_pTexture = nullptr;					// �e�N�X�`���̃|�C���^
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_fWidth = 0.0f;						// ��
	m_fHeight = 0.0f;						// ����
}

//*******************************************************************************************************************************************
// ����������
//*******************************************************************************************************************************************
HRESULT CObject2D::Init()
{
	// �V���O���g���C���X�^���X�̎擾
	CManager& manager = CManager::GetInstance();

	m_pDevice = manager.GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	m_pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���̃|�C���^
	VERTEX_2D* pVtx;
	
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*******************************************************************************************************************************************
// �I������
//*******************************************************************************************************************************************
void CObject2D::Uninit()
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
void CObject2D::Update()
{
	VERTEX_2D* pVtx;	// ���_���̃|�C���^

	switch (m_Type)
	{
	case CObject2D::POLYGONTYPE::POLYGON_NORMAL:
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y - m_fHeight, m_Pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y - m_fHeight, m_Pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y + m_fHeight, m_Pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y + m_fHeight, m_Pos.z);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
		pVtx[1].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
		pVtx[2].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
		pVtx[3].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();

		break;
	case CObject2D::POLYGONTYPE::POLYGON_NUMBER:
		break;
	case CObject2D::POLYGONTYPE::POLYGON_BLINK:

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y - m_fHeight, m_Pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y - m_fHeight, m_Pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y + m_fHeight, m_Pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y + m_fHeight, m_Pos.z);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
		pVtx[1].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
		pVtx[2].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
		pVtx[3].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();

		break;
	}
}

//*******************************************************************************************************************************************
// �`�揈��
//*******************************************************************************************************************************************
void CObject2D::Draw()
{
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	m_pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	m_pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//*******************************************************************************************************************************************
// ��������
//*******************************************************************************************************************************************
CObject2D* CObject2D::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if (m_apObject2D[nCnt] == nullptr)
		{
			m_apObject2D[nCnt] = new CObject2D;

			m_apObject2D[nCnt]->Init();

			//*********************************
			// �����̒l�̐ݒ�
			//*********************************
			m_apObject2D[nCnt]->m_Pos = pos;

			m_apObject2D[nCnt]->m_fWidth = fWidth;

			m_apObject2D[nCnt]->m_fHeight = fHeight;

			return m_apObject2D[nCnt];
		}
	}

	return nullptr;
}

//*******************************************************************************************************************************************
// �e�N�X�`���ݒ菈��
//*******************************************************************************************************************************************
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//*******************************************************************************************************************************************
// 2D�I�u�W�F�N�g���ݒ菈��
//*******************************************************************************************************************************************
void CObject2D::SetObject2D(D3DXVECTOR3 pos,D3DXCOLOR col, float fWidth, float fHeight)
{
	m_Pos = pos;			// �ʒu
	m_Col = col;			// �F
	m_fWidth = fWidth;		// ��
	m_fHeight = fHeight;	// ����
}

//*******************************************************************************************************************************************
// �|���S���̎�ސݒ菈��
//*******************************************************************************************************************************************
void CObject2D::SetPolygonType(POLYGONTYPE type)
{
	m_Type = type;
}

//*******************************************************************************************************************************************
// �|���S���̒��_�ݒ菈��
//*******************************************************************************************************************************************
void CObject2D::SetVtxAnimPolygon(float fWidth, float fHeight, float TexPos)
{
	float fheightTex = 1.0f / fHeight;

	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y + m_fHeight, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[1].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[2].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[3].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + TexPos * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(((1 / fWidth) + TexPos * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + TexPos * 0.1f, fheightTex);
	pVtx[3].tex = D3DXVECTOR2(((1 / fWidth) + TexPos * 0.1f), fheightTex);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//*******************************************************************************************************************************************
// �|���S���̒��_�ݒ菈��
//*******************************************************************************************************************************************
void CObject2D::SetColor(D3DXCOLOR col)
{
	m_Col = col;
}

//*******************************************************************************************************************************************
// �|���S���̒��_�ݒ菈��
//*******************************************************************************************************************************************
D3DXCOLOR CObject2D::GetColor()
{
	return m_Col;
}
