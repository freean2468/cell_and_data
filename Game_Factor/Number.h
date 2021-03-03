////////////////////////////////////////////////////////////////////////////////
// Number 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Number_H_
#define _Number_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

class CNumber : public COrganEntity{
private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CNumber>* m_pStateMachine;

	int m_nValue; // 0~9 사이

public:
	CNumber(int _nValue = 0, int _nEntityType = -1);
	~CNumber();

	// 이것은 반드시 설치되어야 한다.
	virtual	void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);
	virtual void RenderOrgan();

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CNumber>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	void InitValue(int _nValue){m_nValue = _nValue;}
	int GetValue(){return m_nValue;}
};

#endif