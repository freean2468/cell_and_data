#include "UIManager.h"
#include "../Engine_System/EntityType.h"
#include "../Engine_System/EntityManager.h"
#include "../Engine_System/TextOwnedStates.h"
#include "../Engine_Logic/EventManager.h"

CUIManager::CUIManager() : m_pAbility(new CAbility(0)),
							m_pTextOfGame(new CTextOfGame()),
							m_pGameMenu(new CGameMenu()),
							m_pMWSquare(new CMessageWindow(0, CMessageWindow::SQUARE)),
							m_pCW(new CCheckWindow(CHECK)),
							m_pIW(new CInputWindow(IW)),
							m_pGauge(new CGauge()),
							m_pArrow(new CArrow())
{
	m_pMWSquare->GetText()->GetFSM()->ChangeState(TextTyping->Instance());
	m_pMWSquare->GetText()->SetFontScale(6);

	m_pCW->GetText()->GetFSM()->ChangeState(TextTyping->Instance());
	m_pCW->GetText()->SetFontScale(9);
	EntityMgr->RegisterEntity(m_pCW);

	m_pIW->GetText()->GetFSM()->ChangeState(TextTyping->Instance());
	m_pIW->GetText()->SetFontScale(9);
	EntityMgr->RegisterEntity(m_pIW);
}

CUIManager::~CUIManager(){
	Delete<CGauge*>(m_pGauge);
	Delete<CMessageWindow*>(m_pMWSquare);
	Delete<CCheckWindow*>(m_pCW);
	Delete<CInputWindow*>(m_pIW);
	Delete<CTextOfGame*>(m_pTextOfGame); 
	Delete<CGameMenu*>(m_pGameMenu); 
	Delete<CArrow*>(m_pArrow);
}

void CUIManager::Update(){
	if(m_pCW->GetActive()){
		m_pCW->Update();
	}
	else if(m_pIW->GetActive()){
		m_pIW->Update();
	}
	else{
		m_pAbility->Update();
		m_pGauge->Update();
		m_pTextOfGame->Update();
		m_pGameMenu->Update();
		if(!EventMgr->GetScript())
			m_pArrow->Update();
	}
}