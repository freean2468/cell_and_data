////////////////////////////////////////////////////////////////////////////////
// Vacine Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Vacine_H_
#define _Vacine_H_

#include "CellEntity.h"
#include "Data.h"

class CVacine : public CCellEntity{
public:
	typedef enum VacineAttType {FIRSTTAIL, SECONDTAIL, FIRSTCYTOPLASM, SECONDCYTOPLASM, 
		THIRDCYTOPLASM, CORE, FIRSTMINICORE, SECONDMINICORE, THIRDMINICORE} VacineATTTYPE;
	
private:
	float		m_fBodyRotVelocity;
	float		m_fFirstAndSecondCytoplasmRotVelocity;
	float		m_fThirdCytoplasmRotVelocity;

	CData* m_pData;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CVacine>* m_pStateMachine;

public:
	CVacine(int _nEntityType, CGrowth::GROWTH _eGrowth, Vector2D _vPos, Vector2D _vVelocity,
         double _dMass, double _dMaxForce, double _dMaxSpeed, double _dMaxTurnRate);
	~CVacine();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	virtual void        Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CVacine>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	float GetBodyRotVelocity(){return m_fBodyRotVelocity;}
	float GetFirstAndSecondCytoplasmRotVelocity(){return m_fFirstAndSecondCytoplasmRotVelocity;}
	float GetThirdCytoplasmRotVelocity(){return m_fThirdCytoplasmRotVelocity;}

	void SetTarget(CData* _pData){m_pData = _pData;}
	CData* GetTarget(){return m_pData;}
};

#endif