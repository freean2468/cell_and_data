#include "BusOwnedStates.h"

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
void CBusActive::Enter(CBus* _pBus){
	
}

void CBusActive::Execute(CBus* _pBus){
	CBody* t_pBody = _pBus->GetBody();

	if(t_pBody->GetPriSca()->x < 1.0f){
		t_pBody->IncreaseSca(0.05f);

		for(int i = 0; i < _pBus->GetAttachmentArray()->GetSize(); ++i){
			CAttachment* t_Att = _pBus->GetAttachment(i);

			t_Att->IncreaseSca(0.05f);
		}
	}
	else	_pBus->GetFSM()->ChangeState(BusMaintain->Instance());

	_pBus->RenderOrgan();
}

void CBusActive::Exit(CBus* _pBus){

}

bool CBusActive::OnMessage(CBus* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Maintain State
///////////////////////////////////////////////////////////
void CBusMaintain::Enter(CBus* _pBus){
	
}

void CBusMaintain::Execute(CBus* _pBus){
	CBody* t_pBody = _pBus->GetBody();

	for(int i = 0; i < _pBus->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_Att = _pBus->GetAttachment(i);

		if(t_Att->GetAttType() == CBus::HOLE){
			t_Att->BigAndSmall(1.1f, 0.9f, 0.01f);
		}
		else if(t_Att->GetAttType() == CBus::FIRST){
			t_Att->BigAndSmall(1.1f, 0.9f, 0.01f);
			t_Att->RotZ(D3DX_PI * 0.005f);
		}
		else if(t_Att->GetAttType() == CBus::SECOND){
			t_Att->BigAndSmall(1.2f, 0.9f, 0.005f);
			t_Att->RotZ(D3DX_PI * 0.01f);
		}
		else if(t_Att->GetAttType() == CBus::THIRD){
			t_Att->BigAndSmall(1.1f, 0.8f, 0.007f);
			t_Att->RotZ(D3DX_PI * 0.007f);
		}		
	}

	_pBus->RenderOrgan();
}

void CBusMaintain::Exit(CBus* _pBus){

}

bool CBusMaintain::OnMessage(CBus* agent, const Telegram& _rMsg){
	return false;
}