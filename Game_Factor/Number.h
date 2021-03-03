////////////////////////////////////////////////////////////////////////////////
// Number Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Number_H_
#define _Number_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

class CNumber : public COrganEntity{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CNumber>* m_pStateMachine;

	int m_nValue; // 0~9 ����

public:
	CNumber(int _nValue = 0, int _nEntityType = -1);
	~CNumber();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	virtual	void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);
	virtual void RenderOrgan();

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CNumber>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	void InitValue(int _nValue){m_nValue = _nValue;}
	int GetValue(){return m_nValue;}
};

#endif