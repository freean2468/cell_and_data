#include "Gauge.h"
#include "GaugeOwnedStates.h"
#include "Controller.h"
#include "WorldManager.h"
#include "UIManager.h"
#include "../Engine_Logic/EventManager.h"

CGauge::CGauge():COrganEntity(-1),
				m_bActive(false),
				m_fMaxGauge(0),
				m_fPresentGauge(0),
				m_fFirstGauge(0),
				m_fSecondGauge(0)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CGauge>(this);

	// 기관 설정
	LoadEntityData("./script/UserInterface/Gauge/Gauge.txt");
			
	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(GaugeMaintain->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	GetBody()->SetColor(&D3DXCOLOR(-1.0f, -1.0f, -1.0f, 1.0f));

	GetAttachmentFromType(GAUGE)->SetColor(&D3DXCOLOR(1.0f, -1.0f, -1.0f, 1.0f));
	GetAttachmentFromType(GAUGE)->SetPriSca(&D3DXVECTOR3(0.0f, 1.0f, 1.0f));

	GetAttachmentFromType(STICK_FIRST)->SetColor(&D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
	GetAttachmentFromType(STICK_SECOND)->SetColor(&D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
	GetAttachmentFromType(OUTLINE)->SetColor(&D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));
}

CGauge::~CGauge(){
	Delete< CStateMachine<CGauge>* >(m_pStateMachine);
}

void CGauge::Initialize(){
	m_fMaxGauge = 0;
	m_fPresentGauge = 0;
	m_fFirstGauge = 0;
	m_fSecondGauge = 0;

	if(WorldMgr->GetMapParam()->m_nFirstData > 0)
		m_fMaxGauge += WorldMgr->GetMapParam()->m_nFirstData * 20.0f * 4.0f;
	
	m_fFirstGauge = m_fMaxGauge * 3.0f / 5.0f;

	if(WorldMgr->GetMapParam()->m_nSecondData > 0){
		m_fMaxGauge += WorldMgr->GetMapParam()->m_nSecondData * 20.0f * 8.0f;
		m_fSecondGauge = m_fMaxGauge * 7.0f / 10.0f;
	}
	else
		m_fSecondGauge = 0.0f;

	if(WorldMgr->GetMapParam()->m_nThirdData > 0)
		m_fMaxGauge += WorldMgr->GetMapParam()->m_nThirdData * 20.0f * 16.0f;
}

void CGauge::Update(){ 
	if(m_bActive && m_fMaxGauge != 0.0f && !EventMgr->GetScript()){
		m_pStateMachine->Update();
		UIMgr->GetTextOfGame()->UpdateScore();

		if(m_fFirstGauge != 0.0f && m_fFirstGauge < m_fPresentGauge && Controller->GetController()->GetGrowth()->IsGrowth(CGrowth::FIRST))
			Controller->Grow(CGrowth::SECOND);
		
		if(m_fSecondGauge != 0.0f &&m_fSecondGauge < m_fPresentGauge  && Controller->GetController()->GetGrowth()->IsGrowth(CGrowth::SECOND))
			Controller->Grow(CGrowth::THIRD);
	}
}