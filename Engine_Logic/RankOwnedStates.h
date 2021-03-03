#ifndef _RankOwnedStates_H_
#define _RankOwnedStates_H_

#include "../Engine_System/State.h"
#include "Rank.h"
#include "../Game_Factor/UIManager.h"

///////////////////////////////////////////////////////////
// Main State
///////////////////////////////////////////////////////////
class CRankMain : public CState<CRank>{
private:  
	CRankMain(){}
	~CRankMain(){}

	//copy ctor and assignment should be private
	CRankMain(const CRankMain&);
	CRankMain& operator=(const CRankMain&);
 
public:
  //this is a singleton
	static CRankMain* Instance(){
		static CRankMain instance;

		return &instance;
	}

	virtual void Enter(CRank* _pRank);

	virtual void Execute(CRank* _pRank);

	virtual void Exit(CRank* _pRank);

	virtual bool OnMessage(CRank* agent, const Telegram& _rMsg);
};

#define RankMain CRankMain::Instance()

///////////////////////////////////////////////////////////
// Record State
///////////////////////////////////////////////////////////
class CRankRecord : public CState<CRank>{
private:  
	CRankRecord(){}
	~CRankRecord(){}

	//copy ctor and assignment should be private
	CRankRecord(const CRankRecord&);
	CRankRecord& operator=(const CRankRecord&);
 
public:
  //this is a singleton
	static CRankRecord* Instance(){
		static CRankRecord instance;

		return &instance;
	}

	virtual void Enter(CRank* _pRank);

	virtual void Execute(CRank* _pRank);

	virtual void Exit(CRank* _pRank);

	virtual bool OnMessage(CRank* agent, const Telegram& _rMsg);
};

#define RankRecord CRankRecord::Instance()

#endif