////////////////////////////////////////////////////
// TextOfGame가 가질 상태들
////////////////////////////////////////////////////
#ifndef _TextOfGameOwnedStates_H_
#define _TextOfGameOwnedStates_H_

#include "../Engine_System/State.h"
#include "TextOfGame.h"

///////////////////////////////////////////////////////////
// Main State
///////////////////////////////////////////////////////////
class CTextOfGameMain : public CState<CTextOfGame>{
private:  
	CTextOfGameMain(){}

	//copy ctor and assignment should be private
	CTextOfGameMain(const CTextOfGameMain&);
	CTextOfGameMain& operator=(const CTextOfGameMain&);
 
public:
  //this is a singleton
	static CTextOfGameMain* Instance(){
		static CTextOfGameMain instance;

		return &instance;
	}

	virtual void Enter(CTextOfGame* _pTextOfGame);

	virtual void Execute(CTextOfGame* _pTextOfGame);

	virtual void Exit(CTextOfGame* _pTextOfGame);

	virtual bool OnMessage(CTextOfGame* agent, const Telegram& _rMsg);
};

#define TextOfGameMain CTextOfGameMain::Instance()

#endif