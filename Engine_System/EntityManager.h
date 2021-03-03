////////////////////////////////////////////////////////////////////////////////////////////////////////
// Entity Manager 
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _EntityManager_H_
#define _EntityManager_H_

#include <map>
#include "BaseEntity.h"

class CEntityManager{
private:
  typedef std::map<int, CBaseEntity*> EntityMap;

private:
  EntityMap m_EntityMap;

  CEntityManager();
	~CEntityManager();

  //copy ctor and assignment should be private
  CEntityManager(const CEntityManager&);
  CEntityManager& operator=(const CEntityManager&);

public:
  static CEntityManager* Instance(){
		static CEntityManager instance;

		return &instance;
	}

  void            RegisterEntity(CBaseEntity* _pNewEntity);

	CBaseEntity*		GetEntityFromType(int _nType)const;

  //this method removes the entity from the list
  void            RemoveEntity(CBaseEntity* _pEntity);

  //clears all entities from the entity map
  void            Reset(){m_EntityMap.clear();}
};

//provide easy access
#define EntityMgr CEntityManager::Instance()

#endif