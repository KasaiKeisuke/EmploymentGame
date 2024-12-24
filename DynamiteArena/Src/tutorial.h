//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(tutorial.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

// include 
#include "scene.h"
#include "input.h"

// �`���[�g���A����ʃN���X�̒�`
class CTutorial : public CScene
{
public:
	CTutorial();						// �R���X�g���N�^
	~CTutorial();						// �f�X�g���N�^
	HRESULT Init();						// ����������
	void Uninit();						// �I������
	void Update();						// �X�V����
	void Draw();						// �`�揈��

private:
	CInputKeyboard* m_InputKeyboard;	// �L�[�{�[�h�̃|�C���^
	CInputJoypad* m_InputJoypad;		// �W���C�p�b�h�̃|�C���^
};
#endif