#include "Snow.h"

CSnow::CSnow(DU::BoundingBox* _pBoundingBox, int _nNumParticles):CParticle(_pBoundingBox,
																			40.0f,
																			2048,
																			0,
																			512)
{
	for(int i =0;i<_nNumParticles; i++)
		addParticle();
}

void CSnow::resetParticle(Attribute* _pAttribute){
	_pAttribute->m_bAlive = true;

	// 눈송이의 위치 지정을위해 임의의 x, z 좌표를 얻는다.
	DU::GetRandomVector(
		&_pAttribute->m_vPosition,
		&m_BoundingBox._min,
		&m_BoundingBox._max);

	// 높이 (y-좌표)는 항상 경계 상자의 최상단이 된다.
	_pAttribute->m_vPosition.y = m_BoundingBox._max.y;

	// 눈송이는 아래쪽으로 떨어지며 약간 왼쪽을 향한다.
	_pAttribute->m_vVelocity.x = DU::GetRandomFloat(0.0f, 1.0f)*-120.0f;
	_pAttribute->m_vVelocity.y = DU::GetRandomFloat(0.0f, 1.0f)*-400.0f;
	_pAttribute->m_vVelocity.z = 0.0f;

	// 회색의 눈송이
	_pAttribute->m_vColor = DU::WHITE;
}

void CSnow::update(float _fTimeDelta){
	std::list<Attribute>::iterator i;
	for(i = m_Particles.begin(); i != m_Particles.end(); i++){
		i->m_vPosition += i->m_vVelocity * _fTimeDelta;

		// 포인트가 경계를 벗어났는가?
		if(m_BoundingBox.isPointInside(i->m_vPosition) == false){
			// 경계를 벗어난 파티클을 재활용한다.
			resetParticle(&(*i));
		}
	}
}