////////////////////////////////////////////////////
// DialogWindow가 가질 상태들
////////////////////////////////////////////////////
#ifndef _DialogWindowOwnedStates_H_
#define _DialogWindowOwnedStates_H_

#include "../Engine_System/State.h"
#include "DialogWindow.h"

///////////////////////////////////////////////////////////
// Normal State
///////////////////////////////////////////////////////////
class CDialogWindowNormal : public CState<CDialogWindow>{
private:  
	CDialogWindowNormal(){}

	//copy ctor and assignment should be private
	CDialogWindowNormal(const CDialogWindowNormal&);
	CDialogWindowNormal& operator=(const CDialogWindowNormal&);
 
public:
  //this is a singleton
	static CDialogWindowNormal* Instance(){
		static CDialogWindowNormal instance;

		return &instance;
	}

	virtual void Enter(CDialogWindow* _pDialogWindow);

	virtual void Execute(CDialogWindow* _pDialogWindow);

	virtual void Exit(CDialogWindow* _pDialogWindow);

	virtual bool OnMessage(CDialogWindow* agent, const Telegram& _rMsg);
};

#define DialogWindowNormal CDialogWindowNormal::Instance()

#endif