#ifndef _InputWindow_H_
#define _InputWindow_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/Text.h"
#include "../Engine_System/Timer.h"
#include <string>

class CInputWindow : public COrganEntity{
public:
	typedef enum InputWindow {INPUT, OK} INPUTWINDOW;

private:
	CText*				m_pText;
	CText*				m_pName;

	bool					m_bActive;

	std::string		m_Line;
	std::string		m_Name;

	CTimer*				m_pCursorTimer;
	bool					m_bCursorActive;

	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CInputWindow>* m_pStateMachine;

public:
	CInputWindow(int _nEntityType);
	~CInputWindow();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	virtual void Update();

	void GivenLine(std::string _pString){if(_pString != m_Line) m_pText->InitValiable();	m_Line = _pString; m_pText->SetString(m_Line);}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CInputWindow>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){	return m_pStateMachine->HandleMessage(_rMsg);	}

	CText* GetText(){return m_pText;}
	std::string&		GetName(){return m_Name;}

	bool		GetActive(){return m_bActive;}

	void		OnActive(){m_bActive = true;}
	void		OffActive(){m_bActive = false;}

	bool		GetCursorActive(){return m_bCursorActive;}

	void		OnCursorActive(){m_bCursorActive = true;}
	void		OffCursorActive(){m_bCursorActive = false;}
	void		ToggleCursor(){m_bCursorActive = !m_bCursorActive;}
};

#endif