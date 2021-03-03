#include "Ability.h"
#include "AbilityOwnedStates.h"
#include "../Engine_System/CameraManager.h"
#include "../Engine_System/EngineManager.h"
#include "../Engine_System/WaveManager.h"
#include "../Game_Factor/WorldManager.h"
#include "Controller.h"
#include "VirusOwnedStates.h"
#include "../Engine_Logic/EventManager.h"
#include "DataOwnedStates.h"
#include "../Engine_System/EntityType.h"
#include "VacineOwnedStates.h"

CAbility::CAbility(int _nEntityType) : COrganEntity(0),
									m_pClosestEntity(NULL),
									m_bControlUse(true),
									m_bControlling(false),
									m_bActive(false),
									m_eAbility(NONE)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CAbility>(this);

	LoadEntityData("./script/UserInterface/Ability/Ability.txt");

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(AbilityInActive->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	this->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
}

CAbility::~CAbility(){
	Delete< CStateMachine<CAbility>* >(m_pStateMachine);
}

void CAbility::Initialize(){
	m_pClosestEntity = NULL;
	m_bControlUse = true;
	m_bControlling = false;
	m_bActive = false;
	m_eAbility = NONE;
}

void CAbility::RenderOrgan(){
	if(GetAttachmentArray()->GetSize()){
		for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){
			BodySetting();
			GetAttachmentArray()->Get(i)->RenderApplyScale(GetChainPos(), GetChainSca(), GetChainCen());
			InitChainVector();
		}
	}

	InitChainVector();
}

void CAbility::Update(double _dTimeElapsed){
	if(!m_pClosestEntity && !m_bControlling){
		m_bActive = false;
		GetFSM()->ChangeState(AbilityInActive->Instance());

		if(CameraMgr->GetMode() != CCameraManager::SCRIPT)
			CameraMgr->SetMode(CCameraManager::CONTROL);
		return;
	}
	else if(m_bControlling){
		m_bActive = true;
		if(EngineMgr->KeyUp(DIK_3)){	m_eAbility = CONTROL;	}
		else{			m_eAbility = NONE;		}

		if(!WorldMgr->GetWorld()->CheckIntersectionFireWallForAbility() && m_eAbility == CONTROL){
			Controller->GetControlData()->SetState(CData::INFECTION);
			Controller->GetControlData()->GetSteering()->ControlledOff();
			Controller->GetController()->GetFSM()->ChangeState(VirusControlOut->Instance());
			m_bControlling = false;
		}
	}
	else{
		m_bActive = true;

		if(!EventMgr->GetScript()){
			if(m_pClosestEntity->GetEntityType() == DATA){
				if(EngineMgr->KeyDown(DIK_2)){	m_eAbility = ABSORPTION;	}
				else if(EngineMgr->KeyUp(DIK_3)){	m_eAbility = CONTROL;		}
				else{			m_eAbility = NONE;		}

				if(m_eAbility == ABSORPTION){
					static_cast<CData*>(m_pClosestEntity)->SetState(CData::ABSORPTION);
				}
				else if(m_eAbility == CONTROL){
					m_bControlling = true;
					Controller->SetControlData(static_cast<CData*>(m_pClosestEntity));
					Controller->GetControlData()->SetState(CData::NORMAL);
					Controller->GetControlData()->GetSteering()->ControlledOn();
					Controller->GetControlData()->GetFSM()->ChangeState(DataCure->Instance());
					Controller->GetController()->GetFSM()->ChangeState(VirusControlIn->Instance());
				}
			}
			else if(m_pClosestEntity->GetEntityType() == VACINE){
				if(EngineMgr->KeyUp(DIK_1)){	m_eAbility = DESTROY;	}
				else{			m_eAbility = NONE;		}

				if(m_eAbility == DESTROY){
					static_cast<CVacine*>(m_pClosestEntity)->GetFSM()->ChangeState(VacineDestroy->Instance());
				}
			}

			if(m_eAbility != NONE)
				CameraMgr->SetMode(CCameraManager::ABILITY);
			else
				CameraMgr->SetMode(CCameraManager::CONTROL);
		}
	}

	m_pStateMachine->Update();
}