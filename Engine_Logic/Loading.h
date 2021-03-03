////////////////////////////////////////////////////////////////////////////////
// 유동적인 로고
////////////////////////////////////////////////////////////////////////////////
#ifndef _Loading_H_
#define _Loading_H_

#include "../Game_Factor/MessageWindow.h"

class CLoading : public COrganEntity{
public:
	typedef enum LoadingAttType {BODY} LOADINGATTTYPE;

private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CLoading>* m_pStateMachine;

	CMessageWindow* m_pMW;

	std::vector<std::string> m_LoadingContents;

	int m_nStepOfLoading;

public:
	CLoading(int _nEntityType);
	~CLoading();

	// 이것은 반드시 설치되어야 한다.
	virtual void Update();

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CLoading>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	void SetStepOfLoading(int _nStep){m_nStepOfLoading = _nStep;}
	int GetStepOfLoading(){return m_nStepOfLoading;}

	void InitLoadingComponents();
	void InitLoadingGameWorldContents();
};

#endif