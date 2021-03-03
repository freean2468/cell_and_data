#ifndef _World_H_
#define _World_H_

#pragma warning (disable:4786)

//------------------------------------------------------------------------
//
//  Name: CWorld.h
//
//  Desc: This is wrap class to manage objects of game contents.
//
//------------------------------------------------------------------------

#include "../Engine_System/DataParticle.h"
#include "Data.h"
#include "Vacine.h"
#include "SecretData.h"
#include "Bus.h"
#include "../Engine_Misc/CellSpaceOfPartition.h"
#include "../Engine_System/EntityFunctionTemplates.h"

class CWorld{ 
private:
	CDataParticle*						m_pDataParticle;
	std::list<CData*>					m_Data;
	std::list<CVacine*>					m_Vacine;
	std::list<CSecretData*>				m_SecretData;

	CBus*								m_pBus;

	//any obstacles
	std::vector<CObstacle*>				 m_Obstacles;

	CCellSpacePartition<CMovingEntity*>* m_pCellSpace;

	//container containing any walls in the environment
	std::vector<CWall3D>           m_Walls;

  //for the vehicles to follow
  std::vector<CPath*>            m_Paths;

  void CreateObstacles();
  void CreateWalls();

public:
	CWorld();
  ~CWorld();

  void	SetupEntities();

  void  Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

  void  Render();

	void	RenderPaths(ID3DXLine* _pLine);
	void	RenderWalls(bool _bNormalRender, ID3DXLine* _pLine);
	void	RenderMap(bool _bNormalRender);

//  void  NonPenetrationContraint(CVehicle* v){EnforceNonPenetrationConstraint(v, m_Vehicles);}

	// ---------------- Sider -----------------------
	int		LoadGameWorld();

	void	CheckCrossingDataAndVirus();
	void	CheckCrossingSecretDataAndVirus();
	void	CheckCrossingVacineAndVirus();
	void	CheckViewVacineAndData();

	void	CheckClosestEntity();

	bool	CheckDataAllDie();
	bool	CheckVacineAllDie();
	bool	CheckSecretDataAllDie();

	void	CheckIntersectionFireWall();
	bool	CheckIntersectionFireWallForAbility();
	// ----------------------------------------------

	// ---------------- ÀÌ¿ô°ü¸® ---------------------
	void TagVehiclesWithinViewRange(CDirectXEntity* _pEntity, double _dRange){
		TagNeighbors(_pEntity, m_Data, _dRange);
	}

	void TagObstaclesWithinViewRange(CDirectXEntity* _pEntity, double _dRange){
		TagNeighbors(_pEntity, m_Obstacles, _dRange);
	}
	// ----------------------------------------------

	CDataParticle*												GetDataParticle(){return m_pDataParticle;}
	std::vector<CWall3D>&									GetWalls(){return m_Walls;}    
	std::vector<CObstacle*>&							GetObstacles(){return m_Obstacles;}
	std::vector<CPath*>&									GetPaths(){return m_Paths;}
	CCellSpacePartition<CMovingEntity*>*	GetCellSpace(){return m_pCellSpace;}
	CBus*																	GetBus(){return m_pBus;}
	std::list<CData*>&										GetData(){return m_Data;}
	std::list<CVacine*>&									GetVacine(){return m_Vacine;}
	std::list<CSecretData*>								GetSecretData(){return m_SecretData;}
};

#endif