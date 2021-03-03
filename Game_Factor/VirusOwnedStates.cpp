#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Normal State
///////////////////////////////////////////////////////////
void CVirusNormal::Enter(CVirus* _pVirus){
	
}

void CVirusNormal::Execute(CVirus* _pVirus){
	// 바디 계산
	CBody* t_pBody = _pVirus->GetBody();

	// 부속물 계산
	for(int i = 0; i < _pVirus->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = _pVirus->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CVirus::FIRSTCYTOPLASM:
				t_Att->GetPriRot()->z -= _pVirus->GetFirstAndSecondCytoplasmRotVelocity();
				break;
			case CVirus::SECONDCYTOPLASM:
				t_Att->GetPriRot()->z += _pVirus->GetFirstAndSecondCytoplasmRotVelocity();
				break;
			case CVirus::THIRDCYTOPLASM:
				t_Att->GetPriRot()->z += _pVirus->GetThirdCytoplasmRotVelocity();
				break;
			case CVirus::FIRSTTAIL:
				t_Att->RoundTripX(2.0f, 0.05f);

				if(EngineMgr->KeyDown(DIK_UP)){
					if(t_Att->BigAndSmallY(1.3f, 0.7f, 0.025f) == false){
						if(_pVirus == Controller->GetController()){
							WaveMgr->Play("./Sound/Moving.wav", false);
						}
					}
				}
				else if(t_Att->GetPriSca()->y > 0.0f)
					t_Att->GetPriSca()->y -= 0.01f;
				break;
			case CVirus::SECONDTAIL:
				t_Att->RoundTripX(2.0f, 0.07f);

				if(EngineMgr->KeyDown(DIK_UP))					t_Att->BigAndSmallY(1.6f, 1.0f, 0.04f);
				else if(t_Att->GetPriSca()->y > 0.0f)		t_Att->GetPriSca()->y -= 0.01f;
				break;
			case CVirus::CORE:
				t_Att->BigAndSmallXYAlternately(0.1f, 0.002f);
				break;
			case CVirus::FIRSTMINICORE:
				t_Att->BigAndSmallXYAlternately(0.2f, 0.02f);
				t_Att->RotZ(D3DX_PI*0.005f);
				break;
			case CVirus::SECONDMINICORE:
				t_Att->BigAndSmallXYAlternately(0.2f, 0.015f);
				t_Att->RotZ(D3DX_PI*-0.0015f);
				break;
			case CVirus::THIRDMINICORE:
				t_Att->BigAndSmallXYAlternately(0.2f, 0.025f);
				t_Att->RotZ(D3DX_PI*0.003f);
				break;
			default:
				break;
		}
	}	
}

void CVirusNormal::Exit(CVirus* _pVirus){

}

