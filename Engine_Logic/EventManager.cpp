#include "EventManager.h"
#include "../Engine_System/EngineManager.h"
#include "EventMainStates.h"
#include "EventSubStates.h"
#include "../Engine_System/CameraManager.h"
#include "../Game_Factor/WorldManager.h"

CEventManager::CEventManager(): m_pMain(new CEvent()),
								m_pSub(new CEvent()),
								m_pScriptLoader(NULL),
								m_pBalloon(new CMessageWindow(-1, CMessageWindow::BALLOON)),
								m_pDW(new CDialogWindow(-1)),
								m_bScript(false),
								m_bNextScript(false),
								m_nEventStep(0),
								m_pTimer(new CTimer(0))
{
	m_pFriend = new CBody();
	m_pLove = new CBody();

	m_pFriend->InitObject(EngineMgr->GetpDevice(), "./Image/UserInterface/CharacterPresent/Friend.dds",
		170, 170, 1.0f, 0);
	m_pLove->InitObject(EngineMgr->GetpDevice(), "./Image/UserInterface/CharacterPresent/Love.dds",
		170, 170, 1.0f, 0);

	m_pFriend->SetColor(&D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
	m_pLove->SetColor(&D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));

	EventMgr->GetBalloon()->GetText()->SetFontScale(5);

	m_pMain->GetFSM()->SetCurrentState(EventMain->Instance());
	m_pMain->GetFSM()->CurrentState()->Enter(m_pMain);

	m_pSub->GetFSM()->SetCurrentState(EventSub->Instance());
	m_pSub->GetFSM()->CurrentState()->Enter(m_pSub);
}

CEventManager::~CEventManager(){
	Delete<CScriptLoader*>(m_pScriptLoader);
	Delete<CMessageWindow*>(m_pBalloon);
	Delete<CDialogWindow*>(m_pDW);
	Delete<CEvent*>(m_pMain);
	Delete<CEvent*>(m_pSub);
	Delete<CTimer*>(m_pTimer);
	Delete<CBody*>(m_pFriend);
	Delete<CBody*>(m_pLove);
}

void CEventManager::Initialize(int _nEventStep, DWORD _dwTime){
	m_nEventStep = _nEventStep;
	m_pTimer->InitTimer(_dwTime);

	m_pMain->GetFSM()->SetCurrentState(EventMain->Instance());
	m_pMain->GetFSM()->CurrentState()->Enter(m_pMain);

	m_pSub->GetFSM()->SetCurrentState(EventSub->Instance());
	m_pSub->GetFSM()->CurrentState()->Enter(m_pSub);
}

void CEventManager::Update(){
	if(GetScript()){
		if(CameraMgr->GetMode() != CCameraManager::SCRIPT && !m_pSub->GetFSM()->isInState(EventSubBreakHeart->Instance())){
			if(EngineMgr->KeyUp(DIK_RETURN)){
				if(m_pScriptLoader->NextScript()){
					OffScript();

					WorldMgr->OffPause();
					return;
				}
			}
		}
		OnScript();
		WorldMgr->OnPause();

		m_pScriptLoader->Update();
	}

	m_pMain->Update();
	m_pSub->Update();
}

void CEventManager::LoadScript(char* _pstrFile){
	OnScript();

	std::string t_strAdress;

	t_strAdress="./Script/Script/";
	t_strAdress+=_pstrFile;

	Delete<CScriptLoader*>(m_pScriptLoader);
	m_pScriptLoader = new CScriptLoader(t_strAdress.c_str());

	if(m_pScriptLoader->GetMaxIndex() <= 0){
		OffScript();
	}
	else{
		OffNextScript();
	}
}