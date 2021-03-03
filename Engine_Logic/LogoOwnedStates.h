////////////////////////////////////////////////////
// Logo가 가질 상태들
////////////////////////////////////////////////////
#ifndef _LogoOwnedStates_H_
#define _LogoOwnedStates_H_

#include "../Engine_System/State.h"
#include "../Engine_System/Timer.h"

class CLogo;

///////////////////////////////////////////////////////////
// Start State
///////////////////////////////////////////////////////////
class CLogoStart : public CState<CLogo>{
private:
	CTimer* m_pTimer;

private:  
	CLogoStart(){}

	//copy ctor and assignment should be private
	CLogoStart(const CLogoStart&);
	CLogoStart& operator=(const CLogoStart&);
 
public:
  //this is a singleton
	static CLogoStart* Instance(){
		static CLogoStart instance;

		return &instance;
	}

	virtual void Enter(CLogo* pLogo);

	virtual void Execute(CLogo* pLogo);

	virtual void Exit(CLogo* pLogo);

	virtual bool OnMessage(CLogo* agent, const Telegram& _rMsg);
};

#define LogoStart CLogoStart::Instance()

#endif