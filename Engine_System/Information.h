//////////////////////////////////////////////////////
// 각종 Information 관리 & 출력을 담당하는 클래스
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
	// FPS 관련 변수
	DWORD m_dwFrameCntForNon;
	float m_fTimeElapsedForNon;
	DWORD m_dwTimeElapsedForAdjusted;
	float m_fTimeElapsedForAdjusted;
	float m_fFPS;				// Engine에 의해 조정되지 않은 실제 Frame
	float m_fFPSAdjusted;		// Engine에 의해 조정된 Frame
	char m_FPSString[30];
	char m_FPSAdjustedString[30];
	RECT m_Rect;

	/////////////////////////////////////
	// 마우스 관련 변수
	char m_crdString[60];
	Vector2D m_vAdjusted;
	Vector2D m_vAbsoluted;

	/////////////////////////////////////
	// 카메라 관련 변수
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
	// 각종 정보 계산 함수
	void CalcInformation(float _fTimeDelta);
	void FPSCalculation(float _fTimeDelta);						 // 본래의 FPS 계산
	void FPSAdjustedCalculation(float _fTimeDelta);				 // Engine에 의해 조정된 FPS를 계산

	// FPS 관련
	float GetFPSofOrgin(){return m_fFPS;}
	
	////////////////////////////////////
	// 마우스 관련 함수
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
	// 카메라 관련 함수
	void SetCameraPos(D3DXVECTOR3* _pvPos){m_vNowPos = *_pvPos;}
	D3DXVECTOR3* GetCameraPos(){return &m_vNowPos;}
	void CoordinatesCalculation();	// 인터페이스 제공

	////////////////////////////////////
	// 각종 정보 출력 함수
	void DrawInformation(ID3DXFont* _pFont, ID3DXSprite* _pSprite);
};

#endif