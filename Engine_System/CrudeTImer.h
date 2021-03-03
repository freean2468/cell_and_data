////////////////////////////////////////////////////////////
// 시간을 나타내는 클래스
////////////////////////////////////////////////////////////
#ifndef _CrudeTimer_H_
#define _CrudeTimer_H_

#include <Windows.h>
#include <MMSystem.h>

class CCrudeTimer{
private:
	 //set to the time (in seconds) when class is instantiated
	double m_dStartTime;
	double m_dLastTime;

public:
	//set the start time
	CCrudeTimer():m_dStartTime(0), m_dLastTime(0){}
	~CCrudeTimer(){};
  
public:
	void Start(){m_dStartTime = timeGetTime() * 0.001;}
	void Stop(){m_dLastTime = GetCurrentTime();}

	//returns how much time has elapsed since the timer was started
	double GetCurrentTime(){return timeGetTime() * 0.001 - m_dStartTime;}
	double GetLastTime(){return m_dLastTime;}
};

#endif