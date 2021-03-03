/////////////////////////////////////////////////////////
// ī�޶� Ŭ����
// ��å ����
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

	float m_fCameraRatio; // ī�޶� ���� :: ��� (float)(Width/Height)

public:
	CCamera();
	CCamera(CameraType _eCameraType);
	~CCamera();

	void strafe(float _fUnits);	// ����/������
	void fly(float _fUunits);		// ����/�Ʒ���
	void walk(float _fUunits);		// ����/����

	void pitch(float _fRadian);	// ���� ���ͷ� ȸ��
	void yaw(float _fRadian);		// ���� ���ͷ� ȸ��
	void roll(float _fRadian);		// ���� ���ͷ� ȸ��

	void GetViewMatrix(D3DXMATRIX* p_V);			// ���� ����Ʈ ��� ��ȯ
	void SetCameraType(CameraType _eCameraType);	// ī�޶� Ÿ�� ����
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