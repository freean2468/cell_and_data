#include "SectionOwnedStates.h"
#include "../Engine_System/EffectManager.h"
#include "../Engine_System/MouseManager.h"
#include "../Engine_System/MP3Manager.h"
#include "../Game_Factor/UIManager.h"
#include "../Game_Factor/WorldManager.h"
#include "../Engine_System/EngineManager.h"
#include "MainMenuOwnedStates.h"
#include "../Engine_Logic/RankOwnedStates.h"
#include "../Engine_System/CollisionManager.h"
#include "../Engine_Logic/EventManager.h"
#include "../Engine_Logic/EventMainStates.h"
#include "EndingOwnedStates.h"
#include "SectionManager.h"

///////////////////////////////////////////////////////////
// Dev 
///////////////////////////////////////////////////////////
void CSectionDev::Enter(CSection* _pSection){
	EffectMgr->FadeInBlackPlane();
}

void CSectionDev::Execute(CSection* _pSection){
	// 이 검사가 Update보다 먼저
	if(EffectMgr->IfBlackFadeOutEnd()){
		_pSection->GetFSM()->ChangeState(SectionMainMenu->Instance());
		return;
	}	
}

void CSectionDev::Exit(CSection* _pSection){
	
}

///////////////////////////////////////////////////////////
// Load 
///////////////////////////////////////////////////////////
void CSectionLoad::Enter(CSection* _pSection){
	MouseMgr->ToggleUseCursor();
	
	m_pLoading->InitLoadingGameWorldContents();
}

void CSectionLoad::Execute(CSection* _pSection){
	m_pLoading->SetStepOfLoading(WorldMgr->GetWorld()->LoadGameWorld());

	if(m_pLoading->GetStepOfLoading() == 100){
		WorldMgr->SetLoadSuccess(true);
		_pSection->GetFSM()->RevertToPreviousState();
		return;
	}

	m_pLoading->Update();
	UIMgr->GetTextOfGame()->UpdateAdress();
}

void CSectionLoad::Exit(CSection* _pSection){
	MouseMgr->ToggleUseCursor();
	m_pLoading->InitLoadingComponents();
}

///////////////////////////////////////////////////////////
// Logo 
///////////////////////////////////////////////////////////
void CSectionLogo::Enter(CSection* _pSection){
	EffectMgr->FadeInBlackPlane();
	MouseMgr->OffCursor();
}

void CSectionLogo::Execute(CSection* _pSection){
	// 이 검사가 Update보다 먼저
	if(EffectMgr->IfBlackFadeOutEnd()){
		_pSection->GetFSM()->ChangeState(SectionMainMenu->Instance());
		return;
	}	

	m_pLogo->Update();	
}

void CSectionLogo::Exit(CSection* _pSection){
	MouseMgr->OnCursor();
}

///////////////////////////////////////////////////////////
// 메인메뉴 
///////////////////////////////////////////////////////////
void CSectionMainMenu::Enter(CSection* _pSection){
	EffectMgr->FadeInBlackPlane();

	if(m_pMainMenu->GetBody()->GetPriSca()->x < 1.0f)
		m_pMainMenu->GetFSM()->ChangeState(MainMenuRevert->Instance());

	MouseMgr->OnCursor();
	MouseMgr->Initialize();

	CameraMgr->SetMode(CCameraManager::SECTION);
	CameraMgr->CameraDefault();

	MP3Mgr->StopMusic();
  MP3Mgr->Reset();
	MP3Mgr->LoadMusic("./Sound/Main_BGM.mp3");
	MP3Mgr->PlayMusic();
	MP3Mgr->FadeInOut(true);
}

void CSectionMainMenu::Execute(CSection* _pSection){
	m_pMainMenu->Update();
	
	MP3Mgr->Loop();
}

void CSectionMainMenu::Exit(CSection* _pSection){
	MP3Mgr->FadeInOut(false);
	MP3Mgr->StopMusic();
}

