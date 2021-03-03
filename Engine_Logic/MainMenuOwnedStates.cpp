#include "MainMenuOwnedStates.h"
#include "../Game_Factor/UIManager.h"
#include "MainMenu.h"
#include "../Engine_System/CollisionManager.h"
#include "../Engine_System/MouseManager.h"
#include "../Engine_Logic/SectionManager.h"

///////////////////////////////////////////////////////////
// Main State
///////////////////////////////////////////////////////////
void CMainMenuMain::Enter(CMainMenu* _pMainMenu){
		UIMgr->GetMWSquare()->SetPos(&D3DXVECTOR3(_pMainMenu->GetBody()->GetPriPos()->x + 170.0f, 
												_pMainMenu->GetBody()->GetPriPos()->y - 80.0f, 
												_pMainMenu->GetBody()->GetPriPos()->z));
}

void CMainMenuMain::Execute(CMainMenu* _pMainMenu){
	bool t_bCollision = false;

	for(int i = 0; i < _pMainMenu->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_pAtt = _pMainMenu->GetAttachment(i);

		switch(t_pAtt->GetAttType()){
			case CMainMenu::C:
				t_pAtt->BigAndSmallXYAlternately(0.3f, 0.04f);
				break;
			case CMainMenu::E:
				t_pAtt->BigAndSmallXYAlternately(0.2f, 0.03f);
				break;
			case CMainMenu::L:
				t_pAtt->BigAndSmallXYAlternately(0.4f, 0.05f);
				break;
			case CMainMenu::AND:
				t_pAtt->BigAndSmallXYAlternately(0.4f, 0.055f);
				break;
			case CMainMenu::D:
				t_pAtt->BigAndSmallXYAlternately(0.35f, 0.03f);
				break;
			case CMainMenu::A:
				t_pAtt->BigAndSmallXYAlternately(0.2f, 0.045f);
				break;
			case CMainMenu::T:
				t_pAtt->BigAndSmallXYAlternately(0.3f, 0.04f);
				break;
		}
	}

	for(int i = 0; i < _pMainMenu->GetMain()->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_pAtt = _pMainMenu->GetMain()->GetAttachment(i);

		switch(t_pAtt->GetAttType()){
			case CMainMenu::SCENARIO:
			case CMainMenu::EXTRA:
			case CMainMenu::CREDIT:
			case CMainMenu::EXIT:				
				if(CollisionMgr->Collision2DRectWithPoint(t_pAtt->GetRect(), MouseMgr->GetCursorPos())){
					t_bCollision = true;

					t_pAtt->BigAndSmallXYAlternately(0.1f, 0.01f);

					if(t_pAtt->GetAttType() == CMainMenu::SCENARIO){
							UIMgr->GetMWSquare()->GivenLine("내 이야기를 들어보겠어?");

							if(MouseMgr->LeftClick())	
								_pMainMenu->GetFSM()->ChangeState(MainMenuToStartFromMain->Instance());	
							break;
					}
					else if(t_pAtt->GetAttType() == CMainMenu::EXTRA){
							UIMgr->GetMWSquare()->GivenLine("도전해 봐!");

							if(MouseMgr->LeftClick())	
								_pMainMenu->GetFSM()->ChangeState(MainMenuToExtraFromMain->Instance());	
							break;
					}
					else if(t_pAtt->GetAttType() == CMainMenu::CREDIT){
							UIMgr->GetMWSquare()->GivenLine("내가 누군지 궁금해?");

							if(MouseMgr->LeftClick())	
								_pMainMenu->GetFSM()->ChangeState(MainMenuToCredit->Instance());	
							break;
					}
					else if(t_pAtt->GetAttType() == CMainMenu::EXIT){
							UIMgr->GetMWSquare()->GivenLine("또 놀러와~");

							if(MouseMgr->LeftClick())	
								SectionMgr->GetSection()->GetFSM()->ChangeState(SectionExit->Instance());														
							break;
					}
				}
				else
					t_pAtt->UniformSca(1.0f);
				break; // case end
		}
	}

	if(!t_bCollision) UIMgr->GetMWSquare()->GivenLine("Hellow World~!");

	_pMainMenu->RenderOrgan();
	_pMainMenu->GetMain()->RenderOrgan();
	UIMgr->GetMWSquare()->Update();
}

void CMainMenuMain::Exit(CMainMenu* _pMainMenu){
	UIMgr->GetMWSquare()->InitLine();
}

