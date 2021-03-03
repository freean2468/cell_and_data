////////////////////////////////////////////////////
// World, 그리고 그와 관련된 정보를 담당 관리
////////////////////////////////////////////////////
#ifndef _WorldManager_H_
#define _WorldManager_H_

#include "World.h"
#include "../Engine_System/BaseParamLoader.h"
#include "../Engine_System/MapParamLoader.h"
#include "../Engine_System/SteeringParamLoader.h"

class CWorldManager{
private:
	CWorld* m_pWorld;

	CBaseParamLoader*			m_pBaseParamLdr;
	CMapParamLoader*			m_pMapParamLdr;
	CSteeringParamLoader*	m_pSteeringParamLdr;

	bool m_bLoad;

	//set true to pause the motion
  bool m_bPaused;

public:
	// Load step
	bool m_b1;
	bool m_b2;
	bool m_b3;
	bool m_b4;
	bool m_b5;
	bool m_b6;
	bool m_b7;
	bool m_b8;
	bool m_b9;
	bool m_b10;

	int m_nItr;

private:
	CWorldManager();
	CWorldManager(const CWorldManager&);
	CWorldManager& operator =(const CWorldManager&);

public:
	~CWorldManager();

	static CWorldManager* Instance(){
		static CWorldManager instance;

		return &instance;
	}

	void Initialize();

	void Update();

	CWorld* GetWorld(){return m_pWorld;}
	void SetParam(const char* _pstrFile);

	void SetLoadSuccess(bool m_bSuccess){m_bLoad = m_bSuccess;}
	bool GetLoadSuccess(){return m_bLoad;}

	void SetInitLoadStep(){m_b1 = false; m_b2 = false; m_b3 = false; m_b4 = false; m_b5 = false; 
													m_b6 = false; m_b7 = false; m_b8 = false; m_b9 = false; m_b10 = false;
													m_nItr = 0;}

	void Increaseitr(){++m_nItr;}

	void	OnPause(){m_bPaused = true;}
	void	OffPause(){m_bPaused = false;}
  void  TogglePause(){m_bPaused = !m_bPaused;}
  bool  IsPaused()const{return m_bPaused;}

	CBaseParamLoader*			GetBaseParam(){return m_pBaseParamLdr;}
	CMapParamLoader*			GetMapParam(){return m_pMapParamLdr;}
	CSteeringParamLoader*	GetSteeringParam(){return m_pSteeringParamLdr;}
};

#define WorldMgr CWorldManager::Instance()

#endif