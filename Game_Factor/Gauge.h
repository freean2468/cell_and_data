////////////////////////////////////////////////////////////////////////////////
// 유동적인 게임메뉴 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Gauge_H_
#define _Gauge_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

class CGauge : public COrganEntity{
public:
	typedef enum GaugeAttType {GAUGE, STICK_FIRST, STICK_SECOND, OUTLINE} GROWTHGAUGEATTTYPE;

private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CGauge>* m_pStateMachine;

	bool m_bActive;

	float m_fMaxGauge;
	float m_fPresentGauge;

	float m_fFirstGauge;
	float m_fSecondGauge;

public:
	CGauge();
	~CGauge();

	void Initialize();

	// 이것은 반드시 설치되어야 한다.
	virtual void Update();

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CGauge>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){	return m_pStateMachine->HandleMessage(_rMsg);	}

	void AddPresentGauge(float _fVal){m_fPresentGauge += _fVal;}

	bool GetActive(){return m_bActive;}

	void OnActive(){m_bActive = true;}
	void OffActive(){m_bActive = false;}

	float GetMaxGauge(){return m_fMaxGauge;}
	float GetPresentGauge(){return m_fPresentGauge;}

	float GetFirstGauge(){return m_fFirstGauge;}
	float GetSecondGauge(){return m_fSecondGauge;}
};

#endif