bool CVirusNormal::OnMessage(CVirus* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// ControlIn State
///////////////////////////////////////////////////////////
void CVirusControlIn::Enter(CVirus* _pVirus){
	
}

void CVirusControlIn::Execute(CVirus* _pVirus){
	// 바디 계산
	CBody* t_pBody = _pVirus->GetBody();

	t_pBody->GetPriRot()->z = (float)Controller->GetControlData()->GetAngleToFacePositionForOrgan();

	_pVirus->GetHeading() = Controller->GetControlData()->GetHeading();

	// 부속물 계산
	for(int i = 0; i < _pVirus->GetAttachmentArray()->GetSize(); ++i){
		CAttachment* t_Att = _pVirus->GetAttachmentArray()->Get(i);

		if(t_Att->GetPriSca()->x > 0.0f){
			t_Att->NoneRelateDecreaseSca(0.02f);
		}
		else
			_pVirus->OnHide();
	}	

	_pVirus->SetPos(Controller->GetControlData()->GetPos3D());
}

void CVirusControlIn::Exit(CVirus* _pVirus){

}

bool CVirusControlIn::OnMessage(CVirus* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// ControlOut State
///////////////////////////////////////////////////////////
void CVirusControlOut::Enter(CVirus* _pVirus){
	_pVirus->OffHide();
}

void CVirusControlOut::Execute(CVirus* _pVirus){
	// 바디 계산
	CBody* t_pBody = _pVirus->GetBody();

	// 부속물 계산
	for(int i = 0; i < _pVirus->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = _pVirus->GetAttachmentArray()->Get(i);

		if(t_Att->GetPriSca()->x < 1.0f)
			t_Att->NoneRelateIncreaseSca(0.02f);
		else
			_pVirus->GetFSM()->ChangeState(VirusNormal->Instance());
	}	
}

void CVirusControlOut::Exit(CVirus* _pVirus){

}

bool CVirusControlOut::OnMessage(CVirus* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Growing State
///////////////////////////////////////////////////////////
void CVirusGrowing::Enter(CVirus* _pVirus){
	_pVirus->UniformOrganSca(1.0f);
}

void CVirusGrowing::Execute(CVirus* _pVirus){
	// 바디 계산
	CBody* t_pBody = _pVirus->GetBody();

	// 부속물 계산
	for(int i = 0; i < _pVirus->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = _pVirus->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CVirus::FIRSTCYTOPLASM:
				t_Att->GetPriRot()->z -= _pVirus->GetFirstAndSecondCytoplasmRotVelocity();
				break;
			case CVirus::SECONDCYTOPLASM:
				t_Att->GetPriRot()->z += _pVirus->GetFirstAndSecondCytoplasmRotVelocity();
				break;
			case CVirus::THIRDCYTOPLASM:
				t_Att->GetPriRot()->z += _pVirus->GetThirdCytoplasmRotVelocity();
				break;
			case CVirus::FIRSTTAIL:
				break;
			case CVirus::SECONDTAIL:
				break;
			case CVirus::CORE:
				break;
			case CVirus::FIRSTMINICORE:
				t_Att->RotZ(D3DX_PI*0.005f);
				break;
			case CVirus::SECONDMINICORE:
				t_Att->RotZ(D3DX_PI*-0.0015f);
				break;
			case CVirus::THIRDMINICORE:
				t_Att->RotZ(D3DX_PI*0.003f);
				break;
			default:
				break;
		}
	}	
}

void CVirusGrowing::Exit(CVirus* _pVirus){

}

bool CVirusGrowing::OnMessage(CVirus* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
void CVirusDie::Enter(CVirus* _pVirus){
	_pVirus->Die();
	WaveMgr->Play("./Sound/VirusDie.wav", false);
}

void CVirusDie::Execute(CVirus* _pVirus){
	// 바디 계산
	CBody* t_pBody = _pVirus->GetBody();

	if(t_pBody->GetPriSca()->x > 0.0f){
		t_pBody->DecreaseSca(0.008f);
		t_pBody->RotZ(D3DX_PI/180.0f);

		if(t_pBody->GetPriSca()->x <= 0.0f){
			if(SectionMgr->GetSection()->GetFSM()->isInState(SectionExtraSurvival->Instance()))
			{
				MessageMgr->DispatchMessage(SEND_MSG_IMMEDIATELY, VIRUS, IW, Msg_Active, NO_ADDITIONAL_INFO);
			}
			else{
				MessageMgr->DispatchMessage(SEND_MSG_IMMEDIATELY, VIRUS, CHECK, Msg_Active, NO_ADDITIONAL_INFO);
			}
		}

		// 부속물 계산
		for(int i = 0; i < _pVirus->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = _pVirus->GetAttachmentArray()->Get(i);

			switch(t_Att->GetAttType()){
				case CVirus::FIRSTCYTOPLASM:
					t_Att->GetPriRot()->z -= _pVirus->GetFirstAndSecondCytoplasmRotVelocity();
					t_Att->NoneRelateIncreaseSca(0.002f);
					break;
				case CVirus::SECONDCYTOPLASM:
					t_Att->GetPriRot()->z += _pVirus->GetFirstAndSecondCytoplasmRotVelocity();
					t_Att->NoneRelateIncreaseSca(0.002f);
					break;
				case CVirus::THIRDCYTOPLASM:
					t_Att->GetPriRot()->z += _pVirus->GetThirdCytoplasmRotVelocity();
					t_Att->NoneRelateIncreaseSca(0.002f);
					break;
				case CVirus::FIRSTTAIL:
					if(t_Att->GetPriSca()->y > 0.0f)		t_Att->GetPriSca()->y -= 0.01f;
					break;
				case CVirus::SECONDTAIL:
					if(t_Att->GetPriSca()->y > 0.0f)		t_Att->GetPriSca()->y -= 0.01f;
					break;
				case CVirus::CORE:
					t_Att->BigAndSmallXYAlternately(0.15f, 0.002f);
					t_Att->NoneRelateDecreaseSca(0.008f);
					break;
				case CVirus::FIRSTMINICORE:
					if(t_Att->GetPriSca()->x > 0.0f)
						t_Att->NoneRelateDecreaseSca(0.01f);
					break;
				case CVirus::SECONDMINICORE:
					if(t_Att->GetPriSca()->x > 0.0f)
						t_Att->NoneRelateDecreaseSca(0.01f);
					break;
				case CVirus::THIRDMINICORE:
					if(t_Att->GetPriSca()->x > 0.0f)
						t_Att->NoneRelateDecreaseSca(0.01f);
					break;
				default:
					break;
			}
		}	
	}
}

void CVirusDie::Exit(CVirus* _pVirus){

}

bool CVirusDie::OnMessage(CVirus* agent, const Telegram& _rMsg){
	return false;
}