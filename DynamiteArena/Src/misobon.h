//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(misobon.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _MISOBON_H_
#define _MISOBON_H_

// include
#include "objectX.h"

// �݂��{���N���X�̒�`
class CMisobon : public CObjectX
{
public:
	CMisobon(int nPriority = 3);											// �R���X�g���N�^
	~CMisobon()override;													// �f�X�g���N�^
	HRESULT Init()override;													// ����������
	void Uninit()override;													// �I������
	void Update()override;													// �X�V����
	void Draw()override;													// �`�揈��
	static CMisobon* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);	// ��������

private:
	void Move();															// �ړ�����

	int m_nType;															// ���
	bool m_bMoveHorizon;													// �G�̉��ړ�
	bool m_bMoveVertical;													// �G�̏c�ړ�
};
#endif