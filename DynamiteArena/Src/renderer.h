//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(randerer.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _RENDERER_H_
#define _RENDERER_H_

// include
#include "main.h"
#include "renderer.h"

// �����_���[�N���X�̒�`
class CRenderer
{
public:
	CRenderer();													// �R���X�g���N�^
	~CRenderer();													// �f�X�g���N�^
	HRESULT Init(HWND hWnd, BOOL bWindow);							// ����������
	void Uninit();													// �I������
	void Update();													// �X�V����
	void Draw();													// �`�揈��
	LPDIRECT3DDEVICE9 GetDevice();									// �f�o�C�X�̎擾

private:
	LPDIRECT3D9 m_pD3D;												// �I�u�W�F�N�g�̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;									// �f�o�C�X�̃|�C���^
};

#endif 
