//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(ItemManager.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _ITEMMANAGER_H_
#define _ITEMMANAGER_H_

// include 
#include "main.h"

// �A�C�e���}�l�[�W���[�N���X�̒�`
class CItemManager
{
public:
	CItemManager();				// �R���X�g���N�^
	~CItemManager();			// �f�X�g���N�^
	HRESULT Init();				// ����������
	void Uninit();				// �I������
	void Update();				// �X�V����
	void Draw();				// �`�揈��

	void SetNumItem(int nNum);	// �A�C�e���̏o�����ݒ�
	int GetNumItem();			// �A�C�e���̏o�����擾

private:
	int m_nNumItem;				// �A�C�e���̌�
};

#endif