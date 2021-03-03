#include "../BaseHeader.h"

CQuestionMark::CQuestionMark(COrgan* _pOrgan):CBaseEffect(QUESTIONMARK),
																								m_pOrigin(_pOrgan),
																								m_bOnOff(true)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CQuestionMark>(this);

	LoadEntityData("./script/Effect/QuestionMark.txt");

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(QuestionMarkUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CQuestionMark::~CQuestionMark(){
	Delete<CStateMachine<CQuestionMark>*>(m_pStateMachine);
}