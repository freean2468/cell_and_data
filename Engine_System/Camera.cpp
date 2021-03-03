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
	// ī�޶��� ���� ���� ������ �ǵ��� �Ѵ�.
	D3DXVec3Normalize(&m_vLook, &m_vLook);
	
	D3DXVec3Cross(&m_vUp, &m_vLook, &m_vRight);
	D3DXVec3Normalize(&m_vUp, &m_vUp);

	D3DXVec3Cross(&m_vRight, &m_vUp, &m_vLook);
	D3DXVec3Normalize(&m_vRight, &m_vRight);

	// �� ����� �����Ѵ�.
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

	// TWODEMENTION��� ī�޶� ȸ�� ����� ����� �� ����.
	if(m_eCameraType == TWODEMENTION)
		return;

	D3DXMatrixRotationAxis(&T, &m_vRight, _fRadian);

	// m_vRight�� �������� m_vUp�� m_vLook�� ȸ���Ѵ�.
	D3DXVec3TransformCoord(&m_vUp, &m_vUp, &T);
	D3DXVec3TransformCoord(&m_vLook, &m_vLook, &T);
}

void CCamera::yaw(float _fRadian){
	D3DXMATRIX T;

	// TWODEMENTION��� ī�޶� ȸ�� ����� ����� �� ����.
	if(m_eCameraType == TWODEMENTION)
		return;

	// ������ ��ü�� ���ؼ��� ���� y(0, 1, 0)�� �������� ȸ���Ѵ�.
	if(m_eCameraType == LANDOBJECT)
		D3DXMatrixRotationY(&T, _fRadian);

	// ���� ��ü�� ���ؼ��� ������ ���� ���ͷ� ȸ���Ѵ�.
	if(m_eCameraType == AIRCRAFT)
		D3DXMatrixRotationAxis(&T, &m_vUp, _fRadian);

	// rotate m_vRight and m_vLook around m_vUp or y_axis
	D3DXVec3TransformCoord(&m_vRight, &m_vRight, &T);
	D3DXVec3TransformCoord(&m_vLook, &m_vLook, &T);
}

void CCamera::roll(float _fRadian){
	D3DXMATRIX T;

	// ���� Ÿ���� ��츸 ȸ���Ѵ�.
	if(m_eCameraType == AIRCRAFT || m_eCameraType == TWODEMENTION){
		m_vRot.z += _fRadian;

		if(m_vRot.z >= D3DX_PI*2.0f) m_vRot.z -= D3DX_PI*2.0f;
		else if(m_vRot.z <= -D3DX_PI*2.0f) m_vRot.z += D3DX_PI*2.0f;

		D3DXMatrixRotationAxis(&T, &m_vLook, _fRadian);

		// look ���� �������� ���� ���������� ȸ���Ѵ�.
		D3DXVec3TransformCoord(&m_vRight, &m_vRight, &T);
		D3DXVec3TransformCoord(&m_vUp, &m_vUp, &T);
	}
}

void CCamera::walk(float _fUnits){
	// TWODEMENTION��� ���� �̵��� �� �� ����.
	if(m_eCameraType == TWODEMENTION)
		return;

	if(_fUnits == 0)
		return;
	// ������ ��ü�� xz������� �������� �����Ѵ�.
	if(m_eCameraType == LANDOBJECT){
		// �ٶ󺸰� �ִ� ������ ����Ѵ�.
		D3DXVECTOR3 dir;
		D3DXVECTOR3 WORLD_UP(0.0f, 1.0f, 0.0f);

		D3DXVec3Cross(&dir, &m_vRight, &WORLD_UP);
		m_vPos += D3DXVECTOR3(dir.x, 0.0f, dir.z) * _fUnits;
	}

	if(m_eCameraType == AIRCRAFT)
		m_vPos += m_vLook*_fUnits;
}

void CCamera::strafe(float _fUnits){
	// TWODEMENTION ī�޶� �¿� �̵�
	if(m_eCameraType == TWODEMENTION)
		m_vPos+=D3DXVECTOR3(m_vRight.x, 0.0f, m_vRight.z) * _fUnits;

	// ������ ��ü�� xz ������� �������� �����Ѵ�.
	if(m_eCameraType == LANDOBJECT)
		m_vPos+=D3DXVECTOR3(m_vRight.x, 0.0f, m_vRight.z) * _fUnits;

	if(m_eCameraType == AIRCRAFT)
		m_vPos += m_vRight * _fUnits;
}

void CCamera::fly(float _fUnits){
	// TWODEMENTION ī�޶� ���� �̵�, yz������� �������� �����Ѵ�.
	if(m_eCameraType == TWODEMENTION)
		m_vPos+= D3DXVECTOR3(0.0f, m_vUp.y, m_vUp.z) * _fUnits;

	if(m_eCameraType == AIRCRAFT)
		m_vPos += m_vUp * _fUnits;
}