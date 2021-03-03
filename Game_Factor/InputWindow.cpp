#include "InputWindow.h"
#include "InputWindowOwnedStates.h"
#include "../Engine_System/EngineManager.h"

CInputWindow::CInputWindow(int _nEntityType):COrganEntity(_nEntityType),
											m_pText(new CText()),
											m_pName(new CText()),
											m_Line(""),
											m_bActive(false),
											m_pCursorTimer(new CTimer(500)),
											m_bCursorActive(true)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CInputWindow>(this);

	// 기관 설정	
	LoadEntityData("./script/UserInterface/InputWindow/InputWindow.txt");

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(InputWindowOK->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);	

	this->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));

	m_pText->InitFont(22, 11, 500, false, "맑은 고딕");
	m_pText->SetFontScale(8);
}

CInputWindow::~CInputWindow(){
	Delete< CStateMachine<CInputWindow>* >(m_pStateMachine);
	Delete<CText*>(m_pText);
	Delete<CText*>(m_pName);
	Delete<CTimer*>(m_pCursorTimer);
}

void CInputWindow::Update(){
	if(m_pCursorTimer->IsElapseTimer()){
		m_pCursorTimer->InitTimer(500);
		ToggleCursor();
	}

	m_pStateMachine->Update();

	D3DXVECTOR3 t_vPos = *(GetBody()->GetPriPos());

	t_vPos.y += 65.0f;

	m_pText->PreRenderLine(&t_vPos);

	m_pText->Update(GetBody()->GetAbsoluteRect());

	t_vPos = *(GetBody()->GetPriPos());

	char t_Text[15];
	
	EngineMgr->EditWndUpdate(t_Text, 15);

	m_Name.clear();
	m_Name = t_Text;
	if(m_bCursorActive)	m_Name.push_back('l');

	m_pName->SetString(m_Name);
	m_pName->PreRenderLine(&t_vPos);

	m_pName->Update(GetBody()->GetAbsoluteRect());
}