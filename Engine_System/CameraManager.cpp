#include "CameraManager.h"
#include "../Game_Factor/Virus.h"
#include "../Game_Factor/Controller.h"
#include "../Engine_Logic/EventManager.h"
#include "MouseManager.h"

// 생성자에서는 초기화만을 담당한다.
CCameraManager::CCameraManager() : 	m_Camera(new CCamera(CCamera::TWODEMENTION)),
									m_eMode(NONE),
									m_ePreviousMode(NONE),
									m_pOrigin(NULL),
									m_pTimer(new CTimer(0)),
									m_dDistance(1),
									m_dMaxDistance(100)
{
	m_Camera->SetVelocity(300.0f);

	CameraDefault();
}

CCameraManager::~CCameraManager(){
	Delete<CTimer*>(m_pTimer);
}

void CCameraManager::CameraUpdate(){

}

void CCameraManager::CameraInit(float _fx, float _fy, float _fz){
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	GetCamera()->GetPosition(&t_vPos);

	m_vDestination.x = t_vPos.x = _fx;
	m_vDestination.y = t_vPos.y = _fy;
	m_vDestination.z = t_vPos.z = _fz;

	GetCamera()->SetPosition(&t_vPos);
	GetCamera()->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	GetCamera()->SetRight(&D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	GetCamera()->SetUp(&D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	GetCamera()->SetLook(&D3DXVECTOR3(0.0f, 0.0f, 1.0f));
}

void CCameraManager::CameraDefault(){
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	GetCamera()->GetPosition(&t_vPos);

	m_vDestination.x = t_vPos.x = 0.0f;
	m_vDestination.y = t_vPos.y = 0.0f;
	m_vDestination.z = t_vPos.z = -700.0f;

	GetCamera()->SetPosition(&t_vPos);

	GetCamera()->yaw(-GetCamera()->GetRotation().y);
	GetCamera()->pitch(-GetCamera()->GetRotation().x);
	GetCamera()->roll(-GetCamera()->GetRotation().z);
	GetCamera()->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	GetCamera()->SetRight(&D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	GetCamera()->SetUp(&D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	GetCamera()->SetLook(&D3DXVECTOR3(0.0f, 0.0f, 1.0f));
}

void CCameraManager::CameraMode(){
	D3DXVECTOR3 t_vHeaving;
	CVirus* t_Controlled = Controller->GetController();
	CVehicle* t_CollisionVehicle;

	switch(m_eMode){
		case CONTROL:
			t_vHeaving.x = ((float)t_Controlled->GetVelocity().x / (float)t_Controlled->GetMass());
			t_vHeaving.y = ((float)t_Controlled->GetVelocity().y / (float)t_Controlled->GetMass());

			if(t_Controlled->GetGrowth()->IsGrowth(CGrowth::FIRST)){
				t_vHeaving.x *= 0.5f;				
				t_vHeaving.y *= 0.5f;
				t_vHeaving.z = -200.0f;
			}
			else if(t_Controlled->GetGrowth()->IsGrowth(CGrowth::SECOND)){
				t_vHeaving.x *= 0.8f;				
				t_vHeaving.y *= 0.8f;
				t_vHeaving.z = -400.0f;
			}
			else if(t_Controlled->GetGrowth()->IsGrowth(CGrowth::THIRD)){
				t_vHeaving.z = -600.0f;
			}

			CameraMgr->SetDestinationX((float)t_Controlled->GetPos2D().x + t_vHeaving.x);
			CameraMgr->SetDestinationY((float)t_Controlled->GetPos2D().y + t_vHeaving.y);
			CameraMgr->SetDestinationZ(t_vHeaving.z);
			break;
		case ABILITY:
			if(Controller->GetCrossingDataCon()->size() > 0){
				t_CollisionVehicle = Controller->GetCrossingDataCon()->at(0);

				if(t_Controlled->GetGrowth()->IsGrowth(CGrowth::FIRST)){
					t_vHeaving.z = -150.0f;
				}
				else if(t_Controlled->GetGrowth()->IsGrowth(CGrowth::SECOND)){
					t_vHeaving.z = -350.0f;
				}
				else if(t_Controlled->GetGrowth()->IsGrowth(CGrowth::THIRD)){
					t_vHeaving.z = -550.0f;
				}

				CameraMgr->SetDestinationX((float)t_CollisionVehicle->GetPos2D().x);
				CameraMgr->SetDestinationY((float)t_CollisionVehicle->GetPos2D().y);
				CameraMgr->SetDestinationZ(t_vHeaving.z);
			}
			break;
		case ORIGIN:
			CameraMgr->SetDestinationX(GetOrigin()->GetPos3D()->x);
			CameraMgr->SetDestinationY(GetOrigin()->GetPos3D()->y);
			AngleToDestination();
			break;
		case SECTION:
			CameraMgr->CameraInit(0.0f, 0.0f, -700.0f);
			break;
		case SCRIPT:
			if(m_pTimer->IsElapseTimer()){
				SetMode(CONTROL);
				EventMgr->GetScriptLoader()->NextScript();
			}
			break;
		case MOUSE:
			CameraMgr->SetDestinationX(MouseMgr->GetCursorPos()->x);
			CameraMgr->SetDestinationY(MouseMgr->GetCursorPos()->y);
			break;
		case NONE:
			break;
		default:
			CameraMgr->SetDestinationX(0.0f);
			CameraMgr->SetDestinationY(0.0f);
			break;
	}

	FaceToDestination();
}

void CCameraManager::LimitDestination(){
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	GetCamera()->GetPosition(&t_vPos);

	//// 우
	//if((StageMgr->GetStage()->GetWidthHalf()*0.5f) < GetDestination()->x)
	//	SetDestinationX(StageMgr->GetStage()->GetWidthHalf()*0.5f);
	//// 좌
	//else if((StageMgr->GetStage()->GetWidthHalf()*-0.5f) > GetDestination()->x)
	//	SetDestinationX(StageMgr->GetStage()->GetWidthHalf()*-0.5f);

	//// 상
	//if((StageMgr->GetStage()->GetHeightHalf()*0.5f) < GetDestination()->y)
	//	SetDestinationY(StageMgr->GetStage()->GetHeightHalf()*0.5f);
	//// 하
	//else if((StageMgr->GetStage()->GetHeightHalf()*-0.5f) > GetDestination()->y)
	//	SetDestinationY(StageMgr->GetStage()->GetHeightHalf()*-0.5f);
}

void CCameraManager::SetDestinationByMouse(){
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	GetCamera()->GetPosition(&t_vPos);

	if(GetOrigin()){
		if(EngineMgr->GetpInformation()->GetAbsolutedX() > SYSTEMWIDTH || EngineMgr->GetpInformation()->GetAbsolutedY() > SYSTEMHEIGHT)
			return;

		// 좌, 우
		if((GetOrigin()->GetWidthHalf()*0.5f) > EngineMgr->GetpInformation()->GetAdjustedX() && 
			-(GetOrigin()->GetWidthHalf()*0.5f) < EngineMgr->GetpInformation()->GetAdjustedX())
			SetDestinationX((float)EngineMgr->GetpInformation()->GetAdjustedX());

		// 상, 하		
		if(-(GetOrigin()->GetHeightHalf()*0.5f) < EngineMgr->GetpInformation()->GetAdjustedY() &&
			(GetOrigin()->GetHeightHalf()*0.5f) > EngineMgr->GetpInformation()->GetAdjustedY())
			SetDestinationY((float)EngineMgr->GetpInformation()->GetAdjustedY());

		if((GetOrigin()->GetWidthHalf()*0.5f) < GetDestination()->x || -(GetOrigin()->GetWidthHalf()*0.5f) > GetDestination()->x ||
			-(GetOrigin()->GetHeightHalf()*0.5f) > GetDestination()->y || (GetOrigin()->GetHeightHalf()*0.5f) < GetDestination()->y){
			SetDestinationX(0.0f);
			SetDestinationY(0.0f);
		}
	}
}

void CCameraManager::FaceToDestination(){
	// deltaS = v * deltaT
	// 벡터를 이용, 방향을 알아내야 한다.
	// 방향 = 벡터의 정규화
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Camera->GetPosition(&t_vPos);

	float t_fDeltaX = m_vDestination.x - t_vPos.x;
	float t_fDeltaY = m_vDestination.y - t_vPos.y;
	float t_fDeltaZ = m_vDestination.z - t_vPos.z;

	// 거리 == 벡터의 크기 == 힘
	float t_fDistance = 0.0f;
	D3DXVECTOR3 t_Heading = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	t_fDistance = sqrt((t_fDeltaX * t_fDeltaX) + (t_fDeltaY * t_fDeltaY) + (t_fDeltaZ * t_fDeltaZ));

	if(t_fDistance > 0.0f){
		// a = f / m;
		float t_fAce = t_fDistance * 300.0f;

		float t_fVel = t_fAce * SYSTEM_FRAME_INTERVAL_VER_60;

		if(t_fVel >= 600.0f) t_fVel = 600.0f;

		//방향
		t_Heading.x = t_fDeltaX / t_fDistance;
		t_Heading.y = t_fDeltaY / t_fDistance;
		t_Heading.z = t_fDeltaZ / t_fDistance;

		t_vPos.x += (t_Heading.x * t_fVel) * SYSTEM_FRAME_INTERVAL_VER_60;
		t_vPos.y += (t_Heading.y * t_fVel) * SYSTEM_FRAME_INTERVAL_VER_60;
		t_vPos.z += (t_Heading.z * t_fVel) * SYSTEM_FRAME_INTERVAL_VER_60;

		m_Camera->SetPosition(&t_vPos);
	}
	else{
		t_vPos.x = m_vDestination.x;
		t_vPos.y = m_vDestination.y;
		t_vPos.z = m_vDestination.z;		
	}
}

void CCameraManager::AngleToDestination(){
	// 거리 == 호의 길이
	float t_fArc = 0.0f;

	Vector2D t_vObject = GetOrigin()->GetPos2D();

	if(t_vObject.x == 0 && t_vObject.y == 0)
		t_vObject.y = 1;

	t_vObject.Normalize();	

	double t_fDot = t_vObject.Dot(m_Camera->GetHeading());

	float t_fDeltaRad = static_cast<float>(acos(t_fDot));

	t_fArc = t_fDeltaRad/D3DX_PI * static_cast<float>(GetOrigin()->GetPos2D().Length());

	if(t_fArc > 0.0f){
		float t_fAngularAce = t_fArc*3.0f;

		float t_fAngularVel = t_fAngularAce * SYSTEM_FRAME_INTERVAL_VER_60;

		//if(t_fAngularVel > t_fDeltaRad)
		//	t_fAngularVel = t_fDeltaRad;

		m_Camera->roll(-1.0f*m_fAdj*t_fAngularVel * SYSTEM_FRAME_INTERVAL_VER_60);
	}
}

// 올려다보기 함수
void CCameraManager::CameraUp(float _fDownLimit){
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	GetCamera()->GetPosition(&t_vPos);

	static float t_fCount = 0.0f;

	/*if( ::GetAsyncKeyState('W') & 0x8000f ){
		t_fCount+=5.0f;
		if((StageMgr->GetStage()->GetHeightHalf()*0.5f) > t_fCount)
			SetDestinationY(t_fCount);
	}
	else{
		SetDestinationY(_fDownLimit);
		t_fCount = 0.0f;
	}*/
}

// 카메라 진동
void CCameraManager::CameraVibration(){
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	GetCamera()->GetPosition(&t_vPos);

	int t_x = rand() % 3;
	int t_y = rand() % 10;
	int t_z = rand() % 3;

	if(rand() % 2 == 0)
		t_vPos.x += t_x;
	else
		t_vPos.x -= t_x;

	if(rand() % 2 == 0)
		t_vPos.y += t_y;
	else
		t_vPos.y -= t_y;
	
	if(rand() % 2 == 0)
		t_vPos.z += t_z;
	else
		t_vPos.z -= t_z;

	GetCamera()->SetPosition(&t_vPos);
}

void CCameraManager::SetOrigin(CBasicEntity* _pOrigin){
	m_pOrigin = _pOrigin;

	if(m_pOrigin->GetDirection() == CBasicEntity::LEFT){
		m_fAdj = -1.0f;
	}
	else{
		m_fAdj = 1.0f;
	}
}