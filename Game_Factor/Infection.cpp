#include "Infection.h"
#include "InfectionOwnedStates.h"

CInfection::CInfection(CData* _pData):COrganEntity(),
									m_pData(_pData),
									m_fEffectFirstFrequency(0.025f),
									m_fEffectSecondFrequency(0.02f)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CInfection>(this);

	LoadEntityData("./script/Effect/Infection.txt");

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(InfectionInit->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	if(GetOrigin()->GetGrowth()->IsGrowth(CGrowth::FIRST)){
		ResizeObject(0.04f);		
	}
	else if(GetOrigin()->GetGrowth()->IsGrowth(CGrowth::SECOND)){
		ResizeObject(0.2f);
	}

	GetBody()->UniformSca(0.0f);

	this->GetBody()->SetShearUse(false);
	this->GetAttachmentFromType(FIRSTMINICORE)->SetShearUse(false);
	this->GetAttachmentFromType(SECONDMINICORE)->SetShearUse(false);
}

CInfection::~CInfection(){
	Delete<CStateMachine<CInfection>*>(m_pStateMachine);
}

void CInfection::Update(double _dTimeElapsed){
	GetBody()->GetPriSca()->x = (float)((double)(20-GetOrigin()->GetByteIndex())/(double)20);
	GetBody()->GetPriSca()->y = (float)((double)(20-GetOrigin()->GetByteIndex())/(double)20);

	for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){
		GetAttachmentArray()->Get(i)->GetPriSca()->x = (float)((double)(20-GetOrigin()->GetByteIndex())/(double)20);
		GetAttachmentArray()->Get(i)->GetPriSca()->y = (float)((double)(20-GetOrigin()->GetByteIndex())/(double)20);
	}	

	m_pStateMachine->Update();
}