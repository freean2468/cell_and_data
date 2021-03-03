#include "EntityManager.h"

CEntityManager::CEntityManager(){
	m_EntityMap.clear();
}

CEntityManager::~CEntityManager(){

}

//------------------------- GetEntityFromType ---------------------------------
//-----------------------------------------------------------------------------
CBaseEntity* CEntityManager::GetEntityFromType(int _nType)const
{
  //find the entity
  EntityMap::const_iterator ent = m_EntityMap.find(_nType);

  //assert that the entity is a member of the map
  //assert ( (ent !=  m_EntityMap.end()) && "<CEntityManager::GetEntityFromID>: invalid Type");

  return ent->second;
}

//--------------------------- RemoveEntity ------------------------------------
//-----------------------------------------------------------------------------
void CEntityManager::RemoveEntity(CBaseEntity* _pEntity){    
  m_EntityMap.erase(m_EntityMap.find(_pEntity->GetEntityType()));
} 

//---------------------------- RegisterEntity ---------------------------------
//-----------------------------------------------------------------------------
void CEntityManager::RegisterEntity(CBaseEntity* _pNewEntity){
  m_EntityMap.insert(std::make_pair(_pNewEntity->GetEntityType(), _pNewEntity));
}
