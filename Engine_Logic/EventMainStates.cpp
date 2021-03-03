#include "EventMainStates.h"
#include "../Engine_Logic/EventMainStates.h"
#include "EventManager.h"
#include "../Engine_System/MP3Manager.h"
#include "../Engine_System/WaveManager.h"
#include "../Engine_System/CameraManager.h"
#include "../Game_Factor/Controller.h"
#include "../Game_Factor/UIManager.h"
#include "EventSubStates.h"
#include "../Engine_System/EffectManager.h"
#include "SectionManager.h"

///////////////////////////////////////////////////////////
// EventMain
///////////////////////////////////////////////////////////
void CEventMain::Enter(CEvent* _pEvent){

}

void CEventMain::Execute(CEvent* _pEvent){
	
}

void CEventMain::Exit(CEvent* _pEvent){

}

///////////////////////////////////////////////////////////
// EventMainTimeAttack
///////////////////////////////////////////////////////////
void CEventMainTimeAttack::Enter(CEvent* _pEvent){
	
}

void CEventMainTimeAttack::Execute(CEvent* _pEvent){	
	if(WorldMgr->GetWorld()->GetBus()){
		if(!WorldMgr->GetWorld()->GetBus()->GetActive()){
			D3DXVECTOR3 t_vPos;
		
			t_vPos.x = 0.0f;
			t_vPos.y = 550.0f;
			t_vPos.z = 0.0f;

			WorldMgr->GetWorld()->GetBus()->OnActive(&t_vPos);
			_pEvent->GetFSM()->ChangeState(EventMain->Instance());	
		}
	}
}

void CEventMainTimeAttack::Exit(CEvent* _pEvent){

}

///////////////////////////////////////////////////////////
// EventMainSurvival
///////////////////////////////////////////////////////////
void CEventMainSurvival::Enter(CEvent* _pEvent){

}

void CEventMainSurvival::Execute(CEvent* _pEvent){
	
}

void CEventMainSurvival::Exit(CEvent* _pEvent){

}

///////////////////////////////////////////////////////////
// EventMainStory1st
///////////////////////////////////////////////////////////
void CEventMainStory1st::Enter(CEvent* _pEvent){
	EventMgr->LoadScript("Story_1st.txt");
}

void CEventMainStory1st::Execute(CEvent* _pEvent){
	if(EventMgr->GetScriptLoader()->GetIndex() == 3)
		EventMgr->SetShowFriend(true);

	if(EventMgr->GetScriptLoader()->GetIndex() == EventMgr->GetScriptLoader()->GetMaxIndex()-1){
		D3DXVECTOR3 t_vPos = *(Controller->GetController()->GetBody()->GetPriPos());
		t_vPos.x += 60.0f;
		t_vPos.y += 60.0f;

		WorldMgr->GetWorld()->GetBus()->OnActive(&t_vPos);
	}
}

void CEventMainStory1st::Exit(CEvent* _pEvent){

}

///////////////////////////////////////////////////////////
// EventMainStory2nd
///////////////////////////////////////////////////////////
void CEventMainStory2nd::Enter(CEvent* _pEvent){
	EventMgr->LoadScript("Story_2nd_1.txt");
}

void CEventMainStory2nd::Execute(CEvent* _pEvent){
	if(!m_b2ndLoad && !m_b3rdLoad && EventMgr->GetScriptLoader()->GetIndex() == 2)
		EventMgr->SetShowFriend(true);

	if(!m_b2ndLoad && !m_b3rdLoad && EventMgr->GetScriptLoader()->GetIndex() == 6 && CameraMgr->GetMode() != CCameraManager::SCRIPT){
		CameraMgr->GetTimer()->InitTimer(3000);		
		CameraMgr->SetMode(CCameraManager::SCRIPT);
		CameraMgr->SetDestinationX((*WorldMgr->GetWorld()->GetData().front()).GetPos3D()->x);
		CameraMgr->SetDestinationY((*WorldMgr->GetWorld()->GetData().front()).GetPos3D()->y);
	}

	if(!m_b2ndLoad && UIMgr->GetAbility()->GetActive()){
		m_b2ndLoad = true;
		EventMgr->LoadScript("Story_2nd_2.txt");
		EventMgr->SetShowFriend(true);
	}

	if(!m_b3rdLoad && WorldMgr->GetWorld()->CheckDataAllDie()){
		m_b3rdLoad = true;
		EventMgr->LoadScript("Story_2nd_3.txt");
		EventMgr->SetShowFriend(true);
	}

	if(m_b3rdLoad && EventMgr->GetScriptLoader()->GetIndex() == 7){
		D3DXVECTOR3 t_vPos = *(Controller->GetController()->GetBody()->GetPriPos());
		
		if(t_vPos.x > 0.0f)			t_vPos.x -= 60.0f;
		else										t_vPos.x += 60.0f;

		if(t_vPos.y > 0.0f)			t_vPos.y -= 60.0f;
		else										t_vPos.y += 60.0f;

		WorldMgr->GetWorld()->GetBus()->OnActive(&t_vPos);
	}
}

