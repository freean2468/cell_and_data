///////////////////////////////////////////////////////////////////////////////////////
// CSystemFrame클래스는 이 엔진의 Frame과 관련된 모든 수치들을 총괄함
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _SystemFrame_H_
#define _SystemFrame_H_

#include <Windows.h>

class CSystemFrame{
private: 	
	DWORD m_dwCurrTimeOfOrigin; // 본래의 진행된 시간값
	DWORD m_dwLastTimeOfOrigin; // 본래의마지막 시간값

	float m_fTimeDeltaOfOrigin; // 다시 돌아오는데 걸린 본래의 시간값 (CurrTime - LastTime)

	DWORD m_dwAdjustedCurrTime;	// 조정된 진행된 시간값
	DWORD m_dwAdjustedLastTime;  // 조정된마지막 시간값
								   
	float m_fAdjustedTimeDelta; // 다시 돌아오는데 걸린 조정된 시간값 (CurrTime - LastTime)

	float m_fLimitFPS; // 최대 Frame
	float m_fFPS; // 실제 계산된 초당 Frame 수

	int m_iFrameCount; // 진행된 Frame의 수
	float m_fSecPerFrame; // 초당 Frame 수
	
	float m_fTimer; // 전체 시간 (0보다 작으면 올바른 Frame, 0보다 크면 FrameSkip)
	float m_fAcculTime; // 실제 시간

public:
	CSystemFrame(void);
	virtual ~CSystemFrame(void);

	void CalculationTimeDeltaOfOrigin(); // 본래의 시간값 계산
	void CalculationAdjustedTimeDelta(); // 조정된 시간값 계산
	void SetFramePerSec(float _fFPS);
	bool Update(float _fTimeDelta); // Frame 계산
	bool IsFrameSkip(); // FrameSkip (True : Skip, False : NoSkip)

	float GetTimeDeltaOfOrigin(); // 본래의 TimeDelta 값 Return
	float GetAdjustedTimeDelta(); // 조정된 TimeDelta 값 Return
	__inline float GetFPS() const;
	__inline float GetLimitFPS() const;
};

__inline float CSystemFrame::GetFPS() const{
	return m_fFPS;
}
__inline float CSystemFrame::GetLimitFPS() const{
	return m_fLimitFPS;
}

#endif