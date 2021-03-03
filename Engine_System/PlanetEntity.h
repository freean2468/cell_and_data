#ifndef _PlanetEntity_H_
#define _PlanetEntity_H_

#include "MovingEntity.h"
#include "Gravity.h"
#include "StateMachine.h"

class CPlanetEntity : public CMovingEntity{
private:
	CGravity* m_pGravity;
	CStateMachine<CPlanetEntity>* m_pStateMachine;

public:
	CPlanetEntity(float _fPlanetRadius, bool _bStatic, int _nEntityType = -1);
	~CPlanetEntity();

	virtual void Update(double _dTImeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	CGravity* GetGravity(){return m_pGravity;}

	CStateMachine<CPlanetEntity>* GetFSM(){return m_pStateMachine;}
};

#endif