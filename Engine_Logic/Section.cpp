#include "Section.h"

CSection::CSection(){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CSection>(this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(SectionLogo->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CSection::~CSection(){
	Delete< CStateMachine<CSection>* >(m_pStateMachine);
}