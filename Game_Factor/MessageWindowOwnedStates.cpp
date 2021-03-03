#include "MessageWindowOwnedStates.h"

///////////////////////////////////////////////////////////
// Normal State
///////////////////////////////////////////////////////////
void CMessageWindowNormal::Enter(CMessageWindow* _pMessageWindow){

}

void CMessageWindowNormal::Execute(CMessageWindow* _pMessageWindow){
	_pMessageWindow->RenderOrgan();
}

void CMessageWindowNormal::Exit(CMessageWindow* _pMessageWindow){

}

bool CMessageWindowNormal::OnMessage(CMessageWindow* agent, const Telegram& _rMsg){
	return false;
}