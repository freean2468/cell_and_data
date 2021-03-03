#include "Byte.h"
#include "ByteOwnedStates.h"

CByte::CByte(CData* _pData):m_pData(_pData), m_eState(BYTE_INACTIVE){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CByte>(this);

	LoadEntityData("./script/GameFactor/Byte/Byte.txt");

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(ByteInActive->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	if(GetOrigin()->GetGrowth()->IsGrowth(CGrowth::FIRST)){
		ResizeObject(0.1f);	
		m_nCapacity = 4;
	}
	else if(GetOrigin()->GetGrowth()->IsGrowth(CGrowth::SECOND)){
		ResizeObject(0.4f);
		m_nCapacity = 8;
	}
	else
		m_nCapacity = 16;

	this->UniformOrganColor(D3DXCOLOR(1.0f, -1.0f, -1.0f, 1.0f));
	this->UniformOrganAlpha(0.7f);
}

CByte::~CByte(){
	Delete<CStateMachine<CByte>*>(m_pStateMachine);
}

void CByte::Update(double _dTimeElapsed){ 
	if(m_eState == BYTE_INACTIVE)
		return;
	else
		m_pStateMachine->Update();
}

void CByte::SetOrigin(){
	GetBody()->GetPriPos()->x = m_pData->GetBody()->GetPriPos()->x;
	GetBody()->GetPriPos()->y = m_pData->GetBody()->GetPriPos()->y;

	GetBody()->GetPriRot()->z = m_pData->GetBody()->GetPriRot()->z;
}