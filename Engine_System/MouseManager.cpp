#include "MouseManager.h"
#include "EngineManager.h"
#include "CameraManager.h"
#include "../Engine_Math&Physics/Transformation.h"
#include "../Engine_Misc/DirectUtils.h"

CMouseManager::CMouseManager():	m_eType(NORMAL),
								m_bUseCursor(true),
								m_bLeftDown(false),
								m_bRightDown(false),
								m_bOldLeftDown(false),
								m_bOldRightDown(false),
								m_bSomethingCollision(false),
								m_vSpot(0.0f, 0.0f, 0.0f)
{
	for(int i=0; i < 2; ++i)	m_pCursor[i] = new CBody();

	m_pCursor[NORMAL]->InitObject(EngineMgr->GetpDevice(), "./Image/Cursor/Cursor.dds", 25, 25, 1.0f, 0);
	m_pCursor[DIRECTION]->InitObject(EngineMgr->GetpDevice(), 	"./Image/Cursor/Cursor2.dds", 30, 30, 1.0f, 0);

	EngineMgr->GetpInformation()->SetAbsolutedX(0.0f);
	EngineMgr->GetpInformation()->SetAbsolutedY(0.0f);

	m_pCursor[0]->SetColor(&D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
}

CMouseManager::~CMouseManager(){
	for(int i=0; i < 2; ++i)	Delete<CBody*>(m_pCursor[i]);
}

bool CMouseManager::LeftDownTheMoment(){
	if(!m_bOldLeftDown){
		if(m_bLeftDown){
			return true;
		}
	}
	return false;
}

bool CMouseManager::RightDownTheMoment(){
	if(!m_bOldRightDown){
		if(m_bRightDown){
			return true;
		}
	}
	return false;
}

bool CMouseManager::LeftClick(){
	if(m_bOldLeftDown){
		if(!m_bLeftDown){
			return true;
		}
	}
	return false;
}

bool CMouseManager::RightClick(){
	if(m_bOldRightDown){
		if(!m_bRightDown)
			return true;
	}
	return false;
}

void CMouseManager::Initialize(){
	m_vSpot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void CMouseManager::UpdateCursorPosition(float _fX, float _fY){
	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);
	float t_fZ = CameraMgr->GetCamera()->GetRotation().z;

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	Vector2D t_vHeaving(static_cast<double>(_fX), static_cast<double>(_fY));

	// DirectX의 회전값은 양수가 반시계방향이다.
	Vec2DRotateAroundOrigin(t_vHeaving, -t_fZ);

	// 카메라 Z축 방향에 따라서 마우스 움직임을 적절히 바꿔준다.
	m_vSpot.x += static_cast<float>(t_vHeaving.x);
	m_vSpot.y -= static_cast<float>(t_vHeaving.y);

	// z축의 좌표값에 따라서 카메라에 상대적으로 보이는 위치가 달라진다.
	//m_vSpot.z = 0.0f;	
	m_vSpot.z = t_vPos.z + 700.0f;

	if(m_vSpot.x >= t_vPos.x + (SYSTEMWIDTH/2))
		m_vSpot.x = t_vPos.x + (SYSTEMWIDTH/2);
	if(m_vSpot.x <= t_vPos.x - (SYSTEMWIDTH/2))	
		m_vSpot.x = t_vPos.x - (SYSTEMWIDTH/2);

	if(m_vSpot.y >= t_vPos.y + (SYSTEMHEIGHT/2))
		m_vSpot.y = t_vPos.y + (SYSTEMHEIGHT/2);
	if(m_vSpot.y <= t_vPos.y - (SYSTEMHEIGHT/2))	
		m_vSpot.y = t_vPos.y - (SYSTEMHEIGHT/2);

	EngineMgr->GetpInformation()->SetAdjustedX(MouseMgr->GetCursorPos()->x);
	EngineMgr->GetpInformation()->SetAdjustedY(MouseMgr->GetCursorPos()->y);

	// 절대좌표는 관리자 초기화에서 한번만

	for(int i = 0; i < 2; ++i){
		*(m_pCursor[i]->GetPriPos()) = m_vSpot;
	}
}

void CMouseManager::CursorUpdate(){
	if(Something()){
		m_eType = DIRECTION;

		if(this->GetLeftDown()){

		}
	}
	else
		m_eType = NORMAL;

	if(m_bUseCursor){
		m_pCursor[GetType()]->Render(&D3DXVECTOR3(m_vSpot.x, m_vSpot.y, m_vSpot.z),
			&D3DXVECTOR3(1.0f, 1.0f, 1.0f),&D3DXVECTOR3(0.0f, 0.0f, 0.0f),&D3DXVECTOR3(0.0f, 0.0f, 0.0f));	
	}

	OffSomething();
}

float CMouseManager::CalRotClickBetweenPos(Vector2D _vPos){
	Vector2D t_vCur((double)m_vSpot.x, (double)m_vSpot.y);
	Vector2D t_vDist = t_vCur - _vPos;

	return DU::CalAngleConsiderTexture(t_vDist);
}

Vector2D CMouseManager::CalHeadingClickBetweenPos(Vector2D _vPos){
	Vector2D t_vCur((double)m_vSpot.x, (double)m_vSpot.y);
	Vector2D t_vDist = t_vCur - _vPos;

	t_vDist.Normalize();
	
	return t_vDist;
}