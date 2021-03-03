////////////////////////////////////////////////////
// SectionMainMenu가 가질 상태들
////////////////////////////////////////////////////
#ifndef _MainMenuOwnedStates_H_
#define _MainMenuOwnedStates_H_

#include "../Engine_System/State.h"

class CMainMenu;

///////////////////////////////////////////////////////////
// Main State
///////////////////////////////////////////////////////////
class CMainMenuMain : public CState<CMainMenu>{
private:  
	CMainMenuMain(){}
	~CMainMenuMain(){}

	//copy ctor and assignment should be private
	CMainMenuMain(const CMainMenuMain&);
	CMainMenuMain& operator=(const CMainMenuMain&);
 
public:
  //this is a singleton
	static CMainMenuMain* Instance(){
		static CMainMenuMain instance;

		return &instance;
	}

	virtual void Enter(CMainMenu* _pMainMenu);

	virtual void Execute(CMainMenu* _pMainMenu);

	virtual void Exit(CMainMenu* _pMainMenu);

	virtual bool OnMessage(CMainMenu* agent, const Telegram& _rMsg);
};

#define MainMenuMain CMainMenuMain::Instance()

///////////////////////////////////////////////////////////
// ToExtraFromMain State
///////////////////////////////////////////////////////////
class CMainMenuToExtraFromMain : public CState<CMainMenu>{
private:  
	CMainMenuToExtraFromMain(){}
	~CMainMenuToExtraFromMain(){}

	//copy ctor and assignment should be private
	CMainMenuToExtraFromMain(const CMainMenuToExtraFromMain&);
	CMainMenuToExtraFromMain& operator=(const CMainMenuToExtraFromMain&);
 
public:
  //this is a singleton
	static CMainMenuToExtraFromMain* Instance(){
		static CMainMenuToExtraFromMain instance;

		return &instance;
	}

	virtual void Enter(CMainMenu* _pMainMenu);

	virtual void Execute(CMainMenu* _pMainMenu);

	virtual void Exit(CMainMenu* _pMainMenu);

	virtual bool OnMessage(CMainMenu* agent, const Telegram& _rMsg);
};

#define MainMenuToExtraFromMain CMainMenuToExtraFromMain::Instance()

///////////////////////////////////////////////////////////
// ToStartFromMain State
///////////////////////////////////////////////////////////
class CMainMenuToStartFromMain : public CState<CMainMenu>{
private:  
	CMainMenuToStartFromMain(){}
	~CMainMenuToStartFromMain(){}

	//copy ctor and assignment should be private
	CMainMenuToStartFromMain(const CMainMenuToStartFromMain&);
	CMainMenuToStartFromMain& operator=(const CMainMenuToStartFromMain&);
 
public:
  //this is a singleton
	static CMainMenuToStartFromMain* Instance(){
		static CMainMenuToStartFromMain instance;

		return &instance;
	}

	virtual void Enter(CMainMenu* _pMainMenu);

	virtual void Execute(CMainMenu* _pMainMenu);

	virtual void Exit(CMainMenu* _pMainMenu);

	virtual bool OnMessage(CMainMenu* agent, const Telegram& _rMsg);
};

#define MainMenuToStartFromMain CMainMenuToStartFromMain::Instance()

///////////////////////////////////////////////////////////
// Start State
///////////////////////////////////////////////////////////
class CMainMenuStart : public CState<CMainMenu>{
private:  
	CMainMenuStart(){}
	~CMainMenuStart(){}

	//copy ctor and assignment should be private
	CMainMenuStart(const CMainMenuStart&);
	CMainMenuStart& operator=(const CMainMenuStart&);
 
public:
  //this is a singleton
	static CMainMenuStart* Instance(){
		static CMainMenuStart instance;

		return &instance;
	}

	virtual void Enter(CMainMenu* _pMainMenu);

	virtual void Execute(CMainMenu* _pMainMenu);

	virtual void Exit(CMainMenu* _pMainMenu);

	virtual bool OnMessage(CMainMenu* agent, const Telegram& _rMsg);
};

#define MainMenuStart CMainMenuStart::Instance()

///////////////////////////////////////////////////////////
// ToMainFromStart State
///////////////////////////////////////////////////////////
class CMainMenuToMainFromStart : public CState<CMainMenu>{
private:  
	CMainMenuToMainFromStart(){}
	~CMainMenuToMainFromStart(){}

