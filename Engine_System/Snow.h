////////////////////////////////////////////////////////////////////////////////
// ´«ÀÌ ¶³¾îÁö´Â È¿°ú
////////////////////////////////////////////////////////////////////////////////
#ifndef _Snow_H_
#define _Snow_H_

#include "Particle.h"

class CSnow : public CParticle{
public:
	CSnow(DU::BoundingBox* _pBoundingBox, int _nNumParticles);
	void resetParticle(Attribute* _pAttribute);
	void update(float _fTimeDelta);
};

#endif