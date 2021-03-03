#include "Rectangle.h"

CRectangle::CRectangle(float _fLeft, float _fRight, float _fBottom, float _fTop) : m_vLB((double)_fLeft, (double)_fBottom),
																																										m_vLT((double)_fLeft, (double)_fTop),
																																										m_vRB((double)_fRight, (double)_fBottom),
																																										m_vRT((double)_fRight, (double)_fTop)
{

}

bool CRectangle::IntersectionRectangle(CRectangle* _pRect){
	Vector2D t_vLT = *(_pRect->GetLT());
	Vector2D t_vLB = *(_pRect->GetLB());
	Vector2D t_vRT = *(_pRect->GetRT());
	Vector2D t_vRB = *(_pRect->GetRB());

	if(InternalPoint(&t_vLT)) return true;
	if(InternalPoint(&t_vLB)) return true;
	if(InternalPoint(&t_vRT)) return true;
	if(InternalPoint(&t_vRB)) return true;

	//// »óÇÏ °ãÄ§
	//if(m_vLT.x > t_vLB.x && m_vLT.y > t_vLB.y && m_vRT.x < t_vRB.x){
	//	return true;
	//}

	//// ÇÏ»ó °ãÄ§
	//if(m_vLB.x < t_vLT.x && m_vLB.y < t_vLT.y && m_vRB.x > t_vRT.x){
	//	return true;
	//}

	//// ÁÂÇÏ&¿ì»ó °ãÄ§
	//if(m_vLB < t_vRT && m_vLB > t_vLB){
	//	return true;
	//}

	//// ÁÂ»ó&¿ìÇÏ °ãÄ§
	//if(m_vLT.x < t_vRB.x && m_vLT.y > t_vRB.y && m_vLT.x > t_vLT.x && m_vLT.y < t_vLT.y){
	//	return true;
	//}

	//// ¿ì»ó&ÁÂÇÏ °ãÄ§
	//if(m_vRT > t_vLB && m_vRT < t_vRT){
	//	return true;
	//}

	//// ¿ìÇÏ&ÁÂ»ó °ãÄ§
	//if(m_vRB.x > t_vLT.x && m_vRB.y < t_vLT.y && m_vRB.x < t_vRB.x && m_vRB.y > t_vRB.y){
	//	return true;
	//}

	return false;
}

bool CRectangle::InternalPoint(Vector2D* _pvPoint){
	if(m_vLB < *_pvPoint && m_vRT > *_pvPoint && m_vRB.x > _pvPoint->x){
		return true;
	}

	return false;
}