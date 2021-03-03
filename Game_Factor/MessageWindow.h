////////////////////////////////////////////////////////////////////////////////
// 메시지창 베이스
////////////////////////////////////////////////////////////////////////////////
#ifndef _MessageWindow_H_
#define _MessageWindow_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/Text.h"

class CMessageWindow : public COrganEntity{
public:
	typedef enum MWType {SQUARE, THIN, BALLOON, TRANSPARENCY} MWTYPE;

private:
	MWTYPE				m_eMWType;
	CText*				m_pText;

	// 한 줄용
	std::string		m_OneLine;

	// script용
	std::string   m_CurrentLine;

	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CMessageWindow>* m_pStateMachine;

public:
	CMessageWindow(int _nEntityType, MWTYPE _eMWType);
	~CMessageWindow();

	// 이것은 반드시 설치되어야 한다.
	virtual void Update();

	void InitLine(){m_OneLine.clear(); m_CurrentLine.clear();}

	void ReadLine(std::string _String);

	void GivenLine(std::string _pString){if(_pString != m_OneLine) m_pText->InitValiable();	m_OneLine = _pString; m_pText->SetString(m_OneLine);}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CMessageWindow>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){	return m_pStateMachine->HandleMessage(_rMsg);	}

	MWTYPE GetMWType(){return m_eMWType;}
	CText* GetText(){return m_pText;}
};

#endif