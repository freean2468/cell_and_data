////////////////////////////////////////////////////////////////////////////////
// 신체 기관을 소유한 Entity 구현 클래스 
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

	// 따로 필요한 몸을 구성한 신체 기관들
	CArray<CAttachment*> m_Attachment;

	// Bound구
	ID3DXMesh* m_pBoundRadiusMesh;

private:
	// 신체 기관 위치 설정 벡터 변수
	D3DXVECTOR3 m_vChainPos; // 위치
	D3DXVECTOR3 m_vChainSca;	// 스케일
	D3DXVECTOR3 m_vChainRot;	// 회전
	D3DXVECTOR3 m_vChainCen;	// 중점

public:
	COrganEntity(int _nEntityType = -1);
	virtual ~COrganEntity();

	// OrganEntity 제공 함수
	ID3DXMesh*				GetBoundRadiusMesh(){return m_pBoundRadiusMesh;}

	virtual float	    GetRadius(){return m_fRadius*Average(m_pBody->GetPriSca()->x,m_pBody->GetPriSca()->y);}

	void							ResizeBoundRadius();
	virtual void			ResizeVertex(float _fWidth, float _fHeight);
	virtual void			ResizeObject(float _fVal);
	virtual void			ResizeObject(float _fWidth, float _fHeight);

	// 균일화 함수
	void  UniformOrganScaZero();
	void	UniformOrganSca(float _fSca);
	void	UniformOrganAlpha(float _fAlpha);
	void	UniformOrganColor(D3DXCOLOR _vColor);

	// 렌더 관련 함수
	void RenderBoundMesh();
	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);
	virtual void Render(D3DXVECTOR3* _pvPos, D3DXVECTOR3* _pvSca, D3DXVECTOR3* _pvRot, D3DXVECTOR3* _pvCen){};
	virtual void RenderOrgan();

	// 스크립트로부터 EntityData Load함수
	void InitOrgan();
	void LoadEntityData(const char* _pstrName);

	// 체인 벡터 초기화 함수
	virtual void InitChainVector(){m_vChainPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);m_vChainSca = D3DXVECTOR3(1.0f, 1.0f, 1.0f);m_vChainRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);m_vChainCen = D3DXVECTOR3(0.0f, 0.0f, 0.0f);}

	// 체인 벡터 바디 셋팅 함수
	virtual void BodySetting(){m_pBody->SettingOrgan(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());	}
	virtual void BodyOnlyPosSetting(){m_pBody->SettingOrgan(GetChainPos(), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f)); }

	// 체인 벡터 Get함수
	D3DXVECTOR3* GetChainPos(){return &m_vChainPos;}
	D3DXVECTOR3* GetChainSca(){return &m_vChainSca;}
	D3DXVECTOR3* GetChainRot(){return &m_vChainRot;}
	D3DXVECTOR3* GetChainCen(){return &m_vChainCen;}
	
	// 랩 클래스 Set함수
	void SetBody(CBody* _pBody){m_pBody = _pBody;}
	void SetAttachment(CAttachment* _pAttachment, int _nIndex){m_Attachment.Insert(_pAttachment, _nIndex); m_Attachment.IncreseCount();}
	
	// 랩 클래스 Get함수
	CBody* GetBody(){return m_pBody;}
	CArray<CAttachment*>* GetAttachmentArray();
	CAttachment* GetAttachment(int _nIndex);
	CAttachment* GetAttachmentFromType(int p_nType);
	int GetAttachmentIndex(int p_nType);

	// 신체 기관 변형 함수
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