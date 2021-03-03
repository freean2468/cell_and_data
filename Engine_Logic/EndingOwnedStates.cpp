#include "EndingOwnedStates.h"
#include "../Engine_System/MP3Manager.h"
#include "../Engine_Logic/SectionManager.h"
#include "../Engine_Logic/EventManager.h"
#include "Event.h"
#include "EventMainStates.h"
#include "../Engine_System/EffectManager.h"

///////////////////////////////////////////////////////////
// Main State
///////////////////////////////////////////////////////////
void CEndingMain::Enter(CEnding* _pEnding){
	MP3Mgr->StopMusic();
	MP3Mgr->Reset();
	MP3Mgr->LoadMusic("./Sound/FinalScream.mp3");
	MP3Mgr->PlayMusic();
	MP3Mgr->FadeInOut(true);
	m_pTimer->InitTimer(7000);
	SectionMgr->SetSign(CSectionManager::EVENT);
	_pEnding->GetAttachmentFromType(CEnding::DARK)->SetAlpha(0.0f);
	_pEnding->GetAttachmentFromType(CEnding::ENDING)->SetAlpha(1.0f);
}

void CEndingMain::Execute(CEnding* _pEnding){
	if(m_pTimer->IsElapseTimer()){
		_pEnding->GetFSM()->ChangeState(EndingStart->Instance());
	}

	_pEnding->RenderOrgan();
}

void CEndingMain::Exit(CEnding* _pEnding){
	
}

bool CEndingMain::OnMessage(CEnding* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Nothing State
///////////////////////////////////////////////////////////
void CEndingNothing::Enter(CEnding* _pEnding){

}

void CEndingNothing::Execute(CEnding* _pEnding){

}

void CEndingNothing::Exit(CEnding* _pEnding){
	
}

bool CEndingNothing::OnMessage(CEnding* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Start State
///////////////////////////////////////////////////////////
void CEndingStart::Enter(CEnding* _pEnding){
	m_pTimer->InitTimer(3500);
}

void CEndingStart::Execute(CEnding* _pEnding){
	for(int i = 0; i < _pEnding->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_pAtt = _pEnding->GetAttachment(i);

		if(t_pAtt->GetAttType() == CEnding::DARK){
			t_pAtt->IncreaseAlpha(0.04f);
		}		
	}

	if(m_pTimer->IsElapseTimer() && _pEnding->GetAttachmentFromType(CEnding::DARK)->GetAlpha() >= 1.0f){
		_pEnding->GetFSM()->ChangeState(EndingEnd->Instance());
	}

	_pEnding->RenderOrgan();
}

void CEndingStart::Exit(CEnding* _pEnding){
	
}

bool CEndingStart::OnMessage(CEnding* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// End State
///////////////////////////////////////////////////////////
void CEndingEnd::Enter(CEnding* _pEnding){
	EventMgr->GetMain()->GetFSM()->ChangeState(EventMainEnding->Instance());
}

void CEndingEnd::Execute(CEnding* _pEnding){
	if(EffectMgr->IfBlackFadeOutEnd()){		
		_pEnding->GetFSM()->ChangeState(EndingNothing->Instance());
		EventMgr->GetMain()->GetFSM()->ChangeState(EventMain->Instance());
	}

	_pEnding->RenderOrgan();
}

void CEndingEnd::Exit(CEnding* _pEnding){
	
}

bool CEndingEnd::OnMessage(CEnding* agent, const Telegram& _rMsg){
	return false;
}