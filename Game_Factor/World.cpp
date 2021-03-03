#include "World.h"
#include "WorldManager.h"
#include "Virus.h"
#include "Controller.h"
#include "UIManager.h"
#include "../Engine_System/EntityManager.h"
#include "../Engine_System/EntityType.h"
#include "../Engine_Math&Physics/Rectangle.h"
#include "SecretDataOwnedStates.h"
#include "VirusOwnedStates.h"
#include "DataOwnedStates.h"
#include "../Engine_Math&Physics/Geometry.h"

//------------------------------- ctor -----------------------------------
//------------------------------------------------------------------------
CWorld::CWorld() :m_Data(NULL),
				m_pDataParticle(NULL),
				m_Vacine(NULL),
				m_Obstacles(NULL),
				m_pCellSpace(NULL),
				m_Walls(NULL),
				m_pBus(NULL),
				m_Paths(NULL)
{
}

//-------------------------------- dtor ----------------------------------
//------------------------------------------------------------------------
CWorld::~CWorld(){
	for (unsigned int ob=0; ob<m_Obstacles.size(); ++ob){
    delete m_Obstacles[ob];
  }

	for (unsigned int i=0; i<m_Paths.size(); ++i){
    delete m_Paths[i];
  }

	std::list<CData*>::iterator t_itrData;

	for (t_itrData = m_Data.begin(); t_itrData != m_Data.end(); ++t_itrData){
		delete *t_itrData;
  }

	std::list<CVacine*>::iterator t_itrVacine;

	for (t_itrVacine = m_Vacine.begin(); t_itrVacine != m_Vacine.end(); ++t_itrVacine){
		delete *t_itrVacine;
  }

	std::list<CSecretData*>::iterator t_itrSecret;

	for(t_itrSecret = m_SecretData.begin(); t_itrSecret != m_SecretData.end(); ++t_itrSecret){
		delete *t_itrSecret;
	}

	Delete< CCellSpacePartition< CMovingEntity* >* >(m_pCellSpace);

	Delete<CBus*>(m_pBus);

	DU::Delete<CDataParticle*>(m_pDataParticle);
}

