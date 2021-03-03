////////////////////////////////////////////////////////////////////////////////
// 확산하는 입자들을 추상화한 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _SpreadParticle_H_
#define _SpreadParticle_H_

#include "Particle.h"

class CSpreadParticle : public CParticle{
private:
	D3DXVECTOR3 m_vOrigin;
	float m_fSetSize;
	float m_fLifeTime;
	D3DXCOLOR m_Color;

public:
	CSpreadParticle(const char* _Adress, D3DXVECTOR3 _vOrigin, D3DXCOLOR _Color, float _fSize, int _nNumParticles, float _fLifeTime);
	void resetParticle(Attribute* _pAttribute);
	void update(float _fTimeDelta);
};

#endif