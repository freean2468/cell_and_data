////////////////////////////////////////////////////
// SectionEnding가 가질 상태들
////////////////////////////////////////////////////
#ifndef _EndingOwnedStates_H_
#define _EndingOwnedStates_H_

#include "../Engine_System/State.h"
#include "../Engine_System/Timer.h"
#include "../Engine_Misc/Utils.h"

class CEnding;

///////////////////////////////////////////////////////////
// Main State
///////////////////////////////////////////////////////////
class CEndingMain : public CState<CEnding>{
private:
	CTimer* m_pTimer;

private:  
	CEndingMain():m_pTimer(new CTimer()){}
	~CEndingMain(){Delete<CTimer*>(m_pTimer);}

	//copy ctor and assignment should be private
	CEndingMain(const CEndingMain&);
	CEndingMain& operator=(const CEndingMain&);
 
public:
  //this is a singleton
	static CEndingMain* Instance(){
		static CEndingMain instance;

		return &instance;
	}

	virtual void Enter(CEnding* _pEnding);

	virtual void Execute(CEnding* _pEnding);

	virtual void Exit(CEnding* _pEnding);

	virtual bool OnMessage(CEnding* agent, const Telegram& _rMsg);
};

#define EndingMain CEndingMain::Instance()

///////////////////////////////////////////////////////////
// Nothing State
///////////////////////////////////////////////////////////
class CEndingNothing : public CState<CEnding>{
private:  
	CEndingNothing(){}
	~CEndingNothing(){}

	//copy ctor and assignment should be private
	CEndingNothing(const CEndingNothing&);
	CEndingNothing& operator=(const CEndingNothing&);
 
public:
  //this is a singleton
	static CEndingNothing* Instance(){
		static CEndingNothing instance;

		return &instance;
	}

	virtual void Enter(CEnding* _pEnding);

	virtual void Execute(CEnding* _pEnding);

	virtual void Exit(CEnding* _pEnding);

	virtual bool OnMessage(CEnding* agent, const Telegram& _rMsg);
};

#define EndingNothing CEndingNothing::Instance()

///////////////////////////////////////////////////////////
// Start State
///////////////////////////////////////////////////////////
class CEndingStart : public CState<CEnding>{
private:
	CTimer* m_pTimer;

private:  
	CEndingStart():m_pTimer(new CTimer()){}
	~CEndingStart(){Delete<CTimer*>(m_pTimer);}

	//copy ctor and assignment should be private
	CEndingStart(const CEndingStart&);
	CEndingStart& operator=(const CEndingStart&);
 
public:
  //this is a singleton
	static CEndingStart* Instance(){
		static CEndingStart instance;

		return &instance;
	}

	virtual void Enter(CEnding* _pEnding);

	virtual void Execute(CEnding* _pEnding);

	virtual void Exit(CEnding* _pEnding);

	virtual bool OnMessage(CEnding* agent, const Telegram& _rMsg);
};

#define EndingStart CEndingStart::Instance()

///////////////////////////////////////////////////////////
// End State
///////////////////////////////////////////////////////////
class CEndingEnd : public CState<CEnding>{
private:  
	CEndingEnd(){}
	~CEndingEnd(){}

	//copy ctor and assignment should be private
	CEndingEnd(const CEndingEnd&);
	CEndingEnd& operator=(const CEndingEnd&);
 
public:
  //this is a singleton
	static CEndingEnd* Instance(){
		static CEndingEnd instance;

		return &instance;
	}

	virtual void Enter(CEnding* _pEnding);

	virtual void Execute(CEnding* _pEnding);

	virtual void Exit(CEnding* _pEnding);

	virtual bool OnMessage(CEnding* agent, const Telegram& _rMsg);
};

#define EndingEnd CEndingEnd::Instance()

#endif