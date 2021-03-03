////////////////////////////////////////////////////
// 메시지 발송을 관리하는 클래스
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
	// std::set는 자동 정렬과 중복 회피라는 이점 때문에,
	// 지연된 메시지를 담고 있기 위한 용기로 사용된다. 메시지들은
	// 자신들이 발송된 시간에 따라 정렬된다.
	std::set<Telegram> m_PriorityQ;

	std::set<Telegram> m_SystemPriorityQ;
	CMessageWindow* m_pSystem;
	CTimer* m_pDelay;
	CTimer* m_pShowTime;

private:
	// 이 메소드를 DispatchMessage나 DispatchDelayedMessages가 활용한다.
	// 이 메소드는, 수신용 엔티티인 _pReceiver라고 하는 메시지 처리 멤버 함수를
	// 새로 생성된 전보화 함께 호출한다.
	void Discharge(CBaseEntity* _pReceiver, const Telegram& _rMsg);

	CMessageManager();
	~CMessageManager();

public:
	// 이 클래스는 유일 객체이다.
	static CMessageManager* Instance(){
		 static CMessageManager instance;

		 return &instance;
	}

	void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	void DispatchSystem(const char* _pstrMessage, double _dDelay, DWORD _dwTime);
	void DispatchDelayedSystem();

	// 다른 에이전트에게 메시지를 보낸다.
	void DispatchMessage(double _dDelay, int _nSender, int _nReceiver, int _nMsg, void* _pExtraInfo);
	
	// 지연된 모든 메시지를 보낸다. 이 메소드는 게임의 주 루프를 통해서 매번 호출된다.
	void DispatchDelayedMessages();
};

#define MessageMgr CMessageManager::Instance()

#endif