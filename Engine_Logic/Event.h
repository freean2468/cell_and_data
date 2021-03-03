////////////////////////////////////////////////////
// ID를 가진 Entity를 상속 받은 Event 부분 클래스
////////////////////////////////////////////////////
#ifndef _Event_H_
#define _Event_H_

#include "../Engine_System/StateMachine.h"
#include "../Engine_System/SystemDefines.h"
#include "../Engine_Misc/DirectUtils.h"

class CEvent{
private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CEvent>* m_pStateMachine;
	
public:
	CEvent(){
		// 상태기계를 설정한다.
		m_pStateMachine = new CStateMachine<CEvent>(this);

		// 처음 상태를 초기화
		m_pStateMachine->SetCurrentState(NULL);

		m_pStateMachine->SetGlobalState(NULL);
	}

	~CEvent(){
		Delete< CStateMachine<CEvent>* >(m_pStateMachine);
	}

	// 이것은 반드시 설치되어야 한다.
	void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CEvent>* GetFSM()const{return m_pStateMachine;}
};

#endif