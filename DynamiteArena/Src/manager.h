//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(manager.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _MANAGER_H_
#define _MANAGER_H_

// include
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "PlayerParam.h"
#include "GameManager.h"
#include "ItemManager.h"

// �}�l�[�W���[�N���X�̒�`
class CManager
{
public:
	// �V���O���g���C���X�^���X���擾����
	static CManager& GetInstance()
	{
		static CManager instance;
		return instance;
	}

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	// ����������
	void Uninit();												// �I������
	void Update();												// �X�V����
	void Draw();												// �`�揈��

	CRenderer* GetRenderer();									// �����_���[�擾����
	CInputKeyboard* GetKeyboard();								// �L�[�{�[�h�擾
	CInputJoypad* GetJoypad();									// �W���C�p�b�h�擾
	CCamera* GetCamera();										// �J�����̎擾����
	CLight* GetLight();											// ���C�g�̎擾����
	CParamManager* GetParamManager();							// �p�����[�^�[�Ǘ��N���X�̃|�C���^�擾
	CGameManager* GetGameManager();								// �Q�[���}�l�[�W���[�擾����
	CItemManager* GetItemManager();								// �A�C�e���}�l�[�W���[�N���X�̃|�C���^�擾

	void SetMode(CScene::MODE mode);							// ���[�h�ݒ菈��

	void SetGoal(bool bGoal);									// �S�[���t���O�ݒ菈��
	bool GetGoal();												// �S�[���t���O�擾����

private:
	CManager();													// �R���X�g���N�^
	~CManager();												// �f�X�g���N�^

	CManager(const CManager&) = delete;
	CManager& operator = (const CManager&) = delete;

	CRenderer* m_pRenderer;										// �����_���[�̃|�C���^
	CInputKeyboard* m_InputKeyboard;							// �L�[�{�[�h�̃|�C���^
	CInputJoypad* m_InputJoypad;								// �W���C�p�b�h�̃|�C���^
	CCamera* m_pCamera;											// �J�����̃|�C���^
	CLight* m_pLight;											// ���C�g�̃|�C���^	
	CScene* m_pScene;											// �V�[���̃|�C���^
	CParamManager* m_pParamManager;								// �p�����[�^�[�Ǘ��N���X�̃|�C���^		
	CGameManager* m_pGameManager;								// �Q�[���}�l�[�W���[�N���X�̃|�C���^
	CItemManager* m_pItemManager;								// �A�C�e���}�l�[�W���[�N���X�̃|�C���^

	bool m_bGoal;												// �S�[������p�t���O

};
#endif