//----------------------------- Load -------------------------------------
//------------------------------------------------------------------------
int CWorld::LoadGameWorld(){
	if(!WorldMgr->m_b1){
		//setup the spatial subdivision class
		m_pCellSpace = new CCellSpacePartition<CMovingEntity*>(WorldMgr->GetMapParam()->WorldWidth, 
																														WorldMgr->GetMapParam()->WorldHeight, 
																														WorldMgr->GetMapParam()->CellSizeX,
																														WorldMgr->GetMapParam()->CellSizeY,
																														WorldMgr->GetMapParam()->m_nSumData);

		WorldMgr->m_b1 = true;
		return 20;
	}

	if(!WorldMgr->m_b2){		
		CVirus* t_pVirus = new CVirus(CGrowth::FIRST,
									WorldMgr->GetMapParam()->m_vStart,										//initial position
									Vector2D(0,0),																			//velocity
									WorldMgr->GetSteeringParam()->VehicleMass,          //mass
									WorldMgr->GetSteeringParam()->MaxSteeringForce,     //max force
									WorldMgr->GetSteeringParam()->MaxSpeed,             //max velocity
									WorldMgr->GetSteeringParam()->MaxTurnRatePerSecond);

		t_pVirus->SmoothingOn();
		t_pVirus->GetSteering()->FlockingOff();
		if(WorldMgr->GetMapParam()->m_bCreateWall)	t_pVirus->GetSteering()->WallAvoidanceOn();
		if(WorldMgr->GetMapParam()->m_bCreateObstacle)	t_pVirus->GetSteering()->ObstacleAvoidanceOn();
		t_pVirus->GetSteering()->ControlledOn();

		//add it to the cell subdivision
		m_pCellSpace->AddEntity(t_pVirus);

		Controller->SetController(t_pVirus);

		EntityMgr->RegisterEntity(t_pVirus);

		WorldMgr->m_b2 = true;		
		return 40;
	}

	if(!WorldMgr->m_b3){
		WorldMgr->m_b3 = true;
		
		DU::BoundingBox t_Bound;

		t_Bound._min.x = (float)-WorldMgr->GetMapParam()->WorldWidth/2;	t_Bound._min.y = (float)-WorldMgr->GetMapParam()->WorldHeight/2;	t_Bound._min.z = -100.0f;
		t_Bound._max.x = (float)WorldMgr->GetMapParam()->WorldWidth/2;		t_Bound._max.y = (float)WorldMgr->GetMapParam()->WorldHeight/2;		t_Bound._max.z = 100.0f;

		m_pDataParticle = new CDataParticle(&t_Bound, WorldMgr->GetMapParam()->m_nDataParticle);
		return 60;
	}

	if(!WorldMgr->m_b5){
		for (int i = 0; i<WorldMgr->GetMapParam()->m_nFirstData;++i){
			int x = RandInt(0, WorldMgr->GetMapParam()->WorldWidth/2-50);	int y = RandInt(0, WorldMgr->GetMapParam()->WorldHeight/2-50);
			if(RandBool())	x*=-1;	if(RandBool())	y*=-1;

			//determine a random starting position
			Vector2D SpawnPos = Vector2D(x, y);

			CData* pData = new CData(DATA,
									1,
									SpawnPos,                 //initial position
									Vector2D(0,0),            //velocity
									WorldMgr->GetSteeringParam()->VehicleMass,          //mass
									WorldMgr->GetSteeringParam()->MaxSteeringForce,     //max force
									WorldMgr->GetSteeringParam()->MaxSpeed,             //max velocity
									WorldMgr->GetSteeringParam()->MaxTurnRatePerSecond);

			m_Data.push_back(pData);

			m_pCellSpace->AddEntity(pData);
		}
		WorldMgr->m_b5 = true;
		return 60;
	}

	if(!WorldMgr->m_b6){
		//setup the Dataes
		for (int i = 0; i<WorldMgr->GetMapParam()->m_nSecondData;++i){
			int x = RandInt(0, WorldMgr->GetMapParam()->WorldWidth/2-50);	int y = RandInt(0, WorldMgr->GetMapParam()->WorldHeight/2-50);
			if(RandBool())				x*=-1;						if(RandBool())				y*=-1;

			//determine a random starting position
			Vector2D SpawnPos = Vector2D(x, y);

			CData* pData = new CData(DATA,
																2,
																SpawnPos,                 //initial position
																Vector2D(0,0),            //velocity
																WorldMgr->GetSteeringParam()->VehicleMass,          //mass
																WorldMgr->GetSteeringParam()->MaxSteeringForce,     //max force
																WorldMgr->GetSteeringParam()->MaxSpeed,             //max velocity
																WorldMgr->GetSteeringParam()->MaxTurnRatePerSecond);//scale

			m_Data.push_back(pData);

			//add it to the cell subdivision
			m_pCellSpace->AddEntity(pData);
		}
		WorldMgr->m_b6 = true;
		return 60;
	}

	if(!WorldMgr->m_b7){
		//setup the Dataes
		for (int i = 0; i<WorldMgr->GetMapParam()->m_nThirdData;++i){
			int x = RandInt(0, WorldMgr->GetMapParam()->WorldWidth/2-50);	int y = RandInt(0, WorldMgr->GetMapParam()->WorldHeight/2-50);
			if(RandBool())				x*=-1;						if(RandBool())				y*=-1;

			//determine a random starting position
			Vector2D SpawnPos = Vector2D(x, y);

			CData* pData = new CData(DATA,
																3,
																SpawnPos,                 //initial position
																Vector2D(0,0),            //velocity
																WorldMgr->GetSteeringParam()->VehicleMass,          //mass
																WorldMgr->GetSteeringParam()->MaxSteeringForce,     //max force
																WorldMgr->GetSteeringParam()->MaxSpeed,             //max velocity
																WorldMgr->GetSteeringParam()->MaxTurnRatePerSecond);//scale

			m_Data.push_back(pData);

			//add it to the cell subdivision
			m_pCellSpace->AddEntity(pData);
		}
		WorldMgr->m_b7 = true;
		return 60;
	}

	if(!WorldMgr->m_b8){
		//setup the Dataes
		for (int i = 0; i<WorldMgr->GetMapParam()->m_nFirstVacine;++i){
			int x = RandInt(50, WorldMgr->GetMapParam()->WorldWidth/2-50);	int y = RandInt(50, WorldMgr->GetMapParam()->WorldHeight/2-50);
			if(RandBool())				x*=-1;						if(RandBool())				y*=-1;

			//determine a random starting position
			Vector2D SpawnPos = Vector2D(x, y);

			CVacine* pVacine = new CVacine(VACINE,
																			CGrowth::FIRST,
																			SpawnPos,                 //initial position
																			Vector2D(0,0),            //velocity
																			WorldMgr->GetSteeringParam()->VehicleMass,          //mass
																			WorldMgr->GetSteeringParam()->MaxSteeringForce,     //max force
																			WorldMgr->GetSteeringParam()->MaxSpeed,             //max velocity
																			WorldMgr->GetSteeringParam()->MaxTurnRatePerSecond);

			pVacine->SmoothingOn();
			pVacine->GetSteering()->WanderOn();
			if(WorldMgr->GetMapParam()->m_bCreateWall)	pVacine->GetSteering()->WallAvoidanceOn();
			if(WorldMgr->GetMapParam()->m_bCreateObstacle)	pVacine->GetSteering()->ObstacleAvoidanceOn();

			m_Vacine.push_back(pVacine);

			m_pCellSpace->AddEntity(pVacine);
		}
		WorldMgr->m_b8 = true;
		return 60;
	}

	if(!WorldMgr->m_b9){
		//setup the Dataes
		for (int i = 0; i<WorldMgr->GetMapParam()->m_nSecondVacine;++i){
			int x = RandInt(50, WorldMgr->GetMapParam()->WorldWidth/2-50);	int y = RandInt(100, WorldMgr->GetMapParam()->WorldHeight/2-50);
			if(RandBool())				x*=-1;						if(RandBool())				y*=-1;

			//determine a random starting position
			Vector2D SpawnPos = Vector2D(x, y);

			CVacine* pVacine = new CVacine(VACINE,
																			CGrowth::SECOND,
																			SpawnPos,                 //initial position
																			Vector2D(0,0),            //velocity
																			WorldMgr->GetSteeringParam()->VehicleMass,          //mass
																			WorldMgr->GetSteeringParam()->MaxSteeringForce,     //max force
																			WorldMgr->GetSteeringParam()->MaxSpeed,             //max velocity
																			WorldMgr->GetSteeringParam()->MaxTurnRatePerSecond);//scale

			pVacine->SmoothingOn();
			pVacine->GetSteering()->WanderOn();
			if(WorldMgr->GetMapParam()->m_bCreateWall)	pVacine->GetSteering()->WallAvoidanceOn();
			if(WorldMgr->GetMapParam()->m_bCreateObstacle)	pVacine->GetSteering()->ObstacleAvoidanceOn();

			m_Vacine.push_back(pVacine);

			m_pCellSpace->AddEntity(pVacine);
		}
		WorldMgr->m_b9 = true;
		return 60;
	}

	 for(std::list<CData*>::iterator t_itr = m_Data.begin(); t_itr != m_Data.end(); ++t_itr){
		(*t_itr)->SmoothingOn();
		(*t_itr)->GetSteering()->FlockingOn();
    (*t_itr)->GetSteering()->EvadeOn(Controller->GetController());
		if(WorldMgr->GetMapParam()->m_bCreateWall)	(*t_itr)->GetSteering()->WallAvoidanceOn();
		if(WorldMgr->GetMapParam()->m_bCreateObstacle)	(*t_itr)->GetSteering()->ObstacleAvoidanceOn();
  }
 
	m_pBus = new CBus();

	if(!WorldMgr->m_b10){
		CRectangle t_Rectangle;
		int x,y;

		for (int i = 0; i<WorldMgr->GetMapParam()->m_nFirstSecret;++i){
			do{
				x = RandInt(0, WorldMgr->GetMapParam()->WorldWidth/2-50);	y = RandInt(0, WorldMgr->GetMapParam()->WorldHeight/2-50);
				if(RandBool())		x*=-1;				
				if(RandBool())		y*=-1;

				CSecretData t_Secret(CGrowth::FIRST, Vector2D(x, y));

				t_Rectangle = CRectangle((float)(x - t_Secret.GetRadius()*4.2), 
																	(float)(x + t_Secret.GetRadius()*4.2), 
																	(float)(y - t_Secret.GetRadius()*4.2), 
																	(float)(y + t_Secret.GetRadius()*4.2));
			}while(t_Rectangle.InternalPoint(&Controller->GetController()->GetPos2D()));

			m_SecretData.push_back(new CSecretData(CGrowth::FIRST, Vector2D(x, y)));
		}

		WorldMgr->m_b10 = true;
		return 60;
	}

  //create any obstacles or walls  
	if(WorldMgr->GetMapParam()->m_bCreateWall)
		CreateWalls();

	if(WorldMgr->GetMapParam()->m_bCreateObstacle)
		CreateObstacles();

	if(!WorldMgr->m_b4){
		for(unsigned int i = 0; i < WorldMgr->GetMapParam()->m_VacineWayPoints.size(); ++i){ 
			std::list<Vector2D> t_nWayPoints = WorldMgr->GetMapParam()->m_VacineWayPoints.at(i);

			m_Paths.push_back(new CPath());
			m_Paths.at(m_Paths.size()-1)->Set(t_nWayPoints);

			CVacine* t_pVacine = new CVacine(VACINE,
																				CGrowth::FIRST,
																				m_Paths.at(m_Paths.size()-1)->CurrentWaypoint(),			//initial position
																				Vector2D(0,0),            //velocity
																				WorldMgr->GetSteeringParam()->VehicleMass,          //mass
																				WorldMgr->GetSteeringParam()->MaxSteeringForce,     //max force
																				WorldMgr->GetSteeringParam()->MaxSpeed,             //max velocity
																				WorldMgr->GetSteeringParam()->MaxTurnRatePerSecond);

			t_pVacine->SmoothingOn();
			t_pVacine->GetSteering()->FollowPathOn();
			t_pVacine->GetSteering()->SetPath(m_Paths.at(m_Paths.size()-1)->GetPath());
			t_pVacine->GetSteering()->OnPathActive();

			m_Vacine.push_back(t_pVacine);

			m_pCellSpace->AddEntity(t_pVacine);
		}

		for(unsigned int i = 0; i < WorldMgr->GetMapParam()->m_DataWayPoints.size(); ++i){ 
			std::list<Vector2D> t_nWayPoints = WorldMgr->GetMapParam()->m_DataWayPoints.at(i);
			std::list<Vector2D>::iterator t_itr = t_nWayPoints.begin();			

			CData* t_pData = new CData(DATA,
																	CGrowth::FIRST,
																	*t_itr,										//initial position
																	Vector2D(0,0),            //velocity
																	WorldMgr->GetSteeringParam()->VehicleMass,          //mass
																	WorldMgr->GetSteeringParam()->MaxSteeringForce,     //max force
																	WorldMgr->GetSteeringParam()->MaxSpeed,             //max velocity
																	WorldMgr->GetSteeringParam()->MaxTurnRatePerSecond);

			m_Paths.push_back(new CPath());

			for(t_itr; t_itr != t_nWayPoints.end(); ++t_itr){
				m_Paths.at(m_Paths.size()-1)->GetPath().push_back(*t_itr);
			}

			t_pData->SmoothingOn();
			t_pData->GetSteering()->FollowPathOn();
			t_pData->GetSteering()->SetPath(m_Paths.at(m_Paths.size()-1)->GetPath());

			m_Data.push_back(t_pData);

			m_pCellSpace->AddEntity(t_pData);
		}

		WorldMgr->m_b4 = true;
	}

	return 100;
}

