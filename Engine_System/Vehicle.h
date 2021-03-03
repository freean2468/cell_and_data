#ifndef _Vehicle_H_
#define _Vehicle_H_

#include "MovingEntity.h"
#include "SteeringBehavior.h"
#include "../Engine_Misc/Smoother.h"

//------------------------------------------------------------------------
//
//  Name:   CVehicle.h
//
//------------------------------------------------------------------------

class CSteeringBehavior;
class CVehicleWorld;

class CVehicle : public CMovingEntity{
protected:
  //the steering behavior class
  CSteeringBehavior*    m_pSteering;

  //some steering behaviors give jerky looking movement. The
  //following members are used to smooth the CVehicle's heading
  CSmoother<Vector2D>*  m_pHeadingSmoother;

  //this vector represents the average of the CVehicle's heading
  //vector smoothed over the last few frames
  Vector2D						  m_vSmoothedHeading;

  //when true, smoothing is active
  bool                  m_bSmoothingOn;
  
  //keeps a track of the most recent update time. (some of the
  //steering behaviors make use of this - see Wander)
  double                m_dTimeElapsed;

  //disallow the copying of CVehicle types
  CVehicle(const CVehicle&);
  CVehicle& operator=(const CVehicle&);

public:
  CVehicle(int _nEntityType, Vector2D _vPos, Vector2D _vHeading, Vector2D _vVelocity,
         double _dMass, double _dMaxForce, double _dMaxSpeed, double _dMaxTurnRate);

  ~CVehicle();

  //updates the CVehicle's position and orientation
  virtual void        Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

  void						    Render();

	//-------------------------------------------adaptor methods
	virtual	void				OrganUpdate();
	double							GetAngleToFacePositionForOrgan();
                                                                          
  //-------------------------------------------accessor methods
  CSteeringBehavior*const  GetSteering()const{return m_pSteering;}
  
  Vector2D    GetSmoothedHeading()const{return m_vSmoothedHeading;}

  bool        isSmoothingOn()const{return m_bSmoothingOn;}
  void        SmoothingOn(){m_bSmoothingOn = true;}
  void        SmoothingOff(){m_bSmoothingOn = false;}
  void        ToggleSmoothing(){m_bSmoothingOn = !m_bSmoothingOn;}
  
  double      TimeElapsed()const{return m_dTimeElapsed;}
};

#endif