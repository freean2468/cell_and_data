////////////////////////////////////////////////////
// Wave가 가질 상태들
////////////////////////////////////////////////////
#ifndef _WaveOwnedStates_H_
#define _WaveOwnedStates_H_

#include "../Engine_System/State.h"
#include "Wave.h"

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
class CWaveUsual : public CState<CWave>{
private:  
	CWaveUsual(){}

	//copy ctor and assignment should be private
	CWaveUsual(const CWaveUsual&);
	CWaveUsual& operator=(const CWaveUsual&);
 
public:
  //this is a singleton
	static CWaveUsual* Instance(){
		static CWaveUsual instance;

		return &instance;
	}

	virtual void Enter(CWave* pWave);

	virtual void Execute(CWave* pWave);

	virtual void Exit(CWave* pWave);

	virtual bool OnMessage(CWave* agent, const Telegram& _rMsg);
};

#define WaveUsual CWaveUsual::Instance()

#endif