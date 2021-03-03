#include "VacineOwnedStates.h"
#include "../Engine_System/WaveManager.h"

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
void CVacineStand::Enter(CVacine* _pVacine){
	
}

void CVacineStand::Execute(CVacine* _pVacine){
	// 바디 계산
	CBody* t_pBody = _pVacine->GetBody();

	// 부속물 계산
	for(int i = 0; i < _pVacine->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = _pVacine->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CVacine::FIRSTCYTOPLASM:
				t_Att->GetPriRot()->z -= _pVacine->GetFirstAndSecondCytoplasmRotVelocity();
				break;
			case CVacine::SECONDCYTOPLASM:
				t_Att->GetPriRot()->z += _pVacine->GetFirstAndSecondCytoplasmRotVelocity();
				break;
			case CVacine::THIRDCYTOPLASM:
				t_Att->GetPriRot()->z += _pVacine->GetThirdCytoplasmRotVelocity();
				break;
			case CVacine::FIRSTTAIL:
				t_Att->RoundTripX(2.0f, 0.05f);

				if(_pVacine->GetMaxSpeed() > 10)	t_Att->BigAndSmallY(1.3f, 0.7f, 0.025f);
				else															t_Att->GetPriSca()->y -= 0.01f;
				break;
			case CVacine::SECONDTAIL:
				t_Att->RoundTripX(2.0f, 0.07f);

				if(_pVacine->GetMaxSpeed() > 10)	t_Att->BigAndSmallY(1.6f, 1.0f, 0.04f);
				else															t_Att->GetPriSca()->y -= 0.01f;
				break;
			case CVacine::CORE:
				t_Att->BigAndSmallXYAlternately(0.15f, 0.002f);
				break;
			case CVacine::FIRSTMINICORE:
				t_Att->BigAndSmallXYAlternately(0.3f, 0.02f);
				t_Att->RotZ(D3DX_PI*0.005f);
				break;
			case CVacine::SECONDMINICORE:
				t_Att->BigAndSmallXYAlternately(0.3f, 0.015f);
				t_Att->RotZ(D3DX_PI*-0.0015f);
				break;
			case CVacine::THIRDMINICORE:
				t_Att->BigAndSmallXYAlternately(0.3f, 0.025f);
				t_Att->RotZ(D3DX_PI*0.003f);
				break;
			default:
				break;
		}
	}	
}

void CVacineStand::Exit(CVacine* _pVacine){

}

bool CVacineStand::OnMessage(CVacine* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Destroy State
///////////////////////////////////////////////////////////
void CVacineDestroy::Enter(CVacine* _pVacine){
	if(!EngineMgr->IsViewOut(_pVacine->GetPos3D())){
		WaveMgr->Play("./Sound/VirusDie.wav", false);
	}
}

void CVacineDestroy::Execute(CVacine* _pVacine){
	// 바디 계산
	CBody* t_pBody = _pVacine->GetBody();

	t_pBody->RotZ(0.1f);

	_pVacine->SetMaxSpeed(0);

	// 부속물 계산
	for(int i = 0; i < _pVacine->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_pAtt = _pVacine->GetAttachmentArray()->Get(i);

		if(t_pAtt->GetMtrl()->Diffuse.r < 1.0f){
			t_pAtt->GetMtrl()->Diffuse.r += 0.02f;
			t_pAtt->GetMtrl()->Diffuse.g -= 0.02f;
			t_pAtt->GetMtrl()->Diffuse.b -= 0.02f;
		}

		if(t_pAtt->GetPriSca()->x > 0.0f){
			t_pAtt->GetPriSca()->x -= 0.008f;
			t_pAtt->GetPriSca()->y -= 0.008f;
		}
		else{
			if(!EngineMgr->IsViewOut(_pVacine->GetPos3D())){
				WaveMgr->Play("./Sound/Laugh.wav", false);
			}
			_pVacine->Die();
		}
	}	
}

void CVacineDestroy::Exit(CVacine* _pVacine){

}

bool CVacineDestroy::OnMessage(CVacine* agent, const Telegram& _rMsg){
	return false;
}