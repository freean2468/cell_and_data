#include "Kindling.h"
#include "EngineManager.h"

CKindling::CKindling(DU::BoundingBox* _pBoundingBox, int _nNumParticles):CParticle(_pBoundingBox,
																				12.0f,
																				2048,
																				0,
																				512)
{
	for(int i =0;i<_nNumParticles; i++)
		addParticle();

	init(EngineMgr->GetpDevice(), "./Image/Particle/kindling.dds");
}

void CKindling::resetParticle(Attribute* _pAttribute){
	_pAttribute->m_bAlive = true;

	// �Ҿ��� ��ġ ���������� ������ x, z ��ǥ�� ��´�.
	DU::GetRandomVector(
		&_pAttribute->m_vPosition,
		&m_BoundingBox._min,
		&m_BoundingBox._max);

	// ���� (y-��ǥ)�� �׻� ��� ������ ���ϴ��� �ȴ�.
	_pAttribute->m_vPosition.y = m_BoundingBox._min.y;

	// �Ҿ��� �������� ���.
	_pAttribute->m_vVelocity.x = 0.0f;
	_pAttribute->m_vVelocity.y = DU::GetRandomFloat(0.1f, 0.6f)*100.0f;
	_pAttribute->m_vVelocity.z = 0.0f;

	// ���� �Ҿ�
	_pAttribute->m_vColor = DU::WHITE;
}

void CKindling::update(float _fTimeDelta){
	std::list<Attribute>::iterator i;
	for(i = m_Particles.begin(); i != m_Particles.end(); i++){
		i->m_vPosition.y += i->m_vVelocity.y * 0.02f;
		i->m_vPosition.x += sin(i->m_vPosition.y*0.07f);

		// ����Ʈ�� ��踦 ����°�?
		if(m_BoundingBox.isPointInside(i->m_vPosition) == false){
			// ��踦 ��� ��ƼŬ�� ��Ȱ���Ѵ�.
			resetParticle(&(*i));
		}
	}
}