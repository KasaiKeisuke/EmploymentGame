//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(object.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _OBJECT_H_
#define _OBJECT_H_

// include
#include "main.h"

// �I�u�W�F�N�g�N���X�̒�`
class CObject
{
public:
	
	// �I�u�W�F�N�g�̎�ޗ񋓌^
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,		// �v���C���[
		TYPE_ENEMY,			// �G
		TYPE_BLOCK,			// �u���b�N
		TYPE_NORMALWALL,	// �ʏ��
		TYPE_SIDEWALL,		// ���ʕ�
		TYPE_BULLET,		// �e
		TYPE_EXPLOSION,		// ����
		TYPE_GOAL,			// �S�[���}�[�J�[
		TYPE_ITEM,			// �A�C�e��
		TYPE_MAX
	}OBJECTTYPE;

	CObject(int nPriority = 3);								// �R���X�g���N�^
	virtual ~CObject();										// �f�X�g���N�^
	virtual HRESULT Init() = 0;								// ����������
	virtual void Uninit() = 0;								// �I������
	virtual void Update() = 0;								// �X�V����
	virtual void Draw() = 0;								// �`�揈��

	static void ReleaseAll();								// �S�I�u�W�F�N�g�j��
	static void UpdateAll();								// �S�I�u�W�F�N�g�X�V
	static void DrawAll();									// �S�I�u�W�F�N�g�`��
	static CObject* GetObjectInfo(int nPriority, int nIdx);	// �I�u�W�F�N�g���擾

	void SetType(OBJECTTYPE type);							// �I�u�W�F�N�g�̎�ސݒ菈��
	OBJECTTYPE GetType();									// �I�u�W�F�N�g�̎�ގ擾����

	static const int MAX_OBJECT = 512;						// �I�u�W�F�N�g�ő吔
	static const int DRAW_PRIORITY = 5;					// �v���C�I���e�B�ő吔

protected:
	void Release();											// �I�u�W�F�N�g�j��

private:
	static CObject* m_apObject[DRAW_PRIORITY][MAX_OBJECT];	// �I�u�W�F�N�g�̏��
	static int m_nNumAll;									// �I�u�W�F�N�g�̑���
	int m_nID;												// �I�u�W�F�N�g��ID
	int m_nPriority;										// �v���C�I���e�B

	OBJECTTYPE m_Type;										// �I�u�W�F�N�g�̎��
};

#endif