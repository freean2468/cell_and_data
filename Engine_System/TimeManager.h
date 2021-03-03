#ifndef _TimeManager_H_
#define _TimeManager_H_

#include "CrudeTImer.h"

class CTimeManager{
private:
	CCrudeTimer* m_pEngineTimer;

private:
	CTimeManager(const CTimeManager&);
	CTimeManager& operator =(const CTimeManager&);

public:
	CTimeManager():m_pEngineTimer(new CCrudeTimer()){m_pEngineTimer->Start();}
	~CTimeManager(){Delete<CCrudeTimer*>(m_pEngineTimer);}

	static CTimeManager* Instance(){
		static CTimeManager instance;

		return &instance;
	}

	CCrudeTimer* GetEngineTimer(){return m_pEngineTimer;}
};

#define TimeMgr CTimeManager::Instance()

#endif