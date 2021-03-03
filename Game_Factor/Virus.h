////////////////////////////////////////////////////////////////////////////////
// Virus Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Virus_H_
#define _Virus_H_

#include "CellEntity.h"

class CVirus : public CCellEntity{
public:
	typedef enum VirusAttType {FIRSTTAIL, SECONDTAIL, FIRSTCYTOPLASM, SECONDCYTOPLASM, 
		THIRDCYTOPLASM, CORE, FIRSTMINICORE, SECONDMINICORE, THIRDMINICORE} VirusATTTYPE;
	
private:
	float m_fBodyRotVelocity;
	float m_fFirstAndSecondCytoplasmRotVelocity;
	float m_fThirdCytoplasmRotVelocity;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CVirus>* m_pStateMachine;

public:
	CVirus(CGrowth::GROWTH _eGrowth, Vector2D _vPos, Vector2D _vVelocity,
         double _dMass, double _dMaxForce, double _dMaxSpeed, double _dMaxTurnRate);
	~CVirus();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	virtual void        Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CVirus>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	float GetBodyRotVelocity(){return m_fBodyRotVelocity;}
	float GetFirstAndSecondCytoplasmRotVelocity(){return m_fFirstAndSecondCytoplasmRotVelocity;}
	float GetThirdCytoplasmRotVelocity(){return m_fThirdCytoplasmRotVelocity;}
};

#endif