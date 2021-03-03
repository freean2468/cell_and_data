////////////////////////////////////////////////////////////////////////////////
// 유동적인 Ending 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Ending_H_
#define _Ending_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

class CEnding : public COrganEntity{
public:
	typedef enum EndingAttType {ENDING, DARK} ENDINGATTTYPE;

private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CEnding>* m_pStateMachine;

public:
	CEnding(int _nID);
	~CEnding();

	// 이것은 반드시 설치되어야 한다.
	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	virtual void RenderOrgan();

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CEnding>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}
};

#endif