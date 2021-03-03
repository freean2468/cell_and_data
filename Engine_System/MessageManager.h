////////////////////////////////////////////////////
// �޽��� �߼��� �����ϴ� Ŭ����
////////////////////////////////////////////////////
#ifndef _MessageManager_H_
#define _MessageManager_H_

#include "../Game_Factor/MessageWindow.h"
#include "../Engine_System/Timer.h"
#include <set>

#define SEND_MSG_IMMEDIATELY 0
#define NO_ADDITIONAL_INFO NULL

class CMessageManager{
private:
	// std::set�� �ڵ� ���İ� �ߺ� ȸ�Ƕ�� ���� ������,
	// ������ �޽����� ��� �ֱ� ���� ���� ���ȴ�. �޽�������
	// �ڽŵ��� �߼۵� �ð��� ���� ���ĵȴ�.
	std::set<Telegram> m_PriorityQ;

	std::set<Telegram> m_SystemPriorityQ;
	CMessageWindow* m_pSystem;
	CTimer* m_pDelay;
	CTimer* m_pShowTime;

private:
	// �� �޼ҵ带 DispatchMessage�� DispatchDelayedMessages�� Ȱ���Ѵ�.
	// �� �޼ҵ��, ���ſ� ��ƼƼ�� _pReceiver��� �ϴ� �޽��� ó�� ��� �Լ���
	// ���� ������ ����ȭ �Բ� ȣ���Ѵ�.
	void Discharge(CBaseEntity* _pReceiver, const Telegram& _rMsg);

	CMessageManager();
	~CMessageManager();

public:
	// �� Ŭ������ ���� ��ü�̴�.
	static CMessageManager* Instance(){
		 static CMessageManager instance;

		 return &instance;
	}

	void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	void DispatchSystem(const char* _pstrMessage, double _dDelay, DWORD _dwTime);
	void DispatchDelayedSystem();

	// �ٸ� ������Ʈ���� �޽����� ������.
	void DispatchMessage(double _dDelay, int _nSender, int _nReceiver, int _nMsg, void* _pExtraInfo);
	
	// ������ ��� �޽����� ������. �� �޼ҵ�� ������ �� ������ ���ؼ� �Ź� ȣ��ȴ�.
	void DispatchDelayedMessages();
};

#define MessageMgr CMessageManager::Instance()

#endif