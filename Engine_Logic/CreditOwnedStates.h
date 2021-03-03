////////////////////////////////////////////////////
// Credit가 가질 상태들
////////////////////////////////////////////////////
#ifndef _CreditOwnedStates_H_
#define _CreditOwnedStates_H_

#include "../Engine_System/State.h"
#include "../Engine_System/Timer.h"
#include "../Engine_Misc/Utils.h"
#include "Credit.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CCreditUsual : public CState<CCredit>{
private:
	CTimer* m_pDelay;
	int		m_nStep;

private:  
	CCreditUsual():m_pDelay(new CTimer(0)), m_nStep(0){}
	~CCreditUsual(){Delete<CTimer*>(m_pDelay);}

	//copy ctor and assignment should be private
	CCreditUsual(const CCreditUsual&);
	CCreditUsual& operator=(const CCreditUsual&);
 
public:
  //this is a singleton
	static CCreditUsual* Instance(){
		static CCreditUsual instance;

		return &instance;
	}

	virtual void Enter(CCredit* _pCredit);

	virtual void Execute(CCredit* _pCredit);

	virtual void Exit(CCredit* _pCredit);

	virtual bool OnMessage(CCredit* agent, const Telegram& _rMsg);
};

#define CreditUsual CCreditUsual::Instance()

///////////////////////////////////////////////////////////
// Revert State
///////////////////////////////////////////////////////////
class CCreditRevert : public CState<CCredit>{
private:
	CTimer* m_pDelay;
	int			m_nStep;

private:  
	CCreditRevert():m_pDelay(new CTimer(0)), m_nStep(0){}
	~CCreditRevert(){Delete<CTimer*>(m_pDelay);}

	//copy ctor and assignment should be private
	CCreditRevert(const CCreditRevert&);
	CCreditRevert& operator=(const CCreditRevert&);
 
public:
  //this is a singleton
	static CCreditRevert* Instance(){
		static CCreditRevert instance;

		return &instance;
	}

	virtual void Enter(CCredit* _pCredit);

	virtual void Execute(CCredit* _pCredit);

	virtual void Exit(CCredit* _pCredit);

	virtual bool OnMessage(CCredit* agent, const Telegram& _rMsg);
};

#define CreditRevert CCreditRevert::Instance()

#endif