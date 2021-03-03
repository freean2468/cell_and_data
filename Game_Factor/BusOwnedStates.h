////////////////////////////////////////////////////
// Bus가 가질 상태들
////////////////////////////////////////////////////
#ifndef _BusOwnedStates_H_
#define _BusOwnedStates_H_

#include "../Engine_System/State.h"
#include "Bus.h"

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
class CBusActive : public CState<CBus>{
private:  
	CBusActive(){}

	//copy ctor and assignment should be private
	CBusActive(const CBusActive&);
	CBusActive& operator=(const CBusActive&);
 
public:
  //this is a singleton
	static CBusActive* Instance(){
		static CBusActive instance;

		return &instance;
	}

	virtual void Enter(CBus* _pBus);

	virtual void Execute(CBus* _pBus);

	virtual void Exit(CBus* _pBus);

	virtual bool OnMessage(CBus* agent, const Telegram& _rMsg);
};

#define BusActive CBusActive::Instance()

///////////////////////////////////////////////////////////
// Maintain State
///////////////////////////////////////////////////////////
class CBusMaintain : public CState<CBus>{
private:
	float m_fPercentage;
	Vector2D m_vDist;

private:  
	CBusMaintain(){}

	//copy ctor and assignment should be private
	CBusMaintain(const CBusMaintain&);
	CBusMaintain& operator=(const CBusMaintain&);
 
public:
  //this is a singleton
	static CBusMaintain* Instance(){
		static CBusMaintain instance;

		return &instance;
	}

	virtual void Enter(CBus* _pBus);

	virtual void Execute(CBus* _pBus);

	virtual void Exit(CBus* _pBus);

	virtual bool OnMessage(CBus* agent, const Telegram& _rMsg);
};

#define BusMaintain CBusMaintain::Instance()

#endif