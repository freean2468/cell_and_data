////////////////////////////////////////////////////
// GameMenu가 가질 상태들
////////////////////////////////////////////////////
#ifndef _GameMenuOwnedStates_H_
#define _GameMenuOwnedStates_H_

#include "../Engine_System/State.h"
#include "GameMenu.h"

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
class CGameMenuActive : public CState<CGameMenu>{
private:  
	CGameMenuActive(){}
	~CGameMenuActive(){}

	//copy ctor and assignment should be private
	CGameMenuActive(const CGameMenuActive&);
	CGameMenuActive& operator=(const CGameMenuActive&);
 
public:
  //this is a singleton
	static CGameMenuActive* Instance(){
		static CGameMenuActive instance;

		return &instance;
	}

	virtual void Enter(CGameMenu* _pGameMenu);

	virtual void Execute(CGameMenu* _pGameMenu);

	virtual void Exit(CGameMenu* _pGameMenu);

	virtual bool OnMessage(CGameMenu* agent, const Telegram& _rMsg);
};

#define GameMenuActive CGameMenuActive::Instance()

///////////////////////////////////////////////////////////
// Maintain State
///////////////////////////////////////////////////////////
class CGameMenuMaintain : public CState<CGameMenu>{
private:  
	CGameMenuMaintain(){}
	~CGameMenuMaintain(){}

	//copy ctor and assignment should be private
	CGameMenuMaintain(const CGameMenuMaintain&);
	CGameMenuMaintain& operator=(const CGameMenuMaintain&);
 
public:
  //this is a singleton
	static CGameMenuMaintain* Instance(){
		static CGameMenuMaintain instance;

		return &instance;
	}

	virtual void Enter(CGameMenu* _pGameMenu);

	virtual void Execute(CGameMenu* _pGameMenu);

	virtual void Exit(CGameMenu* _pGameMenu);

	virtual bool OnMessage(CGameMenu* agent, const Telegram& _rMsg);
};

#define GameMenuMaintain CGameMenuMaintain::Instance()

///////////////////////////////////////////////////////////
// InActive State
///////////////////////////////////////////////////////////
class CGameMenuInActive : public CState<CGameMenu>{
private:  
	CGameMenuInActive(){}
	~CGameMenuInActive(){}

	//copy ctor and assignment should be private
	CGameMenuInActive(const CGameMenuInActive&);
	CGameMenuInActive& operator=(const CGameMenuInActive&);
 
public:
  //this is a singleton
	static CGameMenuInActive* Instance(){
		static CGameMenuInActive instance;

		return &instance;
	}

	virtual void Enter(CGameMenu* _pGameMenu);

	virtual void Execute(CGameMenu* _pGameMenu);

	virtual void Exit(CGameMenu* _pGameMenu);

	virtual bool OnMessage(CGameMenu* agent, const Telegram& _rMsg);
};

#define GameMenuInActive CGameMenuInActive::Instance()

#endif