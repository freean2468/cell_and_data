#include "SteeringBehavior.h"
#include "../Game_Factor/WorldManager.h"
#include "../Engine_Math&Physics/Transformation.h"
#include "../Engine_Math&Physics/Geometry.h"
#include <list>

//------------------------- ctor -----------------------------------------
//
//------------------------------------------------------------------------
CSteeringBehavior::CSteeringBehavior(CVehicle* agent):  m_pVehicle(agent),
														m_iFlags(0),
														m_dDBoxLength(WorldMgr->GetSteeringParam()->MinDetectionBoxLength),
														m_dWeightCohesion(WorldMgr->GetSteeringParam()->CohesionWeight),
														m_dWeightAlignment(WorldMgr->GetSteeringParam()->AlignmentWeight),
														m_dWeightSeparation(WorldMgr->GetSteeringParam()->SeparationWeight),
														m_dWeightObstacleAvoidance(WorldMgr->GetSteeringParam()->ObstacleAvoidanceWeight),
														m_dWeightWander(WorldMgr->GetSteeringParam()->WanderWeight),
														m_dWeightWallAvoidance(WorldMgr->GetSteeringParam()->WallAvoidanceWeight),
														m_dViewDistance(WorldMgr->GetSteeringParam()->ViewDistance),
														m_dWallDetectionFeelerLength(WorldMgr->GetSteeringParam()->WallDetectionFeelerLength),
														m_Feelers(3),
														m_Deceleration(normal),
														m_pTargetAgent1(NULL),
														m_pTargetAgent2(NULL),
														m_dWanderDistance(WanderDist),
														m_dWanderJitter(WanderJitterPerSec),
														m_dWanderRadius(WanderRad),
														m_dWaypointSeekDistSq(WaypointSeekDist*WaypointSeekDist),
														m_dWeightSeek(WorldMgr->GetSteeringParam()->SeekWeight),
														m_dWeightFlee(WorldMgr->GetSteeringParam()->FleeWeight),
														m_dWeightArrive(WorldMgr->GetSteeringParam()->ArriveWeight),
														m_dWeightPursuit(WorldMgr->GetSteeringParam()->PursuitWeight),
														m_dWeightOffsetPursuit(WorldMgr->GetSteeringParam()->OffsetPursuitWeight),
														m_dWeightInterpose(WorldMgr->GetSteeringParam()->InterposeWeight),
														m_dWeightHide(WorldMgr->GetSteeringParam()->HideWeight),
														m_dWeightEvade(WorldMgr->GetSteeringParam()->EvadeWeight),
														m_dWeightFollowPath(WorldMgr->GetSteeringParam()->FollowPathWeight),
														m_bCellSpaceOn(true),
														m_SummingMethod(prioritized),
														m_bPathActive(false)
{
  //stuff for the wander behavior
  double theta = RandFloat() * TwoPi;

  //create a vector to a _vTarget position on the wander circle
  m_vWanderTarget = Vector2D(m_dWanderRadius * cos(theta),
                              m_dWanderRadius * sin(theta));

  //create a CPath
  m_pPath = new CPath();
  m_pPath->LoopOn();
}

//---------------------------------dtor ----------------------------------
CSteeringBehavior::~CSteeringBehavior(){
	delete m_pPath;
}

//---------------------------------- Setting -----------------------------
void	CSteeringBehavior::SetPath(std::list<Vector2D> new_path){
	m_pPath->Set(new_path);
}

void	CSteeringBehavior::CreateRandomPath(int num_waypoints, int mx, int my, int cx, int cy)const
{
	m_pPath->CreateRandomPath(num_waypoints, mx, my, cx, cy);
}

/////////////////////////////////////////////////////////////////////////////// CALCULATE METHODS 

//----------------------- Calculate --------------------------------------
//
//  calculates the accumulated steering force according to the method set
//  in m_SummingMethod
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::Calculate(){ 
  //reset the steering force
  m_vSteeringForce.Zero();

  //use space partitioning to calculate the neighbours of this CVehicle
  //if switched on. If not, use the standard tagging system
  if (!isSpacePartitioningOn()){
    //tag neighbors if any of the following 3 group behaviors are switched on
    if (On(separation) || On(allignment) || On(cohesion)){
      //WorldMgr->GetWorld()->TagVehiclesWithinViewRange(m_pVehicle, m_dViewDistance);
    }
  }
  else{
    //calculate neighbours in cell-space if any of the following 3 group
    //behaviors are switched on
    if (On(separation) || On(allignment) || On(cohesion)){
      WorldMgr->GetWorld()->GetCellSpace()->CalculateNeighbors(m_pVehicle->GetPos2D(), 
																																	m_pVehicle->GetRadius() * 2.0);
    }
  }

	m_vSteeringForce = CalculatePrioritized();

  return m_vSteeringForce;
}

//------------------------- ForwardComponent -----------------------------
//
//  returns the forward oomponent of the steering force
//------------------------------------------------------------------------
double CSteeringBehavior::ForwardComponent(){
  return m_pVehicle->GetHeading().Dot(m_vSteeringForce);
}

//--------------------------- SideComponent ------------------------------
//  returns the side component of the steering force
//------------------------------------------------------------------------
double CSteeringBehavior::SideComponent(){
  return m_pVehicle->GetSide().Dot(m_vSteeringForce);
}

//--------------------- AccumulateForce ----------------------------------
//
//  This function calculates how much of its max steering force the 
//  CVehicle has left to apply and then applies that amount of the
//  force to add.
//------------------------------------------------------------------------
bool CSteeringBehavior::AccumulateForce(Vector2D &RunningTot, Vector2D ForceToAdd){  
  //calculate how much steering force the CVehicle has used so far
  double MagnitudeSoFar = RunningTot.Length();

  //calculate how much steering force remains to be used by this CVehicle
  double MagnitudeRemaining = m_pVehicle->GetMaxForce() - MagnitudeSoFar;

  //return false if there is no more force left to use
  if (MagnitudeRemaining <= 0.0) return false;

  //calculate the magnitude of the force we want to add
  double MagnitudeToAdd = ForceToAdd.Length();
  
  //if the magnitude of the sum of ForceToAdd and the running total
  //does not exceed the maximum force available to this CVehicle, just
  //add together. Otherwise add as much of the ForceToAdd vector is
  //possible without going over the max.
  if (MagnitudeToAdd < MagnitudeRemaining){
    RunningTot += ForceToAdd;
  }
  else{
    //add it to the steering force
    RunningTot += (Vec2DNormalize(ForceToAdd) * MagnitudeRemaining); 
  }

  return true;
}

//---------------------- CalculatePrioritized ----------------------------
//
//  this method calls each active steering behavior in order of priority
//  and acumulates their forces until the max steering force magnitude
//  is reached, at which time the function returns the steering force 
//  accumulated to that  point
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::CalculatePrioritized(){       
  Vector2D force;
  
	if (On(wall_avoidance)){
		force = WallAvoidance(WorldMgr->GetWorld()->GetWalls()) * m_dWeightWallAvoidance;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}
	   
	if (On(obstacle_avoidance)){
		force = ObstacleAvoidance(WorldMgr->GetWorld()->GetObstacles()) * m_dWeightObstacleAvoidance;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if(On(controlled)){
		AccumulateForce(m_vSteeringForce, Controlled() * 200);

		return m_vSteeringForce;
	}

	if(On(evade)){
		assert(m_pTargetAgent1 && "Evade _vTarget not assigned");
	    
		force = Evade(m_pTargetAgent1) * m_dWeightEvade;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if(On(flee)){
		force = Flee(Vector2D(0,0)) * m_dWeightFlee;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	////these next three can be combined for flocking behavior (wander is
	////also a good behavior to add into this mix)
	//if(!isSpacePartitioningOn()){
	//	if(On(separation)){
	//		force = Separation(WorldMgr->GetWorld()->GetData()) * m_dWeightSeparation;

	//		if(!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	//	}

	//	if(On(allignment)){
	//		force = Alignment(WorldMgr->GetWorld()->GetData()) * m_dWeightAlignment;

	//		if(!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	//	}

	//	if(On(cohesion)){
	//		force = Cohesion(WorldMgr->GetWorld()->GetData()) * m_dWeightCohesion;

	//		if(!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	//	}
	//}
	//else{
	//	if(On(separation)){
	//		force = SeparationPlus(WorldMgr->GetWorld()->GetData()) * m_dWeightSeparation;

	//		if(!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	//	}

	//	if(On(allignment)){
	//		force = AlignmentPlus(WorldMgr->GetWorld()->GetData()) * m_dWeightAlignment;

	//		if(!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	//	}

	//	if(On(cohesion)){
	//		force = CohesionPlus(WorldMgr->GetWorld()->GetData()) * m_dWeightCohesion;

	//		if(!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	//	}
	//}

	if(On(seek)){
		force = Seek(Vector2D(0,0)) * m_dWeightSeek;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if(On(arrive)){
		force = Arrive(Vector2D(0,0), m_Deceleration) * m_dWeightArrive;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if(On(wander)){
		force = Wander() * m_dWeightWander;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if(On(pursuit)){
		assert(m_pTargetAgent1 && "pursuit _vTarget not assigned");

		force = Pursuit(m_pTargetAgent1) * m_dWeightPursuit;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if(On(offset_pursuit)){
		assert (m_pTargetAgent1 && "pursuit _vTarget not assigned");
		assert (!m_vOffset.isZero() && "No offset assigned");

		force = OffsetPursuit(m_pTargetAgent1, m_vOffset);

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if(On(interpose)){
		assert (m_pTargetAgent1 && m_pTargetAgent2 && "Interpose agents not assigned");

		force = Interpose(m_pTargetAgent1, m_pTargetAgent2) * m_dWeightInterpose;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if(On(hide)){
		assert(m_pTargetAgent1 && "Hide _vTarget not assigned");

		force = Hide(m_pTargetAgent1, WorldMgr->GetWorld()->GetObstacles()) * m_dWeightHide;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if(On(follow_path)){
		force = FollowPath() * m_dWeightFollowPath;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	return m_vSteeringForce;
}

//////////////////////////////////////////////////////// START OF BEHAVIORS

//------------------------------- Seek -----------------------------------
//
//  Given a _vTarget, this behavior returns a steering force which will
//  direct the agent towards the _vTarget
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::Seek(Vector2D TargetPos){
  Vector2D DesiredVelocity = Vec2DNormalize(TargetPos - m_pVehicle->GetPos2D())
                            * m_pVehicle->GetMaxSpeed();

  return (DesiredVelocity - m_pVehicle->GetVelocity());
}

//----------------------------- Flee -------------------------------------
//
//  Does the opposite of Seek
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::Flee(Vector2D TargetPos){
  //only flee if the _vTarget is within 'panic distance'. Work in distance
  //squared space.
 /* const double PanicDistanceSq = 100.0f * 100.0;
  if (Vec2DDistanceSq(m_pVehicle->GetPos2D(), _vTarget) > PanicDistanceSq)
  {
    return Vector2D(0,0);
  }
  */

  Vector2D DesiredVelocity = Vec2DNormalize(m_pVehicle->GetPos2D() - TargetPos) 
                            * m_pVehicle->GetMaxSpeed();

  return (DesiredVelocity - m_pVehicle->GetVelocity());
}

//--------------------------- Arrive -------------------------------------
//
//  This behavior is similar to seek but it attempts to arrive at the
//  _vTarget with a zero velocity
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::Arrive(Vector2D TargetPos, Deceleration deceleration){
  Vector2D ToTarget = TargetPos - m_pVehicle->GetPos2D();

  //calculate the distance to the _vTarget
  double dist = ToTarget.Length();

  if (dist > 0){
    //because Deceleration is enumerated as an int, this value is required
    //to provide fine tweaking of the deceleration..
    const double DecelerationTweaker = 0.3;

    //calculate the speed required to reach the _vTarget given the desired
    //deceleration
    double speed =  dist / ((double)deceleration * DecelerationTweaker);     

    //make sure the velocity does not exceed the max
    speed = min(speed, m_pVehicle->GetMaxSpeed());

    //from here proceed just like Seek except we don't need to normalize 
    //the ToTarget vector because we have already gone to the trouble
    //of calculating its length: dist. 
    Vector2D DesiredVelocity =  ToTarget * speed / dist;

    return (DesiredVelocity - m_pVehicle->GetVelocity());
  }

  return Vector2D(0,0);
}

//------------------------------ Pursuit ---------------------------------
//
//  this behavior creates a force that steers the agent towards the 
//  evader
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::Pursuit(CVehicle* evader){
  //if the evader is ahead and facing the agent then we can just seek
  //for the evader's current position.
  Vector2D ToEvader = evader->GetPos2D() - m_pVehicle->GetPos2D();

  double RelativeHeading = m_pVehicle->GetHeading().Dot(evader->GetHeading());

  if ((ToEvader.Dot(m_pVehicle->GetHeading()) > 0) && (RelativeHeading < -0.95))  //acos(0.95)=18 degs
  {
    return Seek(evader->GetPos2D());
  }

  //Not considered ahead so we predict where the evader will be.
 
  //the lookahead time is propotional to the distance between the evader
  //and the pursuer; and is inversely proportional to the sum of the
  //agent's velocities
  double LookAheadTime = ToEvader.Length() / 
                        (m_pVehicle->GetMaxSpeed() + evader->GetSpeed());
  
  //now seek to the predicted future position of the evader
  return Seek(evader->GetPos2D() + evader->GetVelocity() * LookAheadTime);
}

//----------------------------- Evade ------------------------------------
//
//  similar to pursuit except the agent Flees from the estimated future
//  position of the pursuer
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::Evade(CVehicle* pursuer){
  /* Not necessary to include the check for facing direction this time */

  Vector2D ToPursuer = pursuer->GetPos2D() - m_pVehicle->GetPos2D();

  //uncomment the following two lines to have Evade only consider pursuers 
  //within a 'threat range'
  const double ThreatRange = 100.0;
  if (ToPursuer.LengthSq() > ThreatRange * ThreatRange) return Vector2D();
 
  //the lookahead time is propotional to the distance between the pursuer
  //and the pursuer; and is inversely proportional to the sum of the
  //agents' velocities
  double LookAheadTime = ToPursuer.Length() / 
                         (m_pVehicle->GetMaxSpeed() + pursuer->GetSpeed());
  
  //now flee away from predicted future position of the pursuer
  return Flee(pursuer->GetPos2D() + pursuer->GetVelocity() * LookAheadTime);
}

//--------------------------- Wander -------------------------------------
//
//  This behavior makes the agent wander about randomly
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::Wander(){ 
  //this behavior is dependent on the update rate, so this line must
  //be included when using time independent framerate.
  double JitterThisTimeSlice = m_dWanderJitter * m_pVehicle->TimeElapsed();

  //first, add a small random vector to the _vTarget's position
  m_vWanderTarget += Vector2D(RandomClamped() * JitterThisTimeSlice,
                              RandomClamped() * JitterThisTimeSlice);

  //reproject this new vector back on to a unit circle
  m_vWanderTarget.Normalize();

  //increase the length of the vector to the same as the radius
  //of the wander circle
  m_vWanderTarget *= m_dWanderRadius;

  //move the _vTarget into a position WanderDist in front of the agent
  Vector2D _vTarget = m_vWanderTarget + Vector2D(m_dWanderDistance, 0);

  //project the _vTarget into world space
  Vector2D Target = PointToWorldSpace(_vTarget,
                                       m_pVehicle->GetHeading(),
                                       m_pVehicle->GetSide(), 
                                       m_pVehicle->GetPos2D());

  //and steer towards it
  return Target - m_pVehicle->GetPos2D(); 
}

//--------------------------- Controlled ---------------------------------
//
//  this function is used when controlled from controller
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::Controlled(){
	Vector2D t_vControlledTarget(0, 0);

	if(EngineMgr->KeyDown(DIK_UP)){
		t_vControlledTarget += Vector2D(1, 0);
	}

	if(EngineMgr->KeyDown(DIK_RIGHT)){
		t_vControlledTarget += Vector2D(0, -1);
	}

	if(EngineMgr->KeyDown(DIK_LEFT)){
		t_vControlledTarget += Vector2D(0, 1);
	}

  //reproject this new vector back on to a unit circle
  t_vControlledTarget.Normalize();

  //increase the length of the vector to the same as the radius
  //of the controlled circle
	t_vControlledTarget *= m_dWanderRadius;

  //move the _vTarget into a position WanderDist in front of the agent
  Vector2D _vTarget = t_vControlledTarget + Vector2D(m_dWanderDistance, 0);

  //project the _vTarget into world space
  Vector2D Target = PointToWorldSpace(_vTarget,
                                       m_pVehicle->GetHeading(),
                                       m_pVehicle->GetSide(), 
                                       m_pVehicle->GetPos2D());

	if(EngineMgr->KeyDown(DIK_UP)){
		//and steer towards it
		return Target - m_pVehicle->GetPos2D(); 
	}
	else{
		AccumulateForce(m_vSteeringForce, Arrive(Target, slow));

		// 왼쪽 오른쪽으로 회전할 경우 힘을 줄여서 회전량을 적게 한다.
		if(EngineMgr->KeyDown(DIK_LEFT) || EngineMgr->KeyDown(DIK_RIGHT))	return m_vSteeringForce / 70;
		else	return m_vSteeringForce;
	}
}

//---------------------- ObstacleAvoidance -------------------------------
//
//  Given a vector of CObstacles, this method returns a steering force
//  that will prevent the agent colliding with the closest CObstacle
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::ObstacleAvoidance(std::vector<CObstacle*>& obstacles){
  //the detection box length is proportional to the agent's velocity
	m_dDBoxLength = m_pVehicle->GetRadius()*2.0f + 
									(m_pVehicle->GetSpeed()/m_pVehicle->GetMaxSpeed()) *
									m_pVehicle->GetRadius()*2.0f;

  //tag all obstacles within range of the box for processing
  WorldMgr->GetWorld()->TagObstaclesWithinViewRange(m_pVehicle, m_dDBoxLength);

  //this will keep track of the closest intersecting CObstacle (CIB)
  CObstacle* ClosestIntersectingObstacle = NULL;
 
  //this will be used to track the distance to the CIB
  double DistToClosestIP = MaxDouble;

  //this will record the transformed local coordinates of the CIB
  Vector2D LocalPosOfClosestObstacle;

  std::vector<CObstacle*>::const_iterator curOb = obstacles.begin();

  while(curOb != obstacles.end()){
    //if the CObstacle has been tagged within range proceed
    if ((*curOb)->IsTagged()){
      //calculate this CObstacle's position in local space
      Vector2D LocalPos = PointToLocalSpace((*curOb)->GetPos2D(),
                                             m_pVehicle->GetHeading(),
                                             m_pVehicle->GetSide(),
                                             m_pVehicle->GetPos2D());

      //if the local position has a negative x value then it must lay
      //behind the agent. (in which case it can be ignored)
      if (LocalPos.x >= 0){
        //if the distance from the x axis to the object's position is less
        //than its radius + half the width of the detection box then there
        //is a potential intersection.
        double ExpandedRadius = (*curOb)->GetRadius() + m_pVehicle->GetRadius()*2.0f;

        if (fabs(LocalPos.y) < ExpandedRadius){
          //now to do a line/circle intersection test. The center of the 
          //circle is represented by (cX, cY). The intersection points are 
          //given by the formula x = cX +/-sqrt(r^2-cY^2) for y=0. 
          //We only need to look at the smallest positive value of x because
          //that will be the closest point of intersection.
          double cX = LocalPos.x;
          double cY = LocalPos.y;
          
          //we only need to calculate the sqrt part of the above equation once
          double SqrtPart = sqrt(ExpandedRadius*ExpandedRadius - cY*cY);

          double ip = cX - SqrtPart;

          if (ip <= 0.0){
            ip = cX + SqrtPart;
          }

          //test to see if this is the closest so far. If it is keep a
          //record of the CObstacle and its local coordinates
          if (ip < DistToClosestIP){
            DistToClosestIP = ip;

            ClosestIntersectingObstacle = *curOb;

            LocalPosOfClosestObstacle = LocalPos;
          }         
        }
      }
    }

    ++curOb;
  }

  //if we have found an intersecting CObstacle, calculate a steering 
  //force away from it
  Vector2D SteeringForce;

  if (ClosestIntersectingObstacle){
    //the closer the agent is to an object, the stronger the 
    //steering force should be
    double multiplier = 1.0 + (m_dDBoxLength - LocalPosOfClosestObstacle.x) /
                        m_dDBoxLength;

    //calculate the lateral force
    SteeringForce.y = (ClosestIntersectingObstacle->GetRadius()-
                       LocalPosOfClosestObstacle.y)  * multiplier;   

    //apply a braking force proportional to the obstacles distance from
    //the CVehicle. 
    const double BrakingWeight = 0.2;

    SteeringForce.x = (ClosestIntersectingObstacle->GetRadius() - 
                       LocalPosOfClosestObstacle.x) * 
                       BrakingWeight;
  }

  //finally, convert the steering vector from local to world space
  return VectorToWorldSpace(SteeringForce,
                            m_pVehicle->GetHeading(),
                            m_pVehicle->GetSide());
}

//--------------------------- WallAvoidance --------------------------------
//
//  This returns a steering force that will keep the agent away from any
//  walls it may encounter
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::WallAvoidance(std::vector<CWall3D>& walls){
  //the feelers are contained in a std::vector, m_Feelers
  CreateFeelers();
  
  double DistToThisIP    = 0.0;
  double DistToClosestIP = MaxDouble;

  //this will hold an index into the vector of walls
  int ClosestWall = -1;

  Vector2D SteeringForce,
            point,         //used for storing temporary info
            ClosestPoint;  //holds the closest intersection point

  //examine each feeler in turn
  for (unsigned int flr=0; flr<m_Feelers.size(); ++flr){
    //run through each wall checking for any intersection points
    for (unsigned int w=0; w<walls.size(); ++w){
      if (LineIntersection2D(m_pVehicle->GetPos2D(),
                             m_Feelers[flr],
                             walls[w].From(),
                             walls[w].To(),
                             DistToThisIP,
                             point))
      {
        //is this the closest found so far? If so keep a record
        if (DistToThisIP < DistToClosestIP)
        {
          DistToClosestIP = DistToThisIP;

          ClosestWall = w;

          ClosestPoint = point;
        }
      }
    }//next wall

  
    //if an intersection point has been detected, calculate a force  
    //that will direct the agent away
    if (ClosestWall >=0){
      //calculate by what distance the projected position of the agent
      //will overshoot the wall
      Vector2D OverShoot = m_Feelers[flr] - ClosestPoint;

      //create a force in the direction of the wall normal, with a 
      //magnitude of the overshoot
      SteeringForce = walls[ClosestWall].Normal() * OverShoot.Length();
    }

  }//next feeler

  return SteeringForce;
}

//------------------------------- CreateFeelers --------------------------
//
//  Creates the antenna utilized by WallAvoidance
//------------------------------------------------------------------------
void CSteeringBehavior::CreateFeelers(){
  //feeler pointing straight in front
  m_Feelers[0] = m_pVehicle->GetPos2D() + m_dWallDetectionFeelerLength * m_pVehicle->GetHeading();

  //feeler to left
  Vector2D temp = m_pVehicle->GetHeading();
  Vec2DRotateAroundOrigin(temp, HalfPi * 3.5f);
  m_Feelers[1] = m_pVehicle->GetPos2D() + m_dWallDetectionFeelerLength/2.0f * temp;

  //feeler to right
  temp = m_pVehicle->GetHeading();
  Vec2DRotateAroundOrigin(temp, HalfPi * 0.5f);
  m_Feelers[2] = m_pVehicle->GetPos2D() + m_dWallDetectionFeelerLength/2.0f * temp;
}

//---------------------------- Separation --------------------------------
//
// this calculates a force repelling from the other neighbors
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::Separation(std::list<CVehicle*> &neighbors){  
  Vector2D SteeringForce;

	std::list<CVehicle*>::const_iterator t_itr;

  for (t_itr = neighbors.begin(); t_itr != neighbors.end(); ++t_itr){
    //make sure this agent isn't included in the calculations and that
    //the agent being examined is close enough. ***also make sure it doesn't
    //include the evade _vTarget ***
    if(((*t_itr) != m_pVehicle) && (*t_itr)->IsTagged() && ((*t_itr) != m_pTargetAgent1))
    {
      Vector2D ToAgent = m_pVehicle->GetPos2D() - (*t_itr)->GetPos2D();

      //scale the force inversely proportional to the agents distance  
      //from its neighbor.
      SteeringForce += Vec2DNormalize(ToAgent)/ToAgent.Length();
    }
  }

  return SteeringForce;
}

//---------------------------- Alignment ---------------------------------
//
//  returns a force that attempts to align this agents heading with that
//  of its neighbors
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::Alignment(std::list<CVehicle*>& neighbors){
  //used to record the average heading of the neighbors
  Vector2D AverageHeading;

  //used to count the number of vehicles in the neighborhood
  int    NeighborCount = 0;

	std::list<CVehicle*>::const_iterator t_itr;

  //iterate through all the tagged vehicles and sum their heading vectors  
  for (t_itr = neighbors.begin(); t_itr != neighbors.end(); ++t_itr){
    //make sure *this* agent isn't included in the calculations and that
    //the agent being examined  is close enough ***also make sure it doesn't
    //include any evade _vTarget ***
    if(((*t_itr) != m_pVehicle) && (*t_itr)->IsTagged() && ((*t_itr) != m_pTargetAgent1)){
      AverageHeading += (*t_itr)->GetHeading();

      ++NeighborCount;
    }
  }

  //if the neighborhood contained one or more vehicles, average their
  //heading vectors.
  if (NeighborCount > 0){
    AverageHeading /= (double)NeighborCount;

    AverageHeading -= m_pVehicle->GetHeading();
  }
  
  return AverageHeading;
}

//-------------------------------- Cohesion ------------------------------
//
//  returns a steering force that attempts to move the agent towards the
//  center of mass of the agents in its immediate area
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::Cohesion(std::list<CVehicle*> &neighbors){
  //first find the center of mass of all the agents
  Vector2D CenterOfMass, SteeringForce;

  int NeighborCount = 0;

	std::list<CVehicle*>::const_iterator t_itr;

  //iterate through the neighbors and sum up all the position vectors
  for (t_itr = neighbors.begin(); t_itr != neighbors.end(); ++t_itr){
    //make sure *this* agent isn't included in the calculations and that
    //the agent being examined is close enough ***also make sure it doesn't
    //include the evade _vTarget ***
    if(((*t_itr) != m_pVehicle) && (*t_itr)->IsTagged() && ((*t_itr) != m_pTargetAgent1)){
      CenterOfMass += (*t_itr)->GetPos2D();

      ++NeighborCount;
    }
  }

  if (NeighborCount > 0){
    //the center of mass is the average of the sum of positions
    CenterOfMass /= (double)NeighborCount;

    //now seek towards that position
    SteeringForce = Seek(CenterOfMass);
  }

  //the magnitude of cohesion is usually much larger than separation or
  //allignment so it usually helps to normalize it.
  return Vec2DNormalize(SteeringForce);
}


/* NOTE: the next three behaviors are the same as the above three, except
          that they use a cell-space partition to find the neighbors
*/


//---------------------------- Separation --------------------------------
//
// this calculates a force repelling from the other neighbors
//
//  USES SPACIAL PARTITIONING
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::SeparationPlus(std::list<CVehicle*> &neighbors){  
  Vector2D SteeringForce;

  //iterate through the neighbors and sum up all the position vectors
  for (CDirectXEntity* pV = WorldMgr->GetWorld()->GetCellSpace()->begin();
       !WorldMgr->GetWorld()->GetCellSpace()->end();     
       pV = WorldMgr->GetWorld()->GetCellSpace()->next())
  {    
    //make sure this agent isn't included in the calculations and that
    //the agent being examined is close enough
    if(pV != m_pVehicle){
      Vector2D ToAgent = m_pVehicle->GetPos2D() - pV->GetPos2D();

      //scale the force inversely proportional to the agents distance  
      //from its neighbor.
      SteeringForce += Vec2DNormalize(ToAgent)/ToAgent.Length();
    }

  }

  return SteeringForce;
}

//---------------------------- Alignment ---------------------------------
//
//  returns a force that attempts to align this agents heading with that
//  of its neighbors
//
//  USES SPACIAL PARTITIONING
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::AlignmentPlus(std::list<CVehicle*> &neighbors){
  //This will record the average heading of the neighbors
  Vector2D AverageHeading;

  //This count the number of vehicles in the neighborhood
  double    NeighborCount = 0.0;

  //iterate through the neighbors and sum up all the position vectors
  for (CMovingEntity* pV = WorldMgr->GetWorld()->GetCellSpace()->begin();
       !WorldMgr->GetWorld()->GetCellSpace()->end();     
       pV = WorldMgr->GetWorld()->GetCellSpace()->next())
  {
    //make sure *this* agent isn't included in the calculations and that
    //the agent being examined  is close enough
    if(pV != m_pVehicle){
      AverageHeading += pV->GetHeading();

      ++NeighborCount;
    }
  }

  //if the neighborhood contained one or more vehicles, average their
  //heading vectors.
  if (NeighborCount > 0.0){
    AverageHeading /= NeighborCount;

    AverageHeading -= m_pVehicle->GetHeading();
  }
  
  return AverageHeading;
}

//-------------------------------- Cohesion ------------------------------
//
//  returns a steering force that attempts to move the agent towards the
//  center of mass of the agents in its immediate area
//
//  USES SPACIAL PARTITIONING
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::CohesionPlus(std::list<CVehicle*> &neighbors){
  //first find the center of mass of all the agents
  Vector2D CenterOfMass, SteeringForce;

  int NeighborCount = 0;

  //iterate through the neighbors and sum up all the position vectors
  for (CDirectXEntity* pV = WorldMgr->GetWorld()->GetCellSpace()->begin();
       !WorldMgr->GetWorld()->GetCellSpace()->end();     
       pV = WorldMgr->GetWorld()->GetCellSpace()->next())
  {
    //make sure *this* agent isn't included in the calculations and that
    //the agent being examined is close enough
    if(pV != m_pVehicle){
      CenterOfMass += pV->GetPos2D();

      ++NeighborCount;
    }
  }

  if (NeighborCount > 0){
    //the center of mass is the average of the sum of positions
    CenterOfMass /= (double)NeighborCount;

    //now seek towards that position
    SteeringForce = Seek(CenterOfMass);
  }

  //the magnitude of cohesion is usually much larger than separation or
  //allignment so it usually helps to normalize it.
  return Vec2DNormalize(SteeringForce);
}

//--------------------------- Interpose ----------------------------------
//
//  Given two agents, this method returns a force that attempts to 
//  position the CVehicle between them
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::Interpose(CVehicle* AgentA, CVehicle* AgentB){
  //first we need to figure out where the two agents are going to be at 
  //time T in the future. This is approximated by determining the time
  //taken to reach the mid way point at the current time at at max speed.
  Vector2D MidPoint = (AgentA->GetPos2D() + AgentB->GetPos2D()) / 2.0;

  double TimeToReachMidPoint = Vec2DDistance(m_pVehicle->GetPos2D(), MidPoint) /
                               m_pVehicle->GetMaxSpeed();

  //now we have T, we assume that agent A and agent B will continue on a
  //straight trajectory and extrapolate to get their future positions
  Vector2D APos = AgentA->GetPos2D() + AgentA->GetVelocity() * TimeToReachMidPoint;
  Vector2D BPos = AgentB->GetPos2D() + AgentB->GetVelocity() * TimeToReachMidPoint;

  //calculate the mid point of these predicted positions
  MidPoint = (APos + BPos) / 2.0;

  //then steer to Arrive at it
  return Arrive(MidPoint, fast);
}

//--------------------------- Hide ---------------------------------------
//
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::Hide(CVehicle* hunter, std::vector<CObstacle*>& obstacles){
  double    DistToClosest = MaxDouble;
  Vector2D BestHidingSpot;

  std::vector<CObstacle*>::const_iterator curOb = obstacles.begin();
  std::vector<CObstacle*>::const_iterator closest;

  while(curOb != obstacles.end()){
    //calculate the position of the hiding spot for this CObstacle
    Vector2D HidingSpot = GetHidingPosition((*curOb)->GetPos2D(),
                                             (*curOb)->GetRadius(),
                                              hunter->GetPos2D());
            
    //work in distance-squared space to find the closest hiding
    //spot to the agent
    double dist = Vec2DDistanceSq(HidingSpot, m_pVehicle->GetPos2D());

    if (dist < DistToClosest){
      DistToClosest = dist;

      BestHidingSpot = HidingSpot;

      closest = curOb;
    }  
            
    ++curOb;

  }//end while
  
  //if no suitable obstacles found then Evade the hunter
  if (DistToClosest == MaxFloat){
    return Evade(hunter);
  }
      
  //else use Arrive on the hiding spot
  return Arrive(BestHidingSpot, fast);
}

//------------------------- GetHidingPosition ----------------------------
//
//  Given the position of a hunter, and the position and radius of
//  an CObstacle, this method calculates a position DistanceFromBoundary 
//  away from its bounding radius and directly opposite the hunter
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::GetHidingPosition(const Vector2D& posOb,
                                              const double     radiusOb,
                                              const Vector2D& posHunter)
{
  //calculate how far away the agent is to be from the chosen CObstacle's
  //bounding radius
  const double DistanceFromBoundary = 30.0;
  double       DistAway    = radiusOb + DistanceFromBoundary;

  //calculate the heading toward the object from the hunter
  Vector2D ToOb = Vec2DNormalize(posOb - posHunter);
  
  //scale it to size and add to the obstacles position to get
  //the hiding spot.
  return (ToOb * DistAway) + posOb;
}

//------------------------------- FollowPath -----------------------------
//
//  Given a series of Vector2Ds, this method produces a force that will
//  move the agent along the waypoints in order. The agent uses the
// 'Seek' behavior to move to the next waypoint - unless it is the last
//  waypoint, in which case it 'Arrives'
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::FollowPath(){ 
  //move to next _vTarget if close enough to current _vTarget (working in
  //distance squared space)
  if(Vec2DDistanceSq(m_pPath->CurrentWaypoint(), m_pVehicle->GetPos2D()) < m_dWaypointSeekDistSq){
    m_pPath->SetNextWaypoint();
  }

  if (!m_pPath->Finished()){
    return Seek(m_pPath->CurrentWaypoint());
  }
  else{
    return Arrive(m_pPath->CurrentWaypoint(), normal);
  }
}

//------------------------- Offset Pursuit -------------------------------
//
//  Produces a steering force that keeps a CVehicle at a specified offset
//  from a leader CVehicle
//------------------------------------------------------------------------
Vector2D CSteeringBehavior::OffsetPursuit(CVehicle* leader, Vector2D offset){
  //calculate the offset's position in world space
  Vector2D WorldOffsetPos = PointToWorldSpace(offset,
                                              leader->GetHeading(),
                                              leader->GetSide(),
                                              leader->GetPos2D());

  Vector2D ToOffset = WorldOffsetPos - m_pVehicle->GetPos2D();

  //the lookahead time is propotional to the distance between the leader
  //and the pursuer; and is inversely proportional to the sum of both
  //agent's velocities
  double LookAheadTime = ToOffset.Length() / (m_pVehicle->GetMaxSpeed() + leader->GetSpeed());
  
  //now Arrive at the predicted future position of the offset
  return Arrive(WorldOffsetPos + leader->GetVelocity() * LookAheadTime, fast);
}