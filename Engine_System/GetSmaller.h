////////////////////////////////////////////////////////////////////////////////
// 점점 작아지는 파티클
////////////////////////////////////////////////////////////////////////////////
#ifndef _GetSmaller_H_
#define _GetSmaller_H_

#include "Particle.h"
#include "DirectXEntity.h"

class CGetSmaller : public CParticle{
private:
	CDirectXEntity* m_pOrigin;
	bool m_bLoop;
	float m_fFrequency;
	D3DXVECTOR3 m_vSpot;

										// 뻗어나갈
	float m_fMin;			// 최소 각도
	float m_fMax;			// 최대 각도

public:
	CGetSmaller(CDirectXEntity* _pOrigin, const char* _strpFileName, float _fSize, float _fFrequency, 
							int _nNumParticles, bool _bLoop, float _fMin = 0.0f, float _fMax = D3DX_PI*2.0f,
							D3DXVECTOR3 _vSpot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	~CGetSmaller();


	void resetParticle(Attribute* _pAttribute);
	void update(float _fTimeDelta);
};

#endif