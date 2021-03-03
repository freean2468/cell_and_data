////////////////////////////////////////////////////
// Section이 가질 상태들
////////////////////////////////////////////////////
#ifndef _SectionOwnedStates_H_
#define _SectionOwnedStates_H_

#include "../Engine_System/State.h"
#include "Section.h"
#include "Loading.h"
#include "Logo.h"
#include "Credit.h"
#include "Rank.h"
#include "Ending.h"
#include "OST.h"
#include "MainMenu.h"

class CSection;
class CSectionLogo;
class CSectionDev;
class CSectionLoad;
class CSectionMainMenu;
class CSectionCredit;
class CSectionOST;
class CSectionRank;
class CSectionExtraTimeAttack;
class CSectionExtraSurvival;
class CSectionStory1st;
class CSectionStory2nd;
class CSectionStory3rd;
class CSectionStory4th;
class CSectionStory5th;
class CSectionStory6th;
class CSectionEnding;
class CSectionExit;

///////////////////////////////////////////////////////////
// Dev 섹션
///////////////////////////////////////////////////////////
class CSectionDev : public CState<CSection>{
private:  
	CSectionDev(){}
	~CSectionDev(){}

  //copy ctor and assignment should be private
  CSectionDev(const CSectionDev&);
  CSectionDev& operator=(const CSectionDev&);
 
public:
  //this is a singleton
	static CSectionDev* Instance(){
		static CSectionDev instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionDev CSectionDev::Instance()

///////////////////////////////////////////////////////////
// Load
///////////////////////////////////////////////////////////
class CSectionLoad : public CState<CSection>{
private:
	CLoading* m_pLoading;

private:  
	CSectionLoad() : m_pLoading(new CLoading(-1)){}
	~CSectionLoad(){Delete<CLoading*>(m_pLoading);}

  //copy ctor and assignment should be private
  CSectionLoad(const CSectionLoad&);
  CSectionLoad& operator=(const CSectionLoad&);
 
public:
  //this is a singleton
	static CSectionLoad* Instance(){
		static CSectionLoad instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionLoad CSectionLoad::Instance()

///////////////////////////////////////////////////////////
// 로고 섹션
///////////////////////////////////////////////////////////
class CSectionLogo : public CState<CSection>{
private:
	CLogo* m_pLogo;

private:  
	CSectionLogo() : m_pLogo(new CLogo(-1)){}
	~CSectionLogo(){ Delete<CLogo*>(m_pLogo); }

  //copy ctor and assignment should be private
  CSectionLogo(const CSectionLogo&);
  CSectionLogo& operator=(const CSectionLogo&);
 
public:
  //this is a singleton
	static CSectionLogo* Instance(){
		static CSectionLogo instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionLogo CSectionLogo::Instance()

///////////////////////////////////////////////////////////
// 메인메뉴 섹션
///////////////////////////////////////////////////////////
class CSectionMainMenu : public CState<CSection>{
private:
	CMainMenu* m_pMainMenu;

private:  
	CSectionMainMenu(): m_pMainMenu(new CMainMenu(-1)){}
	~CSectionMainMenu(){		Delete<CMainMenu*>(m_pMainMenu);	}

  //copy ctor and assignment should be private
  CSectionMainMenu(const CSectionMainMenu&);
  CSectionMainMenu& operator=(const CSectionMainMenu&);
 
public:
  //this is a singleton
	static CSectionMainMenu* Instance(){
		static CSectionMainMenu instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionMainMenu CSectionMainMenu::Instance()

///////////////////////////////////////////////////////////
// Credit 섹션
///////////////////////////////////////////////////////////
class CSectionCredit : public CState<CSection>{
private:
	CCredit* m_pCredit;

private:  
  CSectionCredit():m_pCredit(new CCredit(-1)){}
	~CSectionCredit(){Delete<CCredit*>(m_pCredit);}

  //copy ctor and assignment should be private
  CSectionCredit(const CSectionCredit&);
  CSectionCredit& operator=(const CSectionCredit&);
 
public:
  //this is a singleton
	static CSectionCredit* Instance(){
		static CSectionCredit instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionCredit CSectionCredit::Instance()

///////////////////////////////////////////////////////////
// OST 섹션
///////////////////////////////////////////////////////////
class CSectionOST : public CState<CSection>{
private:
	COST* m_pOST;

private:  
  CSectionOST():m_pOST(new COST()){}
	~CSectionOST(){Delete<COST*>(m_pOST);}

  //copy ctor and assignment should be private
  CSectionOST(const CSectionOST&);
  CSectionOST& operator=(const CSectionOST&);
 
public:
  //this is a singleton
	static CSectionOST* Instance(){
		static CSectionOST instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionOST CSectionOST::Instance()

///////////////////////////////////////////////////////////
// Rank 섹션
///////////////////////////////////////////////////////////
class CSectionRank : public CState<CSection>{
private:
	CRank* m_pTimeAttack;
	CRank* m_pSurvival;
	COrgan* m_pReturn;
	COrgan* m_pInitialize;

private:  
	CSectionRank();
	~CSectionRank();

  //copy ctor and assignment should be private
  CSectionRank(const CSectionRank&);
  CSectionRank& operator=(const CSectionRank&);
 
public:
  //this is a singleton
	static CSectionRank* Instance(){
		static CSectionRank instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionRank CSectionRank::Instance()

///////////////////////////////////////////////////////////
// ExtraTimeAttack 섹션
///////////////////////////////////////////////////////////
class CSectionExtraTimeAttack : public CState<CSection>{
private:  
  CSectionExtraTimeAttack(){}
	~CSectionExtraTimeAttack(){}

  //copy ctor and assignment should be private
  CSectionExtraTimeAttack(const CSectionExtraTimeAttack&);
  CSectionExtraTimeAttack& operator=(const CSectionExtraTimeAttack&);
 
public:
  //this is a singleton
	static CSectionExtraTimeAttack* Instance(){
		static CSectionExtraTimeAttack instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionExtraTimeAttack CSectionExtraTimeAttack::Instance()

///////////////////////////////////////////////////////////
// ExtraSurvival 섹션
///////////////////////////////////////////////////////////
class CSectionExtraSurvival : public CState<CSection>{
private:  
  CSectionExtraSurvival(){}
	~CSectionExtraSurvival(){}

  //copy ctor and assignment should be private
  CSectionExtraSurvival(const CSectionExtraSurvival&);
  CSectionExtraSurvival& operator=(const CSectionExtraSurvival&);
 
public:
  //this is a singleton
	static CSectionExtraSurvival* Instance(){
		static CSectionExtraSurvival instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionExtraSurvival CSectionExtraSurvival::Instance()


///////////////////////////////////////////////////////////
// 이야기 첫번째 섹션
///////////////////////////////////////////////////////////
class CSectionStory1st : public CState<CSection>{
private:  
	CSectionStory1st(){}

  //copy ctor and assignment should be private
  CSectionStory1st(const CSectionStory1st&);
  CSectionStory1st& operator=(const CSectionStory1st&);
 
public:
  //this is a singleton
	static CSectionStory1st* Instance(){
		static CSectionStory1st instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionStory1st CSectionStory1st::Instance()

///////////////////////////////////////////////////////////
// 이야기 두번째 섹션
///////////////////////////////////////////////////////////
class CSectionStory2nd : public CState<CSection>{
private:  
	CSectionStory2nd(){}

  //copy ctor and assignment should be private
  CSectionStory2nd(const CSectionStory2nd&);
  CSectionStory2nd& operator=(const CSectionStory2nd&);
 
public:
  //this is a singleton
	static CSectionStory2nd* Instance(){
		static CSectionStory2nd instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionStory2nd CSectionStory2nd::Instance()

///////////////////////////////////////////////////////////
// 이야기 세번째 섹션
///////////////////////////////////////////////////////////
class CSectionStory3rd : public CState<CSection>{
private:  
	CSectionStory3rd(){}

  //copy ctor and assignment should be private
  CSectionStory3rd(const CSectionStory3rd&);
  CSectionStory3rd& operator=(const CSectionStory3rd&);
 
public:
  //this is a singleton
	static CSectionStory3rd* Instance(){
		static CSectionStory3rd instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionStory3rd CSectionStory3rd::Instance()

///////////////////////////////////////////////////////////
// 이야기 네번째 섹션
///////////////////////////////////////////////////////////
class CSectionStory4th : public CState<CSection>{
private:  
	CSectionStory4th(){}

  //copy ctor and assignment should be private
  CSectionStory4th(const CSectionStory4th&);
  CSectionStory4th& operator=(const CSectionStory4th&);
 
public:
  //this is a singleton
	static CSectionStory4th* Instance(){
		static CSectionStory4th instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionStory4th CSectionStory4th::Instance()

///////////////////////////////////////////////////////////
// 이야기 다섯번째 섹션
///////////////////////////////////////////////////////////
class CSectionStory5th : public CState<CSection>{
private:  
	CSectionStory5th(){}

  //copy ctor and assignment should be private
  CSectionStory5th(const CSectionStory5th&);
  CSectionStory5th& operator=(const CSectionStory5th&);
 
public:
  //this is a singleton
	static CSectionStory5th* Instance(){
		static CSectionStory5th instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionStory5th CSectionStory5th::Instance()

///////////////////////////////////////////////////////////
// 이야기 여섯번째 섹션
///////////////////////////////////////////////////////////
class CSectionStory6th : public CState<CSection>{
private:  
	CSectionStory6th(){}

  //copy ctor and assignment should be private
  CSectionStory6th(const CSectionStory6th&);
  CSectionStory6th& operator=(const CSectionStory6th&);
 
public:
  //this is a singleton
	static CSectionStory6th* Instance(){
		static CSectionStory6th instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionStory6th CSectionStory6th::Instance()

///////////////////////////////////////////////////////////
// Ending 섹션
///////////////////////////////////////////////////////////
class CSectionEnding : public CState<CSection>{
private:
	CEnding* m_pEnding;

private:  
  CSectionEnding():m_pEnding(new CEnding(-1)){}
	~CSectionEnding(){Delete<CEnding*>(m_pEnding);}

  //copy ctor and assignment should be private
  CSectionEnding(const CSectionEnding&);
  CSectionEnding& operator=(const CSectionEnding&);
 
public:
  //this is a singleton
	static CSectionEnding* Instance(){
		static CSectionEnding instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionEnding CSectionEnding::Instance()

///////////////////////////////////////////////////////////
// 게임 끝
///////////////////////////////////////////////////////////
class CSectionExit : public CState<CSection>{
private:
	CLogo* m_pLogo;

private:  
  CSectionExit():m_pLogo(new CLogo(-1)){}
	~CSectionExit(){ Delete<CLogo*>(m_pLogo); }

  //copy ctor and assignment should be private
  CSectionExit(const CSectionExit&);
  CSectionExit& operator=(const CSectionExit&);
 
public:
  //this is a singleton
	static CSectionExit* Instance(){
		static CSectionExit instance;

		return &instance;
	}

	virtual void Enter(CSection* _pSection);

	virtual void Execute(CSection* _pSection);

	virtual void Exit(CSection* _pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& _rMsg){return false;}
};

#define SectionExit CSectionExit::Instance()

#endif