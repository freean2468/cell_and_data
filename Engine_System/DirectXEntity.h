//////////////////////////////////////////////////////
// ���� ������Ʈ���� ���� �κ��� ��� �ִ� ���� Ŭ����
//////////////////////////////////////////////////////
#ifndef _DirectXEntity_H_
#define _DirectXEntity_H_

#include "BaseEntity.h"

class CDirectXEntity : public CBaseEntity{
protected:
	// �������̽� ���� ����
	IDirect3DDevice9*					m_pDevice;				// ��ġ �������̽� ������
	IDirect3DTexture9*					m_pTexture;				// ������Ʈ �ؽ�ó(�̹���) ������
	D3DMATERIAL9						m_Mtrl;						// ������Ʈ ���� ������
	IDirect3DVertexBuffer9*				m_pQuad;					// ���ؽ� ����
	IDirect3DIndexBuffer9*				m_pIndex;					// �ε��� ����

	// Object ��ġ ���� ����
	D3DXMATRIX m_mWorld;			// ���� ���

	D3DXVECTOR3 m_vPos;				// ��ġ ����
	D3DXVECTOR3 m_vRot;				// ȸ�� ����
	D3DXVECTOR3 m_vSca;				// ũ�� ����

	D3DXVECTOR3 m_vTransPos;	// ��ȯ�� ��ġ ����V

	D3DXMATRIXA16 m_mPos;			// ��ġ ��ȯ ���	
	D3DXMATRIXA16 m_mScale;		// ũ�� ��ȯ ���
	D3DXMATRIXA16 m_mRotation;// ȸ�� ��ȯ ���
	
	// Object ������ ���� ����
	RECT	m_TextureRect;			// �ؽ�ó �簢����	
	float m_fWidth, m_fHeight;
	float m_fWidthHalf, m_fHeightHalf;

	// Object �浹 ���� ����
	RECT	m_Rect;
	float	m_fRadius;

	/////////////////////���� ���� ������
	// ���� ����
	// �ִ��� true, �ּҶ�� false
	bool m_bAlphaState;

	bool m_bCycleRotX;
	bool m_bCycleRotY;
	bool m_bCycleRotZ;

public:
	CDirectXEntity(int _nEntityType);
	virtual ~CDirectXEntity();

	////////////////////////////////////////////////
	// �⺻ ���� �Լ�
	bool InitObject(IDirect3DDevice9* _pDevice, const char* _pstrTexFileName, int _nWidth, int _nHeight, float _fAlpha, int _nAction);

	virtual void ResizeObject(float _fVal);
	virtual void ResizeObject(float _fWidth, float _fHeight);

	virtual void ResizeVertex(float _fWidth, float _fHeight);

	virtual void Render();
	virtual void preRender();
	virtual void postRender();

	void TransformObject();

	D3DMATERIAL9* GetMtrl(){return &m_Mtrl;}

	void				 SetPos(Vector2D _vPos){m_vPos.x = (float)_vPos.x; m_vPos.y = (float)_vPos.y; m_vPos.z = 0.0f;}
	void				 SetPos(double _dX, double _dY, double _dZ){m_vPos.x = (float)_dX; m_vPos.y = (float)_dY; m_vPos.z = (float)_dZ;} 
	void				 SetPos(double _dX, double _dY){m_vPos.x = (float)_dX; m_vPos.y = (float)_dY; m_vPos.z = 0.0f;} 
	void				 SetPos(D3DXVECTOR3* _vPos){m_vPos = *(_vPos);} 
	Vector2D		 GetPos2D(){return Vector2D((double)m_vPos.x, (double)m_vPos.y);}
	D3DXVECTOR3* GetPos3D(){return &m_vPos;}

	Vector2D		 GetTransPos2D(){TransformObject(); return Vector2D((double)m_vTransPos.x, (double)m_vTransPos.y);}
	D3DXVECTOR3* GetTransPos3D(){TransformObject(); return &m_vTransPos;}

	D3DXVECTOR3* GetRot3D(){return &m_vRot;}
	void				 SetRot(D3DXVECTOR3* _vRot){m_vRot = *(_vRot);}
	void				 SetRotZ(float _fAngle){m_vRot.z = _fAngle;}
	void				 IncreaseRotZ(float _fFrequency){m_vRot.z += _fFrequency;}
	void				 DecreaseRotZ(float _fFrequency){m_vRot.z -= _fFrequency;}
	void				 CycleRotX(float _fMax, float _fFrequency);
	void				 CycleRotY(float _fMax, float _fFrequency);
	void				 CycleRotZ(float _fMax, float _fFrequency);

