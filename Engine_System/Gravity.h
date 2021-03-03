#ifndef _Gravity_H_
#define _Gravity_H_

#include "../Engine_Math&Physics/Vector2D.h"
#include "MovingEntity.h"

class CGravity{
private:
	CMovingEntity* m_pOrigin;
	float m_fAngle;	
	float m_fRadius;	// 행성 반지름
	bool	m_bStatic;
	float m_fGravity;

public:
	CGravity(CMovingEntity* _pOrigin, float _fRadius, bool _bStatic, float _fAngle = 0.0f);
	~CGravity();

	bool GetStatic(){return m_bStatic;}

	void SetRadius(float _fRadius){m_fRadius = _fRadius;}
	float GetRadius(){return m_fRadius;}

	void CalGravity(Vector2D _vTarget);
	void IncreaseAngle(float _fFrequency){m_fAngle += _fFrequency;}
	void DecreaseAngle(float _fFrequency){m_fAngle -= _fFrequency;}

	float GetGravity(){return m_fGravity;}
	void SetGravity(float _fGravity){m_fGravity = _fGravity;}
	void IncreaseGravity(float _fFrequency){m_fGravity += _fFrequency;}
	void DecreaseGravity(float _fFrequency){m_fGravity -= _fFrequency;}
	bool IsWithinPlanet();

	void SetAngle(float _fAngle){m_fAngle = _fAngle;}
	float GetAngle(){return m_fAngle;}
};

#endif