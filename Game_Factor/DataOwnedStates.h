////////////////////////////////////////////////////
// Data가 가질 상태들
////////////////////////////////////////////////////
#ifndef _DataOwnedStates_H_
#define _DataOwnedStates_H_

#include "../Engine_System/State.h"
#include "Data.h"

///////////////////////////////////////////////////////////
// Normal State
///////////////////////////////////////////////////////////
class CDataNormal : public CState<CData>{
private:  
	CDataNormal(){}

	//copy ctor and assignment should be private
	CDataNormal(const CDataNormal&);
	CDataNormal& operator=(const CDataNormal&);
 
public:
  //this is a singleton
	static CDataNormal* Instance(){
		static CDataNormal instance;

		return &instance;
	}

	virtual void Enter(CData* _pData);

	virtual void Execute(CData* _pData);

	virtual void Exit(CData* _pData);

	virtual bool OnMessage(CData* agent, const Telegram& _rMsg);
};

#define DataNormal CDataNormal::Instance()

///////////////////////////////////////////////////////////
// Normal State
///////////////////////////////////////////////////////////
class CDataVariation : public CState<CData>{
private:  
	CDataVariation(){}
	~CDataVariation(){}

	//copy ctor and assignment should be private
	CDataVariation(const CDataVariation&);
	CDataVariation& operator=(const CDataVariation&);
 
public:
  //this is a singleton
	static CDataVariation* Instance(){
		static CDataVariation instance;

		return &instance;
	}

	virtual void Enter(CData* _pData);

	virtual void Execute(CData* _pData);

	virtual void Exit(CData* _pData);

	virtual bool OnMessage(CData* agent, const Telegram& _rMsg);
};

#define DataVariation CDataVariation::Instance()

///////////////////////////////////////////////////////////
// Cure State
///////////////////////////////////////////////////////////
class CDataCure : public CState<CData>{
private:  
	CDataCure(){}

	//copy ctor and assignment should be private
	CDataCure(const CDataCure&);
	CDataCure& operator=(const CDataCure&);
 
public:
  //this is a singleton
	static CDataCure* Instance(){
		static CDataCure instance;

		return &instance;
	}

	virtual void Enter(CData* _pData);

	virtual void Execute(CData* _pData);

	virtual void Exit(CData* _pData);

	virtual bool OnMessage(CData* agent, const Telegram& _rMsg);
};

#define DataCure CDataCure::Instance()

#endif