#include "TextOfGameOwnedStates.h"
#include "../Engine_System/Telegram.h"

///////////////////////////////////////////////////////////
// Main State
///////////////////////////////////////////////////////////
void CTextOfGameMain::Enter(CTextOfGame* _pTextOfGame){
	
}

void CTextOfGameMain::Execute(CTextOfGame* _pTextOfGame){
	_pTextOfGame->RenderOrgan();
}

void CTextOfGameMain::Exit(CTextOfGame* _pTextOfGame){

}

bool CTextOfGameMain::OnMessage(CTextOfGame* agent, const Telegram& _rMsg){
	return false;
}