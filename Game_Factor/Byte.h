////////////////////////////////////////////////////////////////////////////////
// Byte 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Byte_H_
#define _Byte_H_

#include "../Engine_System/EngineManager.h"
#include "../Engine_System/OrganEntity.h"
#include "Data.h"
#include "../Engine_System/StateMachine.h"

class CData;

class CByte : public COrganEntity{
public: 
	typedef enum ByteState {BYTE_INACTIVE, BYTE_DELETE, BYTE_EXHALE} BYTESTATE;

private:
	CData* m_pData;

	BYTESTATE m_eState;

	int m_nCapacity;

	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CByte>* m_pStateMachine;

public:
	CByte(CData* _pData);
	~CByte();

	// 이것은 반드시 설치되어야 한다.	
	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CByte>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CByte>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	void SetOrigin();

	CData* GetOrigin(){return m_pData;}

	BYTESTATE GetState(){return m_eState;}
	void SetState(BYTESTATE _eState){m_eState = _eState;}

	int GetCapacity(){return m_nCapacity;}
};

#endif