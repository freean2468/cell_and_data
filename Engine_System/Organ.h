////////////////////////////////////////////////////////////////////////////////
// ��ü��� ���� ���� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Organ_H_
#define _Organ_H_

#include "BasicEntity.h"

class COrgan : public CBasicEntity{
protected:
	// ��� ������ Transform ����
	D3DXVECTOR3 m_vPrimitivePos;
	D3DXVECTOR3 m_vPrimitiveSca;
	D3DXVECTOR3 m_vPrimitiveRot;

	// ���� ����
	D3DXVECTOR3 m_vPrimitiveCen;

	// �浹 ������ ���� ������
	RECT	m_Rect;
	float m_fAveRadius;

	// ���� ����
	// �ִ��� true, �ּҶ�� false
	bool m_bAngleState;

	// �̵� ����
	// �ִ��� true, �ּҶ�� false
	bool m_bMoveState;

	// ������ ����
	// �ִ��� true, �ּҶ�� false
	bool m_bScaleState;

	// �þ� ��� ����
	bool m_bShearUse;
	int _nShearType;	// ������
	bool m_bShearState; // �þ� ����, �ִ��� true, �ּҶ�� false
	D3DXVECTOR3 m_vOldPos;
	float m_fShearDegree; // �þ ���� ����

	// ���ӵ�
	float m_fVelocity;

	// �Լ� ���뼺�� ���� ����
	// For RoundTrip
	float m_fTraceX;
	float m_fTraceY;

	// For BigAndSmall
	float m_fBaseScaX;
	float m_fBaseScaY;

	// For BigAndSmallAlternately
	float m_fBaseAlternateSca;

public:
	COrgan();
	COrgan(D3DXVECTOR3 _vPos, D3DXVECTOR3 _vSca, D3DXVECTOR3 _vRot, D3DXVECTOR3 _vCen);
	virtual ~COrgan();

	void Shear(D3DXVECTOR3* _vPos, D3DXMATRIXA16* _pmX, D3DXMATRIXA16* _pmY, D3DXMATRIXA16* _pmZ);
	void Shear(D3DXMATRIXA16* _pmMatrix);

	virtual void SettingOrgan(D3DXVECTOR3* _pvChainPos, D3DXVECTOR3* _pvChainSca, D3DXVECTOR3* _pvChainRot, D3DXVECTOR3* _pvChainCen);
	virtual void SettingOrgan(D3DXVECTOR3* _pvChainPos, D3DXVECTOR3* _pvChainCen);
	virtual void SettingJointOrgan(D3DXVECTOR3* _pvChainRot, D3DXVECTOR3* _pvChainCen);

	// Get �Լ�	
	// �����̴� �� ������_���� �������� �Ѵ�.
	D3DXVECTOR3* GetPriPos(){return &m_vPrimitivePos;}
	D3DXVECTOR3* GetPriSca(){return &m_vPrimitiveSca;}
	D3DXVECTOR3* GetPriRot(){return &m_vPrimitiveRot;}
	D3DXVECTOR3* GetPriCen(){return &m_vPrimitiveCen;}

	virtual RECT*	GetRect(){m_Rect.bottom = (LONG)GetBottom(); m_Rect.top = (LONG)GetTop(); m_Rect.right = (LONG)GetRight(); m_Rect.left = (LONG)GetLeft(); return &m_Rect;}
	virtual RECT*	GetAbsoluteRect(){m_Rect.bottom = (LONG)-GetHeightHalf(); m_Rect.top = (LONG)GetHeightHalf(); m_Rect.right = (LONG)GetWidthHalf(); m_Rect.left = (LONG)-GetWidthHalf(); return &m_Rect;}

	virtual float GetWidth(){return m_fWidth * m_vPrimitiveSca.x;}
	virtual float GetHeight(){return m_fHeight * m_vPrimitiveSca.y;}
	virtual float GetWidthHalf(){return GetWidth() * 0.5f;}
	virtual float GetHeightHalf(){return GetHeight() * 0.5f ;}
	float GetAveRadius(){return (GetWidthHalf() + GetHeightHalf()) * 0.5f;}

