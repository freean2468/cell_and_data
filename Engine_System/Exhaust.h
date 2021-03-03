////////////////////////////////////////////////////////////////////////////////
// 매연 효과
////////////////////////////////////////////////////////////////////////////////
#ifndef _Exhaust_H_
#define _Exhaust_H_

#include "Particle.h"

class CExhaust : public CParticle{
public:
	CExhaust(DU::BoundingBox* _pBoundingBox, D3DXVECTOR3* _pvOrigin, int _nNumParticles);
	void resetParticle(Attribute* _pAttribute);
	void update(float _fTimeDelta);
};

#endif