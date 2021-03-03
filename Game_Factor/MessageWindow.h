////////////////////////////////////////////////////////////////////////////////
// �޽���â ���̽�
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

	// �� �ٿ�
	std::string		m_OneLine;

	// script��
	std::string   m_CurrentLine;

	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CMessageWindow>* m_pStateMachine;

public:
	CMessageWindow(int _nEntityType, MWTYPE _eMWType);
	~CMessageWindow();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	virtual void Update();

	void InitLine(){m_OneLine.clear(); m_CurrentLine.clear();}

	void ReadLine(std::string _String);

	void GivenLine(std::string _pString){if(_pString != m_OneLine) m_pText->InitValiable();	m_OneLine = _pString; m_pText->SetString(m_OneLine);}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CMessageWindow>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){	return m_pStateMachine->HandleMessage(_rMsg);	}

	MWTYPE GetMWType(){return m_eMWType;}
	CText* GetText(){return m_pText;}
};

#endif