//----------------------------- Update -----------------------------------
//------------------------------------------------------------------------
void CWorld::Update(double _dTimeElapsed){ 
  if (WorldMgr->IsPaused()) return;

  //create a CSmoother to smooth the framerate
  const int t_nSampleRate = 10;
  static CSmoother<double> FrameRateSmoother(t_nSampleRate, 0.0);

	// Check
	if(Controller->GetController()->IsAlive()){
		CheckCrossingSecretDataAndVirus();
		this->CheckCrossingVacineAndVirus();
		this->CheckCrossingDataAndVirus();
		CheckViewVacineAndData();
		CheckClosestEntity();
		CheckIntersectionFireWall();
	}

  //update the Data
	std::list<CData*>::iterator t_itrData;

  for (t_itrData = m_Data.begin(); t_itrData != m_Data.end(); ++t_itrData){
		if(!(*t_itrData)->IsAlive()) continue;

		(*t_itrData)->Update(_dTimeElapsed);
  }

	//update the Vacine
	std::list<CVacine*>::iterator t_itrVacine;

  for (t_itrVacine = m_Vacine.begin(); t_itrVacine != m_Vacine.end(); ++t_itrVacine){
		if(!(*t_itrVacine)->IsAlive()) continue;

		(*t_itrVacine)->Update(_dTimeElapsed);
  }
	
	Controller->GetController()->Update(_dTimeElapsed);

	m_pDataParticle->update(SYSTEM_FRAME_INTERVAL_VER_60);
}
  
