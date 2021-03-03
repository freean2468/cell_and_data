////////////////////////////////////////////////////////////////////////////////
// 불씨가 올라가는 효과
////////////////////////////////////////////////////////////////////////////////
#ifndef _Kindling_H_
#define _Kindling_H_

#include "Particle.h"

class CKindling : public CParticle{
public:
	CKindling(DU::BoundingBox* _pBoundingBox, int _nNumParticles);
	void resetParticle(Attribute* _pAttribute);
	void update(float _fTimeDelta);
};

#endif