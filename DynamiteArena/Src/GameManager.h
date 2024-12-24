//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(GameManager.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

// include
#include "main.h"

// �Q�[���}�l�[�W���[�N���X�̒�`
class CGameManager
{
public:
	CGameManager();				// �R���X�g���N�^
	~CGameManager();			// �f�X�g���N�^
	HRESULT Init();				// ����������
	void Uninit();				// �I������
	void Update();				// �X�V����

	void SetTimer(int nTime);	// �������Ԑݒ�
	int GetTimer();				// �������Ԏ擾

	void SetScore(int nScore);	// �X�R�A�ݒ�
	int GetScore();				// �X�R�A�擾

private:
	int m_nTime;				// �������Ԋi�[�p
	int m_nScore;				// �X�R�A�i�[�p
};
#endif // !_GAMEMANAGER_H_
