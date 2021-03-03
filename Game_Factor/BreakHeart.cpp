#include "BreakHeart.h"
#include "BreakHeartOwnedStates.h"

CBreakHeart::CBreakHeart(int _nID) : COrganEntity(_nID), m_bActive(false)
{
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CBreakHeart>(this);

	LoadEntityData("./script/Event/BreakHeart/BreakHeart.txt");
			
	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(BreakHeart1st->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	this->UniformOrganAlpha(0.0f);
}

CBreakHeart::~CBreakHeart(){
	Delete< CStateMachine<CBreakHeart>* >(m_pStateMachine);
}