////////////////////////////////////////////////////////////////////////////////////////////////////////
// ID 번호를 저장하기 위한 private멤버를 가지고 있는 클래스
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _BaseEntity_H_
#define _BaseEntity_H_

#include "../Engine_Math&Physics/Vector2D.h"
#include "SystemDefines.h"

//------------------------------------------------------------------------
//
//  Name: CBaseEntity.h
//
//  Desc: Base class to define a common interface for all game
//        entities
//
//------------------------------------------------------------------------

struct Telegram;

class CBaseEntity{
public:
  typedef enum EntityType {DEFAULT_ENTITY_TYPE = -1, BIRD=0, SORCERER=1,CITY,
							DINOSAUR, FOREST, HUMAN, SMALLTREE, CAR, PLANE, BULLDOZER} ENTITYTYPE;

private:
	//each entity has a unique ID
	int         m_nID;

	//every entity has a type associated with it (health, troll, ammo etc)
	int         m_nEntityType;

	//used by the constructor to give each entity a unique ID
	int					NextValidID(){static int NextID = 0; return NextID++;}

	bool				m_bTag;
	bool				m_bView;
	bool				m_bHide;
	bool				m_bAlive;

public:

  CBaseEntity():m_nID(NextValidID()),
                m_nEntityType(DEFAULT_ENTITY_TYPE),
				m_bTag(false),
				m_bView(true),
				m_bHide(false),
				m_bAlive(true)
  {}

  CBaseEntity(int _nEntityType):m_nID(NextValidID()),
								m_nEntityType(_nEntityType),
								m_bTag(false),
								m_bView(true),
								m_bHide(false),
								m_bAlive(true)
  {}
  
  CBaseEntity(int _nEntityType, Vector2D _vPos, double _dRadius):m_nID(NextValidID()),
																	m_nEntityType(_nEntityType),
																	m_bTag(false),
																	m_bView(true),
																	m_bHide(false),
																	m_bAlive(true)
                                        
  {}

  //this can be used to create an entity with a 'forced' ID. It can be used
  //when a previously created entity has been removed and deleted from the
  //game for some reason. For example, The Raven map editor uses this ctor 
  //in its undo/redo operations. 
  //USE WITH CAUTION!
  CBaseEntity(int _nEntityType, int p_nForcedID):m_nID(p_nForcedID),																									
												m_nEntityType(_nEntityType)
  {}

public:

	virtual ~CBaseEntity(){}

	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60){}; 

	virtual void Render(){};

	virtual bool HandleMessage(const Telegram& _rMsg){return false;}
  
	//entities should be able to read/write their data to a stream
	virtual void Write(std::ostream&  stream_os)const{}
	virtual void Read (std::ifstream& stream_ifs){}

	int	         GetID()const{return m_nID;}

	bool         IsTagged()const{return m_bTag;}
	void         Tag(){m_bTag = true;}
	void         UnTag(){m_bTag = false;}

	bool         IsViewing()const{return m_bView;}
	void         ViewIn(){m_bView = true;}
	void         ViewOut(){m_bView = false;}

	bool				 IsHide()const{return m_bHide;}
	void				 OnHide(){m_bHide = true;}
	void				 OffHide(){m_bHide = false;}

	bool         IsAlive()const{return m_bAlive;}
	void         Alive(){m_bAlive = true;}
	void         Die(){m_bAlive = false;}

	int          GetEntityType()const{return m_nEntityType;}
	void         SetEntityType(int p_nNewType){m_nEntityType = p_nNewType;}
};

#endif