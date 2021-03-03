#include "Credit.h"
#include "CreditOwnedStates.h"

CCredit::CCredit(int _nID) : COrganEntity(_nID){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CCredit>(this);

	LoadEntityData("./script/SectionComposition/Credit/Credit.txt");
			
	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(CreditUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	this->UniformOrganScaZero();
	this->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));

	this->GetAttachmentFromType(LOGO)->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	this->GetAttachmentFromType(SCHOOL)->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

CCredit::~CCredit(){
	Delete< CStateMachine<CCredit>* >(m_pStateMachine);
}