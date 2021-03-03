////////////////////////////////////////////////////////////////////////////////
// 유동적인 메인메뉴 클래스
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
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CMainMenu>* m_pStateMachine;
	
	COrganEntity* m_pMenuMain;
	COrganEntity* m_pMenuStart;
	COrganEntity* m_pMenuExtra;

public:
	CMainMenu(int _nID);
	~CMainMenu();

	// 이것은 반드시 설치되어야 한다.
	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	virtual void RenderOrgan();

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CMainMenu>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	COrganEntity* GetMain(){return m_pMenuMain;}
	COrganEntity* GetExtra(){return m_pMenuExtra;}
	COrganEntity* GetStart(){return m_pMenuStart;}
};

#endif