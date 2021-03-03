////////////////////////////////////////////////////////////////////////////////
// �������� �ΰ�
////////////////////////////////////////////////////////////////////////////////
#ifndef _Loading_H_
#define _Loading_H_

#include "../Game_Factor/MessageWindow.h"

class CLoading : public COrganEntity{
public:
	typedef enum LoadingAttType {BODY} LOADINGATTTYPE;

private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CLoading>* m_pStateMachine;

	CMessageWindow* m_pMW;

	std::vector<std::string> m_LoadingContents;

	int m_nStepOfLoading;

public:
	CLoading(int _nEntityType);
	~CLoading();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	virtual void Update();

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
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