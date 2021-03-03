#include "OST.h"
#include "../Engine_System/MP3Manager.h"
#include "../Engine_System/CollisionManager.h"
#include "../Engine_System/MouseManager.h"
#include "../Engine_Logic/MainMenu.h"
#include "../Engine_Logic/SectionManager.h"

COST::COST():COrganEntity(){
	this->LoadEntityData("./Script/SectionComposition/OST/OST.txt");
	m_nPresent = 1000;
	this->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
}

COST::~COST(){

}

void COST::Update(double _dTimeElapsed){
	if(MP3Mgr->IsEnd()){		m_nPresent = 10000;	}

	for(int i = 0;i<this->GetAttachmentArray()->GetSize();++i){
		CAttachment* t_pAtt = GetAttachment(i);

		if(CollisionMgr->Collision2DRectWithPoint(t_pAtt->GetRect(), MouseMgr->GetCursorPos())){
			t_pAtt->BigAndSmallXYAlternately(0.2f, 0.02f);
			if(MouseMgr->LeftClick()){
				m_nPresent = t_pAtt->GetAttType();
				MP3Mgr->StopMusic();
				MP3Mgr->Reset();
				if(t_pAtt->GetAttType() == ONE){		MP3Mgr->LoadMusic("./Sound/Ending.mp3");		}
				else if(t_pAtt->GetAttType() == TWO){	MP3Mgr->LoadMusic("./Sound/Play_BGM.mp3");		}
				else if(t_pAtt->GetAttType() == THREE){	MP3Mgr->LoadMusic("./Sound/Main_BGM.mp3");		}
				else if(t_pAtt->GetAttType() == FOUR){		MP3Mgr->LoadMusic("./Sound/Credit.mp3");		}
				else if(t_pAtt->GetAttType() == FIVE){		MP3Mgr->LoadMusic("./Sound/BreakHeart.mp3");		}
				else if(t_pAtt->GetAttType() == RETURN){
					MP3Mgr->FadeInOut(false);
					SectionMgr->GetSection()->GetFSM()->ChangeState(SectionMainMenu->Instance());
					return;
				}
				MP3Mgr->PlayMusic();
			}			
		}
		else{
			if(t_pAtt->GetAttType() != m_nPresent){
				t_pAtt->GetPriSca()->x = 1.0f;
				t_pAtt->GetPriSca()->y = 1.0f;
			}
			else{
				t_pAtt->BigAndSmallXYAlternately(0.2f, 0.02f);
			}
		}
	}
}

void COST::Render(){
	RenderOrgan();
}