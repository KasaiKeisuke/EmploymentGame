//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(goal.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _GOAL_H_
#define _GOAL_H_

// include
#include "objectX.h"

// �S�[���}�[�J�[�N���X�̒�`
class CGoal : public CObjectX
{
public:
	CGoal(int nPriority = 3);																	// �R���X�g���N�^
	~CGoal()override;																			// �f�X�g���N�^
	HRESULT Init()override;																		// ����������
	void Uninit()override;																		// �I������
	void Update()override;																		// �X�V����
	void Draw()override;																		// �`�揈��
	static CGoal* Create(D3DXVECTOR3 pos);														// ��������

	bool CollisionGoal(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size, int nType);		// �����蔻��
};
#endif