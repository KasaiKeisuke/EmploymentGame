//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(timer.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _TIMER_H_
#define _TIMER_H_

// include
#include "number.h"
#include "GameManager.h"
#include "object.h"

// �^�C�}�[�N���X�̒�`
class CTimer : public CObject
{
public:
	CTimer(int nPriority = 4);					// �R���X�g���N�^
	~CTimer()override;							// �f�X�g���N�^
	HRESULT Init()override;						// ����������
	void Uninit()override;						// �I������
	void Update()override;						// �X�V����
	void Draw()override;						// �`�揈��
	static CTimer* Create();					// ��������

	static void Sub(int nTime);					// �^�C�}�[���Z����

	static const int MAX_DIGIT = 3;				// �ő包��
private:
	CGameManager* m_pGameManager;				// �Q�[���}�l�[�W���[�N���X�̃|�C���^

	static CNumber* m_aNumber[MAX_DIGIT];		// �����N���X�̏��
	static int m_nTimer;						// �^�C�}�[�i�[�p
};
#endif