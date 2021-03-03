#include "MovingEntity.h"
	
//---------------------------- Adaptor ----------------------------------
void CMovingEntity::OrganUpdate(){
	if(GetBody() && !this->IsHide()){
		GetBody()->GetPriPos()->x = GetPos3D()->x;
		GetBody()->GetPriPos()->y = GetPos3D()->y;

		GetBody()->GetPriRot()->z = (float)GetAngleToFacePositionForOrgan();
	}
}

double CMovingEntity::GetAngleToFacePositionForOrgan(){
	Vector2D O(0, 1);
	
	O.Normalize();

	double angle = acos(m_vHeading.Dot(O));

	// x가 양수 방향을 가리키면 회전 각도를 음수로 바꿔줘야 한다.
	if(m_vHeading.x > 0)
		angle = -angle;

	return angle;
}