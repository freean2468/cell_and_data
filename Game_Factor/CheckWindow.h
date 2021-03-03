#ifndef _CheckWindow_H_
#define _CheckWindow_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/Text.h"
#include <string>

class CCheckWindow : public COrganEntity{
public:
	typedef enum CWAttType{YES, NO, OK} CWATTTYPE;

private:
	CText*				m_pText;

	bool					m_bActive;

	// �� �ٿ�
	std::string		m_OneLine;

	// script��
	std::string   m_CurrentLine;

	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CCheckWindow>* m_pStateMachine;

public:
	CCheckWindow(int _nEntityType);
	~CCheckWindow();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	virtual void Update();

	void InitLine(){m_OneLine.clear(); m_CurrentLine.clear();}

	void ReadLine(std::string _String);

	void GivenLine(std::string _pString){if(_pString != m_OneLine) m_pText->InitValiable();	m_OneLine = _pString; m_pText->SetString(m_OneLine);}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CCheckWindow>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){	return m_pStateMachine->HandleMessage(_rMsg);	}

	CText* GetText(){return m_pText;}

	bool		GetActive(){return m_bActive;}

	void		OnActive(){m_bActive = true;}
	void		OffActive(){m_bActive = false;}
};

#endif