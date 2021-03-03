////////////////////////////////////////////////////////////////////////////////
// 파티클 총 구현 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _ParticleGun_H_
#define _ParticleGun_H_

#include "Particle.h"
#include "Camera.h"

class CParticleGun : public CParticle{
public:
	CParticleGun(CCamera* _pCamera);
	void resetParticle(Attribute* _pAttribute);
	void update(float _fTimeDelta);

private:
	CCamera* m_pCamera;
};

#endif