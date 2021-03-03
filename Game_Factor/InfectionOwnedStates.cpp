#include "InfectionOwnedStates.h"
#include "../Engine_System/Body.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CInfectionUsual::Enter(CInfection* pInfection){
	
}

void CInfectionUsual::Execute(CInfection* pInfection){
	CBody* t_pBody = pInfection->GetBody();
	CBody* t_pOrigin = pInfection->GetOrigin()->GetBody();

	t_pBody->GetPriPos()->x = t_pOrigin->GetPriPos()->x;
	t_pBody->GetPriPos()->y = t_pOrigin->GetPriPos()->y;
	t_pBody->GetPriPos()->z = t_pOrigin->GetPriPos()->z;

	t_pBody->GetPriRot()->z = (float)pInfection->GetOrigin()->GetAngleToFacePositionForOrgan();

	// 부속물 계산
	for(int i = 0; i < pInfection->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pInfection->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CInfection::FIRSTMINICORE:
				t_Att->BigAndSmallXYAlternately(pInfection->GetEffectFirstMax(), pInfection->GetEffectFirstFrequency());
				t_Att->RotZ(D3DX_PI*0.005f);
				break;
			case CInfection::SECONDMINICORE:
				t_Att->BigAndSmallXYAlternately(pInfection->GetEffectSecondMax(), pInfection->GetEffectSecondFrequency());
				t_Att->RotZ(D3DX_PI*0.01f);
				break;
			default:
				break;
		}
	}	

	if(pInfection->GetOrigin()->GetState() == CData::DYING)
		pInfection->GetFSM()->ChangeState(InfectionDisappear->Instance());

	pInfection->RenderOrgan();
}

void CInfectionUsual::Exit(CInfection* pInfection){

}

bool CInfectionUsual::OnMessage(CInfection* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Init State
///////////////////////////////////////////////////////////
void CInfectionInit::Enter(CInfection* pInfection){
	
}

void CInfectionInit::Execute(CInfection* pInfection){
	CBody* t_pBody = pInfection->GetBody();
	CBody* t_pOrigin = pInfection->GetOrigin()->GetBody();

	t_pBody->GetPriPos()->x = t_pOrigin->GetPriPos()->x;
	t_pBody->GetPriPos()->y = t_pOrigin->GetPriPos()->y;
	t_pBody->GetPriPos()->z = t_pOrigin->GetPriPos()->z;

	t_pBody->GetPriRot()->z = (float)pInfection->GetOrigin()->GetAngleToFacePositionForOrgan();

	if(pInfection->GetOrigin()->GetBody()->GetMtrl()->Diffuse.r >= 1.0f)
		pInfection->GetFSM()->ChangeState(InfectionUsual->Instance());

	// 부속물 계산
	for(int i = 0; i < pInfection->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pInfection->GetAttachmentArray()->Get(i);

		if(t_Att->GetPriSca()->x < pInfection->GetMaxSca()){
			t_Att->IncreaseSca(pInfection->GetFrequency());
		}

		switch(t_Att->GetAttType()){
			case CInfection::FIRSTMINICORE:
				t_Att->BigAndSmallXYAlternately(0.1f, 0.02f);
				t_Att->RotZ(D3DX_PI*0.01f);
				break;
			case CInfection::SECONDMINICORE:
				t_Att->BigAndSmallXYAlternately(0.2f, 0.015f);
				t_Att->RotZ(D3DX_PI*0.02f);
				break;
			default:
				break;
		}
	}	

	if(pInfection->GetOrigin() == NULL)
		pInfection->Die();

	pInfection->RenderOrgan();
}

void CInfectionInit::Exit(CInfection* pInfection){

}

bool CInfectionInit::OnMessage(CInfection* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Disappear State
///////////////////////////////////////////////////////////
void CInfectionDisappear::Enter(CInfection* pInfection){
	
}

void CInfectionDisappear::Execute(CInfection* pInfection){
	CBody* t_pBody = pInfection->GetBody();
	CBody* t_pOrigin = pInfection->GetOrigin()->GetBody();

	t_pBody->GetPriPos()->x = t_pOrigin->GetPriPos()->x;
	t_pBody->GetPriPos()->y = t_pOrigin->GetPriPos()->y;
	t_pBody->GetPriPos()->z = t_pOrigin->GetPriPos()->z;

	t_pBody->GetPriRot()->z = (float)pInfection->GetOrigin()->GetAngleToFacePositionForOrgan();

	// 부속물 계산
	for(int i = 0; i < pInfection->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pInfection->GetAttachmentArray()->Get(i);

		if(t_Att->GetPriSca()->x > 0.0f){
			t_Att->DecreaseSca(0.01f);
			t_Att->DecreaseAlpha(0.01f);
		}

		switch(t_Att->GetAttType()){
			case CInfection::FIRSTMINICORE:
				t_Att->BigAndSmallXYAlternately(0.1f, 0.02f);
				t_Att->RotZ(D3DX_PI*0.01f);
				break;
			case CInfection::SECONDMINICORE:
				t_Att->BigAndSmallXYAlternately(0.2f, 0.015f);
				t_Att->RotZ(D3DX_PI*0.02f);
				break;
			default:
				break;
		}
	}	

	if(pInfection->GetOrigin() == NULL)
		pInfection->Die();

	pInfection->RenderOrgan();
}

void CInfectionDisappear::Exit(CInfection* pInfection){

}

bool CInfectionDisappear::OnMessage(CInfection* agent, const Telegram& _rMsg){
	return false;
}