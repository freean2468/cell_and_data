#include "LoadingOwnedStates.h"
#include "Loading.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CLoadingUsual::Enter(CLoading* pLoading){
	
}

void CLoadingUsual::Execute(CLoading* pLoading){
	pLoading->RenderOrgan();
}

void CLoadingUsual::Exit(CLoading* pLoading){
	
}

bool CLoadingUsual::OnMessage(CLoading* agent, const Telegram& _rMsg){
	return false;
}