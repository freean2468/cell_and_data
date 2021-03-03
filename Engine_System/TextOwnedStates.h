////////////////////////////////////////////////////
// Text가 가질 상태들
////////////////////////////////////////////////////
#ifndef _TextOwnedStates_H_
#define _TextOwnedStates_H_

#include "State.h"
#include "Text.h"

///////////////////////////////////////////////////////////
// Normal State
///////////////////////////////////////////////////////////
class CTextNormal : public CState<CText>{
private:  
	CTextNormal(){}

	//copy ctor and assignment should be private
	CTextNormal(const CTextNormal&);
	CTextNormal& operator=(const CTextNormal&);
 
public:
  //this is a singleton
	static CTextNormal* Instance(){
		static CTextNormal instance;

		return &instance;
	}

	virtual void Enter(CText* pText);

	virtual void Execute(CText* pText);

	virtual void Exit(CText* pText);

	virtual bool OnMessage(CText* agent, const Telegram& _rMsg);
};

#define TextNormal CTextNormal::Instance()

///////////////////////////////////////////////////////////
// Typing State
///////////////////////////////////////////////////////////
class CTextTyping : public CState<CText>{
private:  
	CTextTyping(){}

	//copy ctor and assignment should be private
	CTextTyping(const CTextTyping&);
	CTextTyping& operator=(const CTextTyping&);
 
public:
  //this is a singleton
	static CTextTyping* Instance(){
		static CTextTyping instance;

		return &instance;
	}

	virtual void Enter(CText* pText);

	virtual void Execute(CText* pText);

	virtual void Exit(CText* pText);

	virtual bool OnMessage(CText* agent, const Telegram& _rMsg);
};

#define TextTyping CTextTyping::Instance()

#endif