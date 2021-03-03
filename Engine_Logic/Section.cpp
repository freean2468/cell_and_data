#include "Section.h"

CSection::CSection(){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CSection>(this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(SectionLogo->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CSection::~CSection(){
	Delete< CStateMachine<CSection>* >(m_pStateMachine);
}