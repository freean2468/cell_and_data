#include "GaugeOwnedStates.h"
#include "../Engine_System/CameraManager.h"

///////////////////////////////////////////////////////////
// Maintain State
///////////////////////////////////////////////////////////
void CGaugeMaintain::Enter(CGauge* _pGauge){
	
}

void CGaugeMaintain::Execute(CGauge* _pGauge){
	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);
	CBody* t_pBody = _pGauge->GetBody();

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_pBody->GetPriPos()->x = t_vPos.x;
	t_pBody->GetPriPos()->y = t_vPos.y + 240.0f;
	t_pBody->GetPriPos()->z = t_vPos.z + 700.0f;

	for(int i = 0; i < _pGauge->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_pAtt = _pGauge->GetAttachment(i);

		if(t_pAtt->GetAttType() == CGauge::GAUGE){
			t_pAtt->GetPriSca()->x = _pGauge->GetPresentGauge() / _pGauge->GetMaxGauge();
			t_pAtt->GetPriPos()->x = t_pAtt->GetWidthHalf() - t_pBody->GetWidthHalf() + 3.0f;
		}
		else if(t_pAtt->GetAttType() == CGauge::STICK_FIRST){
			t_pAtt->GetPriPos()->x = ((t_pBody->GetWidth()) * (_pGauge->GetFirstGauge() / _pGauge->GetMaxGauge())) - t_pBody->GetWidthHalf();

			if(_pGauge->GetPresentGauge() >= _pGauge->GetMaxGauge())
				t_pAtt->BlinkAlpha(0.6f, 1.0f, 0.02f);
		}
		else if(t_pAtt->GetAttType() == CGauge::STICK_SECOND){
			if(_pGauge->GetSecondGauge() == 0.0f)
				t_pAtt->GetPriPos()->x = t_pBody->GetWidthHalf() - t_pAtt->GetWidth();
			else
				t_pAtt->GetPriPos()->x = ((t_pBody->GetWidth()) * (_pGauge->GetSecondGauge() / _pGauge->GetMaxGauge())) - t_pBody->GetWidthHalf();

			if(_pGauge->GetPresentGauge() >= _pGauge->GetMaxGauge())
				t_pAtt->BlinkAlpha(0.6f, 1.0f, 0.02f);
		}
		else if(t_pAtt->GetAttType() == CGauge::OUTLINE){
			if(_pGauge->GetPresentGauge() >= _pGauge->GetMaxGauge())
				t_pAtt->BlinkAlpha(0.6f, 1.0f, 0.02f);
		}
	}

	_pGauge->RenderOrgan();
}

void CGaugeMaintain::Exit(CGauge* _pGauge){
	
}

bool CGaugeMaintain::OnMessage(CGauge* agent, const Telegram& _rMsg){
	return false;
}