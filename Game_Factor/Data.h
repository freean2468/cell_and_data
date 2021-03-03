////////////////////////////////////////////////////////////////////////////////
// Data 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Data_H_
#define _Data_H_

#include "CellEntity.h"
#include "Byte.h"
#include "Infection.h"
#include <vector>

class CByte;
class CInfection;

#define VARIATIONTIME 8000

class CData : public CCellEntity{
public:
	typedef enum States {NORMAL, INFECTION, VARIATION, DYING, ABSORPTION} STATES;
	typedef enum DataType {TYPEZERO, TYPEONE} DATATYPE;
	typedef enum DataAttType {CORE, FIRSTMINICORE, SECONDMINICORE, DATA} DATAATTTYPE;

private:
	STATES m_eState;
	STATES m_eOldState;
	DATATYPE m_eDataType;

	std::list<CInfection*>	m_pInfections;

	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CData>* m_pStateMachine;

	bool m_bVariation;

	CTimer* m_pVariationTimer;
	CTimer* m_pToDieTimer;

	std::vector<CByte*> m_Bytes;
	int	m_nByteIndex;
	CTimer* m_pExhaleGap;

public:
	CData(int _nEntityType, int _nGrowth, Vector2D _vPos, Vector2D _vVelocity,
         double _dMass, double _dMaxForce, double _dMaxSpeed, double _dMaxTurnRate);
	~CData();

	void Initialize();
	void InsertInfection(CData* _pData);

	// 이것은 반드시 설치되어야 한다.
	void StateUpdate();
	virtual	void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);
	virtual void Render();

	virtual	void OrganUpdate();

	void InfectionRender();

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CData>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	STATES GetState(){return m_eState;}
	void SetState(STATES p_eState){if(m_eOldState != m_eState){m_eOldState = m_eState;} m_eState = p_eState;}
	void SetOldState(){m_eState = m_eOldState;}

	CTimer* GetVariationTimer(){return m_pVariationTimer;}
	void SetVariationTimer(DWORD p_dwTime){m_pVariationTimer = new CTimer(p_dwTime);}

	CTimer* GetToDieTimer(){return m_pToDieTimer;}
	void SetToDieTimer(DWORD p_dwTime){m_pToDieTimer = new CTimer(p_dwTime);}

	std::vector<CByte*>* GetBytes(){return &m_Bytes;}
	std::list<CInfection*>* GetInfectionList(){return &m_pInfections;}

	void UpdateBytes();
	void RenderBytes();

	int GetByteIndex(){return m_nByteIndex;}
};

#endif