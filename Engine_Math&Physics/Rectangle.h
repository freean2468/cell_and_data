#ifndef _Rectangle_H_
#define _Rectangle_H_

#include "Vector2D.h"

class CRectangle{
private:
	Vector2D m_vLB;
	Vector2D m_vLT;
	Vector2D m_vRB;
	Vector2D m_vRT;

public:
	CRectangle(){}
	CRectangle(float _fLeft, float _fRight, float _fBottom, float _fTop);
	~CRectangle(){}

	bool IntersectionRectangle(CRectangle* _pRect);	// ºÒ¿ÏÀü
	bool InternalPoint(Vector2D* _pvPoint);

	Vector2D* GetLB(){return &m_vLB;}
	Vector2D* GetLT(){return &m_vLT;}
	Vector2D* GetRB(){return &m_vRB;}
	Vector2D* GetRT(){return &m_vRT;}
};

#endif