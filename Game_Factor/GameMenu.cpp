#include "GameMenu.h"
#include "GameMenuOwnedStates.h"

CGameMenu::CGameMenu(int _nID):COrganEntity(_nID),
																m_eCameraMode(CCameraManager::NONE)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CGameMenu>(this);

	// 기관 설정
	LoadEntityData("./script/UserInterface/GameMenu/GameMenu.txt");
			
	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(GameMenuInActive->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	this->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
	this->UniformOrganScaZero();
}

CGameMenu::~CGameMenu(){
	Delete< CStateMachine<CGameMenu>* >(m_pStateMachine);
}

void CGameMenu::Update(){ 
	float t_fZ = CameraMgr->GetCamera()->GetRotation().z;

	GetBody()->GetPriRot()->z = t_fZ;

	m_pStateMachine->Update();
}