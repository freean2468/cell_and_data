////////////////////////////////////////////////////////////////////////////////
// �������� Ending Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Ending_H_
#define _Ending_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

class CEnding : public COrganEntity{
public:
	typedef enum EndingAttType {ENDING, DARK} ENDINGATTTYPE;

private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CEnding>* m_pStateMachine;

public:
	CEnding(int _nID);
	~CEnding();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	virtual void RenderOrgan();

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CEnding>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}
};

#endif