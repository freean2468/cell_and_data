////////////////////////////////////////////////////////////////////////////////
// Ÿ�̸� ����� ���� Ŭ����
////////////////////////////////////////////////////////////////////////////////

#ifndef __TIMER_H__
#define __TIMER_H__

#include <Windows.h>

class CTimer{
private:
	DWORD m_dwOldTime;			// ���� �ð��� ��� �ִ� ����
	DWORD m_dwDelayTime;		// ������ �ð��� ��� �ִ� ����

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







