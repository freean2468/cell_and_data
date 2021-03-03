////////////////////////////////////////////////////
// BreakHeart가 가질 상태들
////////////////////////////////////////////////////
#ifndef _BreakHeartOwnedStates_H_
#define _BreakHeartOwnedStates_H_

#include "../Engine_System/State.h"
#include "BreakHeart.h"
#include "../Engine_System/Timer.h"

///////////////////////////////////////////////////////////
// 1st State
///////////////////////////////////////////////////////////
class CBreakHeart1st : public CState<CBreakHeart>{
private:
	CTimer* m_pDelay;
	int			m_nStep;
	bool		m_bScreaming;

private:  
	CBreakHeart1st():m_pDelay(new CTimer(0)), m_nStep(0), m_bScreaming(false){}
	~CBreakHeart1st(){Delete<CTimer*>(m_pDelay);}

	//copy ctor and assignment should be private
	CBreakHeart1st(const CBreakHeart1st&);
	CBreakHeart1st& operator=(const CBreakHeart1st&);
 
public:
  //this is a singleton
	static CBreakHeart1st* Instance(){
		static CBreakHeart1st instance;

		return &instance;
	}

	virtual void Enter(CBreakHeart* _pBreakHeart);

	virtual void Execute(CBreakHeart* _pBreakHeart);

	virtual void Exit(CBreakHeart* _pBreakHeart);

	virtual bool OnMessage(CBreakHeart* agent, const Telegram& _rMsg);
};

#define BreakHeart1st CBreakHeart1st::Instance()

#endif