#include "../BaseHeader.h"

CQuestionMark::CQuestionMark(COrgan* _pOrgan):CBaseEffect(QUESTIONMARK),
																								m_pOrigin(_pOrgan),
																								m_bOnOff(true)
{
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CQuestionMark>(this);

	LoadEntityData("./script/Effect/QuestionMark.txt");

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(QuestionMarkUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CQuestionMark::~CQuestionMark(){
	Delete<CStateMachine<CQuestionMark>*>(m_pStateMachine);
}