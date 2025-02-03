//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(cursor.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _CURSOR_H_
#define _CURSOR_H_

// include 
#include "object2D.h"
#include "manager.h"
#include "input.h"

// �J�[�\���N���X�̒�`
class CCursor : public CObject2D
{
public:
	CCursor(int nPriority = 4);													// �R���X�g���N�^
	~CCursor()override;															// �f�X�g���N�^
	HRESULT Init()override;														// ����������
	void Uninit()override;														// �I������
	void Update()override;														// �X�V����
	void Draw()override;														// �`�揈��
	static CCursor* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);		// ��������

private:
	void Select();																// �I������

	static const int MAX_SELECT = 2;											// �I�����̍ő��

	LPDIRECT3DTEXTURE9 m_pTexture;												// �e�N�X�`���̃|�C���^

	CInputKeyboard* m_InputKeyboard;											// �L�[�{�[�h�̃|�C���^
	CInputJoypad* m_InputJoypad;												// �W���C�p�b�h�̃|�C���^

	int m_nSelect;																// �I�����i�[�p

	bool m_bCursorMove;															// �J�[�\���������Ă��邩�ǂ���
	bool m_bScale;																// �|���S���̊g�k�p�t���O
};
static const float MIN_SCALE = 100.0f;											// �ŏ��X�P�[��
static const float MAX_SCALE = 120.0f;											// �ő�X�P�[��

#endif