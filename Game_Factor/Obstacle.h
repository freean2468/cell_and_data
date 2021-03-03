#ifndef OBSTACLE_H
#define OBSTACLE_H

//------------------------------------------------------------------------
//
//  Name:   CObstacle.h
//
//  Desc:   Simple CObstacle class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//	Modifier : Hoon-il Song (Sider)
//
//------------------------------------------------------------------------

#include "../Engine_System/OrganEntity.h"
#include "../Engine_Math&Physics/Vector2D.h"
#include <fstream>

class CObstacle : public COrganEntity
{
public:
  CObstacle(double _dX, double _dY, double _dResize);

  CObstacle(Vector2D _vPos, double _dResize);

  CObstacle(std::ifstream& _rifs){Read(_rifs);}

  virtual ~CObstacle(){}

  //this is defined as a pure virtual function in CBaseEntity so
  //it must be implemented
  virtual void      Update(double _dTimeElapsed);
};

#endif