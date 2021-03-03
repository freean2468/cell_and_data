////////////////////////////////////////////////////////////////////////////////
// BaseEffect Å¬·¡½º
////////////////////////////////////////////////////////////////////////////////
#ifndef _BaseEffect_H_
#define _BaseEffect_H_

#include "OrganEntity.h"
#include "EffectType.h"

class CBaseEffect : public COrganEntity{
public:
	EFFECTTYPE m_effectType;

public:
	CBaseEffect(EFFECTTYPE _eType);
	~CBaseEffect();

	EFFECTTYPE GetEffectType(){return m_effectType;}

	virtual void Recycle(COrgan* _pOrgan) = 0;
};

#endif