////////////////////////////////////////////////////////////////////////////////
// 데이터입자
////////////////////////////////////////////////////////////////////////////////
#ifndef _DataParticle_H_
#define _DataParticle_H_

#include "Particle.h"

class CDataParticle : public CParticle{
public:
	CDataParticle(DU::BoundingBox* _pBoundingBox, int _nNumParticles);
	void resetParticle(Attribute* _pAttribute);
	void update(float _fTimeDelta);
	void preRender();
	void postRender();
};

#endif