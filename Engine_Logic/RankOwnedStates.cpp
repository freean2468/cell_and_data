#include "RankOwnedStates.h"

///////////////////////////////////////////////////////////
// Main State
///////////////////////////////////////////////////////////
void CRankMain::Enter(CRank* _pRank){

}

void CRankMain::Execute(CRank* _pRank){
	
}

void CRankMain::Exit(CRank* _pRank){
}

bool CRankMain::OnMessage(CRank* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Record State
///////////////////////////////////////////////////////////
void CRankRecord::Enter(CRank* _pRank){
	Ranking t_Ranking;

	if(UIMgr->GetIW()->GetCursorActive()){
		UIMgr->GetIW()->GetName().resize(UIMgr->GetIW()->GetName().size()-1);
	}

	t_Ranking = Ranking(UIMgr->GetIW()->GetName(), static_cast<int>(UIMgr->GetTextOfGame()->GetTimer()->GetLastTime()));
	
	_pRank->SetNew(t_Ranking);

	_pRank->RecordRankingToScript();

	_pRank->SetRank();
}

void CRankRecord::Execute(CRank* _pRank){
	
}

void CRankRecord::Exit(CRank* _pRank){
}

bool CRankRecord::OnMessage(CRank* agent, const Telegram& _rMsg){
	return false;
}