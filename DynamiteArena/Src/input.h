//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(input.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _INPUT_H_
#define _INPUT_H_

// include
#include "main.h"
#include "renderer.h"

// �}�N����`
#define MAX_KEY	(256)	// �L�[�̍ő吔

//******************************************
// ���͊��N���X(DirectInput�̊Ǘ�)�̒�`
//******************************************
class CInput
{
public:
	CInput();												// �R���X�g���N�^
	~CInput();												// �f�X�g���N�^
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	virtual void Uninit();									// �I������
	virtual void Update() = 0;								// �X�V����(���͒[�����ƂɕK�v)

	const static int MAX_PRESSTIME = 5;						// �ő�̒���������	
protected:
	static LPDIRECTINPUT8 m_pInput;							// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice;							// ���̓f�o�C�X�̃|�C���^
	int m_nPressTime;										// �L�[��{�^������������������
};

//******************************************
// �L�[�{�[�h�N���X�̒�`
//******************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();										// �R���X�g���N�^
	~CInputKeyboard();										// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;	// ����������
	void Uninit()override;									// �I������
	void Update()override;									// �X�V����

	bool GetPress(int nKey);								// �v���X���擾
	bool GetTrigger(int nKey);								// �g���K�[���
	bool GetRepeat(int nKey);								// ���s�[�g���

private:
	BYTE m_aKeyState[MAX_KEY];
	BYTE m_aKeyStateTrigger[MAX_KEY];
};

//******************************************
// �W���C�p�b�h�N���X�̒�`
//******************************************
class CInputJoypad : public CInput
{
public:
	// �W���C�p�b�h�̃{�^���z�u
	typedef enum
	{
		JOYKEY_UP = 0,											// �\���L�[(��)
		JOYKEY_DOWN,											// �\���L�[(��)
		JOYKEY_LEFT,											// �\���L�[(��)
		JOYKEY_RIGHT,											// �\���L�[(�E)
		JOYKEY_START,											// �X�^�[�g�{�^��
		JOYKEY_BACK,											// �o�b�N�{�^��
		JOYKEY_LEFT_THUMB,										// ���X�e�B�b�N(��������)
		JOYKEY_RIGHT_THUMB,										// �E�X�e�B�b�N(��������)
		JOYKEY_LEFT_SHOULDER,									// LB�{�^��
		JOYKEY_RIGHT_SHOULDER,									// RB�{�^��
		JOYKEY_AUTO,											// �I�[�g�{�^��
		JOYKEY_CLEAR,											// �N���A�{�^��
		JOYKEY_A,												// A�{�^��
		JOYKEY_B,												// B�{�^��
		JOYKEY_X,												// X�{�^��
		JOYKEY_Y,												// Y�{�^��
		JOYKEY_ZR,												// RT�{�^��
		JOYKEY_ZL,												// LT�{�^��
		JOYKEY_MAX
	}JOYKEY;

	CInputJoypad();												// �R���X�g���N�^
	~CInputJoypad();											// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;		// ����������
	void Uninit()override;										// �I������
	void Update()override;										// �X�V����

	bool GetPress(JOYKEY key);									// �v���X���擾
	bool GetTrigger(JOYKEY key);								// �g���K�[���擾
	bool GetRepeat(JOYKEY key);									// ���s�[�g���

	bool GetLeftTrigger();										// ���g���K�[�{�^��
	bool GetRightTrigger();										// �E�g���K�[�{�^��

	float GetLeftThumbX();										// ���X�e�B�b�N��X��
	float GetLeftThumbY();										// ���X�e�B�b�N��Y��
	float GetRightThumbX();										// �E�X�e�B�b�N��X��
	float GetRightThumbY();										// �E�X�e�B�b�N��Y�� 

private:
	XINPUT_STATE m_JoykeyState;									// �W���C�p�b�h�̃v���X���
	XINPUT_STATE m_JoykeyStateTrigger;							// �W���C�p�b�h�̃g���K�[���


};
#endif