//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(scene.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _SCENE_H_
#define _SCENE_H_

// include
#include "main.h"

// �V�[�����N���X�̒�`
class CScene
{
public:
	// ��ʂ̎��
	typedef enum
	{
		MODE_TITLE = 0,		// �^�C�g�����
		MODE_TUTORIAL,		// �`���[�g���A�����
		MODE_GAME,			// �Q�[�����
		MODE_CLEARRESULT,	// �Q�[���N���A���
		MODE_FAILRESULT,	// �Q�[���I�[�o�[���
		MODE_MAX
	}MODE;

	CScene();							// �R���X�g���N�^
	~CScene();							// �f�X�g���N�^
	virtual HRESULT Init();				// ����������
	virtual void Uninit();				// �I������
	virtual void Update();				// �X�V����
	virtual void Draw();				// �`�揈��
	static CScene* Create(MODE mode);	// ��������
	void SetMode(MODE mode);			// ���[�h�ݒ菈��
	MODE GetMode();						// ���[�h�擾����

private:
	MODE m_Mode;						// ���݂̃��[�h
};
#endif