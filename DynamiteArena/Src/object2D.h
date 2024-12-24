//*******************************************************************************************************************************************
//
// �_�C�i�}�C�g�A���[�i(object2D.h)
// Author : Kasai Keisuke
//
//*******************************************************************************************************************************************

#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

// include
#include "renderer.h"
#include "object.h"

// 2D�|���S���Ǘ��N���X
class CObject2D : public CObject
{
public:
	// �|���S���̎�ނ̗񋓌^
	typedef enum
	{
		POLYGON_NONE = 0,
		POLYGON_NORMAL,		// ���ʂ̃|���S��
		POLYGON_NUMBER,		// �����������|���S��
		POLYGON_BLINK,		// �_�ł�����|���S��
	}POLYGONTYPE;

	CObject2D(int nPriority = 3);											// �R���X�g���N�^
	~CObject2D()override;													// �f�X�g���N�^
	HRESULT Init()override;													// ����������
	void Uninit()override;													// �I������
	void Update()override;													// �X�V����
	void Draw()override;													// �`�揈��

	static CObject2D* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// ��������

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);

	void SetObject2D(D3DXVECTOR3 pos,D3DXCOLOR col, float fWidth, float fHeight);			// ���ݒ菈��

	void SetPolygonType(POLYGONTYPE type);									// �|���S���̎�ސݒ�

	void SetVtxAnimPolygon(float fWidth, float fHeight, float TexPos);		// ���_�ݒ菈��

	void SetColor(D3DXCOLOR col);											// �F�ݒ菈��
	D3DXCOLOR GetColor();													// �F�擾����

	const static int MAX_OBJECT = 128;										// �I�u�W�F�N�g�ő吔

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;										// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;											// �e�N�X�`���̃|�C���^
	LPDIRECT3DDEVICE9 m_pDevice;											// �f�o�C�X�̃|�C���^

	D3DXVECTOR3 m_Pos;														// �ʒu
	D3DXCOLOR m_Col;

	float m_fWidth;															// ��
	float m_fHeight;														// ����

	static CObject2D* m_apObject2D[MAX_OBJECT];								// 2D�|���S���̐�

	POLYGONTYPE m_Type;														// �|���S���̎��
};
#endif