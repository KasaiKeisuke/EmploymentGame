//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(enemy.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _ENEMY_H_
#define _ENEMY_H_

// include
#include "objectX.h"

// �G�N���X�̒�`
class CEnemy : public CObjectX
{
public:
	CEnemy(int nPriority = 3);																	// �R���X�g���N�^
	~CEnemy()override;																			// �f�X�g���N�^
	HRESULT Init()override;																		// ����������
	void Uninit()override;																		// �I������
	void Update()override;																		// �X�V����
	void Draw()override;																		// �`�揈��
	static CEnemy* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move);									// ��������
	
	bool CollisionEnemy(D3DXVECTOR3* pos, D3DXVECTOR3 size, int nType);							// �����蔻��(�G�Ƒ��̃I�u�W�F�N�g)

	static void Load();																			// ���[�h����
private:
	void Move();																				// �ړ�����
	void Death(int nCnt);																		// ���S����
	void Motion(D3DXVECTOR3 &rot);																// ���[�V��������

	int m_nCnt;

	int m_nLife;																				// ����
	D3DXVECTOR3 m_Move;																			// �ړ���

	bool m_bHit;																				// ��e�������ǂ���
	bool m_bHitObstacle;																		// ��Q���ɓ����������ǂ���(�u���b�N���)
	bool m_bMoveRot;																			// �i�s��������p�t���O
	bool m_bRot;																				// ���[�V�����p�t���O
};

static const float ENEMY_SPEED = 0.5f;															// �G�̈ړ����x
static const float ENEMY_MOTIONROT = 0.5f;														// ���[�V�����̊p�x
static const float ENEMY_MOTIONSPEED = 0.01f;													// ���[�V�������x
#endif