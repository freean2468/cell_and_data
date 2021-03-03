#include "AbilityOwnedStates.h"
#include "Controller.h"
#include "UIManager.h"
#include "../Engine_System/EntityType.h"
#include "WorldManager.h"

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
void CAbilityActive::Enter(CAbility* _pAbility){
	if(Controller->GetController()->GetGrowth()->IsGrowth(CGrowth::FIRST)){
		m_fFrequency = 0.005f;
	}
	else if(Controller->GetController()->GetGrowth()->IsGrowth(CGrowth::SECOND)){
		m_fFrequency = 0.01f;
	}
	else if(Controller->GetController()->GetGrowth()->IsGrowth(CGrowth::THIRD)){
		m_fFrequency = 0.04f;
	}		

	if(_pAbility->GetControlUse()){
		_pAbility->GetAttachmentFromType(CAbility::CONTROL)->SetAlpha(0.5f);
		_pAbility->GetAttachmentFromType(CAbility::THIRD)->SetAlpha(0.5f);
	}
	else{
		_pAbility->GetAttachmentFromType(CAbility::CONTROL)->SetAlpha(0.0f);
		_pAbility->GetAttachmentFromType(CAbility::THIRD)->SetAlpha(0.0f);
	}
}

void CAbilityActive::Execute(CAbility* _pAbility){	
	if(_pAbility->GetControlUse()){
		_pAbility->GetAttachmentFromType(CAbility::CONTROL)->SetAlpha(0.5f);
		_pAbility->GetAttachmentFromType(CAbility::THIRD)->SetAlpha(0.5f);
	}
	else{
		_pAbility->GetAttachmentFromType(CAbility::CONTROL)->SetAlpha(0.0f);
		_pAbility->GetAttachmentFromType(CAbility::THIRD)->SetAlpha(0.0f);
	}

	_pAbility->GetBody()->GetPriPos()->x = _pAbility->GetClosestEntity()->GetBody()->GetPriPos()->x;
	_pAbility->GetBody()->GetPriPos()->y = _pAbility->GetClosestEntity()->GetBody()->GetPriPos()->y;
	_pAbility->GetBody()->GetPriPos()->z = _pAbility->GetClosestEntity()->GetBody()->GetPriPos()->z;

	_pAbility->GetBody()->IncreaseSca(m_fFrequency);

	for(int i = 0; i < _pAbility->GetAttachmentArray()->GetSize(); i++){		
		_pAbility->GetAttachment(i)->NoneRelateIncreaseSca(m_fFrequency);
	}

	if(Controller->GetController()->GetGrowth()->IsGrowth(CGrowth::FIRST)){
		if(_pAbility->GetBody()->GetPriSca()->x >= 0.1f)
			_pAbility->GetFSM()->ChangeState(AbilityMaintain->Instance());
	}
	else if(Controller->GetController()->GetGrowth()->IsGrowth(CGrowth::SECOND)){
		if(_pAbility->GetBody()->GetPriSca()->x >= 0.15f)
			_pAbility->GetFSM()->ChangeState(AbilityMaintain->Instance());
	}
	else if(Controller->GetController()->GetGrowth()->IsGrowth(CGrowth::THIRD)){
		if(_pAbility->GetBody()->GetPriSca()->x >= 0.3f)
			_pAbility->GetFSM()->ChangeState(AbilityMaintain->Instance());
	}				

	_pAbility->RenderOrgan();
}

void CAbilityActive::Exit(CAbility* _pAbility){

}

bool CAbilityActive::OnMessage(CAbility* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Maintain State
///////////////////////////////////////////////////////////
void CAbilityMaintain::Enter(CAbility* _pAbility){
	
}

void CAbilityMaintain::Execute(CAbility* _pAbility){
	if(!_pAbility->GetActive() || !Controller->GetController()->IsAlive() || !_pAbility->GetClosestEntity()){
		_pAbility->GetFSM()->ChangeState(AbilityInActive->Instance());
		return;
	}

	_pAbility->GetBody()->GetPriPos()->x = _pAbility->GetClosestEntity()->GetBody()->GetPriPos()->x;
	_pAbility->GetBody()->GetPriPos()->y = _pAbility->GetClosestEntity()->GetBody()->GetPriPos()->y;
	_pAbility->GetBody()->GetPriPos()->z = _pAbility->GetClosestEntity()->GetBody()->GetPriPos()->z;

	for(int i = 0; i < _pAbility->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_pAtt = _pAbility->GetAttachment(i);
		
		switch(t_pAtt->GetAttType()){			
			case CAbility::DESTROY:
			case CAbility::FIRST:
				if(_pAbility->GetAbility() == CAbility::DESTROY){
					t_pAtt->BigAndSmallXYAlternately(0.005f, 0.001f);
					t_pAtt->SetAlpha(1.0f);
				}
				else{
					if(!UIMgr->GetAbility()->GetControlling())
						if(_pAbility->GetClosestEntity()->GetEntityType() != DATA)
							t_pAtt->BlinkAlpha(0.5f, 1.0f, 0.015f);
				}
				break;
			case CAbility::ABSORPTION:
			case CAbility::SECOND:
				if(_pAbility->GetAbility() == CAbility::ABSORPTION){
					t_pAtt->BigAndSmallXYAlternately(0.005f, 0.001f);
					t_pAtt->SetAlpha(1.0f);
				}	
				else{
					if(!UIMgr->GetAbility()->GetControlling())
						if(_pAbility->GetClosestEntity()->GetEntityType() != VACINE)
							t_pAtt->BlinkAlpha(0.5f, 1.0f, 0.015f);
				}
				break;
			case CAbility::CONTROL:			
			case CAbility::THIRD:
				if(_pAbility->GetAbility() == CAbility::CONTROL){
					t_pAtt->BigAndSmallXYAlternately(0.005f, 0.001f);
					t_pAtt->SetAlpha(1.0f);
				}	
				else{
					if(_pAbility->GetClosestEntity()->GetEntityType() != VACINE){
						if(_pAbility->GetControlUse()){
							if(!WorldMgr->GetWorld()->CheckIntersectionFireWallForAbility())
								t_pAtt->BlinkAlpha(0.5f, 1.0f, 0.015f);
						}
						else
							t_pAtt->SetAlpha(0.0f);
					}
				}
				break;
			default: break;
		}
	}

	_pAbility->RenderOrgan();
}

void CAbilityMaintain::Exit(CAbility* _pAbility){

}

bool CAbilityMaintain::OnMessage(CAbility* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Inactive State
///////////////////////////////////////////////////////////
void CAbilityInActive::Enter(CAbility* _pAbility){
	
}

void CAbilityInActive::Execute(CAbility* _pAbility){
	if(Controller->GetController()->IsAlive() && _pAbility->GetClosestEntity()){
		_pAbility->UniformOrganScaZero();
		_pAbility->UniformOrganAlpha(0.5f);
		_pAbility->GetFSM()->ChangeState(AbilityActive->Instance());
	}
}

void CAbilityInActive::Exit(CAbility* _pAbility){

}

bool CAbilityInActive::OnMessage(CAbility* agent, const Telegram& _rMsg){
	return false;
}