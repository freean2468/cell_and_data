#include "BreakHeart.h"
#include "BreakHeartOwnedStates.h"

CBreakHeart::CBreakHeart(int _nID) : COrganEntity(_nID), m_bActive(false)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CBreakHeart>(this);

	LoadEntityData("./script/Event/BreakHeart/BreakHeart.txt");
			
	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(BreakHeart1st->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	this->UniformOrganAlpha(0.0f);
}

CBreakHeart::~CBreakHeart(){
	Delete< CStateMachine<CBreakHeart>* >(m_pStateMachine);
}