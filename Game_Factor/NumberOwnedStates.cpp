#include "NumberOwnedStates.h"

///////////////////////////////////////////////////////////
// Normal State
///////////////////////////////////////////////////////////
void CNumberNormal::Enter(CNumber* _pNumber){
	
}

void CNumberNormal::Execute(CNumber* _pNumber){
	_pNumber->RenderOrgan();
}

void CNumberNormal::Exit(CNumber* _pNumber){

}

bool CNumberNormal::OnMessage(CNumber* agent, const Telegram& _rMsg){
	return false;
}