	//copy ctor and assignment should be private
	CMainMenuToMainFromStart(const CMainMenuToMainFromStart&);
	CMainMenuToMainFromStart& operator=(const CMainMenuToMainFromStart&);
 
public:
  //this is a singleton
	static CMainMenuToMainFromStart* Instance(){
		static CMainMenuToMainFromStart instance;

		return &instance;
	}

	virtual void Enter(CMainMenu* _pMainMenu);

	virtual void Execute(CMainMenu* _pMainMenu);

	virtual void Exit(CMainMenu* _pMainMenu);

	virtual bool OnMessage(CMainMenu* agent, const Telegram& _rMsg);
};

#define MainMenuToMainFromStart CMainMenuToMainFromStart::Instance()

///////////////////////////////////////////////////////////
// Extra State
///////////////////////////////////////////////////////////
class CMainMenuExtra : public CState<CMainMenu>{
private:  
	CMainMenuExtra(){}
	~CMainMenuExtra(){}

	//copy ctor and assignment should be private
	CMainMenuExtra(const CMainMenuExtra&);
	CMainMenuExtra& operator=(const CMainMenuExtra&);
 
public:
  //this is a singleton
	static CMainMenuExtra* Instance(){
		static CMainMenuExtra instance;

		return &instance;
	}

	virtual void Enter(CMainMenu* _pMainMenu);

	virtual void Execute(CMainMenu* _pMainMenu);

	virtual void Exit(CMainMenu* _pMainMenu);

	virtual bool OnMessage(CMainMenu* agent, const Telegram& _rMsg);
};

#define MainMenuExtra CMainMenuExtra::Instance()

///////////////////////////////////////////////////////////
// ToMainFromExtra State
///////////////////////////////////////////////////////////
class CMainMenuToMainFromExtra : public CState<CMainMenu>{
private:  
	CMainMenuToMainFromExtra(){}
	~CMainMenuToMainFromExtra(){}

	//copy ctor and assignment should be private
	CMainMenuToMainFromExtra(const CMainMenuToMainFromExtra&);
	CMainMenuToMainFromExtra& operator=(const CMainMenuToMainFromExtra&);
 
public:
  //this is a singleton
	static CMainMenuToMainFromExtra* Instance(){
		static CMainMenuToMainFromExtra instance;

		return &instance;
	}

	virtual void Enter(CMainMenu* _pMainMenu);

	virtual void Execute(CMainMenu* _pMainMenu);

	virtual void Exit(CMainMenu* _pMainMenu);

	virtual bool OnMessage(CMainMenu* agent, const Telegram& _rMsg);
};

#define MainMenuToMainFromExtra CMainMenuToMainFromExtra::Instance()

///////////////////////////////////////////////////////////
// Revert State
///////////////////////////////////////////////////////////
class CMainMenuRevert : public CState<CMainMenu>{
private:  
	CMainMenuRevert(){}
	~CMainMenuRevert(){}

	//copy ctor and assignment should be private
	CMainMenuRevert(const CMainMenuRevert&);
	CMainMenuRevert& operator=(const CMainMenuRevert&);
 
public:
  //this is a singleton
	static CMainMenuRevert* Instance(){
		static CMainMenuRevert instance;

		return &instance;
	}

	virtual void Enter(CMainMenu* _pMainMenu);

	virtual void Execute(CMainMenu* _pMainMenu);

	virtual void Exit(CMainMenu* _pMainMenu);

	virtual bool OnMessage(CMainMenu* agent, const Telegram& _rMsg);
};

#define MainMenuRevert CMainMenuRevert::Instance()

///////////////////////////////////////////////////////////
// ToCredit State
///////////////////////////////////////////////////////////
class CMainMenuToCredit : public CState<CMainMenu>{
private:  
	CMainMenuToCredit(){}
	~CMainMenuToCredit(){}

	//copy ctor and assignment should be private
	CMainMenuToCredit(const CMainMenuToCredit&);
	CMainMenuToCredit& operator=(const CMainMenuToCredit&);
 
public:
  //this is a singleton
	static CMainMenuToCredit* Instance(){
		static CMainMenuToCredit instance;

		return &instance;
	}

	virtual void Enter(CMainMenu* _pMainMenu);

	virtual void Execute(CMainMenu* _pMainMenu);

	virtual void Exit(CMainMenu* _pMainMenu);

	virtual bool OnMessage(CMainMenu* agent, const Telegram& _rMsg);
};

#define MainMenuToCredit CMainMenuToCredit::Instance()


#endif