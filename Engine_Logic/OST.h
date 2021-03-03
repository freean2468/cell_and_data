#ifndef _OST_H_
#define _OST_H_

#include "../Engine_System/OrganEntity.h"

class COST : public COrganEntity{
public:
	typedef enum OSTAttType {ONE, TWO, THREE, FOUR, FIVE, NONE} OSTATTTYPE;

private:
	int m_nPresent;

public:
	COST();
	~COST();

	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);
	virtual void Render();
};

#endif