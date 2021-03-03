////////////////////////////////////////////////////////////////////////////////
// ���� �۾����� ��ƼŬ
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

										// �����
	float m_fMin;			// �ּ� ����
	float m_fMax;			// �ִ� ����

public:
	CGetSmaller(CDirectXEntity* _pOrigin, const char* _strpFileName, float _fSize, float _fFrequency, 
							int _nNumParticles, bool _bLoop, float _fMin = 0.0f, float _fMax = D3DX_PI*2.0f,
							D3DXVECTOR3 _vSpot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	~CGetSmaller();


	void resetParticle(Attribute* _pAttribute);
	void update(float _fTimeDelta);
};

#endif