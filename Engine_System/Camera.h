/////////////////////////////////////////////////////////
// 카메라 클래스
// 용책 참고
/////////////////////////////////////////////////////////
#ifndef _Camera_H_
#define _Camera_H_

#include <d3dx9math.h>
#include "../Engine_Math&Physics/Vector2D.h"

class CCamera{
public:
	enum CameraType {LANDOBJECT, AIRCRAFT, TWODEMENTION};

private:
	CameraType	m_eCameraType;
	D3DXVECTOR3 m_vRight;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3 m_vLook;
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vRot;

	float m_fVelocity;

	float m_fCameraRatio; // 카메라 비율 :: 배경 (float)(Width/Height)

public:
	CCamera();
	CCamera(CameraType _eCameraType);
	~CCamera();

	void strafe(float _fUnits);	// 왼쪽/오른쪽
	void fly(float _fUunits);		// 위쪽/아래쪽
	void walk(float _fUunits);		// 앞쪽/뒤쪽

	void pitch(float _fRadian);	// 우향 벡터로 회전
	void yaw(float _fRadian);		// 상향 벡터로 회전
	void roll(float _fRadian);		// 전방 벡터로 회전

	void GetViewMatrix(D3DXMATRIX* p_V);			// 현재 뷰포트 행렬 반환
	void SetCameraType(CameraType _eCameraType);	// 카메라 타입 지정
	void GetPosition(D3DXVECTOR3* _pvPos);
	void SetPosition(D3DXVECTOR3* _pvPos);
	D3DXVECTOR3 GetRotation(){return m_vRot;}
	void SetRotation(D3DXVECTOR3 _vRot){m_vRot = _vRot;}
	void SetRight(D3DXVECTOR3* _pvRight);
	void GetRight(D3DXVECTOR3* _pvRight);
	void SetUp(D3DXVECTOR3* _pvUp);
	void GetUp(D3DXVECTOR3* _pvUp);
	void SetLook(D3DXVECTOR3* _pvLook);
	void GetLook(D3DXVECTOR3* _pvLook);
	float GetRatio(){return m_fCameraRatio;}
	void SetRatio(float _fRatio){m_fCameraRatio = _fRatio;}
	Vector2D GetHeading();

	float GetVelocity(){return m_fVelocity;}
	void SetVelocity(float m_fVelocity){m_fVelocity = m_fVelocity;}
};

#endif