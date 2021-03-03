#ifndef WALL_H
#define WALL_H

//------------------------------------------------------------------------
//
//  Name:   CWall3D.h
//
//  Desc:   class to create and render 2D walls. Defined as the two 
//          vectors A - B with a perpendicular normal. 
//          
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//	Modifier : Hoon-il Song (Sider)
//
//------------------------------------------------------------------------

#include "../Engine_Math&Physics/Vector2D.h"
#include <iostream>
#include <fstream>

class CWall3D{
protected:
  Vector2D    m_vA,
              m_vB,
              m_vN;

public:
  CWall3D(){}

  CWall3D(Vector2D p_vA, Vector2D p_vB):m_vA(p_vA), m_vB(p_vB)
  {
    CalculateNormal();
  }

  CWall3D(Vector2D p_vA, Vector2D p_vB, Vector2D p_vN):m_vA(p_vA), m_vB(p_vB), m_vN(p_vN)
  { }

  CWall3D(std::ifstream& _rifs){Read(_rifs);}

	void CalculateNormal();

  virtual void Render(ID3DXLine* p_pLine, D3DXCOLOR* p_pColor, bool RenderNormals = false)const;

  Vector2D From()const  {return m_vA;}
  void     SetFrom(Vector2D v){m_vA = v; CalculateNormal();}

  Vector2D To()const    {return m_vB;}
  void     SetTo(Vector2D v){m_vB = v; CalculateNormal();}
  
  Vector2D Normal()const{return m_vN;}
  void     SetNormal(Vector2D n){m_vN = n;}
  
  Vector2D Center()const{return (m_vA+m_vB)/2.0;}

  std::ostream& CWall3D::Write(std::ostream& _ros)const
  {
    _ros << std::endl;
    _ros << From() << ",";
    _ros << To() << ",";
    _ros << Normal();
    return _ros;
  }

 void Read(std::ifstream& _rifs){
    double x,y;

    _rifs >> x >> y;
    SetFrom(Vector2D(x,y));

    _rifs >> x >> y;
    SetTo(Vector2D(x,y));

    _rifs >> x >> y;
    SetNormal(Vector2D(x,y));
  }  
};

#endif