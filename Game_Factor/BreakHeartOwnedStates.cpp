#include "BreakHeartOwnedStates.h"
#include "../Engine_System/MP3Manager.h"
#include "Data.h"
#include "../Game_Factor/DataOwnedStates.h"
#include "../Game_Factor/WorldManager.h"
#include "../Engine_System/CameraManager.h"
#include "../Engine_Logic/EventManager.h"
#include "../Engine_Logic/EventSubStates.h"
#include "../Engine_System/WaveManager.h"

///////////////////////////////////////////////////////////
// 1st State
///////////////////////////////////////////////////////////
void CBreakHeart1st::Enter(CBreakHeart* _pBreakHeart){
	m_pDelay->InitTimer(5000);
	m_nStep = 0;
	MP3Mgr->StopMusic();
	MP3Mgr->Reset();
	MP3Mgr->LoadMusic("./Sound/BreakHeart.mp3");
	MP3Mgr->PlayMusic();
	
	for(std::list<CData*>::iterator itr = WorldMgr->GetWorld()->GetData().begin();
		itr != WorldMgr->GetWorld()->GetData().end(); ++itr){
			if((*itr)->GetState()==CData::INFECTION || (*itr)->GetState()==CData::VARIATION){
				(*itr)->GetFSM()->ChangeState(DataCure->Instance());
			}
	}
}

void CBreakHeart1st::Execute(CBreakHeart* _pBreakHeart){
	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_vPos.z += 300.0f;

	*(_pBreakHeart->GetBody()->GetPriPos()) = t_vPos;

	if(m_pDelay->IsElapseTimer()/* || MouseMgr->LeftClick() || EngineMgr->KeyUp(DIK_RETURN)*/){
		m_pDelay->InitTimer(5000);
		m_nStep++;
	}

	if(m_nStep >= _pBreakHeart->GetAttachmentArray()->GetSize()){
		_pBreakHeart->OffActive();
		MP3Mgr->StopMusic();
		MP3Mgr->Reset();
		MP3Mgr->LoadMusic("./Sound/Play_BGM.mp3");
		MP3Mgr->PlayMusic();
		EventMgr->GetSub()->GetFSM()->ChangeState(EventSub->Instance());
		return;
	}

	for(int i = 0; i < _pBreakHeart->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_pAtt = _pBreakHeart->GetAttachment(i);


		if(t_pAtt->GetAttType() == m_nStep){
			if(t_pAtt->GetAlpha() < 1.0f)
				t_pAtt->IncreaseAlpha(0.02f);
			else{
				if(m_nStep == 4 && !m_bScreaming){
					MP3Mgr->StopMusic();
					WaveMgr->Play("./Sound/Screaming.wav", false);
					m_bScreaming = true;
				}
			}

			if(m_nStep != 0){
				if(_pBreakHeart->GetAttachment(m_nStep-1)->GetAlpha() < 1.0f)
					_pBreakHeart->GetAttachment(m_nStep-1)->DecreaseAlpha(0.02f);
			}
			break;
		}
	}

	_pBreakHeart->RenderOrgan();
}

void CBreakHeart1st::Exit(CBreakHeart* _pBreakHeart){
	m_bScreaming = false;
}

bool CBreakHeart1st::OnMessage(CBreakHeart* agent, const Telegram& _rMsg){
	return false;
}