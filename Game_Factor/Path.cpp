#include "Path.h"
#include "../Engine_Math&Physics/Transformation.h"
#include "../Engine_System/EngineManager.h"

CPath::CPath():m_bLooped(true)/*, 
								m_curWaypoint(NULL)*/
{
		
}

CPath::CPath(int   p_nNumWaypoints,
							double p_dMinX,
							double p_dMinY,
							double p_dMaxX,
							double p_dMaxY,
							bool   p_blooped):m_bLooped(p_blooped)
{
	CreateRandomPath(p_nNumWaypoints, p_dMinX, p_dMinY, p_dMaxX, p_dMaxY);
		
	m_curWaypoint = m_WayPoints.begin();
}

Vector2D CPath::CurrentWaypoint()const{
//	assert(m_curWaypoint != NULL); 

	return *m_curWaypoint;
}

std::list<Vector2D> CPath::CreateRandomPath(int    p_nNumWaypoints,
                                           double p_dMinX,
                                           double p_dMinY,
                                           double p_dMaxX,
                                           double p_dMaxY)
{
  m_WayPoints.clear();

  double t_dMidX = (p_dMaxX+p_dMinX)/2.0;
  double t_dMidY = (p_dMaxY+p_dMinY)/2.0;

  double t_dSmaller = min(t_dMidX, t_dMidY);

  double t_dSpacing = TwoPi/(double)p_nNumWaypoints;

  for (int i=0; i<p_nNumWaypoints; ++i){
    double t_dRadialDist = RandInRange(t_dSmaller*0.2f, t_dSmaller);

    Vector2D t_vTemp(t_dRadialDist, 0.0f);

    Vec2DRotateAroundOrigin(t_vTemp, i*t_dSpacing);

    t_vTemp.x += t_dMidX; t_vTemp.y += t_dMidY;
      
    m_WayPoints.push_back(t_vTemp);
                            
  }

  m_curWaypoint = m_WayPoints.begin();

  return m_WayPoints;
}

void CPath::Render(ID3DXLine* _pLine, D3DXCOLOR* _pColor){
	std::list<Vector2D>::const_iterator t_constItr = m_WayPoints.begin();
	D3DXVECTOR3 p[3];
	D3DXVECTOR3 t_vMiddle;

	Vector2D t_vPrevious = *t_constItr++;
	Vector2D t_vPresent = *t_constItr;

	do{
		p[0].x = static_cast<float>(t_vPrevious.x);	p[0].y = static_cast<float>(t_vPrevious.y);	p[0].z = 0.0f;
		p[1].x = static_cast<float>(t_vPresent.x);	p[1].y = static_cast<float>(t_vPresent.y);	p[1].z = 0.0f;
		p[2].x = static_cast<float>(t_vPrevious.x);	p[2].y = static_cast<float>(t_vPrevious.y);	p[2].z = 0.0f;
		t_vMiddle = p[0] + p[1] / 2.0f;
		if(!EngineMgr->IsViewOut(&p[0]) || !EngineMgr->IsViewOut(&p[1]) || !EngineMgr->IsViewOut(&t_vMiddle)){
			_pLine->DrawTransform(p, 3, &(*EngineMgr->GetWorldMat() * *EngineMgr->GetViewMat() * *EngineMgr->GetProjMat()), *_pColor);
		}

		t_vPresent = *t_constItr++;
		t_vPrevious = *t_constItr;
  }
  while (t_constItr != m_WayPoints.end());
}