//--------------------------- CreateWalls --------------------------------
//
//  creates some walls that form an enclosure for the steering agents.
//  used to demonstrate several of the steering behaviors
//------------------------------------------------------------------------
void CWorld::CreateWalls(){
	//  create the walls  
  double CornerSize = 0.2;
  double vDist = WorldMgr->GetMapParam()->WorldHeight;
  double hDist = WorldMgr->GetMapParam()->WorldWidth;
  
	const int NumWallVerts = 8;

  //const int NumWallVerts = 4;

  Vector2D walls[NumWallVerts] = {Vector2D(hDist*CornerSize-hDist/2, -vDist/2),
                                   Vector2D(hDist/2-hDist*CornerSize, -vDist/2),
                                   Vector2D(hDist/2, vDist*CornerSize-vDist/2),
                                   Vector2D(hDist/2, vDist/2-vDist*CornerSize),
                                         
                                   Vector2D(hDist/2-hDist*CornerSize, vDist/2),
                                   Vector2D(hDist*CornerSize-hDist/2, vDist/2),
                                   Vector2D(-hDist/2, vDist/2-vDist*CornerSize),
                                   Vector2D(-hDist/2, vDist*CornerSize-vDist/2)};
  
  for (int w=0; w<NumWallVerts-1; ++w){
    m_Walls.push_back(CWall3D(walls[w], walls[w+1]));
  }

  m_Walls.push_back(CWall3D(walls[NumWallVerts-1], walls[0]));
}

//--------------------------- CreateObstacles -----------------------------
//
//  Sets up the vector of obstacles with random positions and sizes. Makes
//  sure the obstacles do not overlap
//------------------------------------------------------------------------
void CWorld::CreateObstacles(){
  ////create a number of randomly sized tiddlywinks
  //for (int o=0; o<BaseParamLdr->NumObstacles; ++o){   
  //  bool bOverlapped = true;

  //  //keep creating tiddlywinks until we find one that doesn't overlap
  //  //any others.Sometimes this can get into an endless loop because the
  //  //CObstacle has nowhere to fit. We test for this case and exit accordingly

  //  int NumTrys = 0; 
		//int NumAllowableTrys = 100;

  //  while (bOverlapped){
  //    NumTrys++;

  //    if (NumTrys > NumAllowableTrys) return;
  //    
  //    double	t_dResize = RandInt((int)BaseParamLdr->MinObstacleRadius, (int)BaseParamLdr->MaxObstacleRadius);
		//	t_dResize += 1; t_dResize/=40;

  //    const int border                 = 50;
  //    const int MinGapBetweenObstacles = 60;

		//	int x = RandInt(border, m_nClientXHalf-border);
		//	int y = RandInt(border, m_nClientYHalf-border);

		//	if(RandBool())				x*=-1;
		//	if(RandBool())				y*=-1;

  //    CObstacle* ob = new CObstacle(x,y,t_dResize);

  //    if (!CollisionMgr->Overlapped(ob, MinGapBetweenObstacles)){
  //      //its not overlapped so we can add it
  //      m_Obstacles.push_back(ob);

  //      bOverlapped = false;
  //    }
  //    else{
  //      delete ob;
  //    }
  //  }
  //}
}

