////////////////////////////////////////////////////////////////////////////////
// Credit Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Credit_H_
#define _Credit_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

class CCredit : public COrganEntity{
public:
	typedef enum CreditAttType {LOGO, DEVELOPER, SPECIAL, SCHOOL, TEACHER,
							FRIENDS, FAMILY, SOFTMAX} CreditATTTYPE;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CCredit>* m_pStateMachine;

public:
	CCredit(int _nID);
	~CCredit();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CCredit>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}
};

#endif