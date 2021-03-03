#include "Logo.h"
#include "LogoOwnedStates.h"

CLogo::CLogo(int _nEntityType):COrganEntity(_nEntityType){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CLogo>(this);

	// 기관 설정
	LoadEntityData("./script/SectionComposition/Logo/Logo.txt");
			
	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(LogoStart->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);	
}

CLogo::~CLogo(){
	Delete< CStateMachine<CLogo>* >(m_pStateMachine);
}