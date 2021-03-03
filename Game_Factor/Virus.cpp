#include "../BaseHeader.h"

CVirus::CVirus(CGrowth::GROWTH _eGrowth, 
								Vector2D _vPos, 
								Vector2D _vVelocity,
								double _dMass, 
								double _dMaxForce, 
								double _dMaxSpeed, 
								double _dMaxTurnRate) : CCellEntity(VIRUS,
																										_eGrowth,
																										_vPos, 
																										_vVelocity,
																										_dMass,
																										_dMaxForce,
																										_dMaxSpeed,
																										_dMaxTurnRate)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CVirus>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Character/Virus.txt");

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(VirusNormal->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	m_fBodyRotVelocity = 0.01f;
	m_fFirstAndSecondCytoplasmRotVelocity = 0.01f;
	m_fThirdCytoplasmRotVelocity = 0.005f;

	this->GetAttachmentFromType(CVirus::FIRSTCYTOPLASM)->SetShearUse(true);
	this->GetAttachmentFromType(CVirus::SECONDCYTOPLASM)->SetShearUse(true);
	this->GetAttachmentFromType(CVirus::THIRDCYTOPLASM)->SetShearUse(true);

	GetGrowth()->SetGrowth(_eGrowth);		

	Controller->SetSecondBRadius(GetRadius()*0.25);
	Controller->SetThirdBRadius(GetRadius()*0.45);

	if(GetGrowth()->IsGrowth(CGrowth::FIRST)){
		ResizeObject(0.1f);
	}
	else if(GetGrowth()->IsGrowth(CGrowth::SECOND)){
		ResizeObject(0.15f);
	}

	WaveInitialize();
}

CVirus::~CVirus(){
	Delete< CStateMachine<CVirus>* >(m_pStateMachine);
}

//------------------------------ Update ----------------------------------
//
//  Updates the CVehicle's position from a series of steering behaviors
//------------------------------------------------------------------------
void CVirus::Update(double _dTimeElapsed){ 
	if(this->IsAlive()){
		CCellEntity::Update(_dTimeElapsed);
	}

	m_pStateMachine->Update();
}