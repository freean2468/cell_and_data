#ifndef _SteeringParamLoader_H_
#define _SteeringParamLoader_H_

//-----------------------------------------------------------------------------
//
//  Name:   CSteeringParamLoader.h
//
//  Desc:   조종힘 관련 파라미터들을 로드
//-----------------------------------------------------------------------------

#include "FileLoaderBase.h"

class CSteeringParamLoader : public CFileLoaderBase	{
public:
	CSteeringParamLoader(const char* _pstrFile);
	~CSteeringParamLoader(){}

public:
	//how many samples the CSmoother will use to average a value
	int   NumSamplesForSmoothing;

	//used to tweak the combined steering force (simply altering the MaxSteeringForce
	//will NOT work!This tweaker affects all the steering force multipliers
	//too).
	double SteeringForceTweaker;

	double MaxSteeringForce;
	double MaxSpeed;
	double VehicleMass;

	double VehicleScale;
	double MaxTurnRatePerSecond;

	double SeparationWeight;
	double AlignmentWeight;
	double CohesionWeight;
	double ObstacleAvoidanceWeight;
	double WallAvoidanceWeight;
	double WanderWeight;
	double SeekWeight;
	double FleeWeight;
	double ArriveWeight;
	double PursuitWeight;
	double OffsetPursuitWeight;
	double InterposeWeight ;
	double HideWeight;
	double EvadeWeight;
	double FollowPathWeight;

	//how close a neighbour must be before an agent perceives it (considers it
	//to be within its neighborhood)
	double ViewDistance;

	//used in CObstacle avoidance
	double MinDetectionBoxLength;

	//used in wall avoidance
	double WallDetectionFeelerLength;

	//these are the probabilities that a steering behavior will be used
	//when the prioritized dither calculate method is used
	double prWallAvoidance;
	double prObstacleAvoidance;
	double prSeparation;
	double prAlignment;
	double prCohesion;
	double prWander;
	double prSeek;
	double prFlee;
	double prEvade;
	double prHide;
	double prArrive;
};

#endif