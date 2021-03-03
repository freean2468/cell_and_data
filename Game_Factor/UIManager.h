////////////////////////////////////////////////////
// UserInterface와 관련된 정보를 담당 관리 클래스
////////////////////////////////////////////////////
#ifndef _UIManager_H_
#define _UIManager_H_

#include "Ability.h"
#include "Gauge.h"
#include "TextOfGame.h"
#include "MessageWindow.h"
#include "CheckWindow.h"
#include "InputWindow.h"
#include "GameMenu.h"
#include "Arrow.h"

class CUIManager{
private:
	// =============== Ability
	CAbility*				m_pAbility;

	// =============== Gauge
	CGauge*		m_pGauge;

	// =============== TextOfGame
	CTextOfGame*		m_pTextOfGame;

	// =============== 메세지 창들
	CMessageWindow* m_pMWSquare;

	// =============== 체크 창
	CCheckWindow*		m_pCW;
	CInputWindow*		m_pIW;

	// =============== GameMenu
	CGameMenu*			m_pGameMenu;

	// =============== Arrow
	CArrow*					m_pArrow;

private:
	CUIManager();
	CUIManager(const CUIManager&);
	CUIManager& operator =(const CUIManager&);

public:
	~CUIManager();
	static CUIManager* Instance(){
		static CUIManager instance;

		return &instance;
	}

	// UI 업데이트
	void Update();

	// ========================================== Ability
	CAbility* GetAbility(){return m_pAbility;}

	// ========================================== Gauge
	CGauge*	GetGauge(){return m_pGauge;}

	// ========================================== Text Of Game
	CTextOfGame* GetTextOfGame(){return m_pTextOfGame;}

	// ========================================== 메세지창 함수들
	CMessageWindow* GetMWSquare(){return m_pMWSquare;}

	// ========================================== 체크창 함수들
	CCheckWindow* GetCW(){return m_pCW;}
	CInputWindow*	GetIW(){return m_pIW;}

	// ========================================== GameMenu 함수들
	CGameMenu* GetGameMenu(){return m_pGameMenu;}

	// ========================================== Arrow
	CArrow*	GetArrow(){return m_pArrow;}

	void SetPosMWSquare(D3DXVECTOR3* _pvPos){m_pMWSquare->GetBody()->GetPriPos()->x = _pvPos->x; m_pMWSquare->GetBody()->GetPriPos()->y = _pvPos->y; m_pMWSquare->GetBody()->GetPriPos()->z = _pvPos->z;}
};

#define UIMgr CUIManager::Instance()

#endif