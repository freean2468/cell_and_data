#include "Logo.h"
#include "LogoOwnedStates.h"

CLogo::CLogo(int _nEntityType):COrganEntity(_nEntityType){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CLogo>(this);

	// ��� ����
	LoadEntityData("./script/SectionComposition/Logo/Logo.txt");
			
	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(LogoStart->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);	
}

CLogo::~CLogo(){
	Delete< CStateMachine<CLogo>* >(m_pStateMachine);
}