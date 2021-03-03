////////////////////////////////////////////////////////////////////////////////
// Wave Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Wave_H_
#define _Wave_H_

#define WAVEGAP 800

#include "../Engine_System/OrganEntity.h"
#include "../Game_Factor/CellEntity.h"
#include "../Engine_System/StateMachine.h"

class CCellEntity;

class CWave : public COrganEntity{
private:
	CCellEntity* m_pOrigin;	// �� Effect�� ����� Entity

	bool m_bActive;

	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CWave>* m_pStateMachine;

	float m_fMaxSca;
	float m_fScaAce;

	float m_fAlphaAce;

public:
	CWave(CCellEntity* _pCell);
	~CWave();

	void Initialize();
	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.	
	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);
	virtual void Render();

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CWave>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CWave>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	bool IsActive(){return m_bActive;}
	void OnActive(){m_bActive = true;}
	void OffActive(){m_bActive = false;}

	float GetMaxSca(){return m_fMaxSca;}
	float GetScaAce(){return m_fScaAce;}
	float GetAlphaAce(){return m_fAlphaAce;}

	void SetOrigin(COrganEntity* _pEntity);

	CCellEntity* GetOrigin(){return m_pOrigin;}
};

#endif