////////////////////////////////////////////////////
// SecretData가 가질 상태들
////////////////////////////////////////////////////
#ifndef _SecretDataOwnedStates_H_
#define _SecretDataOwnedStates_H_

#include "../Engine_System/State.h"
#include "../Engine_System/Timer.h"
#include "../Engine_Misc/DirectUtils.h"
#include  "SecretData.h"

///////////////////////////////////////////////////////////
// Delete State
///////////////////////////////////////////////////////////
class CSecretDataDelete : public CState<CSecretData>{
private:
	CTimer* m_pTimer;

private:  
	CSecretDataDelete():m_pTimer(new CTimer(0)){}
	~CSecretDataDelete(){Delete<CTimer*>(m_pTimer);}

	//copy ctor and assignment should be private
	CSecretDataDelete(const CSecretDataDelete&);
	CSecretDataDelete& operator=(const CSecretDataDelete&);
 
public:
  //this is a singleton
	static CSecretDataDelete* Instance(){
		static CSecretDataDelete instance;

		return &instance;
	}

	virtual void Enter(CSecretData* _pSecretData);

	virtual void Execute(CSecretData* _pSecretData);

	virtual void Exit(CSecretData* _pSecretData);

	virtual bool OnMessage(CSecretData* agent, const Telegram& _rMsg);
};

#define SecretDataDelete CSecretDataDelete::Instance()

///////////////////////////////////////////////////////////
// Maintain State
///////////////////////////////////////////////////////////
class CSecretDataMaintain : public CState<CSecretData>{
private:
	float m_fPercentage;
	Vector2D m_vDist;

private:  
	CSecretDataMaintain(){}

	//copy ctor and assignment should be private
	CSecretDataMaintain(const CSecretDataMaintain&);
	CSecretDataMaintain& operator=(const CSecretDataMaintain&);
 
public:
  //this is a singleton
	static CSecretDataMaintain* Instance(){
		static CSecretDataMaintain instance;

		return &instance;
	}

	virtual void Enter(CSecretData* _pSecretData);

	virtual void Execute(CSecretData* _pSecretData);

	virtual void Exit(CSecretData* _pSecretData);

	virtual bool OnMessage(CSecretData* agent, const Telegram& _rMsg);
};

#define SecretDataMaintain CSecretDataMaintain::Instance()

#endif