///////////////////////////////////////////////////////////
// Credit 
///////////////////////////////////////////////////////////
void CSectionCredit::Enter(CSection* _pSection){
	MP3Mgr->FadeInOut(true);
	MouseMgr->OffCursor();

	MP3Mgr->Reset();
	if(_pSection->GetFSM()->PreviousState() == SectionMainMenu->Instance())
		MP3Mgr->LoadMusic("./Sound/Credit.mp3");
	else
		MP3Mgr->LoadMusic("./Sound/Ending.mp3");

	MP3Mgr->PlayMusic();
}

void CSectionCredit::Execute(CSection* _pSection){
	MP3Mgr->Loop();

	m_pCredit->Update();
}

void CSectionCredit::Exit(CSection* _pSection){
	MP3Mgr->FadeInOut(false);
	MP3Mgr->StopMusic();
}

///////////////////////////////////////////////////////////
// OST 
///////////////////////////////////////////////////////////
void CSectionOST::Enter(CSection* _pSection){
	MP3Mgr->FadeInOut(true);
	MouseMgr->OnCursor();
	MP3Mgr->StopMusic();
	MP3Mgr->Reset();
}

void CSectionOST::Execute(CSection* _pSection){
	m_pOST->Update();
	m_pOST->Render();
}

void CSectionOST::Exit(CSection* _pSection){
	MP3Mgr->FadeInOut(false);
	MP3Mgr->StopMusic();
}

