#include "Controller.h"
#include "VirusOwnedStates.h"
#include "WorldManager.h"

CController::CController() : m_pVirus(NULL),
							m_pControl(NULL),
							m_bGrowing(false)
{
	
}

CController::~CController(){
	Delete<CVirus*>(m_pVirus);
}

void CController::Grow(CGrowth::GROWTH _eGrowth){
	if(_eGrowth == CGrowth::SECOND && Controller->GetController()->GetGrowth()->IsGrowth(CGrowth::FIRST)){
		if(m_nSecondBRadius >= Controller->GetController()->GetRadius()){
			if(m_bGrowing == false)
				Controller->GetController()->GetFSM()->ChangeState(VirusGrowing->Instance());
			Controller->GetController()->ResizeObject(1.005f);
			m_bGrowing = true;
		}
		else{
			WorldMgr->GetWorld()->GetBus()->Initialize();
			Controller->GetController()->GetGrowth()->SetGrowth(CGrowth::SECOND);
			m_bGrowing = false;
			Controller->GetController()->GetFSM()->ChangeState(VirusNormal->Instance());
		}
	}

	if(_eGrowth == CGrowth::THIRD && Controller->GetController()->GetGrowth()->IsGrowth(CGrowth::SECOND)){
		if(m_nThirdBRadius >= Controller->GetController()->GetRadius()){
			if(m_bGrowing == false)
				Controller->GetController()->GetFSM()->ChangeState(VirusGrowing->Instance());
			Controller->GetController()->ResizeObject(1.005f);
			m_bGrowing = true;
		}
		else{
			WorldMgr->GetWorld()->GetBus()->Initialize();
			Controller->GetController()->GetGrowth()->SetGrowth(CGrowth::THIRD);
			m_bGrowing = false;
			Controller->GetController()->GetFSM()->ChangeState(VirusNormal->Instance());
		}
	}
}