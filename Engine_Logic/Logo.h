////////////////////////////////////////////////////////////////////////////////
// 유동적인 로고
////////////////////////////////////////////////////////////////////////////////
#ifndef _Logo_H_
#define _Logo_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

class CLogo : public COrganEntity{
public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CLogo>* m_pStateMachine;

public:
	CLogo(int _nEntityType);
	~CLogo();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CLogo>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}
};

#endif