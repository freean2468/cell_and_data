////////////////////////////////////////////////////
// InputWindow가 가질 상태들
////////////////////////////////////////////////////
#ifndef _InputWindowOwnedStates_H_
#define _InputWindowOwnedStates_H_

#include "../Engine_System/State.h"
#include "InputWindow.h"

///////////////////////////////////////////////////////////
// OK State
///////////////////////////////////////////////////////////
class CInputWindowOK : public CState<CInputWindow>{
private:  
	CInputWindowOK(){}

	//copy ctor and assignment should be private
	CInputWindowOK(const CInputWindowOK&);
	CInputWindowOK& operator=(const CInputWindowOK&);
 
public:
  //this is a singleton
	static CInputWindowOK* Instance(){
		static CInputWindowOK instance;

		return &instance;
	}

	virtual void Enter(CInputWindow* _pInputWindow);

	virtual void Execute(CInputWindow* _pInputWindow);

	virtual void Exit(CInputWindow* _pInputWindow);

	virtual bool OnMessage(CInputWindow* agent, const Telegram& _rMsg);
};

#define InputWindowOK CInputWindowOK::Instance()

#endif