#include "Exhaust.h"
#include "EngineManager.h"

CExhaust::CExhaust(DU::BoundingBox* _pBoundingBox, D3DXVECTOR3* _pvOrigin, int _nNumParticles) :
																					CParticle(_pBoundingBox,
																							_pvOrigin,
																							40.0f,
																							2048,
																							0,
																							1024)
{
	for(int i =0;i<_nNumParticles; i++)
		addParticle();

	init(EngineMgr->GetpDevice(), "./Image/Particle/Exhaust.dds");
}

void CExhaust::resetParticle(Attribute* _pAttribute){
	_pAttribute->m_bAlive = true;
	_pAttribute->m_vPosition = m_vOrigin;

	// �ſ� ������ ���� ���Ѵ�.
	_pAttribute->m_vVelocity.x = DU::GetRandomFloat(-1.0f, 1.0f)*600.0f;
	_pAttribute->m_vVelocity.y = DU::GetRandomFloat(0.2f, 0.9f)*300.0f;
	_pAttribute->m_vVelocity.z = DU::GetRandomFloat(0.0f, 1.0f)*10.0f; // ���� ��������� ���� Ŀ���鼭 ���������� ���� ȿ��

	// ��ƼŬ �� ����
	_pAttribute->m_vColor = DU::WHITE;
	_pAttribute->m_vColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

void CExhaust::update(float _fTimeDelta){
	std::list<Attribute>::iterator i;
	for(i = m_Particles.begin(); i != m_Particles.end(); i++){
		i->m_vPosition += i->m_vVelocity * 0.001f/* * p_fTimeDelta */;

		// ����Ʈ�� ��踦 ����°�?
		if(m_BoundingBox.isPointInside(i->m_vPosition) == false){
			// ��踦 ��� ��ƼŬ�� ��Ȱ���Ѵ�.
			resetParticle(&(*i));
		}
	}
}