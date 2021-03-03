#ifndef _Leaf_H_
#define _Leaf_H_

#include "Particle.h"
#include "DirectXEntity.h"

class CLeaf : public CParticle{
private:
	CDirectXEntity* m_pOrigin;
	float m_fRadius;

public:
	CLeaf(CDirectXEntity* _pOrigin, int _nNumParticles, float _fRadius);
	~CLeaf();

	virtual void resetParticle(Attribute* _pAttribute);
	virtual void update(float _fTimeDelta);
};

#endif