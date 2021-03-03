////////////////////////////////////////////////////
// QuestionMark가 가질 상태들
////////////////////////////////////////////////////
#ifndef _QuestionMarkOwnedStates_H_
#define _QuestionMarkOwnedStates_H_

class CQuestionMark;

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
class CQuestionMarkUsual : public CState<CQuestionMark>{
private:  
	CQuestionMarkUsual(){}

	//copy ctor and assignment should be private
	CQuestionMarkUsual(const CQuestionMarkUsual&);
	CQuestionMarkUsual& operator=(const CQuestionMarkUsual&);

	int _nCount;
 
public:
  //this is a singleton
	static CQuestionMarkUsual* Instance(){
		static CQuestionMarkUsual instance;

		return &instance;
	}

	virtual void Enter(CQuestionMark* pQuestionMark);

	virtual void Execute(CQuestionMark* pQuestionMark);

	virtual void Exit(CQuestionMark* pQuestionMark);

	virtual bool OnMessage(CQuestionMark* agent, const Telegram& _rMsg);
};

#define QuestionMarkUsual CQuestionMarkUsual::Instance()

#endif