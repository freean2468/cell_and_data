////////////////////////////////////////////////////////////////////////////////
// Vacine 클래스
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
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CVacine>* m_pStateMachine;

public:
	CVacine(int _nEntityType, CGrowth::GROWTH _eGrowth, Vector2D _vPos, Vector2D _vVelocity,
         double _dMass, double _dMaxForce, double _dMaxSpeed, double _dMaxTurnRate);
	~CVacine();

	// 이것은 반드시 설치되어야 한다.
	virtual void        Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
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