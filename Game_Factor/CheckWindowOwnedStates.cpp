#include "CheckWindowOwnedStates.h"
#include "../Engine_System/MouseManager.h"
#include "../Engine_System/CameraManager.h"
#include "../Engine_Logic/SectionManager.h"
#include "../Engine_System/CollisionManager.h"
#include "../Game_Factor/WorldManager.h"
#include "../Game_Factor/UIManager.h"
#include "../Engine_System/MessageManager.h"
#include "../Engine_System/EntityType.h"
#include "../Engine_System/MessageTypes.h"
#include "../Engine_System/Telegram.h"
#include "../Engine_System/EffectManager.h"

///////////////////////////////////////////////////////////
// YesNo State
///////////////////////////////////////////////////////////
void CCheckWindowYesNo::Enter(CCheckWindow* _pCheckWindow){
	for(int i = 0; i < _pCheckWindow->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_pAtt = _pCheckWindow->GetAttachment(i);

		if(t_pAtt->GetAttType() == CCheckWindow::YES){
			t_pAtt->SetAlpha(0.5f);
		}
		else if(t_pAtt->GetAttType() == CCheckWindow::NO){
			t_pAtt->SetAlpha(0.5f);
		}
		else if(t_pAtt->GetAttType() == CCheckWindow::OK){
			t_pAtt->SetAlpha(0.0f);
		}
	}
}

void CCheckWindowYesNo::Execute(CCheckWindow* _pCheckWindow){
	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	_pCheckWindow->GetBody()->GetPriPos()->x = t_vPos.x;
	_pCheckWindow->GetBody()->GetPriPos()->y = t_vPos.y;
	_pCheckWindow->GetBody()->GetPriPos()->z = t_vPos.z + 700.0f;

	for(int i = 0; i < _pCheckWindow->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_pAtt = _pCheckWindow->GetAttachment(i);

		if(CollisionMgr->Collision2DRectWithPoint(t_pAtt->GetRect(), MouseMgr->GetCursorPos())){
			if(t_pAtt->GetAttType() != CCheckWindow::OK)
				t_pAtt->SetAlpha(1.0f);

			if(MouseMgr->LeftClick()){
				if(t_pAtt->GetAttType() == CCheckWindow::YES){
					MessageMgr->DispatchMessage(SEND_MSG_IMMEDIATELY, CHECK, CHECK, Msg_True, NO_ADDITIONAL_INFO);
				}
				else if(t_pAtt->GetAttType() == CCheckWindow::NO){
					MessageMgr->DispatchMessage(SEND_MSG_IMMEDIATELY, CHECK, CHECK, Msg_False, NO_ADDITIONAL_INFO);
				}
			}
		}
		else{
			if(t_pAtt->GetAttType() == CCheckWindow::OK)
				t_pAtt->SetAlpha(0.0f);
			else
				t_pAtt->SetAlpha(0.5f);
		}
	}

	_pCheckWindow->RenderOrgan();
}

void CCheckWindowYesNo::Exit(CCheckWindow* _pCheckWindow){

}

bool CCheckWindowYesNo::OnMessage(CCheckWindow* agent, const Telegram& _rMsg){
	if(_rMsg.m_nSender == CHECK){
		if(_rMsg.m_nMsg == Msg_True){
			EffectMgr->FadeOutBlackPlane();
			SectionMgr->GetSection()->GetFSM()->ChangeState(SectionMgr->GetSection()->GetFSM()->CurrentState());
			MouseMgr->OffCursor();
		}
		else{
			EffectMgr->FadeOutBlackPlane();
			SectionMgr->GetSection()->GetFSM()->ChangeState(SectionMainMenu->Instance());
			MouseMgr->OnCursor();
		}
		
		agent->OffActive();
		WorldMgr->OffPause();
	}

	if(_rMsg.m_nMsg == Msg_Active){
		agent->OnActive();
		WorldMgr->OnPause();
		MouseMgr->OnCursor();
	}
	else if(_rMsg.m_nMsg == Msg_InActive){
		agent->OffActive();
		WorldMgr->OffPause();
		MouseMgr->OffCursor();
	}
		
	if(_rMsg.m_nSender == VIRUS){
		UIMgr->GetCW()->GivenLine("Retry?");
	}
	return true;
}

///////////////////////////////////////////////////////////
// OK State
///////////////////////////////////////////////////////////
void CCheckWindowOK::Enter(CCheckWindow* _pCheckWindow){
	for(int i = 0; i < _pCheckWindow->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_pAtt = _pCheckWindow->GetAttachment(i);

		if(t_pAtt->GetAttType() == CCheckWindow::YES){
			t_pAtt->SetAlpha(0.0f);
		}
		else if(t_pAtt->GetAttType() == CCheckWindow::NO){
			t_pAtt->SetAlpha(0.0f);
		}
		else if(t_pAtt->GetAttType() == CCheckWindow::OK){
			t_pAtt->SetAlpha(1.0f);
		}
	}
}

void CCheckWindowOK::Execute(CCheckWindow* _pCheckWindow){
	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	_pCheckWindow->GetBody()->GetPriPos()->x = t_vPos.x;
	_pCheckWindow->GetBody()->GetPriPos()->y = t_vPos.y;
	_pCheckWindow->GetBody()->GetPriPos()->z = t_vPos.z + 700.0f;

	WorldMgr->OnPause();

	for(int i = 0; i < _pCheckWindow->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_pAtt = _pCheckWindow->GetAttachment(i);

		if(CollisionMgr->Collision2DRectWithPoint(t_pAtt->GetRect(), MouseMgr->GetCursorPos())){
			t_pAtt->SetPriSca(&D3DXVECTOR3(1.2f, 1.2f, 1.2f));

			if(MouseMgr->LeftClick()){				
				MessageMgr->DispatchMessage(SEND_MSG_IMMEDIATELY, CHECK, CHECK, Msg_True, NO_ADDITIONAL_INFO);				
			}
		}
		else
			t_pAtt->SetPriSca(&D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	}

	_pCheckWindow->RenderOrgan();
}

void CCheckWindowOK::Exit(CCheckWindow* _pCheckWindow){

}

bool CCheckWindowOK::OnMessage(CCheckWindow* agent, const Telegram& _rMsg){
	return false;
}