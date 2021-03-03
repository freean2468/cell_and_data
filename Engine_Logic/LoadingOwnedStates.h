////////////////////////////////////////////////////
// Loading가 가질 상태들
////////////////////////////////////////////////////
#ifndef _LoadingOwnedStates_H_
#define _LoadingOwnedStates_H_

#include "../Engine_System/State.h"

class CLoading;

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CLoadingUsual : public CState<CLoading>{
private:  
	CLoadingUsual(){}

	//copy ctor and assignment should be private
	CLoadingUsual(const CLoadingUsual&);
	CLoadingUsual& operator=(const CLoadingUsual&);
 
public:
  //this is a singleton
	static CLoadingUsual* Instance(){
		static CLoadingUsual instance;

		return &instance;
	}

	virtual void Enter(CLoading* pLoading);

	virtual void Execute(CLoading* pLoading);

	virtual void Exit(CLoading* pLoading);

	virtual bool OnMessage(CLoading* agent, const Telegram& _rMsg);
};

#define LoadingUsual CLoadingUsual::Instance()

#endif