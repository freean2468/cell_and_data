////////////////////////////////////////////////////////////////////////////////
// Credit 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Credit_H_
#define _Credit_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

class CCredit : public COrganEntity{
public:
	typedef enum CreditAttType {LOGO, DEVELOPER, SPECIAL, SCHOOL, TEACHER,
							FRIENDS, FAMILY, SOFTMAX} CreditATTTYPE;

public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CCredit>* m_pStateMachine;

public:
	CCredit(int _nID);
	~CCredit();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CCredit>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}
};

#endif