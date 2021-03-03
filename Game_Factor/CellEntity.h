#ifndef _CellEntity_H_
#define _CellEntity_H_

#include <list>
#include "../Engine_System/Vehicle.h"
#include "Wave.h"
#include "Growth.h"

class CWave;

class CCellEntity : public CVehicle{
private:
	std::list<CWave*>						m_pWaves;

	bool m_bDivision;

	// Effect Wave¸¦ À§ÇÑ Timer
	CTimer*									m_pTimer;

	CGrowth*								m_pGrowth;

	double									m_dCellSpeedLimit;

public:
	CCellEntity(int _nEntityType, CGrowth::GROWTH _eGrowth, Vector2D _vPos, Vector2D _vVelocity,
							double _dMass, double _dMaxForce, double _dMaxSpeed, double _dMaxTurnRate);
	~CCellEntity();

	virtual void Render();
	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	void MovingOfCell();

	void InsertWave(CCellEntity* _pAgent);

	void WaveSetting();
	void WaveInitialize();
	void WaveUpdate();
	void WaveRender();
	void WaveDie();

	std::list<CWave*>* GetWaveList(){return &m_pWaves;}

	CTimer*  GetTimer(){return m_pTimer;}
	CGrowth* GetGrowth(){return m_pGrowth;}
	void		 SetCellSpeedLimit(double _dLimit){m_dCellSpeedLimit = _dLimit;}
};

#endif