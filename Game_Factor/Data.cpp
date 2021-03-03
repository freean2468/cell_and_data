#include "Data.h"
#include "DataOwnedStates.h"
#include "ByteOwnedStates.h"
#include "UIManager.h"
#include "../Engine_System/WaveManager.h"

CData::CData(int _nEntityType,
			int _nGrowth, 
			Vector2D _vPos, 
			Vector2D _vVelocity,
			double _dMass, 
			double _dMaxForce, 
			double _dMaxSpeed, 
			double _dMaxTurnRate) : CCellEntity(_nEntityType,
												static_cast<CGrowth::GROWTH>(_nGrowth),
												_vPos, 
												_vVelocity,
												_dMass,
												_dMaxForce,
												_dMaxSpeed,
												_dMaxTurnRate),
									m_pExhaleGap(new CTimer(0)),
									m_nByteIndex(0),
									m_eState(NORMAL),
									m_pVariationTimer(new CTimer(0)),
									m_pToDieTimer(new CTimer(0)),
									m_bVariation(false)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CData>(this);

	// Data는 0과 1 둘 중 하나.
	if(RandInt(1, 100)%2 != 0){
		LoadEntityData("./script/Character/One.txt");
		m_eDataType = TYPEONE;
	}
	else{
		LoadEntityData("./script/Character/Zero.txt");
		m_eDataType = TYPEZERO;
	}

	switch(_nGrowth){
		case 2:
			ResizeObject(0.2f);
			GetGrowth()->SetGrowth(CGrowth::SECOND);			
			this->SetMaxSpeed(60);
			this->SetCellSpeedLimit(60);
			break;
		case 3:
			ResizeBoundRadius();
			GetGrowth()->SetGrowth(CGrowth::THIRD);			
			break;
		case 1:
		default:
			ResizeObject(0.04f);
			GetGrowth()->SetGrowth(CGrowth::FIRST);			
			this->SetMaxSpeed(30);
			this->SetCellSpeedLimit(30);
			break;
	}

	UniformOrganSca(1.0f);

	D3DXCOLOR t_vCor(-1.0f, 1.0f, -1.0f, 1.0f);

	// 처음 초록색
	this->UniformOrganColor(t_vCor);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(DataNormal->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	this->GetBody()->SetShearUse(false);

	InsertInfection(this);
	WaveInitialize();

	m_Bytes.resize(20);

	for(int i = 0; i != m_Bytes.size(); ++i)
		m_Bytes[i] = new CByte(this);
}

CData::~CData(){
	Delete< CStateMachine<CData>* >(m_pStateMachine);
	Delete< CTimer* >(m_pVariationTimer);
	Delete< CTimer* >(m_pToDieTimer);
	
	for(std::vector<CByte*>::size_type i = 0; i < m_Bytes.size(); ++i)
		Delete<CByte*>(m_Bytes[i]);
	
	Delete<CTimer*>(m_pExhaleGap);

	
	std::list<CInfection*>::iterator t_itrInfection;

	for(t_itrInfection = m_pInfections.begin(); t_itrInfection != m_pInfections.end();){
		t_itrInfection = m_pInfections.erase(t_itrInfection);
	}
}

void CData::InsertInfection(CData* _pData){
	m_pInfections.push_back(new CInfection(_pData));
}

void CData::Initialize(){
	m_bVariation = false;

	if(this->GetGrowth()->IsGrowth(CGrowth::FIRST)){
		SetMaxSpeed(30);
		SetCellSpeedLimit(30);
	}
	else if(this->GetGrowth()->IsGrowth(CGrowth::SECOND)){
		SetMaxSpeed(60);
		SetCellSpeedLimit(60);
	}
	else if(this->GetGrowth()->IsGrowth(CGrowth::THIRD)){
		SetMaxSpeed(100);
		SetCellSpeedLimit(100);
	}
}

void CData::OrganUpdate(){
	if(GetBody()){
		GetBody()->GetPriPos()->x = (float)GetPos3D()->x;
		GetBody()->GetPriPos()->y = (float)GetPos3D()->y;

		GetBody()->GetPriRot()->z = (float)GetAngleToFacePositionForOrgan();
	}
}

void CData::Update(double _dTimeElapsed){
	CCellEntity::Update(_dTimeElapsed);

	StateUpdate();

	UpdateBytes();

	m_pStateMachine->Update();

	if(this->m_eState == ABSORPTION)
		SetOldState(); 

	RenderBytes();
}

void CData::Render(){
	CCellEntity::Render();

	this->InfectionRender();
}

void CData::StateUpdate(){
	if(m_eState == NORMAL || m_eState == ABSORPTION){
		return;
	}
	else if(m_eState == INFECTION){
		if(!m_bVariation){
			m_bVariation = true;
			m_pVariationTimer->InitTimer(5000);
		}
		else{
			if(m_pVariationTimer->IsElapseTimer()){
				m_eState = VARIATION;

				m_pToDieTimer->InitTimer(20000);
			}
		}
	}
	else if(m_eState == VARIATION){
		this->SetMass(this->GetMass()+0.01);

		if(m_pToDieTimer->IsElapseTimer()){
			m_eState = DYING;
		}
	}
}

void CData::UpdateBytes(){
	if(m_eState == DYING){
		if(m_nByteIndex < 20){
			if(m_pExhaleGap->IsElapseTimer()){
				m_pExhaleGap->InitTimer(150);
				GetBytes()->at(m_nByteIndex)->SetState(CByte::BYTE_EXHALE);
				GetBytes()->at(m_nByteIndex++)->GetFSM()->ChangeState(ByteExhale->Instance());
				if(!EngineMgr->IsViewOut(GetPos3D()))
					WaveMgr->Play("./Sound/Absorption.wav", false);
			}		
		}
	}
	else if(m_eState == ABSORPTION){
		if(m_nByteIndex < 20){
			if(m_pExhaleGap->IsElapseTimer()){
				m_pExhaleGap->InitTimer(150);
				UIMgr->GetGauge()->AddPresentGauge(static_cast<float>(GetBytes()->at(m_nByteIndex++)->GetCapacity()));
				WaveMgr->Play("./Sound/Absorption.wav", false);
			}		
		}		
	}
}

void CData::RenderBytes(){
	for(std::vector<CByte*>::size_type i = 0; i < m_Bytes.size(); ++i){
		m_Bytes[i]->Update();
	}
}

void CData::InfectionRender(){
	std::list<CInfection*>::iterator t_itr;

	for(t_itr = m_pInfections.begin(); t_itr != m_pInfections.end(); ++t_itr){
		if(GetState() != CData::NORMAL && IsAlive()){
			(*t_itr)->Update();					
			break;
		}
	}
}