#include "SteeringParamLoader.h"
#include "../Engine_Misc/Utils.h"

CSteeringParamLoader::CSteeringParamLoader(const char* _pstrFile):CFileLoaderBase(_pstrFile)
{
	NumSamplesForSmoothing  = GetNextParameterInt();

	SteeringForceTweaker    = GetNextParameterFloat();
	MaxSteeringForce        = GetNextParameterFloat() * SteeringForceTweaker;
	MaxSpeed                = GetNextParameterFloat();
	VehicleMass             = GetNextParameterFloat();
	VehicleScale            = GetNextParameterFloat();

	SeparationWeight        = GetNextParameterFloat() * SteeringForceTweaker;
	AlignmentWeight         = GetNextParameterFloat() * SteeringForceTweaker;
	CohesionWeight          = GetNextParameterFloat() * SteeringForceTweaker;
	ObstacleAvoidanceWeight = GetNextParameterFloat() * SteeringForceTweaker;
	WallAvoidanceWeight     = GetNextParameterFloat() * SteeringForceTweaker;
	WanderWeight            = GetNextParameterFloat() * SteeringForceTweaker;
	SeekWeight              = GetNextParameterFloat() * SteeringForceTweaker;
	FleeWeight              = GetNextParameterFloat() * SteeringForceTweaker;
	ArriveWeight            = GetNextParameterFloat() * SteeringForceTweaker;
	PursuitWeight           = GetNextParameterFloat() * SteeringForceTweaker;
	OffsetPursuitWeight     = GetNextParameterFloat() * SteeringForceTweaker;
	InterposeWeight         = GetNextParameterFloat() * SteeringForceTweaker;
	HideWeight              = GetNextParameterFloat() * SteeringForceTweaker;
	EvadeWeight             = GetNextParameterFloat() * SteeringForceTweaker;
	FollowPathWeight        = GetNextParameterFloat() * SteeringForceTweaker;

	ViewDistance            = GetNextParameterFloat();
	MinDetectionBoxLength   = GetNextParameterFloat();
	WallDetectionFeelerLength=GetNextParameterFloat();

	prWallAvoidance         = GetNextParameterFloat();
	prObstacleAvoidance     = GetNextParameterFloat();  
	prSeparation            = GetNextParameterFloat();
	prAlignment             = GetNextParameterFloat();
	prCohesion              = GetNextParameterFloat();
	prWander                = GetNextParameterFloat();
	prSeek                  = GetNextParameterFloat();
	prFlee                  = GetNextParameterFloat();
	prEvade                 = GetNextParameterFloat();
	prHide                  = GetNextParameterFloat();
	prArrive                = GetNextParameterFloat();

	MaxTurnRatePerSecond    = Pi/4;
}