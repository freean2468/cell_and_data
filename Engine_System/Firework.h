////////////////////////////////////////////////////////////////////////////////
// ÆøÁ× ±¸Çö Å¬·¡½º
////////////////////////////////////////////////////////////////////////////////
#ifndef _Firework_H_
#define _Firework_H_

#include "Particle.h"

class CFirework : public CParticle{
public:
	CFirework(D3DXVECTOR3* _pvOrigin, int _nNumParticles);
	void resetParticle(Attribute* _pAttribute);
	void update(float _fTimeDelta);
	void preRender();
	void postRender();
};

#endif