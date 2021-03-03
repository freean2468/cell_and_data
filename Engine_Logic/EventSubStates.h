#ifndef _EventSubStates_
#define _EventSubStates_

#include "../Game_Factor/BreakHeart.h"
#include "../Engine_System/State.h"
#include "Event.h"
#include "../Engine_System/Timer.h"

///////////////////////////////////////////////////////////
// CEventSub
///////////////////////////////////////////////////////////
class CEventSub : public CState<CEvent>{
private:
	CTimer* m_pTimer;

private:  
	CEventSub():m_pTimer(new CTimer()){}
	~CEventSub(){Delete<CTimer*>(m_pTimer);}

  //copy ctor and assignment should be private
  CEventSub(const CEventSub&);
  CEventSub& operator=(const CEventSub&);
 
public:
  //this is a singleton
	static CEventSub* Instance(){
		static CEventSub instance;

		return &instance;
	}

	virtual void Enter(CEvent* _pEvent);

	virtual void Execute(CEvent* _pEvent);

	virtual void Exit(CEvent* _pEvent);

	virtual bool OnMessage(CEvent* agent, const Telegram& _rMsg){return false;}
};

#define EventSub CEventSub::Instance()

///////////////////////////////////////////////////////////
// CEventSubBreakHeart
///////////////////////////////////////////////////////////
class CEventSubBreakHeart : public CState<CEvent>{
private:
	CTimer* m_pTimer;
	CBreakHeart* m_pBreakHeart;

private:  
	CEventSubBreakHeart():m_pTimer(new CTimer()){}
	~CEventSubBreakHeart(){Delete<CTimer*>(m_pTimer);Delete<CBreakHeart*>(m_pBreakHeart);}

  //copy ctor and assignment should be private
  CEventSubBreakHeart(const CEventSubBreakHeart&);
  CEventSubBreakHeart& operator=(const CEventSubBreakHeart&);
 
public:
  //this is a singleton
	static CEventSubBreakHeart* Instance(){
		static CEventSubBreakHeart instance;

		return &instance;
	}

	virtual void Enter(CEvent* _pEvent);

	virtual void Execute(CEvent* _pEvent);

	virtual void Exit(CEvent* _pEvent);

	virtual bool OnMessage(CEvent* agent, const Telegram& _rMsg){return false;}
};

#define EventSubBreakHeart CEventSubBreakHeart::Instance()

#endif