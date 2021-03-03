#include "SpreadParticle.h"
#include "EngineManager.h"

CSpreadParticle::CSpreadParticle(const char* _Adress, D3DXVECTOR3 _vOrigin, D3DXCOLOR _Color, 
																	float _fSize, int _nNumParticles, float _fLifeTime):CParticle(_fSize,
																																64,
																																0,
																																32)
{
	for(int i =0;i<_nNumParticles; i++)
		addParticle();

	m_vOrigin = _vOrigin;
	m_fLifeTime = _fLifeTime;
	m_Color = _Color;
	m_fSetSize = _fSize;

	init(EngineMgr->GetpDevice(), _Adress);
}

void CSpreadParticle::resetParticle(Attribute* _pAttribute){
	_pAttribute->m_bAlive = true;
	m_fSize = (float)RandInRange(m_fSetSize*0.5f, m_fSetSize*1.5f);

	_pAttribute->m_fAge = 0.0f;
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

	_pAttribute->m_vVelocity *= 50.0f;

	_pAttribute->m_vColor = D3DXCOLOR(m_Color);

	_pAttribute->m_fLifeTime = (float)::RandInRange(m_fLifeTime * 0.5, m_fLifeTime * 1.5);
}

void CSpreadParticle::update(float _fTimeDelta){
	std::list<Attribute>::iterator i;
	for(i = m_Particles.begin(); i != m_Particles.end(); i++){
		// 생존한 파티클만 갱신한다.
		if(i->m_bAlive){
			i->m_vPosition += i->m_vVelocity * _fTimeDelta;

			i->m_fAge += _fTimeDelta;

			if(i->m_fAge > i->m_fLifeTime){ // 죽인다.
				resetParticle(&(*i));
			}
		}
	}
}