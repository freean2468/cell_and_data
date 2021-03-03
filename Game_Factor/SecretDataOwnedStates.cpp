#include "SecretDataOwnedStates.h"
#include "../Engine_System/Body.h"
#include "../Engine_System/WaveManager.h"

///////////////////////////////////////////////////////////
// Delete State
///////////////////////////////////////////////////////////
void CSecretDataDelete::Enter(CSecretData* _pSecretData){
	
}

void CSecretDataDelete::Execute(CSecretData* _pSecretData){
	CBody* t_pBody = _pSecretData->GetBody();

	if(t_pBody->GetMtrl()->Diffuse.r < 1.0f){
		t_pBody->GetMtrl()->Diffuse.r += 0.01f;
		t_pBody->GetMtrl()->Diffuse.g -= 0.01f;
		m_pTimer->InitTimer(50);
	}
	else{
		if(t_pBody->GetPriSca()->x > 0.0f){
			t_pBody->DecreaseSca(0.01f);
			if(m_pTimer->IsElapseTimer()){
				m_pTimer->InitTimer(50);
				WaveMgr->Play("./Sound/SecretDie.wav", false);
			}
		}
		else{
			if(_pSecretData->IsAlive()){
				_pSecretData->Die();
				WaveMgr->Play("./Sound/Laugh.wav", false);
			}
		}

		_pSecretData->GetDataBomb()->update(SYSTEM_FRAME_INTERVAL_VER_60);
		_pSecretData->GetDataBomb()->render();
	}

	_pSecretData->RenderOrgan();
}

void CSecretDataDelete::Exit(CSecretData* _pSecretData){

}

bool CSecretDataDelete::OnMessage(CSecretData* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Maintain State
///////////////////////////////////////////////////////////
void CSecretDataMaintain::Enter(CSecretData* _pSecretData){
	
}

void CSecretDataMaintain::Execute(CSecretData* _pSecretData){
	CBody* t_pBody = _pSecretData->GetBody();

	_pSecretData->RenderOrgan();
}

void CSecretDataMaintain::Exit(CSecretData* _pSecretData){

}

bool CSecretDataMaintain::OnMessage(CSecretData* agent, const Telegram& _rMsg){
	return false;
}