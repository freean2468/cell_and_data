#include "CheckWindow.h"
#include "CheckWindowOwnedStates.h"

CCheckWindow::CCheckWindow(int _nEntityType):COrganEntity(_nEntityType),
											m_pText(new CText()),
											m_OneLine(""),
											m_CurrentLine(""),
											m_bActive(false)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CCheckWindow>(this);

	// 기관 설정	
	LoadEntityData("./script/UserInterface/CheckWindow/CheckWIndow.txt");

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(CheckWindowYesNo->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);	

	this->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));

	for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_pAtt = GetAttachment(i);

		if(t_pAtt->GetAttType() == CCheckWindow::YES){
			t_pAtt->SetAlpha(0.5f);
		}
		else if(t_pAtt->GetAttType() == CCheckWindow::NO){
			t_pAtt->SetAlpha(0.5f);
		}
		else if(t_pAtt->GetAttType() == CCheckWindow::OK){
			t_pAtt->SetAlpha(0.0f);
		}
	}
	
	m_pText->InitFont(22, 11, 500, false, "맑은 고딕");
	m_pText->SetFontScale(8);
}

CCheckWindow::~CCheckWindow(){
	Delete< CStateMachine<CCheckWindow>* >(m_pStateMachine);
	Delete<CText*>(m_pText);
}

void CCheckWindow::Update(){
	m_pStateMachine->Update();

	D3DXVECTOR3 t_vPos = *(GetBody()->GetPriPos());

	t_vPos.y += 30.0f;

	m_pText->PreRenderLine(&t_vPos);

	m_pText->Update(GetBody()->GetAbsoluteRect());
}