void CEventMainStory2nd::Exit(CEvent* _pEvent){
	m_b2ndLoad = false;
	m_b3rdLoad = false;
}

///////////////////////////////////////////////////////////
// EventMainStory3rd
///////////////////////////////////////////////////////////
void CEventMainStory3rd::Enter(CEvent* _pEvent){
	EventMgr->LoadScript("Story_3rd_1.txt");
}

void CEventMainStory3rd::Execute(CEvent* _pEvent){
	if(!m_b2ndLoad && !m_b3rdLoad && EventMgr->GetScriptLoader()->GetIndex() == 0)
		EventMgr->SetShowFriend(true);

	if(!m_b2ndLoad && !m_b3rdLoad && EventMgr->GetScriptLoader()->GetIndex() == 1 && CameraMgr->GetMode() != CCameraManager::SCRIPT){
		CameraMgr->GetTimer()->InitTimer(2000);		
		CameraMgr->SetMode(CCameraManager::SCRIPT);
		CameraMgr->SetDestinationX((*WorldMgr->GetWorld()->GetVacine().front()).GetBody()->GetPriPos()->x);
		CameraMgr->SetDestinationY((*WorldMgr->GetWorld()->GetVacine().front()).GetBody()->GetPriPos()->y);
	}

	if(!m_b2ndLoad && !m_b3rdLoad && Controller->GetController()->GetGrowth()->IsGrowth(CGrowth::SECOND)){
		m_b2ndLoad = true;
		EventMgr->LoadScript("Story_3rd_2.txt");
		EventMgr->SetShowFriend(true);
	}

	if(!m_b3rdLoad && WorldMgr->GetWorld()->CheckVacineAllDie()){
		m_b3rdLoad = true;
		EventMgr->LoadScript("Story_3rd_3.txt");
		EventMgr->SetShowFriend(true);
	}

	if(m_b3rdLoad && EventMgr->GetScriptLoader()->GetIndex() == 1){
		D3DXVECTOR3 t_vPos = *(Controller->GetController()->GetBody()->GetPriPos());
		
		if(t_vPos.x > 0.0f)			t_vPos.x -= 60.0f;
		else										t_vPos.x += 60.0f;

		if(t_vPos.y > 0.0f)			t_vPos.y -= 60.0f;
		else										t_vPos.y += 60.0f;

		WorldMgr->GetWorld()->GetBus()->OnActive(&t_vPos);
	}
}

void CEventMainStory3rd::Exit(CEvent* _pEvent){
	m_b2ndLoad = false;
	m_b3rdLoad = false;
}

///////////////////////////////////////////////////////////
// EventMainStory4th
///////////////////////////////////////////////////////////
void CEventMainStory4th::Enter(CEvent* _pEvent){
	EventMgr->LoadScript("Story_4th_1.txt");
}

