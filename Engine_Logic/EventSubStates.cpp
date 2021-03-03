#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// EventSub
///////////////////////////////////////////////////////////
void CEventSub::Enter(CEvent* _pEvent){
	
}

void CEventSub::Execute(CEvent* _pEvent){
	
}

void CEventSub::Exit(CEvent* _pEvent){
	
}

///////////////////////////////////////////////////////////
// EventSubBreakHeart
///////////////////////////////////////////////////////////
void CEventSubBreakHeart::Enter(CEvent* _pEvent){
	m_pBreakHeart = new CBreakHeart(-1);
	m_pBreakHeart->OnActive();
}

void CEventSubBreakHeart::Execute(CEvent* _pEvent){
	m_pBreakHeart->Update();
}

void CEventSubBreakHeart::Exit(CEvent* _pEvent){
	Delete<CBreakHeart*>(m_pBreakHeart);
}