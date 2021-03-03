#include "Gravity.h"
#include "../Engine_Math&Physics/Transformation.h"
#include "../Engine_Misc/DirectUtils.h"

CGravity::CGravity(CMovingEntity* _pOrigin, float _fRadius, bool _bStatic, float _fAngle): 	m_pOrigin(_pOrigin),
																							m_fRadius(_fRadius),
																							m_fAngle(_fAngle),
																							m_bStatic(_bStatic),
																							m_fGravity(1.0f)
{
	m_pOrigin->SetRotZ(m_fAngle);
}

CGravity::~CGravity(){

}

void CGravity::CalGravity(Vector2D _vTarget){
	Vec2DRotateAroundOrigin(m_pOrigin->GetPos2D(), m_fAngle);

	Vector2D t_vPos;

	if(m_pOrigin->GetPos2D().x != 0 || m_pOrigin->GetPos2D().y != 0)
		t_vPos = m_pOrigin->GetPos2D();
	else
		t_vPos = Vector2D(0, 1);

	if(!m_bStatic)		t_vPos += _vTarget;

	t_vPos.Normalize();

	m_pOrigin->SetRotZ(DU::CalAngleConsiderTexture(t_vPos));
	m_pOrigin->SetHeading(t_vPos);
	m_pOrigin->SetSide(t_vPos.Perp());

	t_vPos = t_vPos * m_fRadius * m_fGravity;
	m_pOrigin->SetPos(t_vPos);
}

bool CGravity::IsWithinPlanet(){
	if(m_fRadius > m_pOrigin->GetPos2D().Length()-m_pOrigin->GetRadius())
		return true;

	return false;
}