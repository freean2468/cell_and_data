////////////////////////////////////////////////////////////////////////////////
// Infection Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Infection_H_
#define _Infection_H_

#define INFECTIONGAP 8000

#include "../Engine_System/OrganEntity.h"
#include "Data.h"

class CData;

class CInfection : public COrganEntity{
public:
	typedef enum InfectionAttType {FIRSTMINICORE, SECONDMINICORE} INFECTIONATTTYPE;

private:
	CData* m_pData;

	float m_fMaxSca;
	float m_fFrequency;

	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CInfection>* m_pStateMachine;

	float m_fEffectFirstMax;
	float m_fEffectSecondMax;

	float m_fEffectFirstFrequency;
	float m_fEffectSecondFrequency;

public:
	CInfection(CData* _pData);
	~CInfection();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.	
	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CInfection>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CInfection>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	void SetOrigin(CBody* p_pBody){
		GetBody()->GetPriPos()->x = p_pBody->GetPriPos()->x;
		GetBody()->GetPriPos()->y = p_pBody->GetPriPos()->y;

		GetBody()->GetPriRot()->z = p_pBody->GetPriRot()->z;
	}

	CData* GetOrigin(){return m_pData;}

	float GetMaxSca(){return m_fMaxSca;}
	float GetFrequency(){return m_fFrequency;}

	float GetEffectFirstMax(){return m_fEffectFirstMax;}
	float	GetEffectSecondMax(){return m_fEffectSecondMax;}

	float GetEffectFirstFrequency(){return m_fEffectFirstFrequency;}
	float GetEffectSecondFrequency(){return m_fEffectSecondFrequency;}
};

#endif