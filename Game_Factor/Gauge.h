////////////////////////////////////////////////////////////////////////////////
// �������� ���Ӹ޴� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Gauge_H_
#define _Gauge_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

class CGauge : public COrganEntity{
public:
	typedef enum GaugeAttType {GAUGE, STICK_FIRST, STICK_SECOND, OUTLINE} GROWTHGAUGEATTTYPE;

private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
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

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	virtual void Update();

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
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