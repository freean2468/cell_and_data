#include "GameMenuOwnedStates.h"
#include "../Game_Factor/WorldManager.h"
#include "../Engine_System/MouseManager.h"
#include "../Engine_System/CollisionManager.h"
#include "../Engine_Logic/SectionManager.h"

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
void CGameMenuActive::Enter(CGameMenu* _pGameMenu){
	WorldMgr->OnPause();
	MouseMgr->OnCursor();
}

void CGameMenuActive::Execute(CGameMenu* _pGameMenu){
	bool t_bCollision = false;

	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	_pGameMenu->GetBody()->GetPriPos()->x = t_vPos.x;
	_pGameMenu->GetBody()->GetPriPos()->y = t_vPos.y;
	_pGameMenu->GetBody()->GetPriPos()->z = t_vPos.z + 700.0f;

	for(int i = 0; i < _pGameMenu->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_pAtt = _pGameMenu->GetAttachment(i);

		switch(t_pAtt->GetAttType()){
			case CGameMenu::RETURN_TO_MENU:
			case CGameMenu::RETRY:
			case CGameMenu::RESUME:
				t_pAtt->NoneRelateIncreaseSca(0.05f);
				break;
		}
	}

	_pGameMenu->GetBody()->IncreaseSca(0.05f);

	if(_pGameMenu->GetBody()->GetPriSca()->x >= 1.0f)
		_pGameMenu->GetFSM()->ChangeState(GameMenuMaintain->Instance());

	_pGameMenu->RenderOrgan();
}

void CGameMenuActive::Exit(CGameMenu* _pGameMenu){
	
}

bool CGameMenuActive::OnMessage(CGameMenu* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Maintain State
///////////////////////////////////////////////////////////
void CGameMenuMaintain::Enter(CGameMenu* _pGameMenu){
	
}

void CGameMenuMaintain::Execute(CGameMenu* _pGameMenu){
	bool t_bCollision = false;

	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	_pGameMenu->GetBody()->GetPriPos()->x = t_vPos.x;
	_pGameMenu->GetBody()->GetPriPos()->y = t_vPos.y;
	_pGameMenu->GetBody()->GetPriPos()->z = t_vPos.z + 700.0f;

	if(EngineMgr->KeyUp(DIK_ESCAPE)){
		_pGameMenu->GetFSM()->ChangeState(GameMenuInActive->Instance());
	}

	for(int i = 0; i < _pGameMenu->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_pAtt = _pGameMenu->GetAttachment(i);

		switch(t_pAtt->GetAttType()){
			case CGameMenu::RETURN_TO_MENU:
			case CGameMenu::RETRY:
			case CGameMenu::RESUME:
				if(CollisionMgr->Collision2DRectWithPoint(t_pAtt->GetRect(), MouseMgr->GetCursorPos())){
					t_bCollision = true;

					t_pAtt->BigAndSmallXYAlternately(0.1f, 0.01f);

					if(t_pAtt->GetAttType() == CGameMenu::RETRY){
						if(MouseMgr->LeftClick()){
							_pGameMenu->GetFSM()->ChangeState(GameMenuInActive->Instance());	
							SectionMgr->GetSection()->GetFSM()->ChangeState(SectionMgr->GetSection()->GetFSM()->CurrentState());
							return;
						}
						break;
					}
					else if(t_pAtt->GetAttType() == CGameMenu::RETURN_TO_MENU){
						if(MouseMgr->LeftClick()){	
							_pGameMenu->UniformOrganScaZero();
							_pGameMenu->GetFSM()->ChangeState(GameMenuInActive->Instance());	
							SectionMgr->GetSection()->GetFSM()->ChangeState(SectionMainMenu->Instance());
							return;
						}
						break;
					}
					else if(t_pAtt->GetAttType() == CGameMenu::RESUME){
						if(MouseMgr->LeftClick())	
							_pGameMenu->GetFSM()->ChangeState(GameMenuInActive->Instance());	
						break;
					}
				}
				else
					t_pAtt->UniformSca(1.0f);
				break;
		}
	}

	_pGameMenu->RenderOrgan();
}

void CGameMenuMaintain::Exit(CGameMenu* _pGameMenu){
	CameraMgr->SetMode(_pGameMenu->GetCameraMode());
	WorldMgr->OffPause();
}

bool CGameMenuMaintain::OnMessage(CGameMenu* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// InActive State
///////////////////////////////////////////////////////////
void CGameMenuInActive::Enter(CGameMenu* _pGameMenu){
	WorldMgr->OffPause();
	MouseMgr->OffCursor();
}

void CGameMenuInActive::Execute(CGameMenu* _pGameMenu){
	if(EngineMgr->KeyUp(DIK_ESCAPE)){
		_pGameMenu->SetCameraMode(CameraMgr->GetMode());
		CameraMgr->SetMode(CCameraManager::NONE);
		_pGameMenu->GetFSM()->ChangeState(GameMenuActive->Instance());
	}

	for(int i = 0; i < _pGameMenu->GetAttachmentArray()->GetSize(); ++i){
		if(_pGameMenu->GetAttachment(i)->GetPriSca()->x > 0.0f)
			_pGameMenu->GetAttachment(i)->NoneRelateDecreaseSca(0.05f);
	}

	if(_pGameMenu->GetBody()->GetPriSca()->x > 0.0f){
		_pGameMenu->GetBody()->DecreaseSca(0.05f);

		_pGameMenu->RenderOrgan();
	}
}

void CGameMenuInActive::Exit(CGameMenu* _pGameMenu){

}

bool CGameMenuInActive::OnMessage(CGameMenu* agent, const Telegram& _rMsg){
	return false;
}