//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(bg.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _BG_H_
#define _BG_H_

// include
#include "object2D.h"

// ��ʔw�i�N���X�̒�`
class CBg : public CObject2D
{
public:
	// �w�i�e�N�X�`����ނ̗񋓌^
	typedef enum
	{
		TYPE_TITLE = 0,																	// �^�C�g�����
		TYPE_TUTORIAL,																	// �`���[�g���A�����
		TYPE_GAME,																		// �Q�[�����
		TYPE_CLEARRESULT,																// �Q�[���N���A���
		TYPE_FAILRESULT,																// �Q�[���I�[�o�[���
		TYPE_MAX
	}TEXTYPE;

	CBg(int nPriority = 4);																// �R���X�g���N�^
	~CBg()override;																		// �f�X�g���N�^
	HRESULT Init()override;																// ����������
	void Uninit()override;																// �I������
	void Update()override;																// �X�V����
	void Draw()override;																// �`�揈��
	static CBg* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, TEXTYPE type);		// ��������

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;												// �e�N�X�`��
};
#endif