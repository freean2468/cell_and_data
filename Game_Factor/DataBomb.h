////////////////////////////////////////////////////////////////////////////////
// 데이터 집단 구현 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _DataBomb_H_
#define _DataBomb_H_

#include "../Engine_System/Particle.h"

class CDataBomb : public CParticle{
public:
	CDataBomb(D3DXVECTOR3* _pvOrigin, int _nNumParticles);

	void resetParticle(Attribute* _pAttribute);
	void update(float _fTimeDelta);
	void preRender();
	void postRender();
};

#endif