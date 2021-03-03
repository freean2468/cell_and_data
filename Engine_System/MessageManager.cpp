#include "MessageManager.h"
#include "CameraManager.h"
#include "Telegram.h"
#include "TimeManager.h"
#include "EntityManager.h"

CMessageManager::CMessageManager() : m_pShowTime(new CTimer(0))
{
	m_pSystem = new CMessageWindow(-1, CMessageWindow::TRANSPARENCY);
	m_pSystem->GetText()->SetFontScale(5);
	m_pSystem->GetText()->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

	m_PriorityQ.clear();
	m_SystemPriorityQ.clear();
}

CMessageManager::~CMessageManager(){
	Delete<CMessageWindow*>(m_pSystem);
	Delete<CTimer*>(m_pShowTime);
}

void CMessageManager::Update(double _dTimeElapsed){
	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);
	
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_vPos.y += 100.0f;
	t_vPos.z += 410.0f;

	m_pSystem->SetPos(&t_vPos);

	if(m_pShowTime->IsValidTimer()){
		if(!m_pShowTime->IsElapseTimer()){
			m_pSystem->Update();
		}
	}

	DispatchDelayedSystem();
	DispatchDelayedMessages();
}

void CMessageManager::DispatchSystem(const char* _pstrMessage, double _dDelay, DWORD _dwTime){
	if(_dDelay <= SmallestDelay){
		m_pShowTime->InitTimer(_dwTime);
		m_pSystem->GetText()->SetString(_pstrMessage);
	}
	else{
		Telegram telegram(_pstrMessage, _dDelay, _dwTime);
	
		double CurrentTime = TimeMgr->GetEngineTimer()->GetCurrentTime();

		telegram.m_dDispatchTime = CurrentTime + _dDelay;

		// 그리고 큐에 집어 넣는다.
		m_SystemPriorityQ.insert(telegram);
	}
}

void CMessageManager::DispatchDelayedSystem(){
	// 우선 현재 시간을 가져온다.
	double CurrentTime = TimeMgr->GetEngineTimer()->GetCurrentTime();

	// 전송될 필요가 있는 전보가 있는지를 알아보기 위해, 큐를 들여다본다.
	// 시간상 유통기한이 지난 전보들을 큐의 앞부분부터 제거해 나간다.
	while((m_SystemPriorityQ.begin()->m_dDispatchTime < CurrentTime) && (m_SystemPriorityQ.begin()->m_dDispatchTime > 0)){
		// 큐의 앞부분부터 전보를 읽어 나간다.
		Telegram telegram = *m_SystemPriorityQ.begin();

		m_pSystem->GetText()->SetString(telegram.m_strMessage);
		m_pShowTime->InitTimer(telegram.m_dwShowTime);

		// 그리고 큐로부터 제거한다.
		m_SystemPriorityQ.erase(m_SystemPriorityQ.begin());
	}
}

// 이 메소드는 하나의 엔티티가 다른 엔티티에게 메시지를 보낼 때 호출된다.
void CMessageManager::DispatchMessage(double _dDelay, int _nSender, int _nReceiver, int _nMsg, void* _pExtraInfo){
	// 메시지 발신자와 수신자를 가리키는 포인터를 얻어낸다.
	CBaseEntity* pSender = EntityMgr->GetEntityFromType(_nSender);
	CBaseEntity* _pReceiver = EntityMgr->GetEntityFromType(_nReceiver);

	// 전보를 생성한다.
	Telegram telegram(0, _nSender, _nReceiver, _nMsg, _pExtraInfo);

	// 지연될 필요가 없다면, 그 전보를 당장 발송한다.
	if(_dDelay <= SmallestDelay){
		// 전보를 수신자에게 보낸다.
		Discharge(_pReceiver, telegram);
	}
	else{ // 아니면 전보가 언제 발송되어야 하는지 그 시간을 계산한다.
		double CurrentTime = TimeMgr->GetEngineTimer()->GetCurrentTime();

		telegram.m_dDispatchTime = CurrentTime + _dDelay;

		// 그리고 큐에 집어 넣는다.
		m_PriorityQ.insert(telegram);
	}
}

void CMessageManager::Discharge(CBaseEntity* _pReceiver, const Telegram& telegram){
  if (!_pReceiver->HandleMessage(telegram)){
    //telegram could not be handled
	  OutputDebugString("Message not handled");
  }
}

void CMessageManager::DispatchDelayedMessages(){
	// 우선 현재 시간을 가져온다.
	double CurrentTime = TimeMgr->GetEngineTimer()->GetCurrentTime();

	// 전송될 필요가 있는 전보가 있는지를 알아보기 위해, 큐를 들여다본다.
	// 시간상 유통기한이 지난 전보들을 큐의 앞부분부터 제거해 나간다.
	while((m_PriorityQ.begin()->m_dDispatchTime < CurrentTime) && (m_PriorityQ.begin()->m_dDispatchTime > 0)){
		// 큐의 앞부분부터 전보를 읽어 나간다.
		Telegram telegram = *m_PriorityQ.begin();

		// 수신자를 찾아낸다.
		CBaseEntity* _pReceiver = EntityMgr->GetEntityFromType(telegram.m_nReceiver);

		// 수신자에게 전보를 보낸다.
		Discharge(_pReceiver, telegram);

		// 그리고 큐로부터 제거한다.
		m_PriorityQ.erase(m_PriorityQ.begin());
	}
}