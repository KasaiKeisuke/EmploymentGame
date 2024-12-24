//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(player.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _PLAYER_H_
#define _PLAYER_H_

// include
#include "objectX.h"
#include "input.h"
#include "camera.h"
#include "PlayerParam.h"

// �v���C���[�N���X�̒�`
class CPlayer : public CObjectX
{
public:
	CPlayer(int nPriority = 3);					// �R���X�g���N�^
	~CPlayer()override;							// �f�X�g���N�^
	HRESULT Init()override;						// ����������
	void Uninit()override;						// �I������
	void Update()override;						// �X�V����
	void Draw()override;						// �`�揈��
	static CPlayer* Create(D3DXVECTOR3 pos);	// ��������

	static const int COOLDOWN = 250;			// �e���˂̃N�[���_�E��

	static const int SHAKE_FRAME = 30;			// �J������h�炷����

	static const int DAMAGE_TIME = 80;			// �_���[�W���o����
	static const int GOAL_TIME = 100;			// �S�[�����o����

private:
	void Move();								// �ړ�
	void Attack();								// �U��
	void Damage(int nCnt);						// ��e����
	void GoalParformance(int nCnt);				// �S�[�����o
	void Motion(D3DXVECTOR3 &rot);				// ���[�V��������

	CInputKeyboard* m_InputKeyboard;			// �L�[�{�[�h�̃|�C���^
	CInputJoypad* m_InputJoypad;				// �W���C�p�b�h�̃|�C���^
	CCamera* m_pCamera;							// �J�����̃|�C���^
	CParamManager* m_pParamManager;				// �p�����[�^�[�Ǘ��N���X�̃|�C���^

	D3DXVECTOR3 m_Move;							// �ړ���
	
	int m_nLife;								// �v���C���[�̗̑�
	bool m_bHit;								// �����������ǂ���(�v���C���[�ƕ�)
	bool m_bDamage;								// �����������ǂ���(�v���C���[�Ɣ��e)
	bool m_bDeath;								// �����������ǂ���(�v���C���[�ƓG)
	bool m_bGoal;								// �����������ǂ���(�v���C���[�ƃS�[��)

	int m_nCoolCount;							// �N�[���_�E���J�E���g�p
	bool m_bHasFired;							// 1���ڂ̒e���ǂ���

	int m_nCnt;									// �S�[�����o�̎���
	int m_nDeathCnt;							// ���S���o�̎���

	float m_fShake;								// �J������h�炷����

	bool m_bRot;								// ���[�V�����p�t���O
};

static const float CAMERA_SHAKE = 5.0f;			// �J������h�炷�ʂ̍ő�l
static const float PLAYER_SPEED = 1.3f;			// �v���C���[�̈ړ����x

static const float MAX_MOTIONROT = 0.5f;		// ���[�V�����ŉ�]������ő��
static const float MOTION_SPEED = 0.05f;		// ���[�V�������x
#endif