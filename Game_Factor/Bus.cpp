#include "Bus.h"
#include "BusOwnedStates.h"
#include "../Engine_Logic/EventManager.h"
#include "../Engine_System/CollisionManager.h"
#include "../Game_Factor/Controller.h"
#include "../Engine_Logic/SectionManager.h"
#include "../Engine_System/MessageManager.h"
#include "../Engine_System/EntityType.h"
#include "../Game_Factor/WorldManager.h"
#include "../Engine_System/MessageTypes.h"
#include "../Engine_System/EffectManager.h"

CBus::CBus():COrganEntity(),
							m_bActive(false)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CBus>(this);

	LoadEntityData("./script/GameFactor/Bus/Bus.txt");

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(BusActive->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	this->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, this->GetBody()->GetAlpha()));

	ResizeObject(0.2f);
}

CBus::~CBus(){
	Delete<CStateMachine<CBus>*>(m_pStateMachine);
}

void CBus::Initialize(){
	ResizeObject(2.0f);

	this->UniformOrganScaZero();

	GetFSM()->ChangeState(BusActive->Instance());
}

void CBus::Update(double _dTimeElapsed){
	if(m_bActive){
		if(!EventMgr->GetNextScript() && CollisionMgr->Collision2DOrganByRadius(Controller->GetController()->GetAttachment(CVirus::CORE),GetBody())){
			if(SectionMgr->GetSection()->GetFSM()->CurrentState() == SectionExtraTimeAttack->Instance()){
				MessageMgr->DispatchMessage(SEND_MSG_IMMEDIATELY, VIRUS, IW, Msg_Active, NO_ADDITIONAL_INFO);
				m_bActive = false;
			}
			else{
				EventMgr->OnNextScript();
				WorldMgr->OnPause();
				EffectMgr->FadeOutBlackPlane();
			}
		}

		m_pStateMachine->Update();
	}
}