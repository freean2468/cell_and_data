////////////////////////////////////////////////////////////////////////////////
// ���ӿ� �ʿ��� �ؽ�Ʈ���� ���� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _TextOfGame_H_
#define _TextOfGame_H_

#include "../Engine_System/CrudeTImer.h"
#include "NumberArray.h"
#include "../Engine_System/Text.h"

class CTextOfGame : public COrganEntity{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CTextOfGame>* m_pStateMachine;

	// ���
	CText* m_pAdress;

	// Score
	CText* m_pScore;

	// Time
	bool m_bTimeActive;
	CNumberArray* m_pTime;
	CCrudeTimer*	m_pTimer;

public:
	CTextOfGame(int _nEntityType = -1);
	~CTextOfGame();

	void Initialize();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	virtual	void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CTextOfGame>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	CNumberArray* GetTime(){return m_pTime;}

	CText*	GetScore(){return m_pScore;}
	void		UpdateScore();
	CText*	GetAdress(){return m_pAdress;}
	void		UpdateAdress();

	CCrudeTimer*	GetTimer(){return m_pTimer;}
	bool IsTimeActive(){return m_bTimeActive;}
	void OnTime(){m_bTimeActive = true; m_pTimer->Start();}
	void OffTime(){m_bTimeActive = false;}
	void UpdateTimer(){m_pTime->SetValue(static_cast<int>(m_pTimer->GetCurrentTime()));}
};

#endif