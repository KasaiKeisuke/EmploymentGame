//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(objectX.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _OBJECTX_H_
#define _OBJECTX_H_

// include 
#include "object.h"

// X�t�@�C���N���X�̒�`
class CObjectX : public CObject
{
public:
	CObjectX(int nPriority = 3);								// �R���X�g���N�^
	~CObjectX()override;										// �f�X�g���N�^
	HRESULT Init()override;										// ����������
	void Uninit()override;										// �I������
	void Update()override;										// �X�V����
	void Draw()override;										// �`�揈��

	static CObjectX* Create();									// ��������

	void SetPos(D3DXVECTOR3 pos);								// �ʒu�ݒ菈��
	D3DXVECTOR3 GetPos();										// �ʒu�擾����

	void SetRot(D3DXVECTOR3 rot);								// �����ݒ菈��
	D3DXVECTOR3 GetRot();										// �����擾����

	D3DXVECTOR3 GetPosOld();									// 1�O�̈ʒu�̎擾

	const static int MAX_SENTENCE = 128;						// �t�@�C���p�X�̕�����
	const static int MAX_OBJECTX = 256;							// X�t�@�C���I�u�W�F�N�g�̍ő��
	const static int NUM_MATCOLOR = 20;							// �}�e���A���̐�

	void BindFileName(const char aPath[MAX_SENTENCE]);			// �t�@�C���p�X�ݒ菈��

	void SetModelSize();										// ���f���̃T�C�Y�ݒ�
	D3DXVECTOR3 GetModelSize();									// ���f���̃T�C�Y�擾

	D3DXVECTOR3 GetMinVtx();									// ���f���̒��_�̍ŏ��l�擾		
	D3DXVECTOR3 GetMaxVtx();									// ���f���̒��_�̍ő�l�擾

	void SetScale(D3DXVECTOR3 scale);							// �X�P�[���ݒ�
	D3DXVECTOR3 GetScale();										// �X�P�[���擾

	void SetColor(D3DXCOLOR col);								// �}�e���A���F�ݒ�

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							// ���_�o�b�t�@�̃|�C���^
	LPD3DXMESH m_pMesh;											// ���b�V���̃|�C���^
	LPD3DXBUFFER m_pBuffMat;									// �}�e���A���̃|�C���^
	DWORD m_dwNumMat;											// �}�e���A���̐�
	LPDIRECT3DTEXTURE9* m_pTexture;								// �e�N�X�`���̃|�C���^
	char m_cFileName[MAX_SENTENCE];								// �t�@�C���p�X
	int m_nNumVtx;												// ���_�o�b�t�@��
	DWORD m_sizeFVF;											// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* m_pVtxBuffer;											// ���_�o�b�t�@�̃|�C���^

	D3DXVECTOR3 m_Pos;											// �ʒu
	D3DXVECTOR3 m_PosOld;										// 1�O�̈ʒu
	D3DXVECTOR3 m_Scale;										// �T�C�Y

	D3DXVECTOR3 m_Rot;											// ����
	D3DXMATRIX m_mtxWorld;										// ���[���h�}�g���b�N�X

	LPDIRECT3DDEVICE9 m_pDevice;								// �f�o�C�X�̃|�C���^

	D3DXVECTOR3 m_MinVtx;										// ���_�̍ŏ��l
	D3DXVECTOR3 m_MaxVtx;										// ���_�̍ő�l
	D3DXVECTOR3 m_Size;											// ���f���̃T�C�Y

	D3DCOLORVALUE m_FormalDiffuse[MAX_OBJECTX];					// �}�e���A���̐F����(�����l)
	D3DCOLORVALUE m_Diffuse[MAX_OBJECTX];						// �}�e���A���̐F����(�ύX��)

	static CObjectX* m_apObjectX[DRAW_PRIORITY][MAX_OBJECTX];	// X�t�@�C���I�u�W�F�N�g�̏��


};
#endif