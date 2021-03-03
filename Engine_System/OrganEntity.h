////////////////////////////////////////////////////////////////////////////////
// ��ü ����� ������ Entity ���� Ŭ���� 
////////////////////////////////////////////////////////////////////////////////
#ifndef _OrganEntity_H_
#define _OrganEntity_H_

#include "BasicEntity.h"
#include "Body.h"
#include "../Engine_Data Structures/Array.h"
#include "Attachment.h"

class COrganEntity : public CBasicEntity{
protected:
	CBody* m_pBody;

	// ���� �ʿ��� ���� ������ ��ü �����
	CArray<CAttachment*> m_Attachment;

	// Bound��
	ID3DXMesh* m_pBoundRadiusMesh;

private:
	// ��ü ��� ��ġ ���� ���� ����
	D3DXVECTOR3 m_vChainPos; // ��ġ
	D3DXVECTOR3 m_vChainSca;	// ������
	D3DXVECTOR3 m_vChainRot;	// ȸ��
	D3DXVECTOR3 m_vChainCen;	// ����

public:
	COrganEntity(int _nEntityType = -1);
	virtual ~COrganEntity();

	// OrganEntity ���� �Լ�
	ID3DXMesh*				GetBoundRadiusMesh(){return m_pBoundRadiusMesh;}

	virtual float	    GetRadius(){return m_fRadius*Average(m_pBody->GetPriSca()->x,m_pBody->GetPriSca()->y);}

	void							ResizeBoundRadius();
	virtual void			ResizeVertex(float _fWidth, float _fHeight);
	virtual void			ResizeObject(float _fVal);
	virtual void			ResizeObject(float _fWidth, float _fHeight);

	// ����ȭ �Լ�
	void  UniformOrganScaZero();
	void	UniformOrganSca(float _fSca);
	void	UniformOrganAlpha(float _fAlpha);
	void	UniformOrganColor(D3DXCOLOR _vColor);

	// ���� ���� �Լ�
	void RenderBoundMesh();
	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);
	virtual void Render(D3DXVECTOR3* _pvPos, D3DXVECTOR3* _pvSca, D3DXVECTOR3* _pvRot, D3DXVECTOR3* _pvCen){};
	virtual void RenderOrgan();

	// ��ũ��Ʈ�κ��� EntityData Load�Լ�
	void InitOrgan();
	void LoadEntityData(const char* _pstrName);

	// ü�� ���� �ʱ�ȭ �Լ�
	virtual void InitChainVector(){m_vChainPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);m_vChainSca = D3DXVECTOR3(1.0f, 1.0f, 1.0f);m_vChainRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);m_vChainCen = D3DXVECTOR3(0.0f, 0.0f, 0.0f);}

	// ü�� ���� �ٵ� ���� �Լ�
	virtual void BodySetting(){m_pBody->SettingOrgan(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());	}
	virtual void BodyOnlyPosSetting(){m_pBody->SettingOrgan(GetChainPos(), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f)); }

	// ü�� ���� Get�Լ�
	D3DXVECTOR3* GetChainPos(){return &m_vChainPos;}
	D3DXVECTOR3* GetChainSca(){return &m_vChainSca;}
	D3DXVECTOR3* GetChainRot(){return &m_vChainRot;}
	D3DXVECTOR3* GetChainCen(){return &m_vChainCen;}
	
	// �� Ŭ���� Set�Լ�
	void SetBody(CBody* _pBody){m_pBody = _pBody;}
	void SetAttachment(CAttachment* _pAttachment, int _nIndex){m_Attachment.Insert(_pAttachment, _nIndex); m_Attachment.IncreseCount();}
	
	// �� Ŭ���� Get�Լ�
	CBody* GetBody(){return m_pBody;}
	CArray<CAttachment*>* GetAttachmentArray();
	CAttachment* GetAttachment(int _nIndex);
	CAttachment* GetAttachmentFromType(int p_nType);
	int GetAttachmentIndex(int p_nType);

	// ��ü ��� ���� �Լ�
	void RotationZOrgan(D3DXVECTOR3* _pvRot, float _fScalar);
	void RotationYOrgan(D3DXVECTOR3* _pvRot, float _fScalar);
	void RotationXOrgan(D3DXVECTOR3* _pvRot, float _fScalar);
	void TranslationXOrgan(D3DXVECTOR3* _pvPos, float _fScalar);
	void TranslationYOrgan(D3DXVECTOR3* _pvPos, float _fScalar);
	void TranslationZOrgan(D3DXVECTOR3* _pvPos, float _fScalar);
	void TranslationCenXOrgan(D3DXVECTOR3* _pvCen, float _fScalar);
	void TranslationCenYOrgan(D3DXVECTOR3* _pvCen, float _fScalar);
	void TranslationCenZOrgan(D3DXVECTOR3* _pvCen, float _fScalar);
};

#endif