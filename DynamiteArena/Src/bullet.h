//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(bullet.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _BULLET_H_
#define _BULLET_H_

// include
#include "objectX.h"
#include "PlayerParam.h"

// ���e�N���X�̒�`
class CBullet : public CObjectX
{
public:
	CBullet(int nPriority = 3);										// �R���X�g���N�^
	~CBullet()override;												// �f�X�g���N�^
	HRESULT Init()override;											// ����������
	void Uninit()override;											// �I������
	void Update()override;											// �X�V����
	void Draw()override;											// �`�揈��
	static CBullet* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move);		// ��������

	bool IsBlockPos(D3DXVECTOR3 pos, float fWidth, float fDepth);	// �u���b�N�����邩�ǂ���

	bool CollisionBullet(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size, int nType);	// �����蔻��

	static const int UI_TIMING = 120;								// UI��\��������^�C�~���O
	static const int DELETE_BULLET = 240;							// �e�̏����^�C�~���O
	static const int NUM_EXPLOSION = 15;							// �����̐�����(1����)
	static const int FALL_INDEX = 2;								// �e�̗����n�_�̃C���f�b�N�X

private:
	void Move();													// �ړ�
	void Death();													// �x���\��UI�o������
	void Motion();													// �e�̃��[�V����

	CParamManager* m_pParamManager;									// �p�����[�^�[�Ǘ��N���X�̃|�C���^

	D3DXVECTOR3 m_Move;												// �ړ���
	bool m_bDeath;													// �g�p����Ă��邩�ǂ���
	bool m_bScale;													// �g�k�p�t���O

	float m_fGravity;												// �e�̏d��
	float m_fInitialYSpeed;											// Y�������̏����x

	bool m_bHitObstacle;											// ��Q���ɓ����������ǂ���

	int m_nLag;														// �n�ʂɂ��Ă��������܂ł̎���

	int m_nNotCollision;											// �����蔻�肪�@�\���Ȃ�����
};

static const float BULLET_LIFE = 170.0f;							// �e�̎���
static const float CAVEAT_SPAN = 15.0f;								// �x���\��UI�̕\�������镝�̊Ԋu
static const float POLYGON_SIZE = 10.0f;							// �x���\��UI�̑傫��(���a)

static const float MOTION_SPEEDFAST = 0.05f;						// ���[�V�������x(����)
static const float MOTION_SPEEDLATE = 0.01f;						// ���[�V�������x(�x��)

static const float MIN_BULLETSCALE = 1.0f;								// �ŏ��̑傫��
static const float MAX_BULLETSCALE = 1.5f;								// �ő�̑傫��
#endif

