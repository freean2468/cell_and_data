#include "Timer.h"

// 타이머 초기화
// 처음 시간을 설정할 때 호출
CTimer::CTimer(DWORD _dwDelayTime) : m_dwOldTime(GetTickCount()),
									m_dwDelayTime(_dwDelayTime)
{
	
}

void CTimer::InitTimer(DWORD _dwTime){
	m_dwOldTime = GetTickCount();
	m_dwDelayTime = _dwTime;
}

// 시간의 경과
// 초기에 설정된 시간이 경과되었는지 질의하는 함수
BOOL CTimer::IsElapseTimer(){	
	// GetTickCount함수 : OS가 시작된 후부터 현재까지의 시간을 밀리세컨드(1/1000초) 단위로 반환
	DWORD dwCurTime = GetTickCount();
	DWORD dwElapsed = dwCurTime - this->m_dwOldTime;	

	if (dwElapsed >= this->m_dwDelayTime){		
		this->m_dwDelayTime = 0;				// 0으로 초기화
		this->m_dwOldTime = dwCurTime;			// 현재 시간으로 초기화
		return TRUE;							// 현재 시간이 경과되었음을 알림.
	}	

	return FALSE;
}

// 타이머가 아직 유효한지 질의하는 함수
// Timer를 지속적으로 검사해야 한다면 이 함수를 사용
BOOL CTimer::IsValidTimer(){
	if (this->m_dwDelayTime)
		return TRUE;
	else 
		return FALSE;
}

DWORD CTimer::GetElapseTime(){
	// GetTickCount함수 : OS가 시작된 후부터 현재까지의 시간을 밀리세컨드(1/1000초) 단위로 반환
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
	// GetTickCount함수 : OS가 시작된 후부터 현재까지의 시간을 밀리세컨드(1/1000초) 단위로 반환
	DWORD dwCurTime = GetTickCount();
	DWORD dwElapsed = dwCurTime - this->m_dwOldTime;	

	return m_dwDelayTime - dwElapsed;
}













