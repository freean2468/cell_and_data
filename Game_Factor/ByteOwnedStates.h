////////////////////////////////////////////////////
// Byte가 가질 상태들
////////////////////////////////////////////////////
#ifndef _ByteOwnedStates_H_
#define _ByteOwnedStates_H_

#include "../Engine_System/State.h"
#include "Byte.h"

///////////////////////////////////////////////////////////
// InActive State
///////////////////////////////////////////////////////////
class CByteInActive : public CState<CByte>{
private:  
	CByteInActive(){}

	//copy ctor and assignment should be private
	CByteInActive(const CByteInActive&);
	CByteInActive& operator=(const CByteInActive&);
 
public:
  //this is a singleton
	static CByteInActive* Instance(){
		static CByteInActive instance;

		return &instance;
	}

	virtual void Enter(CByte* _pByte);

	virtual void Execute(CByte* _pByte);

	virtual void Exit(CByte* _pByte);

	virtual bool OnMessage(CByte* agent, const Telegram& _rMsg);
};

#define ByteInActive CByteInActive::Instance()

///////////////////////////////////////////////////////////
// Delete State
///////////////////////////////////////////////////////////
class CByteDelete : public CState<CByte>{
private:
	float m_fPercentage;
	Vector2D m_vDist;

private:  
	CByteDelete(){}

	//copy ctor and assignment should be private
	CByteDelete(const CByteDelete&);
	CByteDelete& operator=(const CByteDelete&);
 
public:
  //this is a singleton
	static CByteDelete* Instance(){
		static CByteDelete instance;

		return &instance;
	}

	virtual void Enter(CByte* _pByte);

	virtual void Execute(CByte* _pByte);

	virtual void Exit(CByte* _pByte);

	virtual bool OnMessage(CByte* agent, const Telegram& _rMsg);
};

#define ByteDelete CByteDelete::Instance()

///////////////////////////////////////////////////////////
// Exhale State
///////////////////////////////////////////////////////////
class CByteExhale : public CState<CByte>{
private:
	Vector2D m_vDist;
	D3DXVECTOR3 m_vOldPos;

	float m_fPercentage;
	double m_nLength;

private:  
	CByteExhale(){}

	//copy ctor and assignment should be private
	CByteExhale(const CByteExhale&);
	CByteExhale& operator=(const CByteExhale&);
 
public:
  //this is a singleton
	static CByteExhale* Instance(){
		static CByteExhale instance;

		return &instance;
	}

	virtual void Enter(CByte* _pByte);

	virtual void Execute(CByte* _pByte);

	virtual void Exit(CByte* _pByte);

	virtual bool OnMessage(CByte* agent, const Telegram& _rMsg);
};

#define ByteExhale CByteExhale::Instance()

#endif