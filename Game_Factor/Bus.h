#ifndef _BUS_H_
#define _BUS_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

class CBus : public COrganEntity{
public:
	typedef enum BusAttType {HOLE, FIRST, SECOND, THIRD} BUSATTTYPE;

private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CBus>* m_pStateMachine;

	bool m_bActive;

public:
	CBus();
	~CBus();

	void Initialize();

	// 이것은 반드시 설치되어야 한다.	
	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CBus>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CBus>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){return m_pStateMachine->HandleMessage(_rMsg);	}

	bool GetActive(){return m_bActive;}
	void OnActive(D3DXVECTOR3* _pvPos){m_bActive = true; *(GetBody()->GetPriPos()) = *(_pvPos);}
	void OffActive(){m_bActive = false;}
};

#endif