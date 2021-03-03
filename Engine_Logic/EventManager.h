////////////////////////////////////////////////////
// Event 관리 클래스
////////////////////////////////////////////////////
#ifndef _EventManager_H_
#define _EventManager_H_

#include "../Engine_System/ScriptLoader.h"
#include "../Game_Factor/DialogWindow.h"
#include "Event.h"
#include "../Game_Factor/MessageWindow.h"

class CEventManager{
private:
	CScriptLoader* m_pScriptLoader;	

	// =============== Character Present (이벤트 주체들)
	CBody* m_pFriend;
	CBody* m_pLove;

	bool m_bShowFriend;
	bool m_bShowLove;

	// 말풍선
	CMessageWindow* m_pBalloon;

	// =============== 대화 
	CDialogWindow* m_pDW;

	bool m_bScript;			// Script 진행 중 여부
	bool m_bNextScript; // 다음 Script 진행 여부

	// =============== Event 객체
	CEvent* m_pMain;
	CEvent* m_pSub;

	int m_nEventStep;
	CTimer* m_pTimer;

private:
	CEventManager();
	CEventManager(const CEventManager&);
	CEventManager& operator =(const CEventManager&);

public:
	~CEventManager();
	static CEventManager* Instance(){
		static CEventManager instance;

		return &instance;
	}

	void Initialize(int _nEventStep=0, DWORD _dwTime=0);
	void Update();

	void LoadScript(char* _pstrFile);
	CScriptLoader* GetScriptLoader(){return m_pScriptLoader;}

	CMessageWindow* GetBalloon(){return m_pBalloon;}

	// ========================================== CharacterPresent
	CBody* GetFriend(){return m_pFriend;}
	CBody* GetLove(){return m_pLove;}

	void SetShowFriend(bool _bShow){m_bShowFriend = _bShow;}
	void SetShowLove(bool _bShow){m_bShowLove = _bShow;}
	bool GetShowFriend(){return m_bShowFriend;}
	bool GetShowLove(){return m_bShowLove;}

	// ========================================== Event 객체
	CEvent* GetMain(){return m_pMain;}
	CEvent* GetSub(){return m_pSub;}	

	// ========================================== 대화 함수들
	CDialogWindow* GetDW(){return m_pDW;}

	void OffScript(){m_bScript = false;}
	void OnScript(){m_bScript = true;}
	bool GetScript(){return m_bScript;}

	bool GetNextScript(){return m_bNextScript;}
	void OnNextScript(){m_bNextScript = true;}
	void OffNextScript(){m_bNextScript = false;}

	// ========================================== 이벤트 함수들
	int GetEventStep(){return m_nEventStep;}
	void EventStepAdvance(){m_nEventStep++;}

	CTimer* GetTimer(){return m_pTimer;}
};

#define EventMgr CEventManager::Instance()

#endif