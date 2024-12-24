//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(billboard.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

// include
#include "object.h"

// �r���{�[�h�N���X�̒�`
class CBillboard : public CObject
{
public:
	// �r���{�[�h�̎�ނ̗񋓌^
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_BULLET,			// �e
		TYPE_PARTICLE,			// �p�[�e�B�N��
		TYPE_EFFECT,			// �G�t�F�N�g
		TYPE_EXPLOSION,			// ����
		TYPE_CAVEATUI,			// �x���\��UI
		TYPE_MAX
	}BILLBOARDTYPE;

	CBillboard(int nPriority = 3);																		// �R���X�g���N�^
	~CBillboard()override;																				// �f�X�g���N�^
	HRESULT Init()override;																				// ����������
	void Uninit()override;																				// �I������
	void Update()override;																				// �X�V����
	void Draw()override;																				// �`�揈��
	static CBillboard* Create();																		// ��������

	void SetBillboard(D3DXVECTOR3 pos, float fWidth, float fHeight, int nDivision,BILLBOARDTYPE type);	// �r���{�[�h�̏��ݒ�(�ʒu/��/����/�e�N�X�`���̕�����)
	void SetVtx(BILLBOARDTYPE type);																	// ���_���̐ݒ�

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);															// �e�N�X�`���̐ݒ�

	void SetPos(D3DXVECTOR3 pos);																		// �ʒu�ݒ菈��
	D3DXVECTOR3 GetPos();																				// �ʒu�擾����

	void SetColor(D3DXCOLOR col);																		// �F�ݒ菈��
	D3DXCOLOR GetColor();																				// �F�擾����

	void SetAnimCount(int nCnt);																		// �A�j���[�V�����������񐔐ݒ菈��
	int GetAnimCount();																					// �A�j���[�V�����������񐔎擾����

	static const int MAX_BILLBOARD = 512;																// �r���{�[�h�̍ő吔

private:
	LPDIRECT3DDEVICE9 m_pDevice;																		// �f�o�C�X�̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;																	// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;																		// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_Pos;																					// �ʒu
	D3DXVECTOR3 m_PosOld;																				// 1�O�̈ʒu
	D3DXCOLOR m_Col;																					// �F
	D3DXMATRIX m_mtxWorld;																				// ���[���h�}�g���b�N�X

	int m_nTexDivision;																					// �e�N�X�`���̕�����
	int m_nAnimFrame;																					// �A�j���[�V���������鎞�ԊԊu
	int m_nAnimCount;																					// �A�j���[�V������������

	float m_fWidth;																						// ��
	float m_fHeight;																					// ����
	float m_fLength;																					// �Ίp���̒���

	BILLBOARDTYPE m_Type;																				// �r���{�[�h�̎��

	static CBillboard* m_apBillboard[MAX_BILLBOARD];													// �r���{�[�h�̏��
};
#endif