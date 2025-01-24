//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(caveat.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _CAVEAT_H_
#define _CAVEAT_H_

// include 
#include "object3D.h"

// �x���\��UI�N���X�̒�`
class CCaveat : public CObject3D
{
public:
	CCaveat(int nPriority = 4);																// �R���X�g���N�^
	~CCaveat()override;																		// �f�X�g���N�^
	HRESULT Init()override;																	// ����������
	void Uninit()override;																	// �I������
	void Update()override;																	// �X�V����
	void Draw()override;																	// �`�揈��
	static CCaveat* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fDepth);		// ��������

	static HRESULT Load();																	// �e�N�X�`�����[�h
	static void UnLoad();																	// �e�N�X�`���A�����[�h

	static const int DRAW_COUNT = 120;														// UI�̕\������
private:
	void Death();																			// ���S����

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;												// �e�N�X�`��

	int m_nCnt;																				// UI�\������
	bool m_bDeath;																			// �\������Ă��邩�ǂ���
	bool m_bDelete;																			// �`�悳���邩�ǂ���
};
#endif