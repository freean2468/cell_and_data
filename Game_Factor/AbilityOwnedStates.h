////////////////////////////////////////////////////
// Ability가 가질 상태들
////////////////////////////////////////////////////
#ifndef _AbilityOwnedStates_H_
#define _AbilityOwnedStates_H_

#include "../Engine_System/State.h"
#include "Ability.h"

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
class CAbilityActive : public CState<CAbility>{
private:
	float m_fFrequency;

private:  
	CAbilityActive(){}

	//copy ctor and assignment should be private
	CAbilityActive(const CAbilityActive&);
	CAbilityActive& operator=(const CAbilityActive&);
 
public:
  //this is a singleton
	static CAbilityActive* Instance(){
		static CAbilityActive instance;

		return &instance;
	}

	virtual void Enter(CAbility* _pAbility);

	virtual void Execute(CAbility* _pAbility);

	virtual void Exit(CAbility* _pAbility);

	virtual bool OnMessage(CAbility* agent, const Telegram& _rMsg);
};

#define AbilityActive CAbilityActive::Instance()

///////////////////////////////////////////////////////////
// Maintain State
///////////////////////////////////////////////////////////
class CAbilityMaintain : public CState<CAbility>{
private:  
	CAbilityMaintain(){}

	//copy ctor and assignment should be private
	CAbilityMaintain(const CAbilityMaintain&);
	CAbilityMaintain& operator=(const CAbilityMaintain&);
 
public:
  //this is a singleton
	static CAbilityMaintain* Instance(){
		static CAbilityMaintain instance;

		return &instance;
	}

	virtual void Enter(CAbility* _pAbility);

	virtual void Execute(CAbility* _pAbility);

	virtual void Exit(CAbility* _pAbility);

	virtual bool OnMessage(CAbility* agent, const Telegram& _rMsg);
};

#define AbilityMaintain CAbilityMaintain::Instance()

///////////////////////////////////////////////////////////
// Inactive State
///////////////////////////////////////////////////////////
class CAbilityInActive : public CState<CAbility>{
private:  
	CAbilityInActive(){}

	//copy ctor and assignment should be private
	CAbilityInActive(const CAbilityInActive&);
	CAbilityInActive& operator=(const CAbilityInActive&);
 
public:
  //this is a singleton
	static CAbilityInActive* Instance(){
		static CAbilityInActive instance;

		return &instance;
	}

	virtual void Enter(CAbility* _pAbility);

	virtual void Execute(CAbility* _pAbility);

	virtual void Exit(CAbility* _pAbility);

	virtual bool OnMessage(CAbility* agent, const Telegram& _rMsg);
};

#define AbilityInActive CAbilityInActive::Instance()

#endif