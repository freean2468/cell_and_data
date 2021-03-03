#include "Firework.h"

CFirework::CFirework(D3DXVECTOR3* _pvOrigin, int _nNumParticles) : CParticle(_pvOrigin,
																				0.9f,
																				2048,
																				0,  
																				512)
{
	for(int i = 0; i < _nNumParticles; i++)
		addParticle();
}

void CFirework::resetParticle(Attribute* _pAttribute){
	_pAttribute->m_bAlive = true;
	_pAttribute->m_vPosition = m_vOrigin;

	D3DXVECTOR3 min = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	D3DXVECTOR3 max = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	DU::GetRandomVector(&_pAttribute->m_vVelocity,
		&min,
		&max);

	// 구체를 만들기 위한 정규화
	D3DXVec3Normalize(
		&_pAttribute->m_vVelocity,
		&_pAttribute->m_vVelocity);

	_pAttribute->m_vVelocity *= 400.0f;

	_pAttribute->m_vColor = D3DXCOLOR(
		DU::GetRandomFloat(0.0f, 1.0f),
		DU::GetRandomFloat(0.0f, 1.0f),
		DU::GetRandomFloat(0.0f, 1.0f),
		1.0f);

	_pAttribute->m_fAge = 0.0f;
	_pAttribute->m_fLifeTime = 2.0f;	// 2초 동안의 수명을 가진다.
}

void CFirework::update(float _fTimeDelta){
	std::list<Attribute>::iterator i;

	for(i = m_Particles.begin();i!=m_Particles.end(); i++){
		// 생존한 파티클만 갱신한다.
		if(i->m_bAlive){
			i->m_vPosition += i->m_vVelocity * _fTimeDelta;

			i->m_fAge += _fTimeDelta;

			if(i->m_fAge > i->m_fLifeTime) // 죽인다.
				i->m_bAlive = false;
		}
	}
}

void CFirework::preRender(){
	CParticle::preRender();

	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// z-버퍼 읽기는 가능하지만 쓰기는 허용되지 않는다.
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void CFirework::postRender(){
	CParticle::postRender();

	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}