/////////////////////////////////////////////////////
// CCameraManager클래스는 이 엔진의 시스템을 총괄함
////////////////////////////////////////////////////

#ifndef _CameraManager_H_
#define _CameraManager_H_

#include "Camera.h"
#include "BasicEntity.h"

class CCameraManager{
public:
	typedef enum CameraMode{NONE, ORIGIN, SECTION, SCRIPT, EVENT, MOUSE, CONTROL, ABILITY}CAMERAMODE;

private:
	CCamera* m_Camera;
	D3DXVECTOR3 m_vDestination;	// 카메라 목적지
	CAMERAMODE m_eMode;
	CAMERAMODE m_ePreviousMode;

	CBasicEntity* m_pOrigin;

	CTimer* m_pTimer;

	float m_fAdj;
	double	m_dDistance;				// 카메라와 거리
	double	m_dMaxDistance;			// 최대 거리 제한

    // 생성자와 소멸자를 복사하고 할당은 private이어야 한다.
	CCameraManager(const CCameraManager&);
	CCameraManager& operator=(const CCameraManager&);

public:
	CCameraManager();
	~CCameraManager();

	static CCameraManager* Instance(){
		 static CCameraManager instance;

		 return &instance;
	}

	void CameraUpdate();

	///////////////////////////////////////////////////
	// CCameraManager 클래스 제공 함수
	void SetDestinationByMouse();
	void LimitDestination();
	void FaceToDestination();
	void AngleToDestination();
	void CameraUp(float _fDownLimit);
	void CameraInit(float _fx, float _fy, float _fz);
	void CameraDefault();
	void CameraMode();
	void CameraVibration();

	void SetOrigin(CBasicEntity* _pOrigin);
	CBasicEntity* GetOrigin(){return m_pOrigin;}

	void SetDestination(D3DXVECTOR3* _pvDestination){m_vDestination = *(_pvDestination);}
	void SetDestinationX(float _fPosX){m_vDestination.x = _fPosX;}
	void SetDestinationY(float _fPosY){m_vDestination.y = _fPosY;}
	void SetDestinationZ(float _fPosZ){m_vDestination.z = _fPosZ;}

	void IncreaseDistance(){if(m_dMaxDistance > m_dDistance) m_dDistance++;}
	void DecreaseDistance(){if(m_dDistance > 1) m_dDistance--;}

	//Set & Get Function
	D3DXVECTOR3* GetDestination(){return &m_vDestination;}
	CCamera* GetCamera(){return m_Camera;}

	void SetMode(CAMERAMODE _eCameraMode){m_ePreviousMode = m_eMode; m_eMode = _eCameraMode;}
	CAMERAMODE GetMode(){return m_eMode;}
	void SetPreviousMoude(){m_eMode = m_ePreviousMode;}

	CTimer* GetTimer(){return m_pTimer;}

	double GetDistance(){return m_dDistance;}
	double GetMaxDistance(){return m_dMaxDistance;}
};

// CCameraManager의 인스턴스를 쉽게 접근할 수 있는 방법을 제공한다.
#define CameraMgr CCameraManager::Instance()

#endif