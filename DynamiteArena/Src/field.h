//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(field.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _FIELD_H_
#define _FIELD_H_

// include 
#include "object3D.h"

// ���N���X�̒�`
class CField : public CObject3D
{
public:
	CField(int nPriority = 2);																// �R���X�g���N�^
	~CField()override;																		// �f�X�g���N�^
	HRESULT Init()override;																	// ����������
	void Uninit()override;																	// �I������
	void Update()override;																	// �X�V����
	void Draw()override;																	// �`�揈��
	static CField* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth);		// ��������

	static HRESULT Load();																	// �e�N�X�`�����[�h
	static void UnLoad();																	// �e�N�X�`���A�����[�h

private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;												// �e�N�X�`��
};
#endif