#include "MainMenu.h"
#include "MainMenuOwnedStates.h"

CMainMenu::CMainMenu(int _nID):COrganEntity(_nID){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CMainMenu>(this);

	// ��� ����
	LoadEntityData("./script/SectionComposition/MainMenu/MainMenu.txt");

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(MainMenuMain->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	this->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));

	m_pMenuMain = new COrganEntity(-1);
	m_pMenuMain->LoadEntityData("./script/SectionComposition/MainMenu/MenuMain.txt");
	m_pMenuMain->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));

	m_pMenuExtra = new COrganEntity(-1);
	m_pMenuExtra->LoadEntityData("./script/SectionComposition/MainMenu/MenuExtra.txt");
	m_pMenuExtra->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
	m_pMenuExtra->UniformOrganScaZero();

	m_pMenuStart = new COrganEntity(-1);
	m_pMenuStart->LoadEntityData("./script/SectionComposition/MainMenu/MenuStart.txt");
	m_pMenuStart->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
	m_pMenuStart->UniformOrganScaZero();
}

CMainMenu::~CMainMenu(){
	Delete< CStateMachine<CMainMenu>* >(m_pStateMachine);
	Delete< COrganEntity* >(m_pMenuMain);
	Delete< COrganEntity* >(m_pMenuStart);
	Delete< COrganEntity* >(m_pMenuExtra);
}

void CMainMenu::Update(double _dTimeElapsed){
	m_pStateMachine->Update();
}

void CMainMenu::RenderOrgan(){
	if(GetBody()){
		BodySetting();
		GetBody()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
	}
	
	InitChainVector();

	if(GetAttachmentArray()->GetSize()){
		for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){
			BodySetting();
			GetAttachmentArray()->Get(i)->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
			InitChainVector();
		}
	}

	InitChainVector();
}