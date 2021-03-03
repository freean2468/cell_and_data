#ifndef _PATH_H_
#define _PATH_H_

//------------------------------------------------------------------------
//
//  Name:   CPath.h
//
//  Desc:   class to define, manage, and traverse a CPath (defined by a series of 2D vectors)
//          
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//	Modifier : Hoon-il Song (Sider)
//
//------------------------------------------------------------------------

#include <list>
#include "../Engine_Math&Physics/Vector2D.h"

class CPath{
private:  
  std::list<Vector2D>            m_WayPoints;

  //points to the current waypoint
  std::list<Vector2D>::iterator  m_curWaypoint;

  //flag to indicate if the CPath should be looped
  //(The last waypoint connected to the first)
  bool                           m_bLooped;

public:
	// First Create, and Initialization(Setting WayPoints) do later.
  CPath();

  //constructor for creating a CPath with initial random waypoints. MinX/Y
  //& MaxX/Y define the bounding box of the CPath.
  CPath(int    p_nNumWaypoints,
       double p_dMinX,
       double p_dMinY,
       double p_dMaxX,
       double p_dMaxY,
       bool   p_blooped);


  //returns the current waypoint
  Vector2D    CurrentWaypoint()const;

  //returns true if the end of the list has been reached
  bool        Finished(){return !(m_curWaypoint != m_WayPoints.end());}
  
  //moves the iterator on to the next waypoint in the list
  inline void SetNextWaypoint();

  //creates a random CPath which is bound by rectangle described by
  //the min/max values
  std::list<Vector2D> CreateRandomPath(int    p_nNumWaypoints,
                                       double p_dMinX,
                                       double p_dMinY,
                                       double p_dMaxX,
                                       double p_dMaxY);


  void LoopOn(){m_bLooped = true;}
  void LoopOff(){m_bLooped = false;}

  //methods for setting the CPath with either another CPath or a list of vectors
  void Set(std::list<Vector2D> p_NewPath){m_WayPoints = p_NewPath;m_curWaypoint = m_WayPoints.begin();}
  void Set(CPath& p_rPath){m_WayPoints=p_rPath.GetPath(); m_curWaypoint = m_WayPoints.begin();}

  void Clear(){m_WayPoints.clear();}

  std::list<Vector2D>& GetPath(){return m_WayPoints;}

  void Render(ID3DXLine* _pLine, D3DXCOLOR* _pColor); 
};

//-------------------- Methods -------------------------------------------

inline void CPath::SetNextWaypoint(){    
  if (++m_curWaypoint == m_WayPoints.end()){
    if (m_bLooped){
      m_curWaypoint = m_WayPoints.begin(); 
    }
  }
}  

#endif