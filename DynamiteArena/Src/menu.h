//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(menu.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _MENU_H_
#define _MENU_H_

// include 
#include "object2D.h"
#include "manager.h"

// �I�����N���X�̒�`
class CMenu : public CObject2D
{
public:
	// �摜�̎�ނ̗񋓌^
	typedef enum
	{
		MENU_NONE = 0,
		MENU_TUTORIAL,		// �`���[�g���A��
		MENU_GAME,			// �Q�[��
		MENU_MAX
	}MENUTYPE;

	CMenu(int nPriority = 4);																// �R���X�g���N�^
	~CMenu()override;																		// �f�X�g���N�^
	HRESULT Init()override;																	// ����������
	void Uninit()override;																	// �I������
	void Update()override;																	// �X�V����
	void Draw()override;																	// �`�揈��
	static CMenu* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, MENUTYPE type);		// ��������

private:
	LPDIRECT3DTEXTURE9 m_pTexture;															// �e�N�X�`���̃|�C���^
	MENUTYPE m_Type;																		// �e�N�X�`���̎��
};
#endif