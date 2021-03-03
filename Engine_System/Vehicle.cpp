#include "Vehicle.h"
#include "../Game_Factor/WorldManager.h"

//----------------------------- ctor -------------------------------------
//------------------------------------------------------------------------
CVehicle::CVehicle(int _nEntityType,
					Vector2D _vPos, 
					Vector2D _vHeading,
					Vector2D _vVelocity,
					double _dMass, 
					double _dMaxForce, 
					double _dMaxSpeed, 
					double _dMaxTurnRate) : CMovingEntity(_nEntityType,
														_vPos,
														_vVelocity, 
														_dMaxSpeed,
														_vHeading,
														_dMass, 
														_dMaxTurnRate, 
														_dMaxForce),
											m_vSmoothedHeading(Vector2D(0,0)),
											m_bSmoothingOn(false),
											m_dTimeElapsed(0.0)
{  
  //set up the steering behavior class
  m_pSteering = new CSteeringBehavior(this);    

  //set up the CSmoother
  m_pHeadingSmoother = new CSmoother<Vector2D>(WorldMgr->GetSteeringParam()->NumSamplesForSmoothing, 
																								Vector2D(0.0, 0.0)); 
}

//---------------------------- dtor -------------------------------------
//-----------------------------------------------------------------------
CVehicle::~CVehicle(){
	Delete<CSteeringBehavior*>(m_pSteering);
	Delete<CSmoother<Vector2D>*>(m_pHeadingSmoother);
}

//---------------------------- Adaptor ----------------------------------
void CVehicle::OrganUpdate(){
	if(GetBody() && !this->IsHide()){
		GetBody()->GetPriPos()->x = (float)GetPos2D().x;
		GetBody()->GetPriPos()->y = (float)GetPos2D().y;

		GetBody()->GetPriRot()->z = (float)GetAngleToFacePositionForOrgan();
	}
}

double CVehicle::GetAngleToFacePositionForOrgan(){
	Vector2D O(0, 1);
	
	O.Normalize();

  double Dot = m_vHeading.Dot(O);

	double angle = acos(m_vHeading.Dot(O));

	// x가 양수 방향을 가리키면 회전 각도를 음수로 바꿔줘야 한다.
	if(m_vHeading.x > 0)
		angle = -angle;

	return angle;
}

//------------------------------ Update ----------------------------------
//
//  Updates the CVehicle's position from a series of steering behaviors
//------------------------------------------------------------------------
void CVehicle::Update(double _dTimeElapsed){    
  //update the time elapsed
  m_dTimeElapsed = _dTimeElapsed;

  //keep a record of its old position so we can update its cell later
  //in this method
  Vector2D OldPos = GetPos2D();

  Vector2D SteeringForce;

  //calculate the combined force from each steering behavior in the 
  //CVehicle's list
  SteeringForce = m_pSteering->Calculate();
    
  //Acceleration = Force/Mass
  Vector2D acceleration = SteeringForce / m_dMass;

  //update velocity
  m_vVelocity += acceleration * _dTimeElapsed; 

  //make sure CVehicle does not exceed maximum velocity
  m_vVelocity.Truncate(m_dMaxSpeed);

  //update the position
  SetPos(GetPos2D() += (m_vVelocity * _dTimeElapsed));

  //update the heading if the CVehicle has a non zero velocity
  if(m_vVelocity.LengthSq() > 0.00000001){    
    m_vHeading = Vec2DNormalize(m_vVelocity);

    m_vSide = m_vHeading.Perp();
  }

  //treat the screen as a toroid
  //WrapAround(GetPos2D(), m_pVehicleWorld->cxClient(), m_pVehicleWorld->cyClient());

  //update the CVehicle's current cell if space partitioning is turned on
  if(GetSteering()->isSpacePartitioningOn()){
  //  GetVehicleWorld()->GetCellSpace()->UpdateEntity(this, OldPos);
  }

  if(isSmoothingOn()){
    m_vSmoothedHeading = m_pHeadingSmoother->Update(GetHeading());
  }

	// OrganUpdate
	OrganUpdate();
}

//-------------------------------- Render -------------------------------------
//-----------------------------------------------------------------------------
void CVehicle::Render(){ 
	COrganEntity::RenderOrgan();
}