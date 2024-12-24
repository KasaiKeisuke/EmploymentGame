//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(game.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _GAME_H_
#define _GAME_H_

// include
#include "scene.h"
#include "input.h"
#include "PlayerParam.h"
#include "GameManager.h"
#include "timer.h"
#include "score.h"

// �Q�[����ʃN���X�̒�`
class CGame : public CScene
{
public:
	CGame();							// �R���X�g���N�^
	~CGame();							// �f�X�g���N�^
	HRESULT Init()override;				// ����������
	void Uninit()override;				// �I������
	void Update()override;				// �X�V����
	void Draw()override;				// �`�揈��

private:
	CInputKeyboard* m_InputKeyboard;	// �L�[�{�[�h�̃|�C���^
	CInputJoypad* m_InputJoypad;		// �W���C�p�b�h�̃|�C���^
	CParamManager* m_pParamManager;		// �p�����[�^�[�Ǘ��N���X�̃|�C���^
	CGameManager* m_pGameManager;		// �Q�[���}�l�[�W���[�N���X�̃|�C���^

	static const int FIELD_SIZE = 500;	// ���̑傫��

	int m_nTime;						// ��������
};
#endif