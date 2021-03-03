#include "Camera.h"
#include "SystemDefines.h"
#include "../Engine_Math&Physics/Transformation.h"

CCamera::CCamera() : m_eCameraType(AIRCRAFT),
					m_vPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
					m_vRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
					m_vRight(D3DXVECTOR3(1.0f, 0.0f, 0.0f)),
					m_vUp(D3DXVECTOR3(0.0f, 1.0f, 0.0f)),
					m_vLook(D3DXVECTOR3(0.0f, 0.0f, 1.0f)),
					m_fCameraRatio((float)((float)(SYSTEMWIDTH)/(float)(SYSTEMHEIGHT)))
{
}

CCamera::CCamera(CameraType m_eCameraType) :	m_eCameraType(m_eCameraType),
												m_vRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
												m_vRight(D3DXVECTOR3(1.0f, 0.0f, 0.0f)),
												m_vUp(D3DXVECTOR3(0.0f, 1.0f, 0.0f)),
												m_vLook(D3DXVECTOR3(0.0f, 0.0f, 1.0f))
{
	if(m_eCameraType == TWODEMENTION)
		m_vPos   = D3DXVECTOR3(0.0f, 0.0f, -700.0f);
	else
		m_vPos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

CCamera::~CCamera(){

}

Vector2D CCamera::GetHeading(){
	Vector2D t_vHeading(0,1);

	Vec2DRotateAroundOrigin(t_vHeading, m_vRot.z);

	return t_vHeading;
}

void CCamera::GetPosition(D3DXVECTOR3* _pvPos){
	*_pvPos = m_vPos;
}

void CCamera::SetPosition(D3DXVECTOR3* _pvPos){
	m_vPos = *_pvPos;
}

void CCamera::SetRight(D3DXVECTOR3* _pvRight){
	m_vRight = *_pvRight;
}

void CCamera::GetRight(D3DXVECTOR3* _pvRight){
	*_pvRight = m_vRight;
}

void CCamera::SetUp(D3DXVECTOR3* _pvUp){
	m_vUp = *_pvUp;
}

void CCamera::GetUp(D3DXVECTOR3* _pvUp){
	*_pvUp = m_vUp;
}

void CCamera::SetLook(D3DXVECTOR3* _pvLook){
	m_vLook = *_pvLook;
}

void CCamera::GetLook(D3DXVECTOR3* _pvLook){
	*_pvLook = m_vLook;
}

void CCamera::GetViewMatrix(D3DXMATRIX* p_V){
	// 카메라의 축이 서로 직각이 되도록 한다.
	D3DXVec3Normalize(&m_vLook, &m_vLook);
	
	D3DXVec3Cross(&m_vUp, &m_vLook, &m_vRight);
	D3DXVec3Normalize(&m_vUp, &m_vUp);

	D3DXVec3Cross(&m_vRight, &m_vUp, &m_vLook);
	D3DXVec3Normalize(&m_vRight, &m_vRight);

	// 뷰 행렬을 구성한다.
	float x = -D3DXVec3Dot(&m_vRight, &m_vPos);
	float y = -D3DXVec3Dot(&m_vUp, &m_vPos);
	float z = -D3DXVec3Dot(&m_vLook, &m_vPos);

	(*p_V)(0,0) = m_vRight.x;
	(*p_V)(0,1) = m_vUp.x;
	(*p_V)(0,2) = m_vLook.x;
	(*p_V)(0,3) = 0.0f;

	(*p_V)(1,0) = m_vRight.y;
	(*p_V)(1,1) = m_vUp.y;
	(*p_V)(1,2) = m_vLook.y;
	(*p_V)(1,3) = 0.0f;

	(*p_V)(2,0) = m_vRight.z;
	(*p_V)(2,1) = m_vUp.z;
	(*p_V)(2,2) = m_vLook.z;
	(*p_V)(2,3) = 0.0f;

	(*p_V)(3,0) = x;
	(*p_V)(3,1) = y;
	(*p_V)(3,2) = z;
	(*p_V)(3,3) = 1.0f;
}

void CCamera::pitch(float _fRadian){
	D3DXMATRIX T;

	// TWODEMENTION라면 카메라 회전 기능을 사용할 수 없다.
	if(m_eCameraType == TWODEMENTION)
		return;

	D3DXMatrixRotationAxis(&T, &m_vRight, _fRadian);

	// m_vRight를 기준으로 m_vUp과 m_vLook을 회전한다.
	D3DXVec3TransformCoord(&m_vUp, &m_vUp, &T);
	D3DXVec3TransformCoord(&m_vLook, &m_vLook, &T);
}

void CCamera::yaw(float _fRadian){
	D3DXMATRIX T;

	// TWODEMENTION라면 카메라 회전 기능을 사용할 수 없다.
	if(m_eCameraType == TWODEMENTION)
		return;

	// 지상의 물체에 대해서는 월드 y(0, 1, 0)를 기준으로 회전한다.
	if(m_eCameraType == LANDOBJECT)
		D3DXMatrixRotationY(&T, _fRadian);

	// 비행 물체에 대해서는 원래의 상향 벡터로 회전한다.
	if(m_eCameraType == AIRCRAFT)
		D3DXMatrixRotationAxis(&T, &m_vUp, _fRadian);

	// rotate m_vRight and m_vLook around m_vUp or y_axis
	D3DXVec3TransformCoord(&m_vRight, &m_vRight, &T);
	D3DXVec3TransformCoord(&m_vLook, &m_vLook, &T);
}

void CCamera::roll(float _fRadian){
	D3DXMATRIX T;

	// 비행 타입일 경우만 회전한다.
	if(m_eCameraType == AIRCRAFT || m_eCameraType == TWODEMENTION){
		m_vRot.z += _fRadian;

		if(m_vRot.z >= D3DX_PI*2.0f) m_vRot.z -= D3DX_PI*2.0f;
		else if(m_vRot.z <= -D3DX_PI*2.0f) m_vRot.z += D3DX_PI*2.0f;

		D3DXMatrixRotationAxis(&T, &m_vLook, _fRadian);

		// look 벡터 기준으로 위와 오른쪽으로 회전한다.
		D3DXVec3TransformCoord(&m_vRight, &m_vRight, &T);
		D3DXVec3TransformCoord(&m_vUp, &m_vUp, &T);
	}
}

void CCamera::walk(float _fUnits){
	// TWODEMENTION라면 깊이 이동을 할 수 없다.
	if(m_eCameraType == TWODEMENTION)
		return;

	if(_fUnits == 0)
		return;
	// 지상의 물체는 xz평면으로 움직임을 제한한다.
	if(m_eCameraType == LANDOBJECT){
		// 바라보고 있는 방향을 계산한다.
		D3DXVECTOR3 dir;
		D3DXVECTOR3 WORLD_UP(0.0f, 1.0f, 0.0f);

		D3DXVec3Cross(&dir, &m_vRight, &WORLD_UP);
		m_vPos += D3DXVECTOR3(dir.x, 0.0f, dir.z) * _fUnits;
	}

	if(m_eCameraType == AIRCRAFT)
		m_vPos += m_vLook*_fUnits;
}

void CCamera::strafe(float _fUnits){
	// TWODEMENTION 카메라 좌우 이동
	if(m_eCameraType == TWODEMENTION)
		m_vPos+=D3DXVECTOR3(m_vRight.x, 0.0f, m_vRight.z) * _fUnits;

	// 지상의 물체는 xz 평면으로 움직임을 제한한다.
	if(m_eCameraType == LANDOBJECT)
		m_vPos+=D3DXVECTOR3(m_vRight.x, 0.0f, m_vRight.z) * _fUnits;

	if(m_eCameraType == AIRCRAFT)
		m_vPos += m_vRight * _fUnits;
}

void CCamera::fly(float _fUnits){
	// TWODEMENTION 카메라 상하 이동, yz명면으로 움직임을 제한한다.
	if(m_eCameraType == TWODEMENTION)
		m_vPos+= D3DXVECTOR3(0.0f, m_vUp.y, m_vUp.z) * _fUnits;

	if(m_eCameraType == AIRCRAFT)
		m_vPos += m_vUp * _fUnits;
}