//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(object3D.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

// include
#include "object.h"
#include "renderer.h"

// 3D�|���S���N���X�̒�`
class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 3);															// �R���X�g���N�^
	~CObject3D()override;																	// �f�X�g���N�^
	HRESULT Init()override;																	// ����������
	void Uninit()override;																	// �I������
	void Update()override;																	// �X�V����
	void Draw()override;																	// �`�揈��

	static CObject3D* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth);	// ��������(�ʒu/��/����/���s)

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);												// �e�N�X�`���ݒ菈��

	void SetObject3D(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth);			// ���ݒ菈��


	void SetPos(D3DXVECTOR3 pos);															// �ʒu�ݒ菈��
	D3DXVECTOR3 GetPos();																	// �ʒu�擾����

	void SetRot(D3DXVECTOR3 rot);															// �����ݒ菈��
	D3DXVECTOR3 GetRot();																	// �����擾����

	void DrawShadow();																		// �e�̕`��

	const static int MAX_OBJECT3D = 64;														// 3D�|���S���ő吔

private:
	LPDIRECT3DDEVICE9 m_pDevice;															// �f�o�C�X�̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;														// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;															// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_Pos;																		// �ʒu
	D3DXVECTOR3 m_Rot;																		// ����
	D3DXCOLOR m_Col;																		// �F
	D3DXMATRIX m_mtxWorld;																	// ���[���h�}�g���b�N�X


	float m_fWidth;																			// ��
	float m_fHeight;																		// ����
	float m_fDepth;																			// ���s

	static CObject3D* m_apObject3D[MAX_OBJECT3D];											// 3D�|���S���̐�
};
#endif