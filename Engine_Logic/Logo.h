////////////////////////////////////////////////////////////////////////////////
// �������� �ΰ�
////////////////////////////////////////////////////////////////////////////////
#ifndef _Logo_H_
#define _Logo_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

class CLogo : public COrganEntity{
public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CLogo>* m_pStateMachine;

public:
	CLogo(int _nEntityType);
	~CLogo();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CLogo>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}
};

#endif