bool CMainMenuMain::OnMessage(CMainMenu* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// ToExtraFromMain State
///////////////////////////////////////////////////////////
void CMainMenuToExtraFromMain::Enter(CMainMenu* _pMainMenu){
	UIMgr->SetPosMWSquare(&D3DXVECTOR3(_pMainMenu->GetBody()->GetPriPos()->x + 170.0f, 
		_pMainMenu->GetBody()->GetPriPos()->y - 80.0f, _pMainMenu->GetBody()->GetPriPos()->z));
}

void CMainMenuToExtraFromMain::Execute(CMainMenu* _pMainMenu){
	bool t_bCollision = false;

	for(int i = 0; i < _pMainMenu->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_pAtt = _pMainMenu->GetAttachment(i);

		switch(t_pAtt->GetAttType()){
			case CMainMenu::C:
				t_pAtt->BigAndSmallXYAlternately(0.3f, 0.04f);
				break;
			case CMainMenu::E:
				t_pAtt->BigAndSmallXYAlternately(0.2f, 0.03f);
				break;
			case CMainMenu::L:
				t_pAtt->BigAndSmallXYAlternately(0.4f, 0.05f);
				break;
			case CMainMenu::AND:
				t_pAtt->BigAndSmallXYAlternately(0.4f, 0.055f);
				break;
			case CMainMenu::D:
				t_pAtt->BigAndSmallXYAlternately(0.35f, 0.03f);
				break;
			case CMainMenu::A:
				t_pAtt->BigAndSmallXYAlternately(0.2f, 0.045f);
				break;
			case CMainMenu::T:
				t_pAtt->BigAndSmallXYAlternately(0.3f, 0.04f);
				break;
		}
	}

	for(int i = 0; i < _pMainMenu->GetMain()->GetAttachmentArray()->GetSize(); ++i){
		_pMainMenu->GetMain()->GetAttachment(i)->NoneRelateDecreaseSca(0.05f);
	}

	for(int i = 0; i < _pMainMenu->GetExtra()->GetAttachmentArray()->GetSize(); ++i){
		_pMainMenu->GetExtra()->GetAttachment(i)->NoneRelateIncreaseSca(0.05f);
	}

	if(_pMainMenu->GetMain()->GetAttachment(0)->GetPriSca()->x <= 0.0f)
		_pMainMenu->GetFSM()->ChangeState(MainMenuExtra->Instance());

	_pMainMenu->RenderOrgan();
	_pMainMenu->GetMain()->RenderOrgan();
	_pMainMenu->GetExtra()->RenderOrgan();	
	UIMgr->GetMWSquare()->Update();
}

void CMainMenuToExtraFromMain::Exit(CMainMenu* _pMainMenu){
	
}

bool CMainMenuToExtraFromMain::OnMessage(CMainMenu* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Extra State
///////////////////////////////////////////////////////////
void CMainMenuExtra::Enter(CMainMenu* _pMainMenu){
	UIMgr->SetPosMWSquare(&D3DXVECTOR3(_pMainMenu->GetBody()->GetPriPos()->x + 170.0f, 
		_pMainMenu->GetBody()->GetPriPos()->y - 80.0f, _pMainMenu->GetBody()->GetPriPos()->z));
}

void CMainMenuExtra::Execute(CMainMenu* _pMainMenu){
	bool t_bCollision = false;

	for(int i = 0; i < _pMainMenu->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_pAtt = _pMainMenu->GetAttachment(i);

		switch(t_pAtt->GetAttType()){
			case CMainMenu::C:
				t_pAtt->BigAndSmallXYAlternately(0.3f, 0.04f);
				break;
			case CMainMenu::E:
				t_pAtt->BigAndSmallXYAlternately(0.2f, 0.03f);
				break;
			case CMainMenu::L:
				t_pAtt->BigAndSmallXYAlternately(0.4f, 0.05f);
				break;
			case CMainMenu::AND:
				t_pAtt->BigAndSmallXYAlternately(0.4f, 0.055f);
				break;
			case CMainMenu::D:
				t_pAtt->BigAndSmallXYAlternately(0.35f, 0.03f);
				break;
			case CMainMenu::A:
				t_pAtt->BigAndSmallXYAlternately(0.2f, 0.045f);
				break;
			case CMainMenu::T:
				t_pAtt->BigAndSmallXYAlternately(0.3f, 0.04f);
				break;
		}
	}

	for(int i = 0; i < _pMainMenu->GetExtra()->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_pAtt = _pMainMenu->GetExtra()->GetAttachment(i);

		switch(t_pAtt->GetAttType()){
			case RETURN:
			case CMainMenu::TIMEATTACK:				
			case CMainMenu::SURVIVAL:
			case CMainMenu::RANK:
			case CMainMenu::OST:
				if(CollisionMgr->Collision2DRectWithPoint(t_pAtt->GetRect(), MouseMgr->GetCursorPos())){
					t_bCollision = true;

					t_pAtt->BigAndSmallXYAlternately(0.1f, 0.01f);

					if(t_pAtt->GetAttType() == CMainMenu::TIMEATTACK){
						UIMgr->GetMWSquare()->GivenLine("골인이나 할 수 있을까?");

						if(MouseMgr->LeftClick())	
							SectionMgr->GetSection()->GetFSM()->ChangeState(SectionExtraTimeAttack->Instance());	
						break;
					}
					else if(t_pAtt->GetAttType() == CMainMenu::SURVIVAL){
						UIMgr->GetMWSquare()->GivenLine("근성을 발휘해 보라구~");

						if(MouseMgr->LeftClick())	
							SectionMgr->GetSection()->GetFSM()->ChangeState(SectionExtraSurvival->Instance());														
						break;
					}
					else if(t_pAtt->GetAttType() == CMainMenu::RANK){
						UIMgr->GetMWSquare()->GivenLine("안 봐도 도토리 키재기지.");

						if(MouseMgr->LeftClick())	
							SectionMgr->GetSection()->GetFSM()->ChangeState(SectionRank->Instance());														
						break;
					}
					else if(t_pAtt->GetAttType() == CMainMenu::OST){
						UIMgr->GetMWSquare()->GivenLine("나의 영혼을 들어봐!");

						if(MouseMgr->LeftClick())	
							SectionMgr->GetSection()->GetFSM()->ChangeState(SectionOST->Instance());														
						break;
					}
					else if(t_pAtt->GetAttType() == RETURN){
						UIMgr->GetMWSquare()->GivenLine("뒤로~ 뒤로~");

						if(MouseMgr->LeftClick())	
							_pMainMenu->GetFSM()->ChangeState(MainMenuToMainFromExtra->Instance());														
						break;
					}
				}
				else
					t_pAtt->UniformSca(1.0f);
				break; // case end
		}
	}

	if(!t_bCollision) UIMgr->GetMWSquare()->GivenLine("Hellow World~!");

	_pMainMenu->RenderOrgan();
	_pMainMenu->GetExtra()->RenderOrgan();
	UIMgr->GetMWSquare()->Update();
}

void CMainMenuExtra::Exit(CMainMenu* _pMainMenu){

}

bool CMainMenuExtra::OnMessage(CMainMenu* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// ToMainFromExtra State
///////////////////////////////////////////////////////////
void CMainMenuToMainFromExtra::Enter(CMainMenu* _pMainMenu){
	UIMgr->SetPosMWSquare(&D3DXVECTOR3(_pMainMenu->GetBody()->GetPriPos()->x + 170.0f, 
		_pMainMenu->GetBody()->GetPriPos()->y - 80.0f, _pMainMenu->GetBody()->GetPriPos()->z));
}

void CMainMenuToMainFromExtra::Execute(CMainMenu* _pMainMenu){
	bool t_bCollision = false;

	for(int i = 0; i < _pMainMenu->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_pAtt = _pMainMenu->GetAttachment(i);

		switch(t_pAtt->GetAttType()){
			case CMainMenu::C:
				t_pAtt->BigAndSmallXYAlternately(0.3f, 0.04f);
				break;
			case CMainMenu::E:
				t_pAtt->BigAndSmallXYAlternately(0.2f, 0.03f);
				break;
			case CMainMenu::L:
				t_pAtt->BigAndSmallXYAlternately(0.4f, 0.05f);
				break;
			case CMainMenu::AND:
				t_pAtt->BigAndSmallXYAlternately(0.4f, 0.055f);
				break;
			case CMainMenu::D:
				t_pAtt->BigAndSmallXYAlternately(0.35f, 0.03f);
				break;
			case CMainMenu::A:
				t_pAtt->BigAndSmallXYAlternately(0.2f, 0.045f);
				break;
			case CMainMenu::T:
				t_pAtt->BigAndSmallXYAlternately(0.3f, 0.04f);
				break;
		}
	}

	for(int i = 0; i < _pMainMenu->GetMain()->GetAttachmentArray()->GetSize(); ++i){
		_pMainMenu->GetMain()->GetAttachment(i)->NoneRelateIncreaseSca(0.05f);
	}

	for(int i = 0; i < _pMainMenu->GetExtra()->GetAttachmentArray()->GetSize(); ++i){
		_pMainMenu->GetExtra()->GetAttachment(i)->NoneRelateDecreaseSca(0.05f);
	}

	if(_pMainMenu->GetMain()->GetAttachment(0)->GetPriSca()->x >= 1.0f)
		_pMainMenu->GetFSM()->ChangeState(MainMenuMain->Instance());

	_pMainMenu->RenderOrgan();
	_pMainMenu->GetExtra()->RenderOrgan();
	_pMainMenu->GetMain()->RenderOrgan();
	UIMgr->GetMWSquare()->Update();
}

void CMainMenuToMainFromExtra::Exit(CMainMenu* _pMainMenu){

}

bool CMainMenuToMainFromExtra::OnMessage(CMainMenu* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// ToStartFromMain State
///////////////////////////////////////////////////////////
void CMainMenuToStartFromMain::Enter(CMainMenu* _pMainMenu){
	UIMgr->SetPosMWSquare(&D3DXVECTOR3(_pMainMenu->GetBody()->GetPriPos()->x + 170.0f, 
		_pMainMenu->GetBody()->GetPriPos()->y - 80.0f, _pMainMenu->GetBody()->GetPriPos()->z));
}

void CMainMenuToStartFromMain::Execute(CMainMenu* _pMainMenu){
	bool t_bCollision = false;

	for(int i = 0; i < _pMainMenu->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_pAtt = _pMainMenu->GetAttachment(i);

		switch(t_pAtt->GetAttType()){
			case CMainMenu::C:
				t_pAtt->BigAndSmallXYAlternately(0.3f, 0.04f);
				break;
			case CMainMenu::E:
				t_pAtt->BigAndSmallXYAlternately(0.2f, 0.03f);
				break;
			case CMainMenu::L:
				t_pAtt->BigAndSmallXYAlternately(0.4f, 0.05f);
				break;
			case CMainMenu::AND:
				t_pAtt->BigAndSmallXYAlternately(0.4f, 0.055f);
				break;
			case CMainMenu::D:
				t_pAtt->BigAndSmallXYAlternately(0.35f, 0.03f);
				break;
			case CMainMenu::A:
				t_pAtt->BigAndSmallXYAlternately(0.2f, 0.045f);
				break;
			case CMainMenu::T:
				t_pAtt->BigAndSmallXYAlternately(0.3f, 0.04f);
				break;
		}
	}

	for(int i = 0; i < _pMainMenu->GetMain()->GetAttachmentArray()->GetSize(); ++i){
		_pMainMenu->GetMain()->GetAttachment(i)->NoneRelateDecreaseSca(0.05f);
	}

	for(int i = 0; i < _pMainMenu->GetStart()->GetAttachmentArray()->GetSize(); ++i){
		_pMainMenu->GetStart()->GetAttachment(i)->NoneRelateIncreaseSca(0.05f);
	}

	if(_pMainMenu->GetMain()->GetAttachment(0)->GetPriSca()->x <= 0.0f)
		_pMainMenu->GetFSM()->ChangeState(MainMenuStart->Instance());

	_pMainMenu->RenderOrgan();
	_pMainMenu->GetMain()->RenderOrgan();
	_pMainMenu->GetStart()->RenderOrgan();	
	UIMgr->GetMWSquare()->Update();
}

void CMainMenuToStartFromMain::Exit(CMainMenu* _pMainMenu){
	
}

bool CMainMenuToStartFromMain::OnMessage(CMainMenu* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Start State
///////////////////////////////////////////////////////////
void CMainMenuStart::Enter(CMainMenu* _pMainMenu){
	UIMgr->SetPosMWSquare(&D3DXVECTOR3(_pMainMenu->GetBody()->GetPriPos()->x + 170.0f, 
		_pMainMenu->GetBody()->GetPriPos()->y - 80.0f, _pMainMenu->GetBody()->GetPriPos()->z));
}

void CMainMenuStart::Execute(CMainMenu* _pMainMenu){
	bool t_bCollision = false;

	for(int i = 0; i < _pMainMenu->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_pAtt = _pMainMenu->GetAttachment(i);

		switch(t_pAtt->GetAttType()){
			case CMainMenu::C:
				t_pAtt->BigAndSmallXYAlternately(0.3f, 0.04f);
				break;
			case CMainMenu::E:
				t_pAtt->BigAndSmallXYAlternately(0.2f, 0.03f);
				break;
			case CMainMenu::L:
				t_pAtt->BigAndSmallXYAlternately(0.4f, 0.05f);
				break;
			case CMainMenu::AND:
				t_pAtt->BigAndSmallXYAlternately(0.4f, 0.055f);
				break;
			case CMainMenu::D:
				t_pAtt->BigAndSmallXYAlternately(0.35f, 0.03f);
				break;
			case CMainMenu::A:
				t_pAtt->BigAndSmallXYAlternately(0.2f, 0.045f);
				break;
			case CMainMenu::T:
				t_pAtt->BigAndSmallXYAlternately(0.3f, 0.04f);
				break;
		}
	}

	for(int i = 0; i < _pMainMenu->GetStart()->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_pAtt = _pMainMenu->GetStart()->GetAttachment(i);

		switch(t_pAtt->GetAttType()){
			case RETURN:
			case CMainMenu::START:				
			case CMainMenu::LOAD:				
				if(CollisionMgr->Collision2DRectWithPoint(t_pAtt->GetRect(), MouseMgr->GetCursorPos())){
					t_bCollision = true;

					t_pAtt->BigAndSmallXYAlternately(0.1f, 0.01f);

					if(t_pAtt->GetAttType() == CMainMenu::START){
						UIMgr->GetMWSquare()->GivenLine("떠올리고 싶지 않은 기억이야......");

						if(MouseMgr->LeftClick())	
							SectionMgr->GetSection()->GetFSM()->ChangeState(SectionStory1st->Instance());	
						break;
					}					
					else if(t_pAtt->GetAttType() == CMainMenu::LOAD){
						UIMgr->GetMWSquare()->GivenLine("계속하자구!");

						if(MouseMgr->LeftClick())	
							//_pMainMenu->GetFSM()->ChangeState(MainMenuToMainFromStart->Instance());														
						break;
					}
					else if(t_pAtt->GetAttType() == RETURN){
						UIMgr->GetMWSquare()->GivenLine("뒤로~ 뒤로~");

						if(MouseMgr->LeftClick())	
							_pMainMenu->GetFSM()->ChangeState(MainMenuToMainFromStart->Instance());														
						break;
					}
				}
				else
					t_pAtt->UniformSca(1.0f);
				break; // case end
		}
	}

	if(!t_bCollision) UIMgr->GetMWSquare()->GivenLine("Hellow World~!");

	_pMainMenu->RenderOrgan();
	_pMainMenu->GetStart()->RenderOrgan();
	UIMgr->GetMWSquare()->Update();
}

void CMainMenuStart::Exit(CMainMenu* _pMainMenu){

}

bool CMainMenuStart::OnMessage(CMainMenu* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// ToMainFromStart State
///////////////////////////////////////////////////////////
void CMainMenuToMainFromStart::Enter(CMainMenu* _pMainMenu){
	UIMgr->SetPosMWSquare(&D3DXVECTOR3(_pMainMenu->GetBody()->GetPriPos()->x + 170.0f, 
		_pMainMenu->GetBody()->GetPriPos()->y - 80.0f, _pMainMenu->GetBody()->GetPriPos()->z));
}

void CMainMenuToMainFromStart::Execute(CMainMenu* _pMainMenu){
	bool t_bCollision = false;

	for(int i = 0; i < _pMainMenu->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_pAtt = _pMainMenu->GetAttachment(i);

		switch(t_pAtt->GetAttType()){
			case CMainMenu::C:
				t_pAtt->BigAndSmallXYAlternately(0.3f, 0.04f);
				break;
			case CMainMenu::E:
				t_pAtt->BigAndSmallXYAlternately(0.2f, 0.03f);
				break;
			case CMainMenu::L:
				t_pAtt->BigAndSmallXYAlternately(0.4f, 0.05f);
				break;
			case CMainMenu::AND:
				t_pAtt->BigAndSmallXYAlternately(0.4f, 0.055f);
				break;
			case CMainMenu::D:
				t_pAtt->BigAndSmallXYAlternately(0.35f, 0.03f);
				break;
			case CMainMenu::A:
				t_pAtt->BigAndSmallXYAlternately(0.2f, 0.045f);
				break;
			case CMainMenu::T:
				t_pAtt->BigAndSmallXYAlternately(0.3f, 0.04f);
				break;
		}
	}

	for(int i = 0; i < _pMainMenu->GetMain()->GetAttachmentArray()->GetSize(); ++i){
		_pMainMenu->GetMain()->GetAttachment(i)->NoneRelateIncreaseSca(0.05f);
	}

	for(int i = 0; i < _pMainMenu->GetStart()->GetAttachmentArray()->GetSize(); ++i){
		_pMainMenu->GetStart()->GetAttachment(i)->NoneRelateDecreaseSca(0.05f);
	}

	if(_pMainMenu->GetMain()->GetAttachment(0)->GetPriSca()->x >= 1.0f)
		_pMainMenu->GetFSM()->ChangeState(MainMenuMain->Instance());

	_pMainMenu->RenderOrgan();
	_pMainMenu->GetStart()->RenderOrgan();
	_pMainMenu->GetMain()->RenderOrgan();
	UIMgr->GetMWSquare()->Update();
}

void CMainMenuToMainFromStart::Exit(CMainMenu* _pMainMenu){

}

bool CMainMenuToMainFromStart::OnMessage(CMainMenu* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Revert State
///////////////////////////////////////////////////////////
void CMainMenuRevert::Enter(CMainMenu* _pMainMenu){
	UIMgr->SetPosMWSquare(&D3DXVECTOR3(_pMainMenu->GetBody()->GetPriPos()->x + 170.0f, 
		_pMainMenu->GetBody()->GetPriPos()->y - 80.0f, _pMainMenu->GetBody()->GetPriPos()->z));
}

void CMainMenuRevert::Execute(CMainMenu* _pMainMenu){
	for(int i = 0; i < _pMainMenu->GetAttachmentArray()->GetSize(); ++i){
		_pMainMenu->GetAttachment(i)->NoneRelateIncreaseSca(0.05f);
	}

	for(int i = 0; i < _pMainMenu->GetMain()->GetAttachmentArray()->GetSize(); ++i){
		_pMainMenu->GetMain()->GetAttachment(i)->NoneRelateIncreaseSca(0.05f);
	}

	UIMgr->GetMWSquare()->GetBody()->IncreaseSca(0.05f);

	if(UIMgr->GetMWSquare()->GetBody()->GetPriSca()->x >= 1.0f){
		_pMainMenu->GetFSM()->ChangeState(MainMenuMain->Instance());
	}

	_pMainMenu->RenderOrgan();
	_pMainMenu->GetMain()->RenderOrgan();
	UIMgr->GetMWSquare()->Update();
}

void CMainMenuRevert::Exit(CMainMenu* _pMainMenu){

}

bool CMainMenuRevert::OnMessage(CMainMenu* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// ToCredit State
///////////////////////////////////////////////////////////
void CMainMenuToCredit::Enter(CMainMenu* _pMainMenu){
	UIMgr->SetPosMWSquare(&D3DXVECTOR3(_pMainMenu->GetBody()->GetPriPos()->x + 170.0f, 
		_pMainMenu->GetBody()->GetPriPos()->y - 80.0f, _pMainMenu->GetBody()->GetPriPos()->z));
}

void CMainMenuToCredit::Execute(CMainMenu* _pMainMenu){
	for(int i = 0; i < _pMainMenu->GetAttachmentArray()->GetSize(); ++i){
		_pMainMenu->GetAttachment(i)->NoneRelateDecreaseSca(0.05f);
	}

	for(int i = 0; i < _pMainMenu->GetMain()->GetAttachmentArray()->GetSize(); ++i){
		_pMainMenu->GetMain()->GetAttachment(i)->NoneRelateDecreaseSca(0.05f);
	}

	UIMgr->GetMWSquare()->GetBody()->DecreaseSca(0.05f);

	if(UIMgr->GetMWSquare()->GetBody()->GetPriSca()->x <= 0.0f){
		SectionMgr->GetSection()->GetFSM()->ChangeState(SectionCredit->Instance());
		_pMainMenu->GetFSM()->ChangeState(MainMenuRevert->Instance());
	}

	_pMainMenu->RenderOrgan();
	_pMainMenu->GetMain()->RenderOrgan();
	UIMgr->GetMWSquare()->Update();
}

void CMainMenuToCredit::Exit(CMainMenu* _pMainMenu){

}

bool CMainMenuToCredit::OnMessage(CMainMenu* agent, const Telegram& _rMsg){
	return false;
}