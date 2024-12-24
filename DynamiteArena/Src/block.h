//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(block.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _BLOCK_H_
#define _BLOCK_H_

// include
#include "objectX.h"

// �u���b�N�N���X�̒�`
class CBlock : public CObjectX
{
public:
	// �u���b�N�̎�ނ̗񋓌^
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_BREAK,			// �j��ł���
		TYPE_NOTBREAK,		// �j��ł��Ȃ�
	}BLOCKTYPE;

	CBlock(int nPriority = 2);																	// �R���X�g���N�^
	~CBlock()override;																			// �f�X�g���N�^
	HRESULT Init()override;																		// ����������
	void Uninit()override;																		// �I������
	void Update()override;																		// �X�V����
	void Draw()override;																		// �`�揈��
	static CBlock* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int type);							// ��������
	bool CollisionBlock(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size,int nType);		// �����蔻��(�Ώە��̈ʒu/�Ώە���1�O�̈ʒu/�Ώە��̑傫��/�Ώە��̎��)

	static void Load();																			// ���[�h����

	void SetBlockType(BLOCKTYPE type);															// �u���b�N�̎�ސݒ�
	BLOCKTYPE GetType();																		// �u���b�N�̎�ގ擾

private:
	bool m_bDeath;																				// �j�󂳂ꂽ���ǂ���
	int m_nLife;																				// �ϋv��
	BLOCKTYPE m_Type;																			// �u���b�N�̎��

	static const int BLOCK_SIZE = 15;															// �u���b�N�̑傫��(���a)
	static const int PLAYER_SIZE = 20;															// �v���C���[�̑傫��(���a)
};

static const float ADJUST_HIT = 5.0f;		// �����蔻�蒲���p
#endif