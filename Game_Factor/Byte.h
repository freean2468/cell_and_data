////////////////////////////////////////////////////////////////////////////////
// Byte Ŭ����
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

	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CByte>* m_pStateMachine;

public:
	CByte(CData* _pData);
	~CByte();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.	
	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
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