void CEventMainStory4th::Execute(CEvent* _pEvent){
	if(!m_b2ndLoad && !m_b3rdLoad && EventMgr->GetScriptLoader()->GetIndex() == 1 && CameraMgr->GetMode() != CCameraManager::SCRIPT){
		CameraMgr->GetTimer()->InitTimer(2000);		
		CameraMgr->SetMode(CCameraManager::SCRIPT);
		CameraMgr->SetDestinationX((*WorldMgr->GetWorld()->GetSecretData().front()).GetBody()->GetPriPos()->x);
		CameraMgr->SetDestinationY((*WorldMgr->GetWorld()->GetSecretData().front()).GetBody()->GetPriPos()->y);
		EventMgr->SetShowFriend(true);
	}

	if(!m_b2ndLoad && !m_b3rdLoad && UIMgr->GetAbility()->GetActive()){
		m_b2ndLoad = true;
		EventMgr->LoadScript("Story_4th_2.txt");
		EventMgr->SetShowFriend(true);
	}

	if(m_b2ndLoad && !m_b3rdLoad && WorldMgr->GetWorld()->CheckSecretDataAllDie()){
		m_b3rdLoad = true;
		EventMgr->LoadScript("Story_4th_3.txt");
		EventMgr->SetShowFriend(true);
	}

	if(m_b2ndLoad && m_b3rdLoad && EventMgr->GetScriptLoader()->GetIndex() == 1){
		D3DXVECTOR3 t_vPos = *(Controller->GetController()->GetBody()->GetPriPos());

		if(t_vPos.x > 0.0f)			t_vPos.x -= 60.0f;
		else										t_vPos.x += 60.0f;

		if(t_vPos.y > 0.0f)			t_vPos.y -= 60.0f;
		else										t_vPos.y += 60.0f;

		WorldMgr->GetWorld()->GetBus()->OnActive(&t_vPos);
	}

	if(m_b2ndLoad && m_b3rdLoad && EventMgr->GetScriptLoader()->GetIndex() == 2){
		EventMgr->SetShowFriend(false);
		EventMgr->SetShowLove(true);
	}

	if(m_b2ndLoad && m_b3rdLoad && EventMgr->GetScriptLoader()->GetIndex() == 19 && !m_bHearBreak){
		EventMgr->GetSub()->GetFSM()->ChangeState(EventSubBreakHeart->Instance());
		m_bHearBreak = true;
	}
}

void CEventMainStory4th::Exit(CEvent* _pEvent){
	m_b2ndLoad = false;
	m_b3rdLoad = false;
	m_bHearBreak = false;
	EventMgr->SetShowLove(false);
}

///////////////////////////////////////////////////////////
// EventMainStory5th
///////////////////////////////////////////////////////////
void CEventMainStory5th::Enter(CEvent* _pEvent){
	EventMgr->LoadScript("Story_5th.txt");
	UIMgr->GetGauge()->OnActive();
}

void CEventMainStory5th::Execute(CEvent* _pEvent){
	if(!m_bBusActive){
		D3DXVECTOR3 t_vPos;
		
		t_vPos.x = 0.0f;
		t_vPos.y = 550.0f;
		t_vPos.z = 0.0f;

		WorldMgr->GetWorld()->GetBus()->OnActive(&t_vPos);
		m_bBusActive = true;
	}
}

void CEventMainStory5th::Exit(CEvent* _pEvent){
	m_bBusActive = false;
}

///////////////////////////////////////////////////////////
// EventMainStory6th
///////////////////////////////////////////////////////////
void CEventMainStory6th::Enter(CEvent* _pEvent){
	EventMgr->LoadScript("Story_6th_1.txt");
	m_bFadeActive = false;
}

void CEventMainStory6th::Execute(CEvent* _pEvent){
	if(EventMgr->GetScriptLoader()->GetIndex() == 1){
		EventMgr->SetShowFriend(true);
	}

	if(EventMgr->GetScriptLoader()->GetIndex() == 12){
		EventMgr->SetShowFriend(false);
	}

	if(WorldMgr->GetWorld()->CheckDataAllDie() && !m_bFadeActive){
		EffectMgr->FadeOutBlackPlane();
		m_bFadeActive = true;
	}
}

void CEventMainStory6th::Exit(CEvent* _pEvent){
	
}

///////////////////////////////////////////////////////////
// EventMainEnding
///////////////////////////////////////////////////////////
void CEventMainEnding::Enter(CEvent* _pEvent){
	WaveMgr->Play("./Sound/laugh.wav", false);
	CameraMgr->SetMode(CCameraManager::NONE);
	CameraMgr->SetDestinationZ(m_pVirus->GetPos3D()->z - 50.0f);
	m_pTimer->InitTimer(6000);
}

void CEventMainEnding::Execute(CEvent* _pEvent){
	if(m_pTimer->IsElapseTimer()){
		MP3Mgr->FadeInOut(false);
		EffectMgr->FadeOutBlackPlane();
		SectionMgr->SetSign(CSectionManager::CREDIT);
		m_pTimer->InitTimer(100000000);
	}

	m_pVirus->Update();
	m_pVirus->Render();
}

void CEventMainEnding::Exit(CEvent* _pEvent){
	
}