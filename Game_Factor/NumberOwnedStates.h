////////////////////////////////////////////////////
// Number가 가질 상태들
////////////////////////////////////////////////////
#ifndef _NumberOwnedStates_H_
#define _NumberOwnedStates_H_

#include "../Engine_System/State.h"
#include "Number.h"

///////////////////////////////////////////////////////////
// Normal State
///////////////////////////////////////////////////////////
class CNumberNormal : public CState<CNumber>{
private:  
	CNumberNormal(){}

	//copy ctor and assignment should be private
	CNumberNormal(const CNumberNormal&);
	CNumberNormal& operator=(const CNumberNormal&);
 
public:
  //this is a singleton
	static CNumberNormal* Instance(){
		static CNumberNormal instance;

		return &instance;
	}

	virtual void Enter(CNumber* _pNumber);

	virtual void Execute(CNumber* _pNumber);

	virtual void Exit(CNumber* _pNumber);

	virtual bool OnMessage(CNumber* agent, const Telegram& _rMsg);
};

#define NumberNormal CNumberNormal::Instance()


#endif