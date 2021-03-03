////////////////////////////////////////////////////
// CheckWindow가 가질 상태들
////////////////////////////////////////////////////
#ifndef _CheckWindowOwnedStates_H_
#define _CheckWindowOwnedStates_H_

#include "../Engine_System/State.h"
#include "CheckWindow.h"

///////////////////////////////////////////////////////////
// YesNo State
///////////////////////////////////////////////////////////
class CCheckWindowYesNo : public CState<CCheckWindow>{
private:  
	CCheckWindowYesNo(){}

	//copy ctor and assignment should be private
	CCheckWindowYesNo(const CCheckWindowYesNo&);
	CCheckWindowYesNo& operator=(const CCheckWindowYesNo&);
 
public:
  //this is a singleton
	static CCheckWindowYesNo* Instance(){
		static CCheckWindowYesNo instance;

		return &instance;
	}

	virtual void Enter(CCheckWindow* _pCheckWindow);

	virtual void Execute(CCheckWindow* _pCheckWindow);

	virtual void Exit(CCheckWindow* _pCheckWindow);

	virtual bool OnMessage(CCheckWindow* agent, const Telegram& _rMsg);
};

#define CheckWindowYesNo CCheckWindowYesNo::Instance()

///////////////////////////////////////////////////////////
// OK State
///////////////////////////////////////////////////////////
class CCheckWindowOK : public CState<CCheckWindow>{
private:  
	CCheckWindowOK(){}

	//copy ctor and assignment should be private
	CCheckWindowOK(const CCheckWindowOK&);
	CCheckWindowOK& operator=(const CCheckWindowOK&);
 
public:
  //this is a singleton
	static CCheckWindowOK* Instance(){
		static CCheckWindowOK instance;

		return &instance;
	}

	virtual void Enter(CCheckWindow* _pCheckWindow);

	virtual void Execute(CCheckWindow* _pCheckWindow);

	virtual void Exit(CCheckWindow* _pCheckWindow);

	virtual bool OnMessage(CCheckWindow* agent, const Telegram& _rMsg);
};

#define CheckWindowOK CCheckWindowOK::Instance()

#endif