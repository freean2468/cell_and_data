#include "PlanetEntity.h"
#include "PlanetEntityOwnedstates.h"
#include "../Engine_Math&Physics/Transformation.h"

CPlanetEntity::CPlanetEntity(float _fPlanetRadius, bool _bStatic, int _nEntityType) : CMovingEntity(_nEntityType,
																									Vector2D(0,1),
																									Vector2D(0,0),
																									10,
																									Vector2D(0,1),
																									1,
																									1,
																									10)
{
	//SetBody(new CBody());
	//GetBody()->InitObject(EngineMgr->GetpDevice(), "./Image/GameFactor/PlanetEntity/Human.dds", 50, 70, 1.0f, 0);

	//SetPos(::RandInRange(-180,180), ::RandInRange(-180,180));

	m_pGravity = new CGravity(this, _fPlanetRadius*0.99f, _bStatic);

	if(RandBool()){
		SetDirection(CBasicEntity::RIGHT);
	}
	else{
		SetDirection(CBasicEntity::LEFT);
	}

	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CPlanetEntity>(this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(PlanetEntityNormal->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	//this->UniformOrganSca(BaseParamLdr->m_fGrowth);
}

CPlanetEntity::~CPlanetEntity(){
	Delete< CStateMachine<CPlanetEntity>* >(m_pStateMachine);
	Delete<CGravity*>(m_pGravity);
}

void CPlanetEntity::Update(double _dTImeElapsed){
	GetFSM()->Update();

	Vector2D t_vControlledTarget(0, 0);
	
	if(m_eDirection == CBasicEntity::RIGHT){
		t_vControlledTarget += (m_vVelocity*-1);
	}
	else{
		t_vControlledTarget += m_vVelocity;
	}

	t_vControlledTarget.Normalize();

	Vector2D Target = PointToWorldSpace(t_vControlledTarget,
                                       GetHeading(),
                                       GetSide(), 
                                       GetPos2D());

	m_pGravity->CalGravity(Target-GetPos2D());

	if(!GetGravity()->GetStatic()){
		this->CycleRotX(D3DX_PI/12.0f, D3DX_PI/120.0f);
		this->CycleRotY(D3DX_PI/6.0f, D3DX_PI/100.0f);
	}

	GetBody()->SetPriPos(GetPos3D());
	GetBody()->SetPriRot(GetRot3D());
}