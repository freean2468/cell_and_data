#ifndef _SpreadEffect_H_
#define _SpreadEffect_H_

#include "BaseEffect.h"

class CSpreadEffect : public CBaseEffect{
private:
	D3DXVECTOR3* m_pvPos;			 
	
public:
	CSpreadEffect(const char* _pAdress, D3DXVECTOR3* _pvPos, D3DXCOLOR _Color);
	~CSpreadEffect();

	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);
	virtual void Render();

	virtual void Recycle(COrgan* _pOrgan);
};

#endif