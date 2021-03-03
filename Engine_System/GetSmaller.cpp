#include "GetSmaller.h"
#include "EngineManager.h"
#include "CollisionManager.h"

CGetSmaller::CGetSmaller(CDirectXEntity* _pOrigin, const char* _strpFileName, float _fSize, 
														float _fFrequency, int _nNumParticles, bool _bLoop, 
														float _fMin, float _fMax, D3DXVECTOR3 _vSpot):	CParticle(_fSize,
																												512,
																												0,
																												256),
																							m_pOrigin(_pOrigin),
																							m_bLoop(_bLoop),
																							m_fFrequency(_fFrequency),
																							m_fMin(_fMin),
																							m_fMax(_fMax),
																							m_vSpot(_vSpot)
{
	for(int i =0;i<_nNumParticles; i++)
		addParticle();

	init(EngineMgr->GetpDevice(), "./Image/Particle/Kindling.dds");
}

CGetSmaller::~CGetSmaller(){

}

void CGetSmaller::resetParticle(Attribute* _pAttribute){
	_pAttribute->m_bAlive = true;

	// 위치 지정을위해 임의의 x, y 좌표를 얻는다.
	_pAttribute->m_vPosition = *m_pOrigin->GetTransPos3D() + m_vSpot;
	
	// 뻗어갈 방향
	Vector2D _vHeading;
	Vector2D _vNormal(-1, 0);

	do{
		_vHeading = Vector2D(::RandInRange(-100,100), ::RandInRange(-100,100));

		_vHeading.Normalize();

	}while(m_fMin < acos(_vHeading.Dot(_vNormal)) && m_fMax > acos(_vHeading.Dot(_vNormal)));

	_pAttribute->m_vVelocity.x = DU::GetRandomFloat(1.0f, 1.7f) * (float)_vHeading.x * 2.0f;
	_pAttribute->m_vVelocity.y = DU::GetRandomFloat(1.0f, 1.7f) * (float)_vHeading.y * 2.0f;
	_pAttribute->m_vVelocity.z = 0.0f;

	_pAttribute->m_vColor = DU::RED;
}

void CGetSmaller::update(float _fTimeDelta){
	std::list<Attribute>::iterator i;

	for(i = m_Particles.begin(); i != m_Particles.end(); ++i){
		i->m_vPosition.y += i->m_vVelocity.y;
		i->m_vPosition.x += i->m_vVelocity.x;

		if(CollisionMgr->Collision2DRadiusWithPoint(m_pOrigin->GetTransPos3D(), m_pOrigin->GetRadius(),	&i->m_vPosition)
			|| !CollisionMgr->Collision2DRadiusWithPoint(m_pOrigin->GetTransPos3D(), m_pOrigin->GetRadius()*1.5f,	&i->m_vPosition)){
			if(m_bLoop){
				// 경계를 벗어난 파티클을 재활용한다.
				resetParticle(&(*i));
			}
		}
	}
}