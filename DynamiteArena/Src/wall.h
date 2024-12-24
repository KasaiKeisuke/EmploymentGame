//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(wall.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _WALL_H_
#define _WALL_H_

// include 
#include "objectX.h"
#include <stdio.h>

// �ǃN���X�̒�`
class CWall : public CObjectX
{
public:
	// �ǂ̎�ނ̗񋓌^
	typedef enum
	{
		WALL_NONE = 0,
		WALL_NORMAL,	// �ʏ��
		WALL_SIDE,		// ���ʕ�
		WALL_MAX
	}WALLTYPE;

	CWall(int nPriority = 3);																					// �R���X�g���N�^
	~CWall()override;																							// �f�X�g���N�^
	HRESULT Init()override;																						// ����������
	void Uninit()override;																						// �I������
	void Update()override;																						// �X�V����
	void Draw()override;																						// �`�揈��
	static CWall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);											// ��������
	bool CollisionWall(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3 size,int type ,int nType);			// �����蔻��(�������Ă������̂̈ʒu/�������Ă������̂�1�O�̈ʒu/�������Ă������̂̑傫��/���������ǂ̎��/�������Ă������̂̎��)
	static void Load();																							// ���[�h����

private:
	static const int NORMALWALL_WIDTH = 50;																		// �ʏ�ǂ̕�
	static const int NORMALWALL_DEPTH = 10;																		// �ʏ�ǂ̉��s
	
	static const int SIDEWALL_WIDTH = 10;																		// ���ʕǂ̕�
	static const int SIDEWALL_DEPTH = 51;																		// ���ʕǂ̉��s

	static const int PLAYER_SIZE = 20;																			// �v���C���[�̑傫��(���a)

};
#endif