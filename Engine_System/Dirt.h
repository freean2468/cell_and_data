////////////////////////////////////////////////////////////////////////////////
// ������ �������� ȿ��
////////////////////////////////////////////////////////////////////////////////
#ifndef _Dirt_H_
#define _Dirt_H_

#include "../Engine_Misc/DirectUtils.h"
#include "Particle.h"

class CDirt : public CParticle{
public:
	CDirt(DU::BoundingBox* _pBoundingBox, int _nNumParticles);
	void resetParticle(Attribute* _pAttribute);
	void update(float _fTimeDelta);
};

#endif