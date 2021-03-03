#include "Wall3D.h"
#include "../Engine_System/EngineManager.h"

void CWall3D::CalculateNormal(){
  Vector2D _vtemp = Vec2DNormalize(m_vB - m_vA);

  m_vN.x = -_vtemp.y;
  m_vN.y = _vtemp.x;
}

void CWall3D::Render(ID3DXLine* p_pLine, D3DXCOLOR* p_pColor, bool RenderNormals)const{
	D3DXVECTOR3 p[3];

	p[0].x = (float)m_vA.x;		p[0].y = (float)m_vA.y;		p[0].z = 0.0f;
	p[1].x = (float)m_vB.x;		p[1].y = (float)m_vB.y;		p[1].z = 0.0f;
	p[2].x = (float)m_vA.x;		p[2].y = (float)m_vA.y;		p[2].z = 0.0f;

	p_pLine->DrawTransform(p, 3, &(*EngineMgr->GetWorldMat() * *EngineMgr->GetViewMat() * *EngineMgr->GetProjMat()), *p_pColor);

	//render the normals if rqd
	if (RenderNormals){
		int t_nMidX = (int)((m_vA.x+m_vB.x)/2);
		int t_nMidY = (int)((m_vA.y+m_vB.y)/2);

		p[0].x = (float)t_nMidX;								p[0].y = (float)t_nMidY;									p[0].z = 0.0f;
		p[1].x = (float)(t_nMidX+(m_vN.x * 5));	p[1].y = (float)(t_nMidY+(m_vN.y * 5));		p[1].z = 0.0f;
		p[2].x = (float)t_nMidX;								p[2].y = (float)t_nMidY;									p[2].z = 0.0f;

		p_pLine->DrawTransform(p, 3, &(*EngineMgr->GetWorldMat() * *EngineMgr->GetViewMat() * *EngineMgr->GetProjMat()), *p_pColor);
	}
}