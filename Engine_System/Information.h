//////////////////////////////////////////////////////
// ���� Information ���� & ����� ����ϴ� Ŭ����
//////////////////////////////////////////////////////
#ifndef _Information_H_
#define _Information_H_

#include <Windows.h>
#include "../Engine_Math&Physics/Vector2D.h"

class CInformation{
public:
	typedef enum Space {DOWN = 0, UP} SPACE;
	SPACE m_eSpace;

private:	
	/////////////////////////////////////
	// FPS ���� ����
	DWORD m_dwFrameCntForNon;
	float m_fTimeElapsedForNon;
	DWORD m_dwTimeElapsedForAdjusted;
	float m_fTimeElapsedForAdjusted;
	float m_fFPS;				// Engine�� ���� �������� ���� ���� Frame
	float m_fFPSAdjusted;		// Engine�� ���� ������ Frame
	char m_FPSString[30];
	char m_FPSAdjustedString[30];
	RECT m_Rect;

	/////////////////////////////////////
	// ���콺 ���� ����
	char m_crdString[60];
	Vector2D m_vAdjusted;
	Vector2D m_vAbsoluted;

	/////////////////////////////////////
	// ī�޶� ���� ����
	char m_cameraString[60];
	D3DXVECTOR3 m_vNowPos;
	
	char m_distanceString[30];
	D3DXVECTOR3 m_vDisPos;
	D3DXVECTOR3 m_vFirstPos;
	D3DXVECTOR3 m_vLastPos;

public:
	CInformation();
	~CInformation();

	////////////////////////////////////
	// ���� ���� ��� �Լ�
	void CalcInformation(float _fTimeDelta);
	void FPSCalculation(float _fTimeDelta);						 // ������ FPS ���
	void FPSAdjustedCalculation(float _fTimeDelta);				 // Engine�� ���� ������ FPS�� ���

	// FPS ����
	float GetFPSofOrgin(){return m_fFPS;}
	
	////////////////////////////////////
	// ���콺 ���� �Լ�
	Vector2D GetAdjusted(){return m_vAdjusted;}
	void SetAdjustedX(double _dX){m_vAdjusted.x = _dX;}
	void SetAdjustedY(double _dY){m_vAdjusted.y = _dY;}
	double GetAdjustedX(){return m_vAdjusted.x;}
	double GetAdjustedY(){return m_vAdjusted.y;}
	void SetAbsolutedX(double _dX){m_vAbsoluted.x = _dX;}
	void SetAbsolutedY(double _dY){m_vAbsoluted.y = _dY;}
	double GetAbsolutedX(){return m_vAbsoluted.x;}
	double GetAbsolutedY(){return m_vAbsoluted.y;}

	////////////////////////////////////
	// ī�޶� ���� �Լ�
	void SetCameraPos(D3DXVECTOR3* _pvPos){m_vNowPos = *_pvPos;}
	D3DXVECTOR3* GetCameraPos(){return &m_vNowPos;}
	void CoordinatesCalculation();	// �������̽� ����

	////////////////////////////////////
	// ���� ���� ��� �Լ�
	void DrawInformation(ID3DXFont* _pFont, ID3DXSprite* _pSprite);
};

#endif