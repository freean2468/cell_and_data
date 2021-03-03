////////////////////////////////////////////////////
// ID를 가진 Entity를 상속 받은 Section 부분 클래스
////////////////////////////////////////////////////
#ifndef _Section_H_
#define _Section_H_

#include "SectionOwnedStates.h"
#include "../Engine_System/StateMachine.h"
#include "../Engine_System/SystemDefines.h"

class CSection{
private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CSection>* m_pStateMachine;

public:
	CSection();

	~CSection();

	// 이것은 반드시 설치되어야 한다.
	void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CSection>* GetFSM()const{return m_pStateMachine;}
};

#endif