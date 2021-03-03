////////////////////////////////////////////////////////////////////////////////
// 신체조직 외의 유동적인 생명력을 부여하기 위한 부속품 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Attachment_H_
#define _Attachment_H_

#include "Organ.h"
#include "Body.h"

class CAttachment : public COrgan{
private:
	CBody* m_pBody;
	int m_nAttType;

public:
	CAttachment():COrgan(){}
	CAttachment(D3DXVECTOR3 _vPos, D3DXVECTOR3 _vSca, D3DXVECTOR3 _vRot, D3DXVECTOR3 _vCen, int _nAttType);
	CAttachment(CBody* _pBody, D3DXVECTOR3 _vPos, D3DXVECTOR3 _vSca, D3DXVECTOR3 _vRot, D3DXVECTOR3 _vCen, int _nAttType);
	~CAttachment();

	virtual void Update(){}
	virtual bool HandleMessage(const Telegram& _rMsg){return false;}

	virtual float GetLeft(){return m_pBody->GetPriPos()->x + GetPriPos()->x - GetWidthHalf();}
	virtual float GetRight(){return m_pBody->GetPriPos()->x + GetPriPos()->x + GetWidthHalf();}
	virtual float GetTop(){return m_pBody->GetPriPos()->y + GetPriPos()->y + GetHeightHalf();}
	virtual float GetBottom(){return m_pBody->GetPriPos()->y + GetPriPos()->y - GetHeightHalf();}

	void RelationshipScaAndPos(D3DXVECTOR3* _pvVec);
	void RelationshipScaAndPos(float _fX, float _fY, float _fZ);
	void RelationshipScaAndPos(float _fVal);

	virtual void SetPriSca(D3DXVECTOR3* _pvVec);

	virtual void	UniformSca(float _fSca);

	void	NoneRelateIncreaseSca(float _fFrequncy);
	void	NoneRelateDecreaseSca(float _fFrequncy);
	virtual void	IncreaseSca(float _fFrequncy);
	virtual void	DecreaseSca(float _fFrequncy);

	CBody* GetBody(){return m_pBody;}

	int GetAttType(){return m_nAttType;}
};

#endif