///////////////////////////////////////////////////////////
// Rank 
///////////////////////////////////////////////////////////
CSectionRank::CSectionRank():m_pTimeAttack(new CRank("TimeAttack.txt", CRuntimeCmp<Ranking>::NORMAL)), 
															m_pSurvival(new CRank("Survival.txt", CRuntimeCmp<Ranking>::REVERSE)),
															m_pReturn(new COrgan()),
															m_pInitialize(new COrgan())
{
	m_pReturn->InitObject(EngineMgr->GetpDevice(), "./Image/SectionComposition/Rank/Return.dds", 190, 50, 1.0f, 0);
	m_pReturn->SetPriPos(&D3DXVECTOR3(-250.0f, -250.0f, 0.0f));
	m_pReturn->SetColor(&D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
	m_pInitialize->InitObject(EngineMgr->GetpDevice(), "./Image/SectionComposition/Rank/Initialize.dds", 220, 50, 1.0f, 0);
	m_pInitialize->SetPriPos(&D3DXVECTOR3(240.0f, -250.0f, 0.0f));
	m_pInitialize->SetColor(&D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
}

CSectionRank::~CSectionRank(){
	Delete<CRank*>(m_pTimeAttack); 
	Delete<CRank*>(m_pSurvival);
	Delete<COrgan*>(m_pReturn);
	Delete<COrgan*>(m_pInitialize);
}

void CSectionRank::Enter(CSection* _pSection){
	EffectMgr->FadeInBlackPlane();

	if(_pSection->GetFSM()->PreviousState() == SectionExtraTimeAttack->Instance())
		m_pTimeAttack->GetFSM()->ChangeState(RankRecord->Instance());
	else if(_pSection->GetFSM()->PreviousState() == SectionExtraSurvival->Instance())
		m_pSurvival->GetFSM()->ChangeState(RankRecord->Instance());

	MP3Mgr->Reset();
	MP3Mgr->LoadMusic("./Sound/Play_BGM.mp3");
	MP3Mgr->PlayMusic();
	MP3Mgr->FadeInOut(true);
}

void CSectionRank::Execute(CSection* _pSection){
	if(EffectMgr->IfBlackFadeOutEnd()){
		_pSection->GetFSM()->ChangeState(SectionMainMenu->Instance());
		return;
	}	
	
	if(CollisionMgr->Collision2DRectWithPoint(m_pReturn->GetRect(), MouseMgr->GetCursorPos())){
		m_pReturn->BigAndSmallXYAlternately(0.2f, 0.02f);
		if(MouseMgr->LeftClick()){
			EffectMgr->FadeOutBlackPlane();
		}
	}
	else{
		m_pReturn->SetPriSca(&D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	}

	if(CollisionMgr->Collision2DRectWithPoint(m_pInitialize->GetRect(), MouseMgr->GetCursorPos())){
		m_pInitialize->BigAndSmallXYAlternately(0.2f, 0.02f);
		if(MouseMgr->LeftClick()){
			m_pSurvival->InitializeScript();
			m_pTimeAttack->InitializeScript();
		}
	}
	else{
		m_pInitialize->SetPriSca(&D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	}

	m_pTimeAttack->Update();
	m_pSurvival->Update();

	m_pTimeAttack->Render();
	m_pSurvival->Render();

	m_pReturn->Render(&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pInitialize->Render(&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

void CSectionRank::Exit(CSection* _pSection){
	m_pTimeAttack->GetFSM()->ChangeState(RankMain->Instance());
	m_pSurvival->GetFSM()->ChangeState(RankMain->Instance());

	MP3Mgr->StopMusic();
	MP3Mgr->FadeInOut(false);
}

///////////////////////////////////////////////////////////
// ExtraTimeAttack 
///////////////////////////////////////////////////////////
void CSectionExtraTimeAttack::Enter(CSection* _pSection){
	if(!WorldMgr->GetLoadSuccess()){
		WorldMgr->SetParam("TimeAttack.txt");
		_pSection->GetFSM()->ChangeState(SectionLoad->Instance());
		UIMgr->GetTextOfGame()->GetAdress()->SetString("\\\\System");
		EventMgr->GetMain()->GetFSM()->ChangeState(EventMainTimeAttack->Instance());
		return;
	}

	MouseMgr->OffCursor();

	MP3Mgr->Reset();
	MP3Mgr->LoadMusic("./Sound/Play_BGM.mp3");
	MP3Mgr->PlayMusic();
	MP3Mgr->FadeInOut(true);

	EffectMgr->FadeInBlackPlane();

	CameraMgr->SetMode(CCameraManager::CONTROL);
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(static_cast<float>(WorldMgr->GetMapParam()->m_vStart.x), 
																		static_cast<float>(WorldMgr->GetMapParam()->m_vStart.y), 
																		-700.0f);
	CameraMgr->GetCamera()->SetPosition(&t_vPos);

	WorldMgr->OffPause();

	UIMgr->GetTextOfGame()->OnTime();
}

void CSectionExtraTimeAttack::Execute(CSection* _pSection){
	if(EffectMgr->IfBlackFadeOutEnd()){
		_pSection->GetFSM()->ChangeState(SectionRank->Instance());
		return;
	}	

	EffectMgr->PreEffectUpdate();

	// 세계 그리기
	WorldMgr->Update();

	EffectMgr->PostEffectUpdate();

	// UI 그리기
	UIMgr->Update();

	EventMgr->Update();

	MP3Mgr->Loop();
}

void CSectionExtraTimeAttack::Exit(CSection* _pSection){
	MP3Mgr->FadeInOut(false);
	MP3Mgr->StopMusic();

	WorldMgr->Initialize();

	CameraMgr->CameraDefault();
	CameraMgr->SetMode(CCameraManager::SECTION);

	MouseMgr->OnCursor();

	UIMgr->GetTextOfGame()->OffTime();
}

///////////////////////////////////////////////////////////
// ExtraSurvival 
///////////////////////////////////////////////////////////
void CSectionExtraSurvival::Enter(CSection* _pSection){
	if(!WorldMgr->GetLoadSuccess()){
		WorldMgr->SetParam("Survival.txt");
		_pSection->GetFSM()->ChangeState(SectionLoad->Instance());
		UIMgr->GetTextOfGame()->GetAdress()->SetString("\\\\System");
		return;
	}

	MouseMgr->OffCursor();

	MP3Mgr->Reset();
	MP3Mgr->LoadMusic("./Sound/Play_BGM.mp3");
	MP3Mgr->PlayMusic();
	MP3Mgr->FadeInOut(true);

	EffectMgr->FadeInBlackPlane();

	CameraMgr->SetMode(CCameraManager::CONTROL);
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(static_cast<float>(WorldMgr->GetMapParam()->m_vStart.x), 
																		static_cast<float>(WorldMgr->GetMapParam()->m_vStart.y), 
																		-700.0f);
	CameraMgr->GetCamera()->SetPosition(&t_vPos);

	WorldMgr->OffPause();

	UIMgr->GetTextOfGame()->OnTime();
}

void CSectionExtraSurvival::Execute(CSection* _pSection){
	if(EffectMgr->IfBlackFadeOutEnd()){
		_pSection->GetFSM()->ChangeState(SectionRank->Instance());
		return;
	}	

	EffectMgr->PreEffectUpdate();

	// 세계 그리기
	WorldMgr->Update();

	EffectMgr->PostEffectUpdate();

	// UI 그리기
	UIMgr->Update();

	MP3Mgr->Loop();
}

void CSectionExtraSurvival::Exit(CSection* _pSection){
	WorldMgr->Initialize();

	MP3Mgr->StopMusic();
	MP3Mgr->FadeInOut(false);

	CameraMgr->CameraDefault();
	CameraMgr->SetMode(CCameraManager::SECTION);

	MouseMgr->OnCursor();

	UIMgr->GetTextOfGame()->OffTime();
}

///////////////////////////////////////////////////////////
// 1st
///////////////////////////////////////////////////////////
void CSectionStory1st::Enter(CSection* _pSection){
	if(!WorldMgr->GetLoadSuccess()){
		WorldMgr->SetParam("Story_1st.txt");
		UIMgr->GetTextOfGame()->GetAdress()->SetString("\\\\My Love\\\\Empty");
		_pSection->GetFSM()->ChangeState(SectionLoad->Instance());
		EventMgr->GetMain()->GetFSM()->ChangeState(EventMainStory1st->Instance());
		return;
	}

	MouseMgr->OffCursor();

	MP3Mgr->Reset();
	MP3Mgr->LoadMusic("./Sound/Play_BGM.mp3");
	MP3Mgr->PlayMusic();
	MP3Mgr->FadeInOut(true);

	EffectMgr->FadeInBlackPlane();

	UIMgr->GetAbility()->OffControl();
	UIMgr->GetGauge()->OffActive();	

	CameraMgr->SetMode(CCameraManager::CONTROL);
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(static_cast<float>(WorldMgr->GetMapParam()->m_vStart.x), 
																		static_cast<float>(WorldMgr->GetMapParam()->m_vStart.y), 
																		-700.0f);
	CameraMgr->GetCamera()->SetPosition(&t_vPos);
	WorldMgr->OffPause();
}

void CSectionStory1st::Execute(CSection* _pSection){
	if(EffectMgr->IfBlackFadeOutEnd()){
		_pSection->GetFSM()->ChangeState(SectionStory2nd->Instance());
		return;
	}	

	EffectMgr->PreEffectUpdate();

	// 세계 그리기
	WorldMgr->Update();

	EffectMgr->PostEffectUpdate();

	// Event
	EventMgr->Update();

	// UI 그리기
	UIMgr->Update();

	MP3Mgr->Loop();
}

void CSectionStory1st::Exit(CSection* _pSection){
	WorldMgr->Initialize();

	CameraMgr->CameraDefault();
	CameraMgr->SetMode(CCameraManager::SECTION);

	MouseMgr->OnCursor();

	UIMgr->GetAbility()->OnControl();

	MP3Mgr->StopMusic();
	MP3Mgr->FadeInOut(false);
}

///////////////////////////////////////////////////////////
// 2nd
///////////////////////////////////////////////////////////
void CSectionStory2nd::Enter(CSection* _pSection){
	if(!WorldMgr->GetLoadSuccess()){
		WorldMgr->SetParam("Story_2nd.txt");
		UIMgr->GetTextOfGame()->GetAdress()->SetString("\\\\My Love\\\\My Photo");
		_pSection->GetFSM()->ChangeState(SectionLoad->Instance());
		EventMgr->GetMain()->GetFSM()->ChangeState(EventMainStory2nd->Instance());
		return;
	}

	MouseMgr->OffCursor();

	MP3Mgr->Reset();
	MP3Mgr->LoadMusic("./Sound/Play_BGM.mp3");
	MP3Mgr->PlayMusic();
	MP3Mgr->FadeInOut(true);

	UIMgr->GetAbility()->OffControl();
	UIMgr->GetGauge()->OffActive();

	EffectMgr->FadeInBlackPlane();

	CameraMgr->SetMode(CCameraManager::CONTROL);
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(static_cast<float>(WorldMgr->GetMapParam()->m_vStart.x), 
																		static_cast<float>(WorldMgr->GetMapParam()->m_vStart.y), 
																		-700.0f);
	CameraMgr->GetCamera()->SetPosition(&t_vPos);
	WorldMgr->OffPause();
}

void CSectionStory2nd::Execute(CSection* _pSection){
	if(EffectMgr->IfBlackFadeOutEnd()){
		_pSection->GetFSM()->ChangeState(SectionStory3rd->Instance());
		return;
	}	

	EffectMgr->PreEffectUpdate();

	// 세계 그리기
	WorldMgr->Update();

	EffectMgr->PostEffectUpdate();

	// Event
	EventMgr->Update();

	// UI 그리기
	UIMgr->Update();

	MP3Mgr->Loop();
}

void CSectionStory2nd::Exit(CSection* _pSection){
	WorldMgr->Initialize();

	MP3Mgr->StopMusic();
	MP3Mgr->FadeInOut(false);

	CameraMgr->CameraDefault();
	CameraMgr->SetMode(CCameraManager::SECTION);

	MouseMgr->OnCursor();

	UIMgr->GetAbility()->OnControl();
}

///////////////////////////////////////////////////////////
// 3rd
///////////////////////////////////////////////////////////
void CSectionStory3rd::Enter(CSection* _pSection){
	if(!WorldMgr->GetLoadSuccess()){
		WorldMgr->SetParam("Story_3rd.txt");
		UIMgr->GetTextOfGame()->GetAdress()->SetString("\\\\My Love\\\\My Document");
		_pSection->GetFSM()->ChangeState(SectionLoad->Instance());
		EventMgr->GetMain()->GetFSM()->ChangeState(EventMainStory3rd->Instance());
		return;
	}

	MouseMgr->OffCursor();

	MP3Mgr->Reset();
	MP3Mgr->LoadMusic("./Sound/Play_BGM.mp3");
	MP3Mgr->PlayMusic();
	MP3Mgr->FadeInOut(true);

	EffectMgr->FadeInBlackPlane();

	UIMgr->GetAbility()->OffControl();

	CameraMgr->SetMode(CCameraManager::CONTROL);
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(static_cast<float>(WorldMgr->GetMapParam()->m_vStart.x), 
																		static_cast<float>(WorldMgr->GetMapParam()->m_vStart.y), 
																		-700.0f);
	CameraMgr->GetCamera()->SetPosition(&t_vPos);
	WorldMgr->OffPause();
}

void CSectionStory3rd::Execute(CSection* _pSection){
	if(EffectMgr->IfBlackFadeOutEnd()){
		_pSection->GetFSM()->ChangeState(SectionStory4th->Instance());
		return;
	}	

	EffectMgr->PreEffectUpdate();

	// 세계 그리기
	WorldMgr->Update();

	EffectMgr->PostEffectUpdate();

	// Event
	EventMgr->Update();

	// UI 그리기
	UIMgr->Update();

	MP3Mgr->Loop();
}

void CSectionStory3rd::Exit(CSection* _pSection){
	WorldMgr->Initialize();
	
	CameraMgr->CameraDefault();
	CameraMgr->SetMode(CCameraManager::SECTION);

	MouseMgr->OnCursor();

	UIMgr->GetAbility()->OnControl();

	MP3Mgr->StopMusic();
	MP3Mgr->FadeInOut(false);
}

///////////////////////////////////////////////////////////
// 4th
///////////////////////////////////////////////////////////
void CSectionStory4th::Enter(CSection* _pSection){
	if(!WorldMgr->GetLoadSuccess()){
		WorldMgr->SetParam("Story_4th.txt");
		UIMgr->GetTextOfGame()->GetAdress()->SetString("\\\\My Love\\\\System");
		_pSection->GetFSM()->ChangeState(SectionLoad->Instance());
		EventMgr->GetMain()->GetFSM()->ChangeState(EventMainStory4th->Instance());
		return;
	}

	MouseMgr->OffCursor();

	MP3Mgr->Reset();
	MP3Mgr->LoadMusic("./Sound/Play_BGM.mp3");
	MP3Mgr->PlayMusic();
	MP3Mgr->FadeInOut(true);

	EffectMgr->FadeInBlackPlane();

	CameraMgr->SetMode(CCameraManager::CONTROL);
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(static_cast<float>(WorldMgr->GetMapParam()->m_vStart.x), 
																		static_cast<float>(WorldMgr->GetMapParam()->m_vStart.y), 
																		-700.0f);
	CameraMgr->GetCamera()->SetPosition(&t_vPos);
	WorldMgr->OffPause();
}

void CSectionStory4th::Execute(CSection* _pSection){
	if(EffectMgr->IfBlackFadeOutEnd()){
		_pSection->GetFSM()->ChangeState(SectionStory5th->Instance());
		return;
	}	

	EffectMgr->PreEffectUpdate();

	// 세계 그리기
	WorldMgr->Update();

	EffectMgr->PostEffectUpdate();

	// Event
	EventMgr->Update();

	// UI 그리기
	UIMgr->Update();	

	MP3Mgr->Loop();
}

void CSectionStory4th::Exit(CSection* _pSection){
	WorldMgr->Initialize();

	CameraMgr->CameraDefault();
	CameraMgr->SetMode(CCameraManager::SECTION);

	MouseMgr->OnCursor();

	MP3Mgr->StopMusic();
	MP3Mgr->FadeInOut(false);
}

///////////////////////////////////////////////////////////
// 5th
///////////////////////////////////////////////////////////
void CSectionStory5th::Enter(CSection* _pSection){
	if(!WorldMgr->GetLoadSuccess()){
		WorldMgr->SetParam("Story_5th.txt");
		UIMgr->GetTextOfGame()->GetAdress()->SetString(".......Transmitting");
		_pSection->GetFSM()->ChangeState(SectionLoad->Instance());
		EventMgr->GetMain()->GetFSM()->ChangeState(EventMainStory5th->Instance());
		return;
	}

	MouseMgr->OffCursor();

	MP3Mgr->Reset();
	MP3Mgr->LoadMusic("./Sound/Play_BGM.mp3");
	MP3Mgr->PlayMusic();
	MP3Mgr->FadeInOut(true);

	EffectMgr->FadeInBlackPlane();

	CameraMgr->SetMode(CCameraManager::CONTROL);
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(static_cast<float>(WorldMgr->GetMapParam()->m_vStart.x), 
																		static_cast<float>(WorldMgr->GetMapParam()->m_vStart.y), 
																		-700.0f);
	CameraMgr->GetCamera()->SetPosition(&t_vPos);
	WorldMgr->OffPause();
}

void CSectionStory5th::Execute(CSection* _pSection){
	if(EffectMgr->IfBlackFadeOutEnd()){
		_pSection->GetFSM()->ChangeState(SectionStory6th->Instance());
		return;
	}	

	EffectMgr->PreEffectUpdate();

	// 세계 그리기
	WorldMgr->Update();

	EffectMgr->PostEffectUpdate();

	// Event
	EventMgr->Update();

	// UI 그리기
	UIMgr->Update();

	MP3Mgr->Loop();
}

void CSectionStory5th::Exit(CSection* _pSection){
	WorldMgr->Initialize();

	MP3Mgr->StopMusic();
	MP3Mgr->FadeInOut(false);

	CameraMgr->CameraDefault();
	CameraMgr->SetMode(CCameraManager::SECTION);

	MouseMgr->OnCursor();
}

///////////////////////////////////////////////////////////
// 6th
///////////////////////////////////////////////////////////
void CSectionStory6th::Enter(CSection* _pSection){
	if(!WorldMgr->GetLoadSuccess()){
		WorldMgr->SetParam("Story_6th.txt");
		UIMgr->GetTextOfGame()->GetAdress()->SetString("\\\\Past Friend\\\\System");
		_pSection->GetFSM()->ChangeState(SectionLoad->Instance());
		EventMgr->GetMain()->GetFSM()->ChangeState(EventMainStory6th->Instance());
		return;
	}

	MouseMgr->OffCursor();

	MP3Mgr->Reset();
	MP3Mgr->LoadMusic("./Sound/Play_BGM.mp3");
	MP3Mgr->PlayMusic();
	MP3Mgr->FadeInOut(true);

	EffectMgr->FadeInBlackPlane();

	CameraMgr->SetMode(CCameraManager::CONTROL);
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(static_cast<float>(WorldMgr->GetMapParam()->m_vStart.x), 
																		static_cast<float>(WorldMgr->GetMapParam()->m_vStart.y), 
																		-700.0f);
	CameraMgr->GetCamera()->SetPosition(&t_vPos);
	WorldMgr->OffPause();
}

void CSectionStory6th::Execute(CSection* _pSection){
	if(EffectMgr->IfBlackFadeOutEnd()){
		_pSection->GetFSM()->ChangeState(SectionEnding->Instance());
		return;
	}	

	EffectMgr->PreEffectUpdate();

	// 세계 그리기
	WorldMgr->Update();

	EffectMgr->PostEffectUpdate();

	// Event
	EventMgr->Update();

	// UI 그리기
	UIMgr->Update();

	MP3Mgr->Loop();
}

void CSectionStory6th::Exit(CSection* _pSection){
	WorldMgr->Initialize();

	MP3Mgr->StopMusic();
	MP3Mgr->FadeInOut(false);

	CameraMgr->CameraDefault();
	CameraMgr->SetMode(CCameraManager::SECTION);

	MouseMgr->OnCursor();
}

///////////////////////////////////////////////////////////
// Ending
///////////////////////////////////////////////////////////
void CSectionEnding::Enter(CSection* _pSection){
	MouseMgr->OffCursor();
	m_pEnding->GetFSM()->ChangeState(EndingMain->Instance());
	CameraMgr->SetMode(CCameraManager::SECTION);

	EffectMgr->FadeInBlackPlane();
}

void CSectionEnding::Execute(CSection* _pSection){
	if(EffectMgr->IfBlackFadeOutEnd()){
		if(SectionMgr->GetSign() == CSectionManager::MAINMENU){
			_pSection->GetFSM()->ChangeState(SectionMainMenu->Instance());
			return;
		}
		else if(SectionMgr->GetSign() == CSectionManager::CREDIT){
			_pSection->GetFSM()->ChangeState(SectionCredit->Instance());
			return;
		}
	}	

	m_pEnding->Update();

	// Event
	EventMgr->Update();
}

void CSectionEnding::Exit(CSection* _pSection){
	CameraMgr->CameraDefault();
	WorldMgr->Initialize();
	MP3Mgr->FadeInOut(false);
}

///////////////////////////////////////////////////////////
// 게임 끝
///////////////////////////////////////////////////////////
void CSectionExit::Enter(CSection* _pSection){
	EffectMgr->FadeInBlackPlane();
}	

void CSectionExit::Execute(CSection* _pSection){
	// 이 검사가 Update보다 먼저
	if(EffectMgr->IfBlackFadeOutEnd()){
		PostQuitMessage(0);
		return;
	}	

	m_pLogo->Update();	
}

void CSectionExit::Exit(CSection* _pSection){
	
}