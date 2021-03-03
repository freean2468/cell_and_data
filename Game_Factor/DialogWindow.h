#ifndef _DialogWindow_H_
#define _DialogWindow_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/Body.h"
#include "../Engine_System/Text.h"
#include <string>

class CDialogWindow : public COrganEntity{
private:
	int				m_nDialogID;

	CBody*			m_pImage[2];
	CText*			m_pText;

	// �� �ٿ�
	std::string		m_OneLine;

	// script��
	std::string		m_CurrentLine;

	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CDialogWindow>* m_pStateMachine;

public:
	CDialogWindow(int _nEntityType);
	~CDialogWindow();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	virtual void Update();

	void InitLine(){m_OneLine.clear(); m_CurrentLine.clear();}

	void ReadLine(std::string _String);

	void GivenLine(std::string _pString){if(_pString != m_OneLine) m_pText->InitValiable();	m_OneLine = _pString; m_pText->SetString(m_OneLine);}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CDialogWindow>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){	return m_pStateMachine->HandleMessage(_rMsg);	}

	CText* GetText(){return m_pText;}

	void SetDialogID(int _ID){m_nDialogID = _ID;}
	int GetDialogID(){return m_nDialogID;}

	CBody* GetImage(){return m_pImage[m_nDialogID];}
};

#endif