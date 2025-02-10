//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(explosion.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

// include 
#include "objectX.h"

// �����N���X�̒�`
class CExplosion : public CObjectX
{
public:
	CExplosion(int nPriority = 3);																	// �R���X�g���N�^
	~CExplosion()override;																			// �f�X�g���N�^
	HRESULT Init()override;																			// ����������
	void Uninit()override;																			// �I������
	void Update()override;																			// �X�V����
	void Draw()override;																			// �`�揈��
	static CExplosion* Create(D3DXVECTOR3 pos);														// ��������

	static HRESULT Load();																			// X�t�@�C�����[�h
	static void UnLoad();																			// X�t�@�C���A�����[�h

	bool CollisionExplosion(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size, int nType);	// �����蔻��

	static const int DRAW_COUNT = 60;																// �\�������鎞��
	static const int FILE_PATH = 256;																// �t�@�C���p�X
	static const int TIME_LAG = 25;																	// ���[�V������؂�ւ���܂ł̎���
	static const int EXPLOSION_SIZE = 20;															// �����̑傫��

private:
	void Turn();																					// ��]����
	void Motion();																					// ���[�V��������

	static char m_pFiletemp[FILE_PATH];																// �t�@�C���p�X
	int m_nCnt;																						// �\�������鎞��

	int m_nLag;																						// �g�k��؂�ւ���܂ł̎���
	bool m_bScale;																					// �g�k�p�t���O
};

static const float MAX_SCALE = 1.6f;																// ���f���̍ő�X�P�[��
static const float ANIM_SPEEDFAST = 0.5f;															// �A�j���[�V�������x(����)
static const float ANIM_SPEEDLATE = 0.05f;															// �A�j���[�V�������x(�x��)

#endif