#include "Timer.h"

// Ÿ�̸� �ʱ�ȭ
// ó�� �ð��� ������ �� ȣ��
CTimer::CTimer(DWORD _dwDelayTime) : m_dwOldTime(GetTickCount()),
									m_dwDelayTime(_dwDelayTime)
{
	
}

void CTimer::InitTimer(DWORD _dwTime){
	m_dwOldTime = GetTickCount();
	m_dwDelayTime = _dwTime;
}

// �ð��� ���
// �ʱ⿡ ������ �ð��� ����Ǿ����� �����ϴ� �Լ�
BOOL CTimer::IsElapseTimer(){	
	// GetTickCount�Լ� : OS�� ���۵� �ĺ��� ��������� �ð��� �и�������(1/1000��) ������ ��ȯ
	DWORD dwCurTime = GetTickCount();
	DWORD dwElapsed = dwCurTime - this->m_dwOldTime;	

	if (dwElapsed >= this->m_dwDelayTime){		
		this->m_dwDelayTime = 0;				// 0���� �ʱ�ȭ
		this->m_dwOldTime = dwCurTime;			// ���� �ð����� �ʱ�ȭ
		return TRUE;							// ���� �ð��� ����Ǿ����� �˸�.
	}	

	return FALSE;
}

// Ÿ�̸Ӱ� ���� ��ȿ���� �����ϴ� �Լ�
// Timer�� ���������� �˻��ؾ� �Ѵٸ� �� �Լ��� ���
BOOL CTimer::IsValidTimer(){
	if (this->m_dwDelayTime)
		return TRUE;
	else 
		return FALSE;
}

DWORD CTimer::GetElapseTime(){
	// GetTickCount�Լ� : OS�� ���۵� �ĺ��� ��������� �ð��� �и�������(1/1000��) ������ ��ȯ
	DWORD dwCurTime = GetTickCount();
	DWORD dwElapsed = dwCurTime - this->m_dwOldTime;	

	if (dwElapsed >= this->m_dwDelayTime){			
		return m_dwDelayTime;							
	}	
	else{
		return dwElapsed;
	}
}

DWORD CTimer::GetLeaveTime(){
	// GetTickCount�Լ� : OS�� ���۵� �ĺ��� ��������� �ð��� �и�������(1/1000��) ������ ��ȯ
	DWORD dwCurTime = GetTickCount();
	DWORD dwElapsed = dwCurTime - this->m_dwOldTime;	

	return m_dwDelayTime - dwElapsed;
}













