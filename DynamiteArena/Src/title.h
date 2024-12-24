//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(title.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _TITLE_H_
#define _TITLE_H_

// include
#include "scene.h"
#include "input.h"

// �^�C�g����ʃN���X�̒�`
class CTitle : public CScene
{
public:
	CTitle();							// �R���X�g���N�^
	~CTitle();							// �f�X�g���N�^
	HRESULT Init()override;				// ����������
	void Uninit()override;				// �I������
	void Update()override;				// �X�V����
	void Draw()override;				// �`�揈��

private:
	CInputKeyboard* m_InputKeyboard;	// �L�[�{�[�h�̃|�C���^
	CInputJoypad* m_InputJoypad;		// �W���C�p�b�h�̃|�C���^
};
#endif