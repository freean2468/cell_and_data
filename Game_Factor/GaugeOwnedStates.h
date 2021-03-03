////////////////////////////////////////////////////
// Gauge가 가질 상태들
////////////////////////////////////////////////////
#ifndef _GaugeOwnedStates_H_
#define _GaugeOwnedStates_H_

#include "../Engine_System/state.h"
#include "Gauge.h"

///////////////////////////////////////////////////////////
// Maintain State
///////////////////////////////////////////////////////////
class CGaugeMaintain : public CState<CGauge>{
private:  
	CGaugeMaintain(){}
	~CGaugeMaintain(){}

	//copy ctor and assignment should be private
	CGaugeMaintain(const CGaugeMaintain&);
	CGaugeMaintain& operator=(const CGaugeMaintain&);
 
public:
  //this is a singleton
	static CGaugeMaintain* Instance(){
		static CGaugeMaintain instance;

		return &instance;
	}

	virtual void Enter(CGauge* _pGauge);

	virtual void Execute(CGauge* _pGauge);

	virtual void Exit(CGauge* _pGauge);

	virtual bool OnMessage(CGauge* agent, const Telegram& _rMsg);
};

#define GaugeMaintain CGaugeMaintain::Instance()

#endif