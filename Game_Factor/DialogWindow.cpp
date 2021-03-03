#include "DialogWindow.h"
#include "DialogWindowOwnedStates.h"
#include "../Engine_System/EngineManager.h"

CDialogWindow::CDialogWindow(int _nEntityType):COrganEntity(_nEntityType),
											m_pText(new CText()),
											m_OneLine(""),
											m_CurrentLine(""),
											m_nDialogID(0)
{
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CDialogWindow>(this);

	// ��� ����
	LoadEntityData("./script/UserInterface/DialogWindow/DialogWindow.txt");

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(DialogWindowNormal->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);	

	this->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
	
	m_pText->InitFont(22, 11, 500, false, "���� ���");

	for(int i = 0; i < 2; ++i) m_pImage[i] = new CBody();

	m_pImage[0]->InitObject(EngineMgr->GetpDevice(), "./Image/UserInterface/DialogWindow/Friend.dds",
		150, 190, 1.0f, 0);
	m_pImage[1]->InitObject(EngineMgr->GetpDevice(), "./Image/UserInterface/DialogWindow/Love.dds",
		150, 190, 1.0f, 0);

	for(int i = 0; i < 2; ++i) m_pImage[i]->SetColor(&D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
}

CDialogWindow::~CDialogWindow(){
	Delete< CStateMachine<CDialogWindow>* >(m_pStateMachine);
	Delete<CText*>(m_pText);
	for(int i = 0; i < 2; ++i)	Delete<CBody*>(m_pImage[i]);
}

void CDialogWindow::Update(){
	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);

	m_pStateMachine->Update();

	t_vPos = *(GetBody()->GetPriPos()) + *(GetAttachment(0)->GetPriPos());

	m_pText->PreRenderLine(&t_vPos);

	m_pText->Update(GetAttachment(0)->GetAbsoluteRect());
}