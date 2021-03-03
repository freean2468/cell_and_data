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

		// �׸��� ť�� ���� �ִ´�.
		m_SystemPriorityQ.insert(telegram);
	}
}

void CMessageManager::DispatchDelayedSystem(){
	// �켱 ���� �ð��� �����´�.
	double CurrentTime = TimeMgr->GetEngineTimer()->GetCurrentTime();

	// ���۵� �ʿ䰡 �ִ� ������ �ִ����� �˾ƺ��� ����, ť�� �鿩�ٺ���.
	// �ð��� ��������� ���� �������� ť�� �պκк��� ������ ������.
	while((m_SystemPriorityQ.begin()->m_dDispatchTime < CurrentTime) && (m_SystemPriorityQ.begin()->m_dDispatchTime > 0)){
		// ť�� �պκк��� ������ �о� ������.
		Telegram telegram = *m_SystemPriorityQ.begin();

		m_pSystem->GetText()->SetString(telegram.m_strMessage);
		m_pShowTime->InitTimer(telegram.m_dwShowTime);

		// �׸��� ť�κ��� �����Ѵ�.
		m_SystemPriorityQ.erase(m_SystemPriorityQ.begin());
	}
}

// �� �޼ҵ�� �ϳ��� ��ƼƼ�� �ٸ� ��ƼƼ���� �޽����� ���� �� ȣ��ȴ�.
void CMessageManager::DispatchMessage(double _dDelay, int _nSender, int _nReceiver, int _nMsg, void* _pExtraInfo){
	// �޽��� �߽��ڿ� �����ڸ� ����Ű�� �����͸� ����.
	CBaseEntity* pSender = EntityMgr->GetEntityFromType(_nSender);
	CBaseEntity* _pReceiver = EntityMgr->GetEntityFromType(_nReceiver);

	// ������ �����Ѵ�.
	Telegram telegram(0, _nSender, _nReceiver, _nMsg, _pExtraInfo);

	// ������ �ʿ䰡 ���ٸ�, �� ������ ���� �߼��Ѵ�.
	if(_dDelay <= SmallestDelay){
		// ������ �����ڿ��� ������.
		Discharge(_pReceiver, telegram);
	}
	else{ // �ƴϸ� ������ ���� �߼۵Ǿ�� �ϴ��� �� �ð��� ����Ѵ�.
		double CurrentTime = TimeMgr->GetEngineTimer()->GetCurrentTime();

		telegram.m_dDispatchTime = CurrentTime + _dDelay;

		// �׸��� ť�� ���� �ִ´�.
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
	// �켱 ���� �ð��� �����´�.
	double CurrentTime = TimeMgr->GetEngineTimer()->GetCurrentTime();

	// ���۵� �ʿ䰡 �ִ� ������ �ִ����� �˾ƺ��� ����, ť�� �鿩�ٺ���.
	// �ð��� ��������� ���� �������� ť�� �պκк��� ������ ������.
	while((m_PriorityQ.begin()->m_dDispatchTime < CurrentTime) && (m_PriorityQ.begin()->m_dDispatchTime > 0)){
		// ť�� �պκк��� ������ �о� ������.
		Telegram telegram = *m_PriorityQ.begin();

		// �����ڸ� ã�Ƴ���.
		CBaseEntity* _pReceiver = EntityMgr->GetEntityFromType(telegram.m_nReceiver);

		// �����ڿ��� ������ ������.
		Discharge(_pReceiver, telegram);

		// �׸��� ť�κ��� �����Ѵ�.
		m_PriorityQ.erase(m_PriorityQ.begin());
	}
}