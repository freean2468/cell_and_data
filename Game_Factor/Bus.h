#ifndef _BUS_H_
#define _BUS_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

class CBus : public COrganEntity{
public:
	typedef enum BusAttType {HOLE, FIRST, SECOND, THIRD} BUSATTTYPE;

private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CBus>* m_pStateMachine;

	bool m_bActive;

public:
	CBus();
	~CBus();

	void Initialize();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.	
	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CBus>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CBus>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){return m_pStateMachine->HandleMessage(_rMsg);	}

	bool GetActive(){return m_bActive;}
	void OnActive(D3DXVECTOR3* _pvPos){m_bActive = true; *(GetBody()->GetPriPos()) = *(_pvPos);}
	void OffActive(){m_bActive = false;}
};

#endif