//------------------------------ Render ----------------------------------
//------------------------------------------------------------------------
void CWorld::Render(){
	RenderMap(false);

	Vector2D t_vPos;

	std::list<CData*>::iterator t_itrData;

	std::list<CSecretData*>::iterator t_itrSecret;

	for(t_itrSecret = m_SecretData.begin(); t_itrSecret != m_SecretData.end(); ++t_itrSecret){
		if(!(*t_itrSecret)->IsAlive()) continue;
		if(!EngineMgr->IsViewOut((*t_itrSecret)->GetBody()->GetPriPos())){
			(*t_itrSecret)->Update();
		}
	}

	m_pBus->Update();

  //render the Data
  for (t_itrData = m_Data.begin(); t_itrData != m_Data.end(); ++t_itrData){
		if(!(*t_itrData)->IsAlive()) continue;
		if(!EngineMgr->IsViewOut((*t_itrData)->GetPos3D())){
			(*t_itrData)->Render();  
		}
  }  

	std::list<CVacine*>::iterator t_itrVacine;

	//render the Vacine
  for (t_itrVacine = m_Vacine.begin(); t_itrVacine != m_Vacine.end(); ++t_itrVacine){
		if(!(*t_itrVacine)->IsAlive()) continue;
		if(!EngineMgr->IsViewOut((*t_itrVacine)->GetPos3D())){
			(*t_itrVacine)->Render();  
		}
  }  

	if(!Controller->GetController()->IsHide()){
		Controller->GetController()->Render();
	}

	m_pDataParticle->render();
}

void	CWorld::RenderPaths(ID3DXLine* _pLine){
	for(unsigned int i = 0; i < m_Paths.size(); ++i){
		m_Paths.at(i)->Render(_pLine, &D3DXCOLOR(-1.0f, -1.0f, 1.0f, 1.0f));
	}
}

void	CWorld::RenderWalls(bool _bNormalRender, ID3DXLine* _pLine){
	for (unsigned int w=0; w<m_Walls.size(); ++w){
    m_Walls[w].Render(_pLine, &D3DXCOLOR(1.0f, 1.0f, -1.0f, 1.0f), _bNormalRender);  //true flag shows normals
  }
}

void	CWorld::RenderMap(bool _bNormalRender){
	EngineMgr->GetpDevice()->BeginScene();

	ID3DXLine* Line;

	D3DXCreateLine(EngineMgr->GetpDevice(), &Line);

	Line->SetAntialias(true);

	// ZBuffer 연산 꺼줌
	EngineMgr->GetpDevice()->SetRenderState(D3DRS_ZENABLE,FALSE);
	EngineMgr->GetpDevice()->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	m_pCellSpace->UpdateCells();		
	m_pCellSpace->RenderCells(Line);
//m_pCellSpace->RenderCellsCoordinate(EngineMgr->GetpSprite(), EngineMgr->GetpFont());

	RenderPaths(Line);

  //render walls
	if(WorldMgr->GetMapParam()->m_bCreateWall){
		Line->SetWidth(5.0f);
		Line->Begin();

		RenderWalls(false, Line);
	}

	std::list<CSecretData*>::iterator t_itr;

	for(t_itr = m_SecretData.begin(); t_itr != m_SecretData.end(); ++t_itr){
		if((*t_itr)->IsAlive())
			(*t_itr)->RenderFireWalls(false, Line);
	}

	Line->End();

	Line->Release();

	// ZBuffer 연산 켜줌
	EngineMgr->GetpDevice()->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
	EngineMgr->GetpDevice()->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	EngineMgr->GetpDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	EngineMgr->GetpDevice()->EndScene();
  
	/*if(BaseParamLdr->m_bCreateObstacle){
		for (unsigned int ob=0; ob<m_Obstacles.size(); ++ob){
			if(!EngineMgr->IsViewOut(m_Obstacles[ob]->GetBody()->GetPriPos()->x,m_Obstacles[ob]->GetBody()->GetPriPos()->y))
				m_Obstacles[ob]->RenderOrgan();
		}
	}*/
}

