////////////////////////////////////////////////////////////////////////////////
// 타이머 기능을 가진 클래스
////////////////////////////////////////////////////////////////////////////////

#ifndef __TIMER_H__
#define __TIMER_H__

#include <Windows.h>

class CTimer{
private:
	DWORD m_dwOldTime;			// 지난 시간을 담고 있는 변수
	DWORD m_dwDelayTime;		// 측정할 시간을 담고 있는 변수

public:
	CTimer():m_dwOldTime(-1), m_dwDelayTime(-1){}
	CTimer(DWORD _dwDelayTime);
	~CTimer(){}

	void InitTimer(DWORD _dwTime);

	DWORD GetElapseTime();
	DWORD GetDelayTime(){return m_dwDelayTime;}
	DWORD GetLeaveTime();

	BOOL IsElapseTimer();
	BOOL IsValidTimer();
};

#endif







