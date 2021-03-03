#include "NumberArray.h"

CNumberArray::CNumberArray(D3DXVECTOR3* _pvPos, int _nPlace, int _nValue, DWORD _dwGap) : m_nMaxPlace(_nPlace),
																						m_nPlace(_nPlace),
																						m_nValue(_nValue),
																						m_nIndex(0),
																						m_fSumWidth(0.0f),
																						m_dwUpdateGap(_dwGap),
																						m_UpdateGap(new CTimer(_dwGap))
{
	m_vPos.x = _pvPos->x;
	m_vPos.y = _pvPos->y;
	m_vPos.z = _pvPos->z;

	InitNumberList();
}
	
CNumberArray::~CNumberArray(){
	for(std::vector<CNumber*>::size_type i = 0; i < m_Number.size(); i++)
		delete m_Number[i];

	Delete<CTimer*>(m_UpdateGap);
}

void CNumberArray::Initialize(){
	m_nValue = 0;

	for(std::vector<CNumber*>::size_type i = 0; i < m_Number.size(); i++)
		m_Number[i]->InitValue(0);
}

void CNumberArray::InitNumberList(){
	int t_nValue = m_nValue;
	int t_nPlace = 1;
	m_nIndex = 0;

	for(int i = 0; i < m_nMaxPlace; i++){		m_Number.push_back(new CNumber());	}

	for(m_nPlace = 1; m_nPlace <= t_nValue; m_nPlace*=10){}

	t_nPlace = m_nPlace;

	for(t_nPlace/=10;t_nPlace > 0; t_nPlace/=10){
		m_Number[m_nIndex++]->InitValue(t_nValue / t_nPlace);
		t_nValue %= t_nPlace;
	}
}

void CNumberArray::Update(){
	int t_nValue = m_nValue;
	int t_nPlace = 1;
	m_nIndex = 0;

	for(m_nPlace = 1; m_nPlace <= t_nValue; m_nPlace*=10){}

	t_nPlace = m_nPlace;

	// 높은자리부터 인덱스를 채워 나간다.
	for(t_nPlace/=10;t_nPlace > 0; t_nPlace/=10){
		m_Number[m_nIndex++]->InitValue(t_nValue / t_nPlace);
		t_nValue %= t_nPlace;
	}
}

void CNumberArray::Render(){
	float t_nSumWidthHalf = 0;

	for(int i = 0; i < m_nIndex; i++){
		t_nSumWidthHalf += m_Number[i]->GetAttachment(m_Number[i]->GetValue())->GetWidthHalf();
	}
	
	D3DXVECTOR3 t_vPos(m_vPos.x, m_vPos.y, m_vPos.z);

	m_fSumWidth = t_nSumWidthHalf*2.0f;

	t_vPos.x -= t_nSumWidthHalf;

	for(int i = 0; i < m_nIndex; i++){
		m_Number[i]->GetBody()->GetPriPos()->x = t_vPos.x;
		m_Number[i]->GetBody()->GetPriPos()->y = t_vPos.y;
		m_Number[i]->GetBody()->GetPriPos()->z = t_vPos.z;

		m_Number[i]->RenderOrgan();

		t_vPos.x += m_Number[i]->GetAttachment(m_Number[i]->GetValue())->GetWidth();
	}
}