	float GetShearDegree(){return m_fShearDegree;}
	void SetShearDegree(float _fDegree){m_fShearDegree = _fDegree;}
	void SetShearUse(bool _bUse){m_bShearUse = _bUse;}
	bool GetShearUse(){return m_bShearUse;}

	// Set �Լ�
	// �����̴� �� ������_���� �������� �Ѵ�.
	virtual void SetPriPos(D3DXVECTOR3* _pvVec){m_vPrimitivePos.x = _pvVec->x; m_vPrimitivePos.y = _pvVec->y; m_vPrimitivePos.z = _pvVec->z;}
	virtual void SetPriSca(D3DXVECTOR3* _pvVec){m_vPrimitiveSca.x = _pvVec->x; m_vPrimitiveSca.y = _pvVec->y; m_vPrimitiveSca.z = _pvVec->z;}
	virtual void SetPriRot(D3DXVECTOR3* _pvVec){m_vPrimitiveRot.x = _pvVec->x; m_vPrimitiveRot.y = _pvVec->y; m_vPrimitiveRot.z = _pvVec->z;}
	virtual void SetPriCen(D3DXVECTOR3* _pvVec){m_vPrimitiveCen.x = _pvVec->x; m_vPrimitiveCen.y = _pvVec->y; m_vPrimitiveCen.z = _pvVec->z;}

	// ��ü ����� Bound������ �����Լ��� ��ӹ޾� �����Ͽ� ���
	virtual float GetLeft(){return GetPriPos()->x - GetWidthHalf();}
	virtual float GetRight(){return GetPriPos()->x + GetWidthHalf();}
	virtual float GetTop(){return GetPriPos()->y + GetHeightHalf();}
	virtual float GetBottom(){return GetPriPos()->y - GetHeightHalf();}

	bool GetAngleState(){return m_bAngleState;}
	void SetAngleState(bool _bState){m_bAngleState = _bState;}
	bool GetMoveState(){return m_bMoveState;}
	void SetMoveState(bool _bState){m_bMoveState = _bState;}
	bool GetScaleState(){return m_bScaleState;}
	void SetScaState(bool _bState){m_bScaleState = _bState;}
	void SetShearState(bool _bState){m_bShearState = _bState;}
	bool GetShearState(){return m_bShearState;}

	virtual void preRender(D3DXVECTOR3* _pvRot);
	virtual void Render(D3DXVECTOR3* _pvPos, D3DXVECTOR3* _pvSca, D3DXVECTOR3* _pvRot, D3DXVECTOR3* _pvCen);
	virtual void RenderApplyScale(D3DXVECTOR3* _pvPos, D3DXVECTOR3* _pvSca, D3DXVECTOR3* _pvCen);

	// ���� Ʈ������ �Լ�
	virtual void	UniformSca(float _fSca){GetPriSca()->x = _fSca; GetPriSca()->y = _fSca; GetPriSca()->z = _fSca;}
	
	void ScaleZero(){GetPriSca()->x = 0.0f; GetPriSca()->y = 0.0f; GetPriSca()->z = 0.0f;}
	virtual void	IncreaseSca(float _fFrequency){GetPriSca()->x += _fFrequency; GetPriSca()->y += _fFrequency; GetPriSca()->z += _fFrequency;}
	virtual void	DecreaseSca(float _fFrequency){GetPriSca()->x -= _fFrequency; GetPriSca()->y -= _fFrequency; GetPriSca()->z -= _fFrequency;}

	void BigAndSmall(float _fMaxSca, float _fMinSca, float _fFrequency);
	void BigAndSmallX(float _fMaxSca, float _fMinSca, float _fFrequency);
	int	 BigAndSmallY(float _fMaxSca, float _fMinSca, float _fFrequency);
	void BigAndSmallXYAlternately(float _fMaxSca, float _fFrequency);
	void RoundTripX(float _fDistance, float _fFrequency);
	void RoundTripY(float _fDistance, float _fFrequency);
	
	void RotZ(float _fFrequency){this->GetPriRot()->z += _fFrequency;}
};

#endif