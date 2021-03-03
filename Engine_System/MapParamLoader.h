#ifndef _MapParamLoader_H_
#define _MapParamLoader_H_

//-----------------------------------------------------------------------------
//
//  Name:   CMapMapParamLoader.h
//
//  Desc:   맵 설정 관련 수치들을 로드
//-----------------------------------------------------------------------------

#include "FileLoaderBase.h"
#include "../Engine_Math&Physics/Vector2D.h"
#include <list>
#include <vector>

class CMapParamLoader : public CFileLoaderBase{
public:
  CMapParamLoader(const char* _pstrFile);
	~CMapParamLoader(){}

public:
	Vector2D m_vStart;

  int	m_nFirstData;
	int m_nSecondData;
	int m_nThirdData;
	int m_nSumData;

	int m_nFirstSecret;
	int m_nSecondSecret;

	int m_nFirstVacine;
	int m_nSecondVacine;

	int m_nDataParticle;

	bool m_bCreateWall;
	bool m_bCreateObstacle;

  int	NumObstacles;
  double MinObstacleRadius;
  double MaxObstacleRadius;

	int		WorldWidth;			
  int   WorldHeight;
  int   CellSizeX;
	int		CellSizeY;

	std::vector< std::list<Vector2D> >	m_VacineWayPoints;
	std::vector< std::list<Vector2D> >	m_DataWayPoints;
};

#endif