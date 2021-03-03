#include "SystemFrame.h"
#include "EngineManager.h"

CSystemFrame::CSystemFrame(void):	m_dwCurrTimeOfOrigin(0),
								m_dwLastTimeOfOrigin(timeGetTime()),
								m_fTimeDeltaOfOrigin(0.0f),
								m_dwAdjustedCurrTime(0),
								m_dwAdjustedLastTime(timeGetTime()),
								m_fAdjustedTimeDelta(0.0f)
{
}

CSystemFrame::~CSystemFrame(void){

}

void CSystemFrame::CalculationTimeDeltaOfOrigin(){
	m_dwCurrTimeOfOrigin  = timeGetTime();
	m_fTimeDeltaOfOrigin = (m_dwCurrTimeOfOrigin - m_dwLastTimeOfOrigin) * 0.001f;

	m_dwLastTimeOfOrigin = m_dwCurrTimeOfOrigin;
}

float CSystemFrame::GetTimeDeltaOfOrigin(){
	return m_fTimeDeltaOfOrigin;
}

void CSystemFrame::CalculationAdjustedTimeDelta(){
	m_dwAdjustedCurrTime  = timeGetTime();
	m_fAdjustedTimeDelta = (m_dwAdjustedCurrTime - m_dwAdjustedLastTime) * 0.001f;

	m_dwAdjustedLastTime = m_dwAdjustedCurrTime;
}

float CSystemFrame::GetAdjustedTimeDelta(){
	return m_fAdjustedTimeDelta;
}

void CSystemFrame::SetFramePerSec(float _fFPS){
	if(_fFPS != 0.0f)
	{
		m_fSecPerFrame = 1.0f / _fFPS;
	}
	else if(_fFPS == 0.0f)
	{
		m_fSecPerFrame = 0.0f; // No Lock
	}

	m_fLimitFPS = _fFPS;
	m_fFPS = 0.0f;

	m_iFrameCount = 0;

	m_fTimer = 0.0f;
	m_fAcculTime = 0.0f;
}

bool CSystemFrame::Update(float _fTimeDelta) {
	m_fTimer += _fTimeDelta; // ����Ǵ� �ð�
	m_fAcculTime += _fTimeDelta; // ���� �ð�

	if(m_fSecPerFrame != 0.0f)
	{
		if(m_fTimer < 0.0f) // Frame�� �ʹ� ���� ��� (������ FPS�� �ѱ���)
		{
			// FPS ���
			if((float)m_iFrameCount / m_fAcculTime != 0.0f)
			{
				m_fFPS = (float)m_iFrameCount / m_fAcculTime;
				m_fAcculTime = 0;
				m_iFrameCount = 0;
			}

			return false;
		}
	}
	else if(m_fSecPerFrame == 0.0f) // No Lock (�׳� ���)
	{
		// FPS ���
		if(m_fAcculTime >= 1.0f)
		{
			if((float)m_iFrameCount / m_fAcculTime != 0.0f)
			{
				m_fFPS = (float)m_iFrameCount / m_fAcculTime;
				m_fAcculTime = 0;
				m_iFrameCount = 0;
			}
		}
	}

	// �������ӿ� �ش��ϴ� �ð��� ����.
	m_fTimer -= m_fSecPerFrame;

	// Frame ���� �ø���.
	m_iFrameCount += 1;

	return true;
} 

bool CSystemFrame::IsFrameSkip(){ 
	// Update �� Skip �� �Ͼ���� Ȯ��
	// Skip�� �Ͼ�� ������ Render �Ѵ�
	
	if(m_fSecPerFrame != 0.0f)
	{
		EngineMgr->GetpInformation()->FPSAdjustedCalculation(EngineMgr->GetAdjustedTimeDelta());
		return m_fTimer >= 0;
	}
	else if(m_fSecPerFrame == 0.0f) // No Lock (Skip ���� ����)
	{
		EngineMgr->GetpInformation()->FPSAdjustedCalculation(EngineMgr->GetAdjustedTimeDelta());
		return false;
	}

	return true;
} 
