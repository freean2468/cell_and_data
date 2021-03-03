#include "InputWindowOwnedStates.h"
#include "../Engine_System/CameraManager.h"
#include "../Engine_System/CollisionManager.h"
#include "../Engine_System/MouseManager.h"
#include "../Engine_System/MessageManager.h"
#include "../Game_Factor/UIManager.h"
#include "../Engine_System/EntityType.h"
#include "../Engine_System/MessageTypes.h"
#include "../Engine_System/Telegram.h"
#include "../Engine_System/EffectManager.h"
#include "../Game_Factor/WorldManager.h"

///////////////////////////////////////////////////////////
// OK State
///////////////////////////////////////////////////////////
void CInputWindowOK::Enter(CInputWindow* _pInputWindow){
	 
}

void CInputWindowOK::Execute(CInputWindow* _pInputWindow){
	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	_pInputWindow->GetBody()->GetPriPos()->x = t_vPos.x;
	_pInputWindow->GetBody()->GetPriPos()->y = t_vPos.y;
	_pInputWindow->GetBody()->GetPriPos()->z = t_vPos.z + 700.0f;

	if(CollisionMgr->Collision2DRectWithPoint(_pInputWindow->GetAttachmentFromType(CInputWindow::OK)->GetRect(), 
																						MouseMgr->GetCursorPos())){
		_pInputWindow->GetAttachmentFromType(CInputWindow::OK)->SetAlpha(1.0f);

		if(MouseMgr->LeftClick()){
			MessageMgr->DispatchMessage(SEND_MSG_IMMEDIATELY, IW, IW, Msg_InActive, NO_ADDITIONAL_INFO);
		}
	}
	else{
		_pInputWindow->GetAttachmentFromType(CInputWindow::OK)->SetAlpha(0.5f);
	}

	_pInputWindow->RenderOrgan();
}

void CInputWindowOK::Exit(CInputWindow* _pInputWindow){

}

bool CInputWindowOK::OnMessage(CInputWindow* agent, const Telegram& _rMsg){
	if(_rMsg.m_nSender == IW){
		EffectMgr->FadeOutBlackPlane();
	}

	if(_rMsg.m_nMsg == Msg_Active){
		agent->OnActive();
		agent->GetFSM()->ChangeState(InputWindowOK->Instance());
		UIMgr->GetTextOfGame()->OffTime();
		UIMgr->GetTextOfGame()->GetTimer()->Stop();
		WorldMgr->OnPause();
		MouseMgr->OnCursor();
		EngineMgr->InitializeEdit();
	}
	else if(_rMsg.m_nMsg == Msg_InActive){
		agent->OffActive();		
		EffectMgr->FadeOutBlackPlane();		
	}
		
	if(_rMsg.m_nSender == VIRUS){
		agent->GivenLine("Name");
	}

	return true;
}