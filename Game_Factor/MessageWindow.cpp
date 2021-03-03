#include "MessageWindow.h"
#include "MessageWindowOwnedStates.h"

CMessageWindow::CMessageWindow(int _nEntityType, MWTYPE _eMWType):COrganEntity(_nEntityType),
																m_pText(new CText()),
																m_OneLine(""),
																m_CurrentLine(""),
																m_eMWType(_eMWType)
{
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CMessageWindow>(this);

	// ��� ����
	if(m_eMWType == SQUARE)		LoadEntityData("./script/UserInterface/MessageWindow/Square.txt");
	else if(m_eMWType == THIN)		LoadEntityData("./script/UserInterface/MessageWindow/Thin.txt");
	else if(m_eMWType == BALLOON)		LoadEntityData("./script/UserInterface/MessageWindow/Balloon.txt");
	else if(m_eMWType == TRANSPARENCY)	LoadEntityData("./script/UserInterface/MessageWindow/Thin.txt");

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(MessageWindowNormal->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);	

	this->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, this->GetBody()->GetAlpha()));
	
	m_pText->InitFont(22, 11, 500, false, "���� ���");
}

CMessageWindow::~CMessageWindow(){
	Delete< CStateMachine<CMessageWindow>* >(m_pStateMachine);
	Delete<CText*>(m_pText);
}

void CMessageWindow::Update(){
	if(m_eMWType != TRANSPARENCY)	m_pStateMachine->Update();

	GetBody()->SetPriPos(this->GetTransPos3D());

	m_pText->PreRenderLine(GetBody()->GetPriPos());

	m_pText->Update(GetBody()->GetAbsoluteRect());
}