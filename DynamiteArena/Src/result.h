//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(result.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _RESULT_H_
#define _RESULT_H_

// include
#include "scene.h"
#include "input.h"

// ���U���g��ʃN���X�̒�`
class CResult : public CScene
{
public:
	CResult();							// �R���X�g���N�^
	~CResult();							// �f�X�g���N�^
	HRESULT Init()override;				// ����������
	void Uninit()override;				// �I������
	void Update()override;				// �X�V����
	void Draw()override;				// �`�揈��

private:
	CInputKeyboard* m_InputKeyboard;	// �L�[�{�[�h�̃|�C���^
	CInputJoypad* m_InputJoypad;		// �W���C�p�b�h�̃|�C���^
};
#endif