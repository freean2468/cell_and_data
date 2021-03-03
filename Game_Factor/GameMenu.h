////////////////////////////////////////////////////////////////////////////////
// �������� ���Ӹ޴� Ŭ����
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
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CGameMenu>* m_pStateMachine;

	CCameraManager::CAMERAMODE m_eCameraMode;

public:
	CGameMenu(int _nID = -1);
	~CGameMenu();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update();

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CGameMenu>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	void SetCameraMode(CCameraManager::CAMERAMODE _eMode){m_eCameraMode = _eMode;}
	CCameraManager::CAMERAMODE GetCameraMode(){return m_eCameraMode;}
};

#endif