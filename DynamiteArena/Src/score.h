//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(score.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _SCORE_H_
#define _SCORE_H_

// include 
#include "object.h"
#include "number.h"
#include "GameManager.h"

// �X�R�A�N���X�̒�`
class CScore : public CObject
{
public:
	CScore(int nPriority = 4);				// �R���X�g���N�^
	~CScore()override;						// �f�X�g���N�^
	HRESULT Init()override;					// ����������
	void Uninit()override;					// �I������
	void Update()override;					// �X�V����
	void Draw()override;					// �`�揈��
	static CScore* Create();				// ��������

	static void Add(int nScore);			// �X�R�A���Z����

	static const int MAX_DIGIT = 8;			// �X�R�A�̌���

private:
	static CNumber* m_aNumber[MAX_DIGIT];	// �����̏��
	CGameManager* m_pGameManager;			// �Q�[���}�l�[�W���[�N���X�̃|�C���^

	static int m_nScore;					//���݂̃X�R�A
};
#endif