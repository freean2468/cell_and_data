#include "Vacine.h"
#include "VacineOwnedStates.h"

CVacine::CVacine(int _nEntityType,
				CGrowth::GROWTH _eGrowth, 
				Vector2D _vPos, 
				Vector2D _vVelocity,
				double _dMass, 
				double _dMaxForce, 
				double _dMaxSpeed, 
				double _dMaxTurnRate) : CCellEntity(_nEntityType,
													_eGrowth, 
													_vPos,
													_vVelocity,
													_dMass,
													_dMaxForce,
													_dMaxSpeed,
													_dMaxTurnRate),
										m_pData(NULL)
{
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CVacine>(this);

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/Character/Vacine.txt");

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(VacineStand->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	m_fBodyRotVelocity = 0.01f;
	m_fFirstAndSecondCytoplasmRotVelocity = 0.01f;
	m_fThirdCytoplasmRotVelocity = 0.005f;

	this->GetAttachmentFromType(CVacine::FIRSTCYTOPLASM)->SetShearUse(true);
	this->GetAttachmentFromType(CVacine::SECONDCYTOPLASM)->SetShearUse(true);
	this->GetAttachmentFromType(CVacine::THIRDCYTOPLASM)->SetShearUse(true);

	GetGrowth()->SetGrowth(_eGrowth);		

	if(GetGrowth()->IsGrowth(CGrowth::FIRST)){
		ResizeObject(0.15f);
		GetSteering()->SetViewDistance(GetSteering()->GetViewDistance() * 1.5);
	}
	else if(GetGrowth()->IsGrowth(CGrowth::SECOND)){
		ResizeObject(0.45f);
		GetSteering()->SetViewDistance(GetSteering()->GetViewDistance() * 3);
	}

	WaveInitialize();
}

CVacine::~CVacine(){
	Delete< CStateMachine<CVacine>* >(m_pStateMachine);
}

//------------------------------ Update ----------------------------------
//
//  Updates the CVehicle's position from a series of steering behaviors
//------------------------------------------------------------------------
void CVacine::Update(double _dTimeElapsed){    
	CCellEntity::Update(_dTimeElapsed);

	m_pStateMachine->Update();
}