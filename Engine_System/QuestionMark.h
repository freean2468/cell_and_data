////////////////////////////////////////////////////////////////////////////////
// QuestionMark Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _QuestionMark_H_
#define _QuestionMark_H_

#include "./Engine_System/EngineManager.h"

class CQuestionMark : public CBaseEffect{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CQuestionMark>* m_pStateMachine;

	COrgan* m_pOrigin;
	bool m_bOnOff; // on = true

public:
	CQuestionMark(COrgan* _pOrgan);
	~CQuestionMark();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CQuestionMark>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CQuestionMark>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	COrgan* GetOrigin(){return m_pOrigin;}
};

#endif