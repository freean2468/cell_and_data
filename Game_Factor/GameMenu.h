////////////////////////////////////////////////////////////////////////////////
// 유동적인 게임메뉴 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _GameMenu_H_
#define _GameMenu_H_

#include "../Engine_System/CameraManager.h"
#include "../Engine_System/OrganEntity.h"
#include "../Engine_System/StateMachine.h"

class CGameMenu : public COrganEntity{
public:
	typedef enum GameMenuAttType {RETURN_TO_MENU=-1,RETRY=0, RESUME=2} GAMEMENUATTTYPE;

private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CGameMenu>* m_pStateMachine;

	CCameraManager::CAMERAMODE m_eCameraMode;

public:
	CGameMenu(int _nID = -1);
	~CGameMenu();

	// 이것은 반드시 설치되어야 한다.
	void Update();

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CGameMenu>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	void SetCameraMode(CCameraManager::CAMERAMODE _eMode){m_eCameraMode = _eMode;}
	CCameraManager::CAMERAMODE GetCameraMode(){return m_eCameraMode;}
};

#endif