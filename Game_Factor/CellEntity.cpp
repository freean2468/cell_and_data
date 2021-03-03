#include "CellEntity.h"
#include "../Engine_System/CollisionManager.h"

CCellEntity::CCellEntity(int _nEntityType,
						CGrowth::GROWTH _eGrowth, 
						Vector2D _vPos, 
						Vector2D _vVelocity,
						double _dMass, 
						double _dMaxForce, 
						double _dMaxSpeed, 
						double _dMaxTurnRate) : CVehicle(_nEntityType,
														_vPos, 
														Vector2D(1,0),
														_vVelocity,
														_dMass,
														_dMaxForce,
														_dMaxSpeed,
														_dMaxTurnRate),
												m_pGrowth(new CGrowth(_eGrowth)),
												m_bDivision(true),
												m_pTimer(new CTimer(800)),
												m_dCellSpeedLimit(_dMaxSpeed)
{
	
}

CCellEntity::~CCellEntity(){
	std::list<CWave*>::iterator t_itrWave;

	for(t_itrWave = m_pWaves.begin(); t_itrWave != m_pWaves.end();){
		t_itrWave = m_pWaves.erase(t_itrWave);
	}

	Delete<CGrowth*>(m_pGrowth);
	Delete<CTimer*>(m_pTimer);
}

void CCellEntity::WaveInitialize(){
	// Effect Ãß°¡
	InsertWave(this);
	InsertWave(this);
	InsertWave(this);
}

void CCellEntity::InsertWave(CCellEntity* _pAgent){
	m_pWaves.push_back(new CWave(_pAgent));
}

void CCellEntity::Update(double _dTimeElapsed){
	MovingOfCell();

	if(GetTimer()->IsValidTimer()){
		if(GetTimer()->IsElapseTimer()){
			GetTimer()->InitTimer(800);
			
			if(IsAlive())
				WaveSetting();
		}
	}

	WaveUpdate();

	CVehicle::Update();
	CollisionMgr->EnforceNonPenetrationOtherEntity(this);
}

void CCellEntity::Render(){
	WaveRender();

	CVehicle::Render();
}

void CCellEntity::WaveSetting(){
	std::list<CWave*>::iterator t_itr;

	for(t_itr = m_pWaves.begin(); t_itr != m_pWaves.end(); ++t_itr){
		if(!(*t_itr)->IsActive()){
			(*t_itr)->SetOrigin(this);
			(*t_itr)->OnActive();
			break;
		}
	}
}

void CCellEntity::WaveUpdate(){
	std::list<CWave*>::iterator t_itr;

	for(t_itr = m_pWaves.begin(); t_itr != m_pWaves.end(); ++t_itr){
		if((*t_itr)->IsActive() && (*t_itr)->IsAlive()){
			(*t_itr)->Update();
		}
	}
}

void CCellEntity::WaveRender(){
	std::list<CWave*>::iterator t_itr;

	for(t_itr = m_pWaves.begin(); t_itr != m_pWaves.end(); ++t_itr){
		if((*t_itr)->IsActive() && (*t_itr)->IsAlive()){
			(*t_itr)->Render();
		}
	}
}

void CCellEntity::WaveDie(){
	std::list<CWave*>::iterator t_itr;

	for(t_itr = m_pWaves.begin(); t_itr != m_pWaves.end();++t_itr){
		(*t_itr)->Die();
	}
}

void CCellEntity::MovingOfCell(){
	if(m_bDivision){
		SetMaxSpeed(GetMaxSpeed() + 6);
		if((m_dCellSpeedLimit + 20.0) * (1/GetMass()) < GetMaxSpeed()){
			m_bDivision = !m_bDivision;
		}
	}
	else{
		SetMaxSpeed(GetMaxSpeed() - 3);
		if(30.0 * (1/GetMass()) > GetMaxSpeed()){
			m_bDivision = !m_bDivision;
		}
	}
}