#ifndef _MathManager_H_
////////////////////////////////////////////
// 수학 함수 관리 담당
////////////////////////////////////////////
#define _MathManager_H_

#include "../Engine_System/Organ.h"

class CMathManager{
private:
	CMathManager();
	CMathManager(const CMathManager&);
	CMathManager& operator =(const CMathManager&);

public:
	~CMathManager();
	static CMathManager* Instance(){
		static CMathManager instance;

		return &instance;
	}

	// 직선 방정식 //
	void swap(float* A, float* B);
	void VLine(float x, float y1, float y2);
	void HLine(float x1, float x2, float y);
	void Line(float x1, float y1, float x2, float y2);
	void LinearMove(COrgan* _pOrgan, float mx, float my, float vx, float vy); // mx, my 움직이고자 하는 좌표, vx, vy는 움직일 거리
};

#define MathMgr CMathManager::Instance()

#endif