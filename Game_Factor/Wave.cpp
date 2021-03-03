#include "Wave.h"
#include "WaveOwnedStates.h"

CWave::CWave(CCellEntity* _pCell):COrganEntity(-1),
								m_pOrigin(_pCell),
								m_fAlphaAce(-0.005f),
								m_fMaxSca(1.0f),
								m_bActive(false)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CWave>(this);

	LoadEntityData("./script/Effect/Wave.txt");

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(WaveUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);	

	if(GetOrigin()->GetGrowth()->IsGrowth(CGrowth::FIRST)){
		ResizeObject(0.2f);		
		m_fScaAce = 0.008f;	
	}
	else if(GetOrigin()->GetGrowth()->IsGrowth(CGrowth::SECOND)){
		ResizeObject(0.4f);
		m_fScaAce = 0.012f;
	}
	else
		m_fScaAce = 0.012f;

	this->UniformOrganSca(0.1f);

	GetBody()->GetMtrl()->Diffuse.a = 0.3f;

	GetBody()->SetShearUse(false);
}

CWave::~CWave(){
	Delete<CStateMachine<CWave>*>(m_pStateMachine);
}

void CWave::Initialize(){
	OffActive();

	m_fMaxSca = this->GetOrigin()->GetBody()->GetPriSca()->x;

	UniformOrganSca(0.1f);

	if(GetOrigin()->GetGrowth()->IsGrowth(CGrowth::FIRST)){
		m_fScaAce = 0.008f * m_fMaxSca;	
	}
	else if(GetOrigin()->GetGrowth()->IsGrowth(CGrowth::SECOND)){
		m_fScaAce = 0.012f * m_fMaxSca;
	}
	else{
		m_fScaAce = 0.012f * m_fMaxSca;
	}

	GetBody()->GetMtrl()->Diffuse.a = 0.3f;
}

void CWave::Update(double _dTimeElapsed){
	GetBody()->GetPriSca()->x += GetScaAce();
	GetBody()->GetPriSca()->y += GetScaAce();
	GetBody()->GetMtrl()->Diffuse.a += GetAlphaAce();

	if(GetOrigin() == NULL){
		Die();
		return;
	}

	if(GetBody()->GetMtrl()->Diffuse.a <= 0.0f)
		Initialize();	
}

void CWave::Render(){
	m_pStateMachine->Update();
}

void CWave::SetOrigin(COrganEntity* _pEntity){
	GetBody()->GetPriPos()->x = _pEntity->GetBody()->GetPriPos()->x;
	GetBody()->GetPriPos()->y = _pEntity->GetBody()->GetPriPos()->y;
	GetBody()->GetPriRot()->z = _pEntity->GetBody()->GetPriRot()->z;
}