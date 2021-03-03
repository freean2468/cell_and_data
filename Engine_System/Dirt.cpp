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

	// ������ ��ġ ���������� ������ x, z ��ǥ�� ��´�.
	DU::GetRandomVector(
		&_pAttribute->m_vPosition,
		&m_BoundingBox._min,
		&m_BoundingBox._max);

	// ���� (y-��ǥ)�� �׻� ��� ������ �ֻ���� �ȴ�.
	_pAttribute->m_vPosition.y = m_BoundingBox._max.y;

	// ������ �Ʒ������� �������� �ణ ������ ���Ѵ�.
	_pAttribute->m_vVelocity.x = DU::GetRandomFloat(0.3f, 1.0f)*-120.0f;
	_pAttribute->m_vVelocity.y = DU::GetRandomFloat(0.3f, 1.0f)*-400.0f;
	_pAttribute->m_vVelocity.z = 0.0f;

	// ȸ���� ����
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

		// ����Ʈ�� ��踦 ����°�?
		if(m_BoundingBox.isPointInside(i->m_vPosition) == false){
			// ��踦 ��� ��ƼŬ�� ��Ȱ���Ѵ�.
			resetParticle(&(*i));
		}
	}
}