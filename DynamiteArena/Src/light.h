//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(light.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _LIGHT_H_
#define _LIGHT_H_

// include
#include "main.h"
#include "camera.h"

// ���C�g�N���X�̒�`
class CLight
{
public:
	CLight();						// �R���X�g���N�^
	~CLight();						// �f�X�g���N�^
	HRESULT Init();					// ����������
	void Uninit();					// �I������
	void Update();					// �X�V����

	const static int MAX_LIGHT = 4;	// ���C�g�̍ő吔
private:
	CCamera* m_pCamera;				// �J�����̃|�C���^
	D3DLIGHT9 m_aLight[MAX_LIGHT];	// ���C�g�̏��

	LPDIRECT3DDEVICE9 m_pDevice;	// �f�o�C�X�̃|�C���^
};
#endif