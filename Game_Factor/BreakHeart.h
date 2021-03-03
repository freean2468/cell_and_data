////////////////////////////////////////////////////////////////////////////////
// BreakHeart Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _BreakHeart_H_
#define _BreakHeart_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

class CBreakHeart : public COrganEntity{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CBreakHeart>* m_pStateMachine;

	bool m_bActive;

public:
	CBreakHeart(int _nID);
	~CBreakHeart();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CBreakHeart>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	bool GetActive(){return m_bActive;}
	void OnActive(){m_bActive = true;}
	void OffActive(){m_bActive = false;}
};

#endif