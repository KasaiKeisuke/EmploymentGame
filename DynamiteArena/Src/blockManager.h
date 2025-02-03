//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(blockManager.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _BLOCKMANAGER_H_
#define _BLOCKMANAGER_H_

// include
#include "main.h"

// �u���b�N�}�l�[�W���[�N���X�̒�`
class CBlockManager
{
public:
	CBlockManager();				// �R���X�g���N�^
	~CBlockManager();				// �f�X�g���N�^
	HRESULT Init();					// ����������
	void Uninit();					// �I������
	void Update();					// �X�V����
	void Draw();					// �`�揈��

	void SetFlag(bool bFlag);
	bool GetFlag();
};
#endif