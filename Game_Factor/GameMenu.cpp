#include "GameMenu.h"
#include "GameMenuOwnedStates.h"

CGameMenu::CGameMenu(int _nID):COrganEntity(_nID),
																m_eCameraMode(CCameraManager::NONE)
{
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CGameMenu>(this);

	// ��� ����
	LoadEntityData("./script/UserInterface/GameMenu/GameMenu.txt");
			
	// ó�� ���¸� �ʱ�ȭ
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