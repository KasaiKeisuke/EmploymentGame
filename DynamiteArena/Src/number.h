//***********************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(number.h)
// Author : Kasai Keisuke
//
//***********************************************************************************************************************

#ifndef _NUMBER_H_
#define _NUMBER_H_

// include
#include "object2D.h"

// �����N���X�̒�`
class CNumber : public CObject2D
{
public:
	CNumber(int nPriority = 4);					// �R���X�g���N�^
	~CNumber()override;							// �f�X�g���N�^
	HRESULT Init()override;						// ����������
	void Uninit()override;						// �I������
	void Update()override;						// �X�V����
	void Draw()override;						// �`�揈��
	static CNumber* Create(D3DXVECTOR3 pos);	// ��������

	static HRESULT Load();						// �e�N�X�`�����[�h
	void UnLoad();								// �e�N�X�`���A�����[�h

private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;	// �e�N�X�`���̃|�C���^

};
#endif