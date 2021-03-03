////////////////////////////////////////////////////////////////////////////////
// BreakHeart 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _BreakHeart_H_
#define _BreakHeart_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

class CBreakHeart : public COrganEntity{
private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CBreakHeart>* m_pStateMachine;

	bool m_bActive;

public:
	CBreakHeart(int _nID);
	~CBreakHeart();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CBreakHeart>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	bool GetActive(){return m_bActive;}
	void OnActive(){m_bActive = true;}
	void OffActive(){m_bActive = false;}
};

#endif