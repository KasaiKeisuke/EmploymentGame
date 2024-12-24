//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(PlayerParam.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _PLAYERPARAM_H_
#define _PLAYERPARAM_H_

// include
#include "main.h"

// �v���C���[�p�����[�^�[�Ǘ��N���X�̒�`
class CParamManager
{
public:
	CParamManager();								// �R���X�g���N�^
	~CParamManager();								// �f�X�g���N�^
	HRESULT Init();									// ����������
	void Uninit();									// �I������
	void Update();									// �X�V����

	void SetSpeed(float fSpeed);					// �v���C���[�̈ړ����x�ݒ�
	float GetSpeed();								// �v���C���[�̈ړ����x�擾

	void SetPower(int nPower);						// ���e�̔����͐ݒ菈��
	int GetPower();									// ���e�̔����͎擾����

	int GetTime();									// �p�����[�^�[���������鎞�Ԏ擾

	void AddParam(int nCnt, int nType);				// �p�����[�^�[��������
	void ResetParam();								// �p�����[�^�[���Z�b�g����

private:


	int m_nCnt;										// �p�����[�^�[���������鎞��
	int m_nPower;									// ������
	float m_fSpeed;									// �ړ����x
};
#endif