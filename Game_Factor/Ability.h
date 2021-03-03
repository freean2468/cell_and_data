////////////////////////////////////////////////////////////////////////////////
// Ability Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Ability_H_
#define _Ability_H_

#include "../Engine_System/Vehicle.h"
#include "../Engine_System/StateMachine.h"

class CAbility : public COrganEntity{
public:
	typedef enum AbilityAttType {DESTROY, ABSORPTION, CONTROL, FIRST, SECOND, THIRD, NONE} ABILITYATTTYPE;
	
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CAbility>* m_pStateMachine;
	ABILITYATTTYPE	m_eAbility;

	bool						m_bControlUse;
	bool						m_bControlling;

	bool						m_bActive;
	CVehicle*					m_pClosestEntity;

public:
	CAbility(int _nEntityType);
	~CAbility();

	void Initialize();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	virtual	void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	virtual void RenderOrgan();

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CAbility>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){
		return m_pStateMachine->HandleMessage(_rMsg);
	}

	ABILITYATTTYPE GetAbility(){return m_eAbility;}
	void SetAbility(ABILITYATTTYPE _eAbility){m_eAbility = _eAbility;}

	void			SetActive(bool _bActive){m_bActive = _bActive;}
	bool			GetActive(){return m_bActive;}

	bool			GetControlling(){return m_bControlling;}
	void			OnControlling(){m_bControlling = true;}
	void			OffControlling(){m_bControlling = false;}

	bool			GetControlUse(){return m_bControlUse;}
	void			OnControl(){m_bControlUse = true;}
	void			OffControl(){m_bControlUse = false;}

	CVehicle* GetClosestEntity(){return m_pClosestEntity;}
	void			SetClosestEntity(CVehicle* _pVehicle){m_pClosestEntity = _pVehicle;}
};

#endif