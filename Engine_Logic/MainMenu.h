////////////////////////////////////////////////////////////////////////////////
// �������� ���θ޴� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _MainMenu_H_
#define _MainMenu_H_

#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

#define RETURN -1

class CMainMenu : public COrganEntity{
public:
	typedef enum MenuAttType {C, E, L, AND, D, A, T} MENUATTTYPE;
	typedef enum MenuMainAttType {SCENARIO, EXTRA, CREDIT, EXIT} MENUMAINATTTYPE;
	typedef enum MenuExtraAttType {TIMEATTACK, SURVIVAL, RANK, OST} MENUEXTRAATTTYPE;
	typedef enum MenuStartAttType {START, LOAD} MENUSTARTATTTYPE;

private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CMainMenu>* m_pStateMachine;
	
	COrganEntity* m_pMenuMain;
	COrganEntity* m_pMenuStart;
	COrganEntity* m_pMenuExtra;

public:
	CMainMenu(int _nID);
	~CMainMenu();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	virtual void RenderOrgan();

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CMainMenu>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	COrganEntity* GetMain(){return m_pMenuMain;}
	COrganEntity* GetExtra(){return m_pMenuExtra;}
	COrganEntity* GetStart(){return m_pMenuStart;}
};

#endif