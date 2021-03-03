////////////////////////////////////////////////////
// Vacine가 가질 상태들
////////////////////////////////////////////////////
#ifndef _VacineOwnedStates_H_
#define _VacineOwnedStates_H_

#include "../Engine_System/state.h"
#include "Vacine.h"

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
class CVacineStand : public CState<CVacine>{
private:  
	CVacineStand(){}

	//copy ctor and assignment should be private
	CVacineStand(const CVacineStand&);
	CVacineStand& operator=(const CVacineStand&);
 
public:
  //this is a singleton
	static CVacineStand* Instance(){
		static CVacineStand instance;

		return &instance;
	}

	virtual void Enter(CVacine* _pVacine);

	virtual void Execute(CVacine* _pVacine);

	virtual void Exit(CVacine* _pVacine);

	virtual bool OnMessage(CVacine* agent, const Telegram& _rMsg);
};

#define VacineStand CVacineStand::Instance()

///////////////////////////////////////////////////////////
// Destroy State
///////////////////////////////////////////////////////////
class CVacineDestroy : public CState<CVacine>{
private:  
	CVacineDestroy(){}

	//copy ctor and assignment should be private
	CVacineDestroy(const CVacineDestroy&);
	CVacineDestroy& operator=(const CVacineDestroy&);
 
public:
  //this is a singleton
	static CVacineDestroy* Instance(){
		static CVacineDestroy instance;

		return &instance;
	}

	virtual void Enter(CVacine* _pVacine);

	virtual void Execute(CVacine* _pVacine);

	virtual void Exit(CVacine* _pVacine);

	virtual bool OnMessage(CVacine* agent, const Telegram& _rMsg);
};

#define VacineDestroy CVacineDestroy::Instance()

#endif