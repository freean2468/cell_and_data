////////////////////////////////////////////////////
// Virus가 가질 상태들
////////////////////////////////////////////////////
#ifndef _VirusOwnedStates_H_
#define _VirusOwnedStates_H_

class CVirus;

///////////////////////////////////////////////////////////
// Normal State
///////////////////////////////////////////////////////////
class CVirusNormal : public CState<CVirus>{
private:  
	CVirusNormal(){}

	//copy ctor and assignment should be private
	CVirusNormal(const CVirusNormal&);
	CVirusNormal& operator=(const CVirusNormal&);
 
public:
  //this is a singleton
	static CVirusNormal* Instance(){
		static CVirusNormal instance;

		return &instance;
	}

	virtual void Enter(CVirus* _pVirus);

	virtual void Execute(CVirus* _pVirus);

	virtual void Exit(CVirus* _pVirus);

	virtual bool OnMessage(CVirus* agent, const Telegram& _rMsg);
};

#define VirusNormal CVirusNormal::Instance()

///////////////////////////////////////////////////////////
// ControlIn State
///////////////////////////////////////////////////////////
class CVirusControlIn : public CState<CVirus>{
private:  
	CVirusControlIn(){}

	//copy ctor and assignment should be private
	CVirusControlIn(const CVirusControlIn&);
	CVirusControlIn& operator=(const CVirusControlIn&);
 
public:
  //this is a singleton
	static CVirusControlIn* Instance(){
		static CVirusControlIn instance;

		return &instance;
	}

	virtual void Enter(CVirus* _pVirus);

	virtual void Execute(CVirus* _pVirus);

	virtual void Exit(CVirus* _pVirus);

	virtual bool OnMessage(CVirus* agent, const Telegram& _rMsg);
};

#define VirusControlIn CVirusControlIn::Instance()

///////////////////////////////////////////////////////////
// ControlOut State
///////////////////////////////////////////////////////////
class CVirusControlOut : public CState<CVirus>{
private:  
	CVirusControlOut(){}

	//copy ctor and assignment should be private
	CVirusControlOut(const CVirusControlOut&);
	CVirusControlOut& operator=(const CVirusControlOut&);
 
public:
  //this is a singleton
	static CVirusControlOut* Instance(){
		static CVirusControlOut instance;

		return &instance;
	}

	virtual void Enter(CVirus* _pVirus);

	virtual void Execute(CVirus* _pVirus);

	virtual void Exit(CVirus* _pVirus);

	virtual bool OnMessage(CVirus* agent, const Telegram& _rMsg);
};

#define VirusControlOut CVirusControlOut::Instance()

///////////////////////////////////////////////////////////
// Growing State
///////////////////////////////////////////////////////////
class CVirusGrowing : public CState<CVirus>{
private:  
	CVirusGrowing(){}

	//copy ctor and assignment should be private
	CVirusGrowing(const CVirusGrowing&);
	CVirusGrowing& operator=(const CVirusGrowing&);
 
public:
  //this is a singleton
	static CVirusGrowing* Instance(){
		static CVirusGrowing instance;

		return &instance;
	}

	virtual void Enter(CVirus* _pVirus);

	virtual void Execute(CVirus* _pVirus);

	virtual void Exit(CVirus* _pVirus);

	virtual bool OnMessage(CVirus* agent, const Telegram& _rMsg);
};

#define VirusGrowing CVirusGrowing::Instance()

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
class CVirusDie : public CState<CVirus>{
private:  
	CVirusDie(){}

	//copy ctor and assignment should be private
	CVirusDie(const CVirusDie&);
	CVirusDie& operator=(const CVirusDie&);
 
public:
  //this is a singleton
	static CVirusDie* Instance(){
		static CVirusDie instance;

		return &instance;
	}

	virtual void Enter(CVirus* _pVirus);

	virtual void Execute(CVirus* _pVirus);

	virtual void Exit(CVirus* _pVirus);

	virtual bool OnMessage(CVirus* agent, const Telegram& _rMsg);
};

#define VirusDie CVirusDie::Instance()

#endif