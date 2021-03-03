#include "Growth.h"

CGrowth::CGrowth(GROWTH _eGrowth):m_eGrowth(_eGrowth)
{
	if(_eGrowth == FIRST)		m_nStep = 1;
	else if(_eGrowth == SECOND)	m_nStep = 2;
	else		m_nStep = 3;
}


CGrowth::CGrowth(GROWTH _eGrowth, float _fLimit, float _fInit, float _fFrequency, DWORD _dwTime):	m_eGrowth(_eGrowth),
																									m_fLimit(_fLimit),		
																									m_fPresent(_fInit),
																									m_fInit(_fInit),																	
																									m_fFrequency(_fFrequency),
																									m_fRatio(1.0f),
																									m_dwTime(_dwTime),
																									m_pTimer(new CTimer(_dwTime))
{
	if(_eGrowth == FIRST)		m_nStep = 1;
	else if(_eGrowth == SECOND)	m_nStep = 2;
	else		m_nStep = 3;
}

void CGrowth::Update(){
	if(!IsGrowthEnd()){
		if(m_pTimer->IsElapseTimer()){
			m_pTimer->InitTimer(m_dwTime);
			m_fPresent += m_fFrequency;
		}
	}
}

void CGrowth::SetGrowth(GROWTH _pGrowth){
	m_eGrowth = _pGrowth;

	if(_pGrowth == FIRST)	m_nStep = 1;
	else if(_pGrowth == SECOND)	m_nStep = 2;
	else		m_nStep = 3;
}

bool CGrowth::less(CGrowth* _pGrowth)const{
	if(m_nStep < _pGrowth->GetStep())		return true;
	else		return false;
}

bool CGrowth::less_equal(CGrowth* _pGrowth)const{
	if(m_nStep <= _pGrowth->GetStep())		return true;
	else		return false;
}

bool CGrowth::greater(CGrowth* _pGrowth)const{
	if(m_nStep > _pGrowth->GetStep())		return true;
	else		return false;
}

bool CGrowth::greater_equal(CGrowth* _pGrowth)const{
	if(m_nStep >= _pGrowth->GetStep())		return true;
	else		return false;
}

bool CGrowth::equal(CGrowth* _pGrowth)const{
	if(m_nStep == _pGrowth->GetStep())		return true;
	else		return false;
}

bool CGrowth::IsGrowth(GROWTH _pGrowth){
	return m_eGrowth == _pGrowth;
}