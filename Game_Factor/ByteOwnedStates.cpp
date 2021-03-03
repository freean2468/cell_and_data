#include "ByteOwnedStates.h"

///////////////////////////////////////////////////////////
// InActive State
///////////////////////////////////////////////////////////
void CByteInActive::Enter(CByte* _pByte){
	
}

void CByteInActive::Execute(CByte* _pByte){
	CBody* t_pBody = _pByte->GetBody();

	if(t_pBody->GetAlpha() > 0.0f){
		t_pBody->DecreaseAlpha(0.05f);
	}

	_pByte->RenderOrgan();
}

void CByteInActive::Exit(CByte* _pByte){

}

bool CByteInActive::OnMessage(CByte* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Delete State
///////////////////////////////////////////////////////////
void CByteDelete::Enter(CByte* _pByte){
	
}

void CByteDelete::Execute(CByte* _pByte){
	CBody* t_pBody = _pByte->GetBody();

	if(t_pBody->GetPriSca()->x > 0.0f){
		t_pBody->DecreaseSca(0.05f);
	}
	else{
		_pByte->SetState(CByte::BYTE_DELETE);
	}

	_pByte->RenderOrgan();
}

void CByteDelete::Exit(CByte* _pByte){

}

bool CByteDelete::OnMessage(CByte* agent, const Telegram& _rMsg){
	return false;
}

///////////////////////////////////////////////////////////
// Exhale State
// 바이러스에게 흡수되지 않고 감염되어 파괴될 때
///////////////////////////////////////////////////////////
void CByteExhale::Enter(CByte* _pByte){
	CBody* t_pBody = _pByte->GetBody();

	_pByte->SetOrigin();

	m_vOldPos.x = t_pBody->GetPriPos()->x;
	m_vOldPos.y = t_pBody->GetPriPos()->y;
	m_vOldPos.z = t_pBody->GetPriPos()->z;

	Vector2D t_vDir = Vector2D(::RandInRange(0, 100), ::RandInRange(0, 100));
	
	if(::RandBool())	t_vDir.x *= -1;
	if(::RandBool())	t_vDir.y *= -1;

	t_vDir.Normalize();

	if(_pByte->GetOrigin()->GetGrowth()->IsGrowth(CGrowth::FIRST)){
		m_nLength = 30;
	}
	else if(_pByte->GetOrigin()->GetGrowth()->IsGrowth(CGrowth::SECOND)){
		m_nLength = 100;
	}
	else
		m_nLength = 170;

	_pByte->SetOrigin();
	m_fPercentage = 0.0f;

	m_vDist = t_vDir * m_nLength;	

	_pByte->UniformOrganScaZero();
}

void CByteExhale::Execute(CByte* _pByte){
	CBody* t_pBody = _pByte->GetBody();
	CBody* t_pOrigin = _pByte->GetOrigin()->GetBody();

	t_pBody->GetPriPos()->x = m_vOldPos.x + ((float)m_vDist.x * (m_fPercentage/100.0f));
	t_pBody->GetPriPos()->y = m_vOldPos.y + ((float)m_vDist.y * (m_fPercentage/100.0f));

	m_fPercentage += 0.5f;

	t_pBody->RotZ(1.0f/D3DX_PI);

	if(t_pBody->GetAlpha() > 0.0f){
		t_pBody->DecreaseAlpha(0.02f);
	}

	if(t_pBody->GetPriSca()->x < 1.0f){
		t_pBody->GetPriSca()->x = m_fPercentage/100.0f;
		t_pBody->GetPriSca()->y = m_fPercentage/100.0f;
	}
	else{
		_pByte->GetFSM()->ChangeState(ByteDelete->Instance());
	}

	_pByte->RenderOrgan();
}

void CByteExhale::Exit(CByte* _pByte){
	m_fPercentage = 0.0f;
}

bool CByteExhale::OnMessage(CByte* agent, const Telegram& _rMsg){
	return false;
}