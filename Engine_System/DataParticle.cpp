#include "DataParticle.h"
#include "EngineManager.h"

CDataParticle::CDataParticle(DU::BoundingBox* _pBoundingBox, int _nNumParticles):CParticle(_pBoundingBox,
																							2.0f,
																							512,
																							0,
																							256)
{
	for(int i =0;i<_nNumParticles; i++)
		addParticle();

	init(EngineMgr->GetpDevice(), "./Image/Particle/DataParticle.bmp");
}

void CDataParticle::resetParticle(Attribute* _pAttribute){
	_pAttribute->m_bAlive = true;

	D3DXVECTOR3 min = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	D3DXVECTOR3 max = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	DU::GetRandomVector(&_pAttribute->m_vVelocity,
		&min,
		&max);

	D3DXVec3Normalize(
		&_pAttribute->m_vVelocity,
		&_pAttribute->m_vVelocity);

	_pAttribute->m_vVelocity *= 10.0f;

	DU::GetRandomVector(
		&_pAttribute->m_vPosition,
		&m_BoundingBox._min,
		&m_BoundingBox._max);

	_pAttribute->m_vColor = D3DXCOLOR(1.0f/255.0f, 255.0f/255.0f, 1.0f/255.0f,	255.0f/255.0f);
}

void CDataParticle::update(float _fTimeDelta){
	std::list<Attribute>::iterator i;
	for(i = m_Particles.begin(); i != m_Particles.end(); i++){
		i->m_vPosition += i->m_vVelocity * _fTimeDelta;

		// ����Ʈ�� ��踦 ����°�?
		if(m_BoundingBox.isPointInside(i->m_vPosition) == false){
			// ��踦 ��� ��ƼŬ�� ��Ȱ���Ѵ�.
			resetParticle(&(*i));
		}
	}
}

void CDataParticle::preRender(){
	CParticle::preRender();

	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// z-���� �б�� ���������� ����� ������ �ʴ´�.
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void CDataParticle::postRender(){
	CParticle::postRender();

	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}