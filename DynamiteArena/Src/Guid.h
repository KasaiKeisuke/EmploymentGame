//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(Guid.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _GUID_H_
#define _GUID_H_

// include
#include "object2D.h"
#include "manager.h"

// �K�C�h�N���X�̒�`
class CGuid : public CObject2D
{
public:
	// �e�N�X�`���̎�ނ̗񋓌^
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_STARTGAME,		// �Q�[�����n�߂�p
		TYPE_RETURNTITLE,	// �^�C�g����ʂɖ߂�p
		TYPE_MAX
	}TEXTURETYPE;

	CGuid(int nPriority = 4);																	// �R���X�g���N�^
	~CGuid()override;																			// �f�X�g���N�^
	HRESULT Init()override;																		// ����������
	void Uninit()override;																		// �I������
	void Update()override;																		// �X�V����
	void Draw()override;																		// �`�揈��
	static CGuid* Create(D3DXVECTOR3 pos, float fWidth, float fHeight,TEXTURETYPE type);		// ��������

private:
	void Animation();																			// �A�j���[�V��������

	LPDIRECT3DTEXTURE9 m_pTexture;																// �e�N�X�`���̃|�C���^

	TEXTURETYPE m_Type;																			// �e�N�X�`���̎��

	bool m_bAnimation;																			// �A�j���[�V�����p�t���O

};

static const float MIN_POLYGONCOLOR = 0.1f;														// �F�̍ŏ��l
static const float POLYGONANIM_SPEED = 0.01f;													// �A�j���[�V�����̑��x

#endif