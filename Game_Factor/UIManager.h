////////////////////////////////////////////////////
// UserInterface�� ���õ� ������ ��� ���� Ŭ����
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

	// =============== �޼��� â��
	CMessageWindow* m_pMWSquare;

	// =============== üũ â
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

	// UI ������Ʈ
	void Update();

	// ========================================== Ability
	CAbility* GetAbility(){return m_pAbility;}

	// ========================================== Gauge
	CGauge*	GetGauge(){return m_pGauge;}

	// ========================================== Text Of Game
	CTextOfGame* GetTextOfGame(){return m_pTextOfGame;}

	// ========================================== �޼���â �Լ���
	CMessageWindow* GetMWSquare(){return m_pMWSquare;}

	// ========================================== üũâ �Լ���
	CCheckWindow* GetCW(){return m_pCW;}
	CInputWindow*	GetIW(){return m_pIW;}

	// ========================================== GameMenu �Լ���
	CGameMenu* GetGameMenu(){return m_pGameMenu;}

	// ========================================== Arrow
	CArrow*	GetArrow(){return m_pArrow;}

	void SetPosMWSquare(D3DXVECTOR3* _pvPos){m_pMWSquare->GetBody()->GetPriPos()->x = _pvPos->x; m_pMWSquare->GetBody()->GetPriPos()->y = _pvPos->y; m_pMWSquare->GetBody()->GetPriPos()->z = _pvPos->z;}
};

#define UIMgr CUIManager::Instance()

#endif