#ifndef _PlanetEntityOwnedStates_
#define _PlanetEntityOwnedStates_

#include "State.h"
#include "PlanetEntity.h"

///////////////////////////////////////////////////////////
// PlanetEntityNormal
///////////////////////////////////////////////////////////
class CPlanetEntityNormal : public CState<CPlanetEntity>{
private:  
	CPlanetEntityNormal(){}
	~CPlanetEntityNormal(){}

  //copy ctor and assignment should be private
  CPlanetEntityNormal(const CPlanetEntityNormal&);
  CPlanetEntityNormal& operator=(const CPlanetEntityNormal&);
 
public:
  //this is a singleton
	static CPlanetEntityNormal* Instance(){
		static CPlanetEntityNormal instance;

		return &instance;
	}

	virtual void Enter(CPlanetEntity* _pPlanetEntity);

	virtual void Execute(CPlanetEntity* _pPlanetEntity);

	virtual void Exit(CPlanetEntity* _pPlanetEntity);

	virtual bool OnMessage(CPlanetEntity* agent, const Telegram& _rMsg){return false;}
};

#define PlanetEntityNormal CPlanetEntityNormal::Instance()

///////////////////////////////////////////////////////////
// PlanetEntityCreation
///////////////////////////////////////////////////////////
class CPlanetEntityCreation : public CState<CPlanetEntity>{
private:  
	CPlanetEntityCreation(){}
	~CPlanetEntityCreation(){}

  //copy ctor and assignment should be private
  CPlanetEntityCreation(const CPlanetEntityCreation&);
  CPlanetEntityCreation& operator=(const CPlanetEntityCreation&);
 
public:
  //this is a singleton
	static CPlanetEntityCreation* Instance(){
		static CPlanetEntityCreation instance;

		return &instance;
	}

	virtual void Enter(CPlanetEntity* _pPlanetEntity);

	virtual void Execute(CPlanetEntity* _pPlanetEntity);

	virtual void Exit(CPlanetEntity* _pPlanetEntity);

	virtual bool OnMessage(CPlanetEntity* agent, const Telegram& _rMsg){return false;}
};

#define PlanetEntityCreation CPlanetEntityCreation::Instance()

///////////////////////////////////////////////////////////
// PlanetEntityDie
///////////////////////////////////////////////////////////
class CPlanetEntityDie : public CState<CPlanetEntity>{
private:  
	CPlanetEntityDie(){}
	~CPlanetEntityDie(){}

  //copy ctor and assignment should be private
  CPlanetEntityDie(const CPlanetEntityDie&);
  CPlanetEntityDie& operator=(const CPlanetEntityDie&);
 
public:
  //this is a singleton
	static CPlanetEntityDie* Instance(){
		static CPlanetEntityDie instance;

		return &instance;
	}

	virtual void Enter(CPlanetEntity* _pPlanetEntity);

	virtual void Execute(CPlanetEntity* _pPlanetEntity);

	virtual void Exit(CPlanetEntity* _pPlanetEntity);

	virtual bool OnMessage(CPlanetEntity* agent, const Telegram& _rMsg){return false;}
};

#define PlanetEntityDie CPlanetEntityDie::Instance()

//////////////////////////////////////////////////////////
// PlanetEntityDark
///////////////////////////////////////////////////////////
class CPlanetEntityDark : public CState<CPlanetEntity>{
private:  
	CPlanetEntityDark(){}
	~CPlanetEntityDark(){}

  //copy ctor and assignment should be private
  CPlanetEntityDark(const CPlanetEntityDark&);
  CPlanetEntityDark& operator=(const CPlanetEntityDark&);
 
public:
  //this is a singleton
	static CPlanetEntityDark* Instance(){
		static CPlanetEntityDark instance;

		return &instance;
	}

	virtual void Enter(CPlanetEntity* _pPlanetEntity);

	virtual void Execute(CPlanetEntity* _pPlanetEntity);

	virtual void Exit(CPlanetEntity* _pPlanetEntity);

	virtual bool OnMessage(CPlanetEntity* agent, const Telegram& _rMsg){return false;}
};

#define PlanetEntityDark CPlanetEntityDark::Instance()

#endif