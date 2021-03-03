////////////////////////////////////////////////////
// MessageWindow가 가질 상태들
////////////////////////////////////////////////////
#ifndef _MessageWindowOwnedStates_H_
#define _MessageWindowOwnedStates_H_

#include "../Engine_System/State.h"
#include "MessageWindow.h"

///////////////////////////////////////////////////////////
// Normal State
///////////////////////////////////////////////////////////
class CMessageWindowNormal : public CState<CMessageWindow>{
private:  
	CMessageWindowNormal(){}

	//copy ctor and assignment should be private
	CMessageWindowNormal(const CMessageWindowNormal&);
	CMessageWindowNormal& operator=(const CMessageWindowNormal&);
 
public:
  //this is a singleton
	static CMessageWindowNormal* Instance(){
		static CMessageWindowNormal instance;

		return &instance;
	}

	virtual void Enter(CMessageWindow* _pMessageWindow);

	virtual void Execute(CMessageWindow* _pMessageWindow);

	virtual void Exit(CMessageWindow* _pMessageWindow);

	virtual bool OnMessage(CMessageWindow* agent, const Telegram& _rMsg);
};

#define MessageWindowNormal CMessageWindowNormal::Instance()

#endif