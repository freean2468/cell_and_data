////////////////////////////////////////////////////////////////////////////////
// �Ҿ��� �ö󰡴� ȿ��
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