//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(TitleLogo.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

// include
#include "object2D.h"
#include "manager.h"

// �^�C�g�����S�N���X�̒�`
class CTitleLogo : public CObject2D
{
public:
	CTitleLogo(int nPriority = 4);													// �R���X�g���N�^
	~CTitleLogo()override;															// �f�X�g���N�^
	HRESULT Init()override;															// ����������
	void Uninit()override;															// �I������
	void Update()override;															// �X�V����
	void Draw()override;															// �`�揈��
	static CTitleLogo* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);		// ��������

private:
	void Animation();																// �A�j���[�V��������

	LPDIRECT3DTEXTURE9 m_pTexture;													// �e�N�X�`���̃|�C���^

	bool m_bAnimation;																// �A�j���[�V�����p�t���O
};
static const float MIN_COLOR = 0.1f;												// �F�̍ŏ��l
static const float ANIM_SPEED = 0.01f;												// �A�j���[�V�����̑��x
#endif