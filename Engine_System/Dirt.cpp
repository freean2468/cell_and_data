#include "Dirt.h"
#include "EngineManager.h"

CDirt::CDirt(DU::BoundingBox* _pBoundingBox, int _nNumParticles) : CParticle(_pBoundingBox,
																				12.0f,
																				2048,
																				0,
																				512)
{
	for(int i =0;i<_nNumParticles; i++)
		addParticle();

	init(EngineMgr->GetpDevice(), "./Image/Particle/Dirt.dds");
}

void CDirt::resetParticle(Attribute* _pAttribute){
	_pAttribute->m_bAlive = true;

	// 먼지의 위치 지정을위해 임의의 x, z 좌표를 얻는다.
	DU::GetRandomVector(
		&_pAttribute->m_vPosition,
		&m_BoundingBox._min,
		&m_BoundingBox._max);

	// 높이 (y-좌표)는 항상 경계 상자의 최상단이 된다.
	_pAttribute->m_vPosition.y = m_BoundingBox._max.y;

	// 먼지는 아래쪽으로 떨어지며 약간 왼쪽을 향한다.
	_pAttribute->m_vVelocity.x = DU::GetRandomFloat(0.3f, 1.0f)*-120.0f;
	_pAttribute->m_vVelocity.y = DU::GetRandomFloat(0.3f, 1.0f)*-400.0f;
	_pAttribute->m_vVelocity.z = 0.0f;

	// 회색의 먼지
	_pAttribute->m_vColor = DU::RED;
}

void CDirt::update(float _fTimeDelta){
	std::list<Attribute>::iterator i;
	for(i = m_Particles.begin(); i != m_Particles.end(); i++){

		if((rand() % 2) == 0)
			i->m_vVelocity.x+=1.0f;
		else
			i->m_vVelocity.x-=1.0f;

		i->m_vPosition += i->m_vVelocity * 0.02f;

		// 포인트가 경계를 벗어났는가?
		if(m_BoundingBox.isPointInside(i->m_vPosition) == false){
			// 경계를 벗어난 파티클을 재활용한다.
			resetParticle(&(*i));
		}
	}
}