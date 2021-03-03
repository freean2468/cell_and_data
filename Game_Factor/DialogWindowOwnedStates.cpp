#include "DialogWindowOwnedStates.h"

///////////////////////////////////////////////////////////
// Normal State
///////////////////////////////////////////////////////////
void CDialogWindowNormal::Enter(CDialogWindow* _pDialogWindow){

}

void CDialogWindowNormal::Execute(CDialogWindow* _pDialogWindow){
	_pDialogWindow->RenderOrgan();

	_pDialogWindow->GetImage()->GetPriPos()->x = _pDialogWindow->GetBody()->GetPriPos()->x + 160.0f;
	_pDialogWindow->GetImage()->GetPriPos()->y = _pDialogWindow->GetBody()->GetPriPos()->y;
	_pDialogWindow->GetImage()->GetPriPos()->z = _pDialogWindow->GetBody()->GetPriPos()->z;

	_pDialogWindow->GetImage()->Render();
}

void CDialogWindowNormal::Exit(CDialogWindow* _pDialogWindow){

}

bool CDialogWindowNormal::OnMessage(CDialogWindow* agent, const Telegram& _rMsg){
	return false;
}