	void				 SetSca2D(float _fScale){m_vSca.x = _fScale; m_vSca.y = _fScale; m_vSca.z = 0.0f;}
	void				 SetSca(Vector2D _vScale){m_vSca.x = (float)m_vSca.x; m_vSca.y = (float)m_vSca.y; m_vSca.z = 0.0f;}
	void				 SetSca(double _dX, double _dY, double _dZ){m_vSca.x = (float)_dX; m_vSca.y = (float)_dY; m_vSca.z = (float)_dZ;} 
	void				 SetSca(double _dX, double _dY){m_vSca.x = (float)_dX; m_vSca.y = (float)_dY; m_vSca.z = 0.0f;} 
	void				 SetSca(D3DXVECTOR3* _vScale){m_vSca = *(_vScale);} 
	D3DXVECTOR3* GetSca3D(){return &m_vSca;}
	Vector2D		 GetSca2D(){return Vector2D(static_cast<double>(m_vSca.x),static_cast<double>(m_vSca.y));}
	float				 GetAveSca2D(){return (m_vSca.x + m_vSca.y) * 0.5f;}
	float				 GetAveSca3D(){return (m_vSca.x + m_vSca.y + m_vSca.z) / 3.0f;}
	void				 IncreaseSca2D(float m_fVal){m_vSca.x+=m_fVal;m_vSca.y+=m_fVal;}
	void				 DecreaseSca2D(float m_fVal){m_vSca.x-=m_fVal;m_vSca.y-=m_fVal;}

	virtual D3DXMATRIX CalMatWorld();
	D3DXMATRIX GetMatPos(){return m_mPos;}			// ��ġ ��ȯ ���	
	D3DXMATRIX GetMatSca(){return m_mScale;}		// ũ�� ��ȯ ���
	D3DXMATRIX GetMatRot(){return m_mRotation;} // ȸ�� ��ȯ ���
	D3DXMATRIX GetMatWorld(){return m_mWorld;}

	IDirect3DDevice9* GetpDevice(){return m_pDevice;}

	void	SetColor(D3DXCOLOR* _pColor){GetMtrl()->Diffuse.a = _pColor->a; GetMtrl()->Diffuse.r = _pColor->r; GetMtrl()->Diffuse.g = _pColor->g; GetMtrl()->Diffuse.b = _pColor->b;}
	void	IncreaseAlpha(float _fFrequency){GetMtrl()->Diffuse.a += _fFrequency;}
	void	DecreaseAlpha(float _fFrequency){GetMtrl()->Diffuse.a -= _fFrequency;}

	float GetAlpha(){return GetMtrl()->Diffuse.a;}
	void	SetAlpha(float _fAlpha){GetMtrl()->Diffuse.a = _fAlpha;}

	virtual float GetWidth(){return m_fWidth * m_vSca.x;}
	virtual float GetHeight(){return m_fHeight * m_vSca.y;}
	virtual float GetWidthHalf(){return GetWidth()*0.5f;}
	virtual float GetHeightHalf(){return GetHeight()*0.5f;}

	virtual float	GetRadius(){return m_fRadius * GetAveSca2D();}
	void SetRadius(float _fRadius){m_fRadius = _fRadius;}

	virtual RECT*	GetRect(){m_Rect.bottom = (LONG)GetBottom(); m_Rect.top = (LONG)GetTop(); m_Rect.right = (LONG)GetRight(); m_Rect.left = (LONG)GetLeft(); return &m_Rect;}
	virtual RECT*	GetAbsoluteRect(){m_Rect.bottom = (LONG)-GetHeightHalf(); m_Rect.top = (LONG)GetHeightHalf(); m_Rect.right = (LONG)GetWidthHalf(); m_Rect.left = (LONG)-GetWidthHalf(); return &m_Rect;}

	// ��ü ����� Bound������ �����Լ��� ��ӹ޾� �����Ͽ� ���
	virtual float GetLeft(){return m_vPos.x - GetWidthHalf();}
	virtual float GetRight(){return m_vPos.x + GetWidthHalf();}
	virtual float GetTop(){return m_vPos.y + GetHeightHalf();}
	virtual float GetBottom(){return m_vPos.y - GetHeightHalf();}

	// ���� ���� ���� �Լ���
	bool GetAlphaState(){return m_bAlphaState;}
	void SetAlphaState(bool _bState){m_bAlphaState = _bState;}

	void BlinkAlpha(float _fMin, float _fMax, float _fFrequency);
};

#endif