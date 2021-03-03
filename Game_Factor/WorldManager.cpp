#include "WorldManager.h"
#include "UIManager.h"

CWorldManager::CWorldManager():m_pWorld(NULL),
							m_pBaseParamLdr(NULL),
							m_pMapParamLdr(NULL),
							m_pSteeringParamLdr(NULL),
							m_bLoad(false),
							m_b1(false),
							m_b2(false),
							m_b3(false),
							m_b4(false),
							m_b5(false),
							m_b6(false),
							m_b7(false),
							m_b8(false),
							m_b9(false),
							m_b10(false),
							m_nItr(0),														
							m_bPaused(false)
{
}

CWorldManager::~CWorldManager(){
	Delete<CWorld*>(m_pWorld); 
	Delete<CBaseParamLoader*>(m_pBaseParamLdr);
	Delete<CMapParamLoader*>(m_pMapParamLdr);
	Delete<CSteeringParamLoader*>(m_pSteeringParamLdr);
}

void CWorldManager::SetParam(const char* _pstrFile){
	Delete<CWorld*>(m_pWorld);
	Delete<CBaseParamLoader*>(m_pBaseParamLdr);
	Delete<CMapParamLoader*>(m_pMapParamLdr);
	Delete<CSteeringParamLoader*>(m_pSteeringParamLdr);

	m_pWorld = new CWorld();

	std::string t_strAdress;

	t_strAdress="./Script/Param/Base/";
	t_strAdress+=_pstrFile;
	m_pBaseParamLdr = new CBaseParamLoader(t_strAdress.c_str());

	t_strAdress="./Script/Param/Map/";
	t_strAdress+=_pstrFile;
	m_pMapParamLdr = new CMapParamLoader(t_strAdress.c_str());

	t_strAdress="./Script/Param/Steering/";
	t_strAdress+=_pstrFile;
	m_pSteeringParamLdr = new CSteeringParamLoader(t_strAdress.c_str());

	UIMgr->GetAbility()->Initialize();
	UIMgr->GetGauge()->Initialize();
	UIMgr->GetGauge()->OnActive();

	OffPause();
}

void CWorldManager::Update(){
	m_pWorld->Update();

	m_pWorld->Render();
}

void CWorldManager::Initialize(){
	if(m_bLoad == true){
		Delete<CWorld*>(m_pWorld);								m_pWorld = new CWorld();

		m_bLoad = false;

		SetInitLoadStep();
	}
}