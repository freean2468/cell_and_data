////////////////////////////////////////////////////
// ID�� ���� Entity�� ��� ���� Event �κ� Ŭ����
////////////////////////////////////////////////////
#ifndef _Event_H_
#define _Event_H_

#include "../Engine_System/StateMachine.h"
#include "../Engine_System/SystemDefines.h"
#include "../Engine_Misc/DirectUtils.h"

class CEvent{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CEvent>* m_pStateMachine;
	
public:
	CEvent(){
		// ���±�踦 �����Ѵ�.
		m_pStateMachine = new CStateMachine<CEvent>(this);

		// ó�� ���¸� �ʱ�ȭ
		m_pStateMachine->SetCurrentState(NULL);

		m_pStateMachine->SetGlobalState(NULL);
	}

	~CEvent(){
		Delete< CStateMachine<CEvent>* >(m_pStateMachine);
	}

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CEvent>* GetFSM()const{return m_pStateMachine;}
};

#endif