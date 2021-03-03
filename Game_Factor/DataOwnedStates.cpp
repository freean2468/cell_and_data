#include "DataOwnedStates.h"
#include "../Engine_System/Body.h"
#include "../Engine_System/WaveManager.h"

///////////////////////////////////////////////////////////
// Normal State
///////////////////////////////////////////////////////////
void CDataNormal::Enter(CData* _pData){
	
}

void CDataNormal::Execute(CData* _pData){
	CBody* t_pBody = _pData->GetBody();

	if(_pData->GetState() == CData::VARIATION){
		t_pBody->GetMtrl()->Diffuse.r += 0.02f;
		t_pBody->GetMtrl()->Diffuse.g -= 0.02f;
		t_pBody->GetMtrl()->Diffuse.b -= 0.02f;

		for(int i = 0; i < _pData->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = _pData->GetAttachmentArray()->Get(i);
			
			t_Att->GetMtrl()->Diffuse.r += 0.02f;
			t_Att->GetMtrl()->Diffuse.g -= 0.02f;
			t_Att->GetMtrl()->Diffuse.b -= 0.02f;
		}	

		if(_pData->GetBody()->GetMtrl()->Diffuse.r >= 1.0f)
			_pData->GetFSM()->ChangeState(DataVariation->Instance());
	}	

	// 부속물 계산
	for(int i = 0; i < _pData->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = _pData->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){			
			case CData::CORE:
				t_Att->BigAndSmallXYAlternately(0.15f, 0.002f);
				break;
			case CData::FIRSTMINICORE:
				t_Att->BigAndSmallXYAlternately(0.2f, 0.02f);
				break;
			case CData::SECONDMINICORE:
				t_Att->BigAndSmallXYAlternately(0.3f, 0.015f);
				break;
			default:
				break;
		}
	}	

	if(_pData->GetState() == CData::ABSORPTION){
		if(t_pBody->GetPriSca()->x > 0.0f){
			t_pBody->GetPriSca()->x = (float)((double)(20-_pData->GetByteIndex())/(double)20);
			t_pBody->GetPriSca()->y = (float)((double)(20-_pData->GetByteIndex())/(double)20);

			for(int i = 0; i < _pData->GetAttachmentArray()->GetSize(); i++){
				_pData->GetAttachmentArray()->Get(i)->GetPriSca()->x = (float)((double)(20-_pData->GetByteIndex())/(double)20);
				_pData->GetAttachmentArray()->Get(i)->GetPriSca()->y = (float)((double)(20-_pData->GetByteIndex())/(double)20);
			}	
		}
		else{
			if(_pData->IsViewing()){
				WaveMgr->Play("./Sound/Laugh.wav", false);
			}

			_pData->Die();
		}
	}
}

void CDataNormal::Exit(CData* _pData){

}

bool CDataNormal::OnMessage(CData* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Variation State
///////////////////////////////////////////////////////////
void CDataVariation::Enter(CData* _pData){

}

void CDataVariation::Execute(CData* _pData){
	CBody* t_pBody = _pData->GetBody();

	// 부속물 계산
	for(int i = 0; i < _pData->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = _pData->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){			
			case CData::CORE:
				t_Att->BigAndSmallXYAlternately(0.15f, 0.002f);
				break;
			case CData::FIRSTMINICORE:
				t_Att->BigAndSmallXYAlternately(0.2f, 0.02f);
				break;
			case CData::SECONDMINICORE:
				t_Att->BigAndSmallXYAlternately(0.3f, 0.015f);
				break;
			default:
				break;
		}
	}	

	if(_pData->GetState() == CData::DYING || _pData->GetState() == CData::ABSORPTION){
		if(t_pBody->GetPriSca()->x > 0.0f){
			t_pBody->GetPriSca()->x = (float)((double)(20-_pData->GetByteIndex())/(double)20);
			t_pBody->GetPriSca()->y = (float)((double)(20-_pData->GetByteIndex())/(double)20);

			for(int i = 0; i < _pData->GetAttachmentArray()->GetSize(); i++){
				_pData->GetAttachmentArray()->Get(i)->GetPriSca()->x = (float)((double)(20-_pData->GetByteIndex())/(double)20);
				_pData->GetAttachmentArray()->Get(i)->GetPriSca()->y = (float)((double)(20-_pData->GetByteIndex())/(double)20);
			}	
		}
		else{
			if(!EngineMgr->IsViewOut(_pData->GetPos3D())){
				WaveMgr->Play("./Sound/Laugh.wav", false);
			}
			_pData->Die();
		}
	}	
}

void CDataVariation::Exit(CData* _pData){

}

bool CDataVariation::OnMessage(CData* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Cure State
///////////////////////////////////////////////////////////
void CDataCure::Enter(CData* _pData){
	
}

void CDataCure::Execute(CData* _pData){
	CBody* t_pBody = _pData->GetBody();

	if(_pData->GetBody()->GetMtrl()->Diffuse.g < 1.0f){
		t_pBody->GetMtrl()->Diffuse.r -= 0.02f;
		t_pBody->GetMtrl()->Diffuse.g += 0.02f;
		t_pBody->GetMtrl()->Diffuse.b += 0.02f;

		for(int i = 0; i < _pData->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = _pData->GetAttachmentArray()->Get(i);
			
			t_Att->GetMtrl()->Diffuse.r -= 0.02f;
			t_Att->GetMtrl()->Diffuse.g += 0.02f;
			t_Att->GetMtrl()->Diffuse.b += 0.02f;
		}	
	}
	else{
		_pData->SetState(CData::NORMAL);
		_pData->Initialize();

		_pData->GetFSM()->ChangeState(DataNormal->Instance());
	}

	// 부속물 계산
	for(int i = 0; i < _pData->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = _pData->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){			
			case CData::CORE:
				t_Att->BigAndSmallXYAlternately(0.15f, 0.002f);
				break;
			case CData::FIRSTMINICORE:
				t_Att->BigAndSmallXYAlternately(0.2f, 0.02f);
				break;
			case CData::SECONDMINICORE:
				t_Att->BigAndSmallXYAlternately(0.3f, 0.015f);
				break;
			default:
				break;
		}
	}	
}

void CDataCure::Exit(CData* _pData){
	
}

bool CDataCure::OnMessage(CData* agent, const Telegram& _rMsg){
	return false;
}