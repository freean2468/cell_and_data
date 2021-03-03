////////////////////////////////////////////////////////////////////////////////
// QuestionMark 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _QuestionMark_H_
#define _QuestionMark_H_

#include "./Engine_System/EngineManager.h"

class CQuestionMark : public CBaseEffect{
private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CQuestionMark>* m_pStateMachine;

	COrgan* m_pOrigin;
	bool m_bOnOff; // on = true

public:
	CQuestionMark(COrgan* _pOrgan);
	~CQuestionMark();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CQuestionMark>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CQuestionMark>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	COrgan* GetOrigin(){return m_pOrigin;}
};

#endif