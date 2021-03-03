#include "MapParamLoader.h"

CMapParamLoader::CMapParamLoader(const char* _pstrFile):CFileLoaderBase(_pstrFile)
{
	int x = GetNextParameterInt();
	int y = GetNextParameterInt();
	m_vStart = Vector2D(x, y);

	m_nFirstData						= GetNextParameterInt();
	m_nSecondData						= GetNextParameterInt();
	m_nThirdData						= GetNextParameterInt();
	m_nSumData							= m_nFirstData + m_nSecondData + m_nThirdData;

	m_nFirstSecret				  = GetNextParameterInt();
	m_nSecondSecret					= GetNextParameterInt();

	m_nFirstVacine					= GetNextParameterInt();
	m_nSecondVacine					= GetNextParameterInt();

	m_nDataParticle					= GetNextParameterInt();

	m_bCreateWall						= GetNextParameterBool();
	m_bCreateObstacle 			= GetNextParameterBool();

  NumObstacles            = GetNextParameterInt();
  MinObstacleRadius       = GetNextParameterFloat();
  MaxObstacleRadius       = GetNextParameterFloat();

	WorldWidth							= GetNextParameterInt();
	WorldHeight							= GetNextParameterInt();

  CellSizeX               = GetNextParameterInt();
  CellSizeY		            = GetNextParameterInt();

	int t_nPathNum					= GetNextParameterInt();
	int t_nNum;

	for(int i = 0; i < t_nPathNum; ++i){
		t_nNum = GetNextParameterInt();
		std::list<Vector2D> t_nWayPoints;

		for(int j = 0; j < t_nNum; ++j){
			int x = GetNextParameterInt();
			int y = GetNextParameterInt();
			t_nWayPoints.push_back(Vector2D(x, y));
		}		

		m_VacineWayPoints.push_back(t_nWayPoints);
	}

	t_nPathNum							= GetNextParameterInt();

	for(int i = 0; i < t_nPathNum; ++i){
		t_nNum = GetNextParameterInt();
		std::list<Vector2D> t_nWayPoints;

		for(int j = 0; j < t_nNum; ++j){
			int x = GetNextParameterInt();
			int y = GetNextParameterInt();
			t_nWayPoints.push_back(Vector2D(x, y));
		}		

		m_DataWayPoints.push_back(t_nWayPoints);
	}
}