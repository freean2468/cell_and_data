////////////////////////////////////////////////////
// ID�� ���� Entity�� ��� ���� Section �κ� Ŭ����
////////////////////////////////////////////////////
#ifndef _Section_H_
#define _Section_H_

#include "SectionOwnedStates.h"
#include "../Engine_System/StateMachine.h"
#include "../Engine_System/SystemDefines.h"

class CSection{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CSection>* m_pStateMachine;

public:
	CSection();

	~CSection();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CSection>* GetFSM()const{return m_pStateMachine;}
};

#endif