// 충돌검출
void	CWorld::CheckCrossingDataAndVirus(){
	std::list<CData*>::const_iterator t_Itr;

	Vector2D ToEntity;
	double DistFromEachOther;
	double AmountOfOverLap;
	CVirus* t_pVirus = Controller->GetController();
	std::vector<CData*>* t_pCrossingData = Controller->GetCrossingDataCon();
	std::vector<double>* t_pOldMaxSpeed = Controller->GetOldMaxSpeedCon();

	// 이전 루프에서 인접했던 데이터들을 다시 원상태로 돌림
	for(std::vector<CData*>::size_type i = 0; i < t_pCrossingData->size(); ++i){
		t_pCrossingData->at(i)->SetMaxSpeed(t_pOldMaxSpeed->at(i));
	}

	t_pCrossingData->clear();
	t_pOldMaxSpeed->clear();
		
	// 바이러스와 데이타 세포질 충돌검사
  for (t_Itr = m_Data.begin(); t_Itr != m_Data.end(); ++t_Itr){
		if(!(*t_Itr)->IsAlive()) continue;

		if((*t_Itr)->GetGrowth()->greater(t_pVirus->GetGrowth())) continue;

    ToEntity = t_pVirus->GetPos2D() - (*t_Itr)->GetPos2D();

    DistFromEachOther = ToEntity.Length();
 
    AmountOfOverLap = ((*t_Itr)->GetRadius()*3.0f) + (t_pVirus->GetRadius()*1.5f) - DistFromEachOther;

    if (AmountOfOverLap >= 0){
			Controller->GetCrossingDataCon()->push_back((*t_Itr));
			Controller->GetOldMaxSpeedCon()->push_back((*t_Itr)->GetMaxSpeed());
			if((*t_Itr)->GetSteering()->isControlledOn()){
				(*t_Itr)->SetMaxSpeed((*t_Itr)->GetMaxSpeed());
				continue;
			}
			else
				(*t_Itr)->SetMaxSpeed((*t_Itr)->GetMaxSpeed()*0.5);

			if((*t_Itr)->GetState() != CData::NORMAL) continue;
			(*t_Itr)->SetState(CData::INFECTION);
    }
  }
}

void	CWorld::CheckCrossingSecretDataAndVirus(){
	if(!UIMgr->GetAbility()->GetControlling()){
		std::list<CSecretData*>::iterator t_Itr;

		Vector2D ToEntity;
		double DistFromEachOther;
		double AmountOfOverLap;
		CVirus* t_pVirus = Controller->GetController();
			
		// 바이러스와 비밀 데이터
		for (t_Itr = m_SecretData.begin(); t_Itr != m_SecretData.end(); ++t_Itr){
			if(!(*t_Itr)->IsAlive()) continue;
			if((*t_Itr)->GetGrowth()->greater(t_pVirus->GetGrowth())) continue;

			ToEntity = t_pVirus->GetPos2D() - (*t_Itr)->GetPos2D();

			DistFromEachOther = ToEntity.Length();
	 
			AmountOfOverLap = ((*t_Itr)->GetRadius()) + (t_pVirus->GetRadius()) - DistFromEachOther;

			if (AmountOfOverLap >= 0){
				(*t_Itr)->GetFSM()->ChangeState(SecretDataDelete->Instance());
			}
		}
	}
}

// 충돌검출
void	CWorld::CheckCrossingVacineAndVirus(){
	std::list<CVacine*>::const_iterator t_Itr;

	Vector2D ToEntity;
	double DistFromEachOther;
	double AmountOfOverLap;
	CVirus* t_pVirus = Controller->GetController();
	
	Controller->GetCrossingVacineCon()->clear();

	// 바이러스와 백신 세포질, 핵 충돌검사
	if(t_pVirus->IsAlive()){
		for (t_Itr = m_Vacine.begin(); t_Itr != m_Vacine.end(); ++t_Itr){
			if(!(*t_Itr)->IsAlive()) continue;
			if(Controller->GetGrowing()) continue;

			ToEntity = t_pVirus->GetPos2D() - (*t_Itr)->GetPos2D();

			DistFromEachOther = ToEntity.Length();

			if(t_pVirus->GetGrowth()->less_equal((*t_Itr)->GetGrowth())){
				AmountOfOverLap = (*t_Itr)->GetRadius() + t_pVirus->GetRadius() - DistFromEachOther;

				if (AmountOfOverLap >= 0){
					t_pVirus->GetFSM()->ChangeState(VirusDie->Instance());		
				}
			}
			else{
				AmountOfOverLap = ((*t_Itr)->GetRadius()*1.5f) + (t_pVirus->GetRadius()*1.5f) - DistFromEachOther;

				if (AmountOfOverLap >= 0){			 
					Controller->GetCrossingVacineCon()->push_back((*t_Itr));
				}
			}
		}
	}
}

void	CWorld::CheckViewVacineAndData(){
	std::list<CVacine*>::const_iterator t_ItrVacine;
	std::list<CData*>::const_iterator t_ItrData;

	Vector2D ToEntity;
	double DistFromEachOther;
	double OldDistFromEachOther = 1000;
	double AmountOfOverLap;

	for(t_ItrVacine = m_Vacine.begin(); t_ItrVacine != m_Vacine.end(); ++t_ItrVacine){
		(*t_ItrVacine)->GetSteering()->PursuitOff();
	}

	// 백신 인식 범위 검사
	for(t_ItrVacine = m_Vacine.begin(); t_ItrVacine != m_Vacine.end(); ++t_ItrVacine){
		for (t_ItrData = m_Data.begin(); t_ItrData != m_Data.end(); ++t_ItrData){
			if(!(*t_ItrData)->IsAlive()){
				if((*t_ItrVacine)->GetTarget()){
					if((*t_ItrVacine)->GetTarget() == (*t_ItrData)){
						(*t_ItrVacine)->GetSteering()->PursuitOff();
						if((*t_ItrVacine)->GetSteering()->IsPathActive())
							(*t_ItrVacine)->GetSteering()->FollowPathOn();
						else
							(*t_ItrVacine)->GetSteering()->WanderOn();
						(*t_ItrVacine)->SetTarget(NULL);
					}
				}
				continue;
			}
			if(!(*t_ItrVacine)->IsAlive()) continue;
			if((*t_ItrData)->GetState() == CData::NORMAL) continue;

			if((*t_ItrData)->GetGrowth()->greater((*t_ItrVacine)->GetGrowth())) continue;

			if((*t_ItrVacine)->GetTarget()){
				ToEntity = (*t_ItrVacine)->GetPos2D() - (*t_ItrVacine)->GetTarget()->GetPos2D();

				DistFromEachOther = ToEntity.Length();

				(*t_ItrVacine)->GetSteering()->PursuitOn((*t_ItrVacine)->GetTarget());
				if((*t_ItrVacine)->GetSteering()->IsPathActive()){
					(*t_ItrVacine)->GetSteering()->PursuitOn((*t_ItrData));
					(*t_ItrVacine)->GetSteering()->FollowPathOff();
					(*t_ItrVacine)->SetTarget(*t_ItrData);

					AmountOfOverLap = (*t_ItrVacine)->GetRadius() + (*t_ItrData)->GetRadius() - DistFromEachOther;
					if(AmountOfOverLap >= 0){
						(*t_ItrData)->GetFSM()->ChangeState(DataCure->Instance());
						(*t_ItrVacine)->GetSteering()->PursuitOff();
						(*t_ItrVacine)->GetSteering()->FollowPathOn();
						(*t_ItrVacine)->SetTarget(NULL);
						OldDistFromEachOther = 1000;
					}
				}
				else{
					ToEntity = (*t_ItrVacine)->GetPos2D() - (*t_ItrVacine)->GetTarget()->GetPos2D();

					DistFromEachOther = ToEntity.Length();

					if(OldDistFromEachOther > DistFromEachOther){
						OldDistFromEachOther = DistFromEachOther;
						(*t_ItrVacine)->GetSteering()->PursuitOn((*t_ItrData));
						(*t_ItrVacine)->GetSteering()->WanderOff();
						(*t_ItrVacine)->SetTarget(*t_ItrData);

						AmountOfOverLap = (*t_ItrVacine)->GetRadius() + (*t_ItrData)->GetRadius() - DistFromEachOther;
						if(AmountOfOverLap >= 0){
							(*t_ItrData)->GetFSM()->ChangeState(DataCure->Instance());
							(*t_ItrVacine)->GetSteering()->PursuitOff();
							(*t_ItrVacine)->GetSteering()->WanderOn();
							(*t_ItrVacine)->SetTarget(NULL);
							OldDistFromEachOther = 1000;
						}
					}
				}
			}
			else{	 
				ToEntity = (*t_ItrVacine)->GetPos2D() - (*t_ItrData)->GetPos2D();

				DistFromEachOther = ToEntity.Length();

				if (DistFromEachOther <= (*t_ItrVacine)->GetSteering()->GetViewDistance()){					
					if(OldDistFromEachOther > DistFromEachOther){
						OldDistFromEachOther = DistFromEachOther;
						(*t_ItrVacine)->GetSteering()->PursuitOn((*t_ItrData));
						if((*t_ItrVacine)->GetSteering()->IsPathActive()){
							(*t_ItrVacine)->GetSteering()->FollowPathOff();
						}
						else{
							(*t_ItrVacine)->GetSteering()->WanderOff();
						}
						(*t_ItrVacine)->SetTarget(*t_ItrData);
					}						
				}
			}
		}
		OldDistFromEachOther = 1000;
	}
}

void	CWorld::CheckClosestEntity(){
	std::vector<CData*>::iterator t_ItrData;
	std::vector<CVacine*>::iterator t_ItrVacine;

	Vector2D ToEntity(0.0, 0.0);
	double t_dDataDistFromEachOther = 10000;
	double t_dVacineDistFromEachOther = 10000;
	double AmountOfOverLap = 0;

	CVirus* t_pVirus = Controller->GetController();
	CData* t_ClosestData = NULL;
	CVacine* t_ClosestVacine = NULL;

	CVehicle* t_pClosestEntity = NULL;

	if(!Controller->GetCrossingDataCon()->empty() || !Controller->GetCrossingVacineCon()->empty()){
		if(!Controller->GetCrossingDataCon()->empty()){
			for(t_ItrData = Controller->GetCrossingDataCon()->begin(); t_ItrData != Controller->GetCrossingDataCon()->end(); ++t_ItrData){
				ToEntity = t_pVirus->GetPos2D() - (*t_ItrData)->GetPos2D();
				
				if(t_dDataDistFromEachOther > ToEntity.Length()){
					t_dDataDistFromEachOther = ToEntity.Length();
					t_ClosestData = (*t_ItrData);
				}
			}
		}

		if(!Controller->GetCrossingVacineCon()->empty()){
			for(t_ItrVacine = Controller->GetCrossingVacineCon()->begin(); t_ItrVacine != Controller->GetCrossingVacineCon()->end(); ++t_ItrVacine){
				ToEntity = t_pVirus->GetPos2D() - (*t_ItrVacine)->GetPos2D();
				
				if(t_dVacineDistFromEachOther > ToEntity.Length()){
					t_dVacineDistFromEachOther = ToEntity.Length();
					t_ClosestVacine = (*t_ItrVacine);
				}
			}
		}

		if(t_dDataDistFromEachOther <= t_dVacineDistFromEachOther){
			UIMgr->GetAbility()->SetClosestEntity(t_ClosestData);
		}
		else
			UIMgr->GetAbility()->SetClosestEntity(t_ClosestVacine);
	}
	else{	
		UIMgr->GetAbility()->SetClosestEntity(NULL);	
	}
}

bool	CWorld::CheckDataAllDie(){
	std::list<CData*>::iterator t_itr;

	for(t_itr = m_Data.begin(); t_itr != m_Data.end(); ++t_itr){
		if((*t_itr)->IsAlive()){
			return false;
		}
	}

	return true;
}

bool	CWorld::CheckVacineAllDie(){
	std::list<CVacine*>::iterator t_itr;

	for(t_itr = m_Vacine.begin(); t_itr != m_Vacine.end(); ++t_itr){
		if((*t_itr)->IsAlive()){
			return false;
		}
	}

	return true;
}

bool	CWorld::CheckSecretDataAllDie(){
	std::list<CSecretData*>::iterator t_itr;

	for(t_itr = m_SecretData.begin(); t_itr != m_SecretData.end(); ++t_itr){
		if((*t_itr)->IsAlive()){
			return false;
		}
	}

	return true;
}

void	CWorld::CheckIntersectionFireWall(){
	if(Controller->GetController()->IsAlive() && !UIMgr->GetAbility()->GetControlling()){
		//test each line segment of object1 against each segment of object2
		Vector2D t_vTempY1(Controller->GetController()->GetPos2D().x,
			Controller->GetController()->GetPos2D().y-Controller->GetController()->GetRadius());
		Vector2D t_vTempY2(Controller->GetController()->GetPos2D().x,
			Controller->GetController()->GetPos2D().y+Controller->GetController()->GetRadius());

		Vector2D t_vTempX1(Controller->GetController()->GetPos2D().x-Controller->GetController()->GetRadius(),
			Controller->GetController()->GetPos2D().y);
		Vector2D t_vTempX2(Controller->GetController()->GetPos2D().x+Controller->GetController()->GetRadius(),
			Controller->GetController()->GetPos2D().y);

		std::list<CSecretData*>::iterator t_itr;

		for(t_itr = m_SecretData.begin(); t_itr != m_SecretData.end(); ++t_itr){
			for (unsigned int r=0; r<(*t_itr)->GetFireWalls().size(); ++r){
				if((*t_itr)->IsAlive()){
					if (LineIntersection2D(t_vTempX1, t_vTempX2, (*t_itr)->GetFireWalls().at(r).From(), (*t_itr)->GetFireWalls().at(r).To())
						|| LineIntersection2D(t_vTempY1, t_vTempY2, (*t_itr)->GetFireWalls().at(r).From(), (*t_itr)->GetFireWalls().at(r).To()))
					{
						Controller->GetController()->GetFSM()->ChangeState(VirusDie->Instance());
					}
				}
			}
		}
	}
}

bool	CWorld::CheckIntersectionFireWallForAbility(){
	Vector2D t_vTempY1(Controller->GetController()->GetPos2D().x,
		Controller->GetController()->GetPos2D().y-Controller->GetController()->GetRadius());
	Vector2D t_vTempY2(Controller->GetController()->GetPos2D().x,
		Controller->GetController()->GetPos2D().y+Controller->GetController()->GetRadius());

	Vector2D t_vTempX1(Controller->GetController()->GetPos2D().x-Controller->GetController()->GetRadius(),
		Controller->GetController()->GetPos2D().y);
	Vector2D t_vTempX2(Controller->GetController()->GetPos2D().x+Controller->GetController()->GetRadius(),
		Controller->GetController()->GetPos2D().y);

	std::list<CSecretData*>::iterator t_itr;

	for(t_itr = m_SecretData.begin(); t_itr != m_SecretData.end(); ++t_itr){
		for (unsigned int r=0; r<(*t_itr)->GetFireWalls().size(); ++r){
			if((*t_itr)->IsAlive()){
				if (LineIntersection2D(t_vTempX1, t_vTempX2, (*t_itr)->GetFireWalls().at(r).From(), (*t_itr)->GetFireWalls().at(r).To())
					|| LineIntersection2D(t_vTempY1, t_vTempY2, (*t_itr)->GetFireWalls().at(r).From(), (*t_itr)->GetFireWalls().at(r).To()))
				{
					return true;
				}
			}
		}
	}

	return false;
}