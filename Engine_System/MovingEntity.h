#ifndef _MovingEntity_H_
#define _MovingEntity_H_

#include "../Engine_Math&Physics/Matrix3X3.h"
#include "OrganEntity.h"

class CMovingEntity : public COrganEntity{
protected:
	Vector2D m_vVelocity;

	// 엔티티가 향하고 있는 방향을 가리키는 정규화된 벡터
	Vector2D m_vHeading;

	// 방향 벡터에 수직인 벡터
	Vector2D m_vSide;

	double   m_dMass;

	//the maximum speed this entity may travel at.
	double   m_dMaxSpeed;

	//the maximum force this entity can produce to power itself 
	//(think rockets and thrust)
	double   m_dMaxForce;

	//the maximum rate (radians per second)this vehicle can rotate         
	double   m_dMaxTurnRate;

public:
	CMovingEntity(int _nEntityType,
								Vector2D _vPos,
								Vector2D _vVelocity, 
								double _dMaxSpeed,
								Vector2D _vHeading, 
								double _dMass,  
								double _dTurnRate, 
								double _dMaxForce): COrganEntity(_nEntityType),
																		m_vHeading(_vHeading),
																		m_vVelocity(_vVelocity),
																		m_dMass(_dMass),
																		m_vSide(m_vHeading.Perp()),
																		m_dMaxSpeed(_dMaxSpeed),
																		m_dMaxTurnRate(_dTurnRate),
																		m_dMaxForce(_dMaxForce)
	{
	  this->SetPos(_vPos);
	}

	virtual ~CMovingEntity(){}

	//-------------------------------------------adaptor methods
	virtual	void				OrganUpdate();
	double							GetAngleToFacePositionForOrgan();

	//accessors
	Vector2D  GetVelocity()const{return m_vVelocity;}
	void      SetVelocity(const Vector2D& r_vNewVel){m_vVelocity = r_vNewVel;}

	void	    SetMass(double _dMass){m_dMass = _dMass;}
	double    GetMass()const{return m_dMass;}

	void			SetSide(Vector2D _vSide){m_vSide = _vSide;}
	Vector2D  GetSide()const{return m_vSide;}

	double    GetMaxSpeed()const{return m_dMaxSpeed;}                       
	void      SetMaxSpeed(double _dNewSpeed){m_dMaxSpeed = _dNewSpeed;}

	double    GetMaxForce()const{return m_dMaxForce;}
	void      SetMaxForce(double _dNewMaxForce){m_dMaxForce = _dNewMaxForce;}

	bool      IsSpeedMaxedOut()const{return m_dMaxSpeed*m_dMaxSpeed >= m_vVelocity.LengthSq();}
	double    GetSpeed()const{return m_vVelocity.Length();}
	double    GetSpeedSq()const{return m_vVelocity.LengthSq();}

	Vector2D  GetHeading()const{return m_vHeading;}
	void      SetHeading(Vector2D _vNewHeading);
	bool      RotateHeadingToFacePosition(Vector2D _vTarget);

	double    GetMaxTurnRate()const{return m_dMaxTurnRate;}
	void      SetMaxTurnRate(double _dVal){m_dMaxTurnRate = _dVal;}
};

//--------------------------- RotateHeadingToFacePosition ---------------------
//
//  given a _vTarget position, this method rotates the entity's heading and
//  side vectors by an amount not greater than m_dMaxTurnRate until it
//  directly faces the _vTarget.
//
//  returns true when the heading is facing in the desired direction
//-----------------------------------------------------------------------------
inline bool CMovingEntity::RotateHeadingToFacePosition(Vector2D _vTarget){
  Vector2D toTarget = Vec2DNormalize(_vTarget - Vector2D((double)m_vPos.x, (double)m_vPos.y));

  //first determine the angle between the heading vector and the _vTarget
  double angle = acos(m_vHeading.Dot(toTarget));

  //return true if the player is facing the _vTarget
  if (angle < 0.00001) return true;

  //clamp the amount to turn to the max turn rate
  if (angle > m_dMaxTurnRate) angle = m_dMaxTurnRate;
  
  //The next few lines use a _dRotation matrix to rotate the player's heading
  //vector accordingly
  CMatrix3X3 RotationMatrix;
  
  //notice how the direction of rotation has to be determined when creating
  //the rotation matrix
  RotationMatrix.Rotate(angle * m_vHeading.Sign(toTarget));	
  RotationMatrix.TransformVector2Ds(m_vHeading);
  RotationMatrix.TransformVector2Ds(m_vVelocity);

  //finally recreate m_vSide
  m_vSide = m_vHeading.Perp();

  return false;
}

//------------------------- SetHeading ----------------------------------------
//
//  first checks that the given heading is not a vector of zero length. If the
//  new heading is valid this function sets the entity's heading and side 
//  vectors accordingly
//-----------------------------------------------------------------------------
inline void CMovingEntity::SetHeading(Vector2D _vNewHeading){
  assert( (_vNewHeading.LengthSq() - 1.0) < 0.00001);
  
  m_vHeading = _vNewHeading;

  //the side vector must always be perpendicular to the heading
  m_vSide = m_vHeading.Perp();
}

#endif