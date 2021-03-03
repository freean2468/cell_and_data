#include "CreditOwnedStates.h"
#include "../Engine_System/MouseManager.h"
#include "../Engine_Logic/SectionManager.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CCreditUsual::Enter(CCredit* _pCredit){
	m_pDelay->InitTimer(2500);
	m_nStep = 0;
	_pCredit->UniformOrganScaZero();
}

void CCreditUsual::Execute(CCredit* _pCredit){
	if(m_pDelay->IsElapseTimer()){
		m_nStep++;

		if(m_nStep == CCredit::DEVELOPER)
			m_pDelay->InitTimer(5000);
		else if(m_nStep == CCredit::SPECIAL)
			m_pDelay->InitTimer(2000);
		else if(m_nStep == CCredit::TEACHER)
			m_pDelay->InitTimer(6500);
		else if(m_nStep == CCredit::FRIENDS)
			m_pDelay->InitTimer(5500);
		else if(m_nStep == CCredit::SOFTMAX)
			m_pDelay->InitTimer(5000);
		else
			m_pDelay->InitTimer(4000);
	}

	for(int i = 0; i < _pCredit->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_pAtt = _pCredit->GetAttachment(i);

		if(t_pAtt->GetAttType() == m_nStep){
			if(t_pAtt->GetPriSca()->x < 1.0f)
				t_pAtt->IncreaseSca(0.05f);

			if(m_nStep != 0){
				if(_pCredit->GetAttachment(m_nStep-1)->GetPriSca()->x > 0.0f)
					_pCredit->GetAttachment(m_nStep-1)->DecreaseSca(0.05f);
			}
			break;
		}
	}

	_pCredit->RenderOrgan();

	if(m_nStep >= _pCredit->GetAttachmentArray()->GetSize() || 
		MouseMgr->LeftClick() || MouseMgr->RightClick()){
		_pCredit->GetFSM()->ChangeState(CreditRevert->Instance());
		return;
	}
}

void CCreditUsual::Exit(CCredit* _pCredit){
	
}

bool CCreditUsual::OnMessage(CCredit* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Revert State
///////////////////////////////////////////////////////////
void CCreditRevert::Enter(CCredit* _pCredit){
	
}

void CCreditRevert::Execute(CCredit* _pCredit){
	bool t_bNone = true;

	for(int i = 0; i < _pCredit->GetAttachmentArray()->GetSize(); i++){
		if(_pCredit->GetAttachment(i)->GetPriSca()->x <= 0.0f)
			if(t_bNone) t_bNone = true;
		else{
			t_bNone = false;
		}

		_pCredit->GetAttachment(i)->DecreaseSca(0.05f);
	}

	_pCredit->RenderOrgan();

	if(t_bNone){
		SectionMgr->GetSection()->GetFSM()->ChangeState(SectionMainMenu->Instance());
		_pCredit->GetFSM()->ChangeState(CreditUsual->Instance());
		return;
	}
}

void CCreditRevert::Exit(CCredit* _pCredit){
	
}

bool CCreditRevert::OnMessage(CCredit* agent, const Telegram& _rMsg){
	return false;
}