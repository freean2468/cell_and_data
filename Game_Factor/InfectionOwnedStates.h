////////////////////////////////////////////////////
// Infection가 가질 상태들
////////////////////////////////////////////////////
#ifndef _InfectionOwnedStates_H_
#define _InfectionOwnedStates_H_

#include "../Engine_System/State.h"
#include "Infection.h"

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
class CInfectionUsual : public CState<CInfection>{
private:  
	CInfectionUsual(){}

	//copy ctor and assignment should be private
	CInfectionUsual(const CInfectionUsual&);
	CInfectionUsual& operator=(const CInfectionUsual&);
 
public:
  //this is a singleton
	static CInfectionUsual* Instance(){
		static CInfectionUsual instance;

		return &instance;
	}

	virtual void Enter(CInfection* pInfection);

	virtual void Execute(CInfection* pInfection);

	virtual void Exit(CInfection* pInfection);

	virtual bool OnMessage(CInfection* agent, const Telegram& _rMsg);
};

#define InfectionUsual CInfectionUsual::Instance()


///////////////////////////////////////////////////////////
// Init State
///////////////////////////////////////////////////////////
class CInfectionInit : public CState<CInfection>{
private:  
	CInfectionInit(){}

	//copy ctor and assignment should be private
	CInfectionInit(const CInfectionInit&);
	CInfectionInit& operator=(const CInfectionInit&);
 
public:
  //this is a singleton
	static CInfectionInit* Instance(){
		static CInfectionInit instance;

		return &instance;
	}

	virtual void Enter(CInfection* pInfection);

	virtual void Execute(CInfection* pInfection);

	virtual void Exit(CInfection* pInfection);

	virtual bool OnMessage(CInfection* agent, const Telegram& _rMsg);
};

#define InfectionInit CInfectionInit::Instance()

///////////////////////////////////////////////////////////
// Disappear State
///////////////////////////////////////////////////////////
class CInfectionDisappear : public CState<CInfection>{
private:  
	CInfectionDisappear(){}

	//copy ctor and assignment should be private
	CInfectionDisappear(const CInfectionDisappear&);
	CInfectionDisappear& operator=(const CInfectionDisappear&);
 
public:
  //this is a singleton
	static CInfectionDisappear* Instance(){
		static CInfectionDisappear instance;

		return &instance;
	}

	virtual void Enter(CInfection* pInfection);

	virtual void Execute(CInfection* pInfection);

	virtual void Exit(CInfection* pInfection);

	virtual bool OnMessage(CInfection* agent, const Telegram& _rMsg);
};

#define InfectionDisappear CInfectionDisappear::Instance()

#endif