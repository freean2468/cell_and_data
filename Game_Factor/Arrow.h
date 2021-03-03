#ifndef _Arrow_H_
#define _Arrow_H_

#include "../Engine_System/BasicEntity.h"

class CArrow : public CBasicEntity{
private:

public:
	CArrow();
	~CArrow();

	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

};

#endif