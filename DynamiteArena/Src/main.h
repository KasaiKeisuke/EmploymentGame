//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(main.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _MAIN_H_
#define _MAIN_H_

// include
#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"																// ���͏����ɕK�v
#include "Xinput.h"																// �W���C�p�b�h�����ɕK�v

// ���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")													// �`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")												// [d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")												// DirectX�R���|�[�l���g
#pragma comment(lib,"dinput8.lib")												// ���͏����ɕK�v
#pragma comment(lib,"xinput.lib")												// �W���C�p�b�h�����ɕK�v
// �}�N����`
#define CLASS_NAME	"windowClass"												// �E�B���h�E�N���X�̖��O
#define WINDOW_NAME	"�_�C�i�}�C�g�A���[�i"												// �E�B���h�E�̖��O(�L���v�V�����ɕ\��)
#define SCREEN_WIDTH	(1920)													// �E�B���h�E�̕�
#define SCREEN_HEIGHT	(1080)													// �E�B���h�E�̍���
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)			// 2D�̒��_�t�H�[�}�b�g(���_���W | ���_�J���[)
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 3D�̒��_�t�H�[�}�b�g(���_���W|�@��)

// ���_���[2D]�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��W��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_2D;

// ���_���W(3D)�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_3D;

#endif