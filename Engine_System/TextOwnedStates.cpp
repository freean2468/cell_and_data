#include "TextOwnedStates.h"

///////////////////////////////////////////////////////////
// Normal State
///////////////////////////////////////////////////////////
void CTextNormal::Enter(CText* pText){

}

void CTextNormal::Execute(CText* pText){
	pText->RenderLine();
}

void CTextNormal::Exit(CText* pText){

}

bool CTextNormal::OnMessage(CText* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Typing State
///////////////////////////////////////////////////////////
void CTextTyping::Enter(CText* pText){

}

void CTextTyping::Execute(CText* pText){
	pText->RenderTypingLine();
}

void CTextTyping::Exit(CText* pText){

}

bool CTextTyping::OnMessage(CText* agent, const Telegram& _rMsg){
	return false;
}