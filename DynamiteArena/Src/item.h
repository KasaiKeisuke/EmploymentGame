//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(item.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _ITEM_H_
#define _ITEM_H_

// include
#include "object3D.h"
#include "PlayerParam.h"

// �A�C�e���N���X�̒�`
class CItem : public CObject3D
{
public:
	// �A�C�e���̎�ނ̗񋓌^
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_POWERUP,		// �p���[�A�b�v
		TYPE_SPEEDUP,		// �X�s�[�h�A�b�v
		TYPE_ENEMYKILL,		// �݂��{�����j�p
		TYPE_MAX
	}ITEMTYPE;

	CItem(int nPriority = 3);																		// �R���X�g���N�^
	~CItem()override;																				// �f�X�g���N�^
	HRESULT Init()override;																			// ����������
	void Uninit()override;																			// �I������
	void Update()override;																			// �X�V����
	void Draw()override;																			// �`�揈��
	static CItem* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth,int nType);		// ��������

	bool CollisionItem(D3DXVECTOR3* pos, D3DXVECTOR3 size, int nType);								// �����蔻��

	void SetItemType(int nType);																	// �A�C�e���̎�ސݒ�
	int GetItemType();																				// �A�C�e���̎�ގ擾

	static void Load();																				// ���[�h����																							// �A�C�e���̃��[�h����
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;															// �e�N�X�`��

	CParamManager* m_pParamManager;																	// �v���C���[�̃p�����[�^�[�Ǘ��N���X

	ITEMTYPE m_Type;																				// �A�C�e���̎��
	float m_fWidth;																					// ��
	float m_fDepth;																					// ���s

	bool m_bHit;																					// �����������ǂ���
	bool m_bDeath;																					// �g�p����Ă��邩�ǂ���

	int m_nLag;																						// �A�C�e������������Ă��瓖���蔻��𔭓�������܂ł̎���
};
static const float ITEM_WIDTH = 15.0f;																// �A�C�e���p�|���S���̕�
static const float ITEM_HEIGHT = 0.0f;																// �A�C�e���p�|���S���̍���
static const float ITEM_DEPTH = 15.0f;																// �A�C�e���p�|���S���̉��s
#endif