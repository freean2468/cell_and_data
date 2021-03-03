#ifndef _EventMainStates_H_
#define _EventMainStates_H_

#include "../Engine_System/State.h"
#include "Event.h"
#include "../Game_Factor/Virus.h"
#include "../Engine_System/Timer.h"
#include "../Game_Factor/WorldManager.h"

class CEventMain;
class CEventMainTimeAttack;
class CEventMainSurvival;
class CEventMainStory1st;
class CEventMainStory2nd;
class CEventMainStory3rd;
class CEventMainStory4th;
class CEventMainStory5th;
class CEventMainStory6th;
class CEventMainEnding;

///////////////////////////////////////////////////////////
// CEventMain
///////////////////////////////////////////////////////////
class CEventMain : public CState<CEvent>{
private:  
	CEventMain(){}
	~CEventMain(){}

  //copy ctor and assignment should be private
  CEventMain(const CEventMain&);
  CEventMain& operator=(const CEventMain&);
 
public:
  //this is a singleton
	static CEventMain* Instance(){
		static CEventMain instance;

		return &instance;
	}

	virtual void Enter(CEvent* _pEvent);

	virtual void Execute(CEvent* _pEvent);

	virtual void Exit(CEvent* _pEvent);

	virtual bool OnMessage(CEvent* agent, const Telegram& _rMsg){return false;}
};

#define EventMain CEventMain::Instance()

///////////////////////////////////////////////////////////
// CEventMainTimeAttack
///////////////////////////////////////////////////////////
class CEventMainTimeAttack : public CState<CEvent>{
private:  
	CEventMainTimeAttack(){}
	~CEventMainTimeAttack(){}

  //copy ctor and assignment should be private
  CEventMainTimeAttack(const CEventMainTimeAttack&);
  CEventMainTimeAttack& operator=(const CEventMainTimeAttack&);
 
public:
  //this is a singleton
	static CEventMainTimeAttack* Instance(){
		static CEventMainTimeAttack instance;

		return &instance;
	}

	virtual void Enter(CEvent* _pEvent);

	virtual void Execute(CEvent* _pEvent);

	virtual void Exit(CEvent* _pEvent);

	virtual bool OnMessage(CEvent* agent, const Telegram& _rMsg){return false;}
};

#define EventMainTimeAttack CEventMainTimeAttack::Instance()

///////////////////////////////////////////////////////////
// CEventMainSurvival
///////////////////////////////////////////////////////////
class CEventMainSurvival : public CState<CEvent>{
private:  
	CEventMainSurvival(){}
	~CEventMainSurvival(){}

  //copy ctor and assignment should be private
  CEventMainSurvival(const CEventMainSurvival&);
  CEventMainSurvival& operator=(const CEventMainSurvival&);
 
public:
  //this is a singleton
	static CEventMainSurvival* Instance(){
		static CEventMainSurvival instance;

		return &instance;
	}

	virtual void Enter(CEvent* _pEvent);

	virtual void Execute(CEvent* _pEvent);

	virtual void Exit(CEvent* _pEvent);

	virtual bool OnMessage(CEvent* agent, const Telegram& _rMsg){return false;}
};

#define EventMainSurvival CEventMainSurvival::Instance()

///////////////////////////////////////////////////////////
// CEventMainStory1st
///////////////////////////////////////////////////////////
class CEventMainStory1st : public CState<CEvent>{
private:  
	CEventMainStory1st(){}
	~CEventMainStory1st(){}

  //copy ctor and assignment should be private
  CEventMainStory1st(const CEventMainStory1st&);
  CEventMainStory1st& operator=(const CEventMainStory1st&);
 
public:
  //this is a singleton
	static CEventMainStory1st* Instance(){
		static CEventMainStory1st instance;

		return &instance;
	}

	virtual void Enter(CEvent* _pEvent);

	virtual void Execute(CEvent* _pEvent);

	virtual void Exit(CEvent* _pEvent);

	virtual bool OnMessage(CEvent* agent, const Telegram& _rMsg){return false;}
};

#define EventMainStory1st CEventMainStory1st::Instance()

///////////////////////////////////////////////////////////
// CEventMainStory2nd
///////////////////////////////////////////////////////////
class CEventMainStory2nd : public CState<CEvent>{
private:
	bool m_b2ndLoad;
	bool m_b3rdLoad;

private:  
	CEventMainStory2nd():m_b2ndLoad(false), m_b3rdLoad(false){}
	~CEventMainStory2nd(){}

  //copy ctor and assignment should be private
  CEventMainStory2nd(const CEventMainStory2nd&);
  CEventMainStory2nd& operator=(const CEventMainStory2nd&);
 
public:
  //this is a singleton
	static CEventMainStory2nd* Instance(){
		static CEventMainStory2nd instance;

		return &instance;
	}

	virtual void Enter(CEvent* _pEvent);

	virtual void Execute(CEvent* _pEvent);

	virtual void Exit(CEvent* _pEvent);

	virtual bool OnMessage(CEvent* agent, const Telegram& _rMsg){return false;}
};

#define EventMainStory2nd CEventMainStory2nd::Instance()

///////////////////////////////////////////////////////////
// CEventMainStory3rd
///////////////////////////////////////////////////////////
class CEventMainStory3rd : public CState<CEvent>{
private:
	bool m_b2ndLoad;
	bool m_b3rdLoad;

private:  
	CEventMainStory3rd():m_b2ndLoad(false), m_b3rdLoad(false){}
	~CEventMainStory3rd(){}

  //copy ctor and assignment should be private
  CEventMainStory3rd(const CEventMainStory3rd&);
  CEventMainStory3rd& operator=(const CEventMainStory3rd&);
 
public:
  //this is a singleton
	static CEventMainStory3rd* Instance(){
		static CEventMainStory3rd instance;

		return &instance;
	}

	virtual void Enter(CEvent* _pEvent);

	virtual void Execute(CEvent* _pEvent);

	virtual void Exit(CEvent* _pEvent);

	virtual bool OnMessage(CEvent* agent, const Telegram& _rMsg){return false;}
};

#define EventMainStory3rd CEventMainStory3rd::Instance()

///////////////////////////////////////////////////////////
// CEventMainStory4th
///////////////////////////////////////////////////////////
class CEventMainStory4th : public CState<CEvent>{
private:
	bool m_b2ndLoad;
	bool m_b3rdLoad;
	bool m_bHearBreak;

private:  
	CEventMainStory4th():m_b2ndLoad(false), m_b3rdLoad(false), m_bHearBreak(false){}
	~CEventMainStory4th(){}

  //copy ctor and assignment should be private
  CEventMainStory4th(const CEventMainStory4th&);
  CEventMainStory4th& operator=(const CEventMainStory4th&);
 
public:
  //this is a singleton
	static CEventMainStory4th* Instance(){
		static CEventMainStory4th instance;

		return &instance;
	}

	virtual void Enter(CEvent* _pEvent);

	virtual void Execute(CEvent* _pEvent);

	virtual void Exit(CEvent* _pEvent);

	virtual bool OnMessage(CEvent* agent, const Telegram& _rMsg){return false;}
};

#define EventMainStory4th CEventMainStory4th::Instance()

///////////////////////////////////////////////////////////
// CEventMainStory5th
///////////////////////////////////////////////////////////
class CEventMainStory5th : public CState<CEvent>{
private:
	bool m_bBusActive;

private:  
	CEventMainStory5th():m_bBusActive(false){}
	~CEventMainStory5th(){}

  //copy ctor and assignment should be private
  CEventMainStory5th(const CEventMainStory5th&);
  CEventMainStory5th& operator=(const CEventMainStory5th&);
 
public:
  //this is a singleton
	static CEventMainStory5th* Instance(){
		static CEventMainStory5th instance;

		return &instance;
	}

	virtual void Enter(CEvent* _pEvent);

	virtual void Execute(CEvent* _pEvent);

	virtual void Exit(CEvent* _pEvent);

	virtual bool OnMessage(CEvent* agent, const Telegram& _rMsg){return false;}
};

#define EventMainStory5th CEventMainStory5th::Instance()

///////////////////////////////////////////////////////////
// CEventMainStory6th
///////////////////////////////////////////////////////////
class CEventMainStory6th : public CState<CEvent>{
private:
	bool m_bFadeActive;

private:  
	CEventMainStory6th(){}
	~CEventMainStory6th(){}

  //copy ctor and assignment should be private
  CEventMainStory6th(const CEventMainStory6th&);
  CEventMainStory6th& operator=(const CEventMainStory6th&);
 
public:
  //this is a singleton
	static CEventMainStory6th* Instance(){
		static CEventMainStory6th instance;

		return &instance;
	}

	virtual void Enter(CEvent* _pEvent);

	virtual void Execute(CEvent* _pEvent);

	virtual void Exit(CEvent* _pEvent);

	virtual bool OnMessage(CEvent* agent, const Telegram& _rMsg){return false;}
};

#define EventMainStory6th CEventMainStory6th::Instance()

///////////////////////////////////////////////////////////
// CEventMainEnding
///////////////////////////////////////////////////////////
class CEventMainEnding : public CState<CEvent>{
private:
	CVirus* m_pVirus;
	CTimer* m_pTimer;

private:  
	CEventMainEnding() : m_pVirus(NULL), m_pTimer(new CTimer()){
		WorldMgr->SetParam("Event.txt");
		m_pVirus = new CVirus(CGrowth::FIRST, 
							Vector2D(0, 0), 
							Vector2D(0, 0),
							1,
							200,
							1,
							1);
	}

	~CEventMainEnding(){Delete<CVirus*>(m_pVirus); Delete<CTimer*>(m_pTimer);}

  //copy ctor and assignment should be private
  CEventMainEnding(const CEventMainEnding&);
  CEventMainEnding& operator=(const CEventMainEnding&);
 
public:
  //this is a singleton
	static CEventMainEnding* Instance(){
		static CEventMainEnding instance;

		return &instance;
	}

	virtual void Enter(CEvent* _pEvent);

	virtual void Execute(CEvent* _pEvent);

	virtual void Exit(CEvent* _pEvent);

	virtual bool OnMessage(CEvent* agent, const Telegram& _rMsg){return false;}
};

#define EventMainEnding CEventMainEnding::Instance()

#endif