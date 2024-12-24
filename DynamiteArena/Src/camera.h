//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(camera.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _CAMERA_H_
#define _CAMERA_H_

// include
#include "main.h"
#include "input.h"

// �J�����N���X�̒�`
class CCamera
{
public:
	CCamera();												// �R���X�g���N�^
	~CCamera();												// �f�X�g���N�^
	HRESULT Init();											// ����������
	void Uninit();											// �I������
	void Update();											// �X�V����
	void SetCamera();										// �J�����ݒ菈��

	void FollowCamera(D3DXVECTOR3 pos);						// �J�����Ǐ]����									

	void SetRot(D3DXVECTOR3 rot);							// �J�����̌����ݒ菈��
	D3DXVECTOR3 GetRot();									// �J�����̌����擾����

	void SetPosV(D3DXVECTOR3 rot);							// �J�����̎��_�ݒ�
	D3DXVECTOR3 GetPosV();									// �J�����̎��_�擾

	void SetPosR(D3DXVECTOR3 rot);							// �J�����̒����_�ݒ�
	D3DXVECTOR3 GetPosR();									// �J�����̒����_�擾

	void SetShake(int nCnt, float fShake);					// �J�����h�炵����
private:
	D3DXVECTOR3 m_PosV;										// �J�����̎��_
	D3DXVECTOR3 m_PosR;										// �J�����̒����_
	D3DXVECTOR3 m_VecU;										// ������x�N�g��
	D3DXVECTOR3 m_Rot;										// �J�����̌���

	D3DXMATRIX m_mtxProjection;								// �v���W�F�N�V�����s��
	D3DXMATRIX m_MtxView;									// �r���[�s��
	
	LPDIRECT3DDEVICE9 m_pDevice;							// �f�o�C�X�̃|�C���^

	CInputKeyboard* m_InputKeyboard;						// �L�[�{�[�h�̃|�C���^
	CInputJoypad* m_InputJoypad;							// �W���C�p�b�h�̃|�C���^

	int m_nCnt;												// �h�炷�t���[��
	float m_fShake;											// �h�炷��
};

// �ÓI�����o�ϐ�
static const float CameraLength = 100.0f;						// �J�����̎��_���璍���_�܂ł̋���
static const float CAMERA_HEIGHT = 200.0f;						// �J�����̎��_�̍���

#endif