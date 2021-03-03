////////////////////////////////////////////////////
// ���� ���� ��� Ŭ����
// ���µ��� ����
////////////////////////////////////////////////////
#ifndef _StateMachine_H_
#define _StateMachine_H_

#include "State.h"
#include <assert.h>
#include <stdlib.h>

template <class EntityType>
class CStateMachine{
private:
	// �� �ν��Ͻ��� �����ϴ� ������Ʈ�� ����Ű�� ������
	EntityType* m_pOwner;

	CState<EntityType>* m_pCurrentState;

	// ������Ʈ�� ���� �־��� ������ ������ ���
	CState<EntityType>* m_pPreviousState;

	// �� ���� ���� FSM�� ���ŵ� ������ ȣ��ȴ�.
	CState<EntityType>* m_pGlobalState;
public:
	CStateMachine(EntityType* _pOwner):m_pOwner(_pOwner),
									m_pCurrentState(NULL),
									m_pPreviousState(NULL),
									m_pGlobalState(NULL)
	{}

	// FSM�� �ʱ�ȭ�ϱ� ���� ���� �޼ҵ���� ����Ѵ�.
	void SetCurrentState(CState<EntityType>* _pSetCurrent){m_pCurrentState = _pSetCurrent;}
	void SetGlobalState(CState<EntityType>* _pSetGlobal){m_pGlobalState = _pSetGlobal;}
	void SetPreviousState(CState<EntityType>* _pSetPrevious){m_pPreviousState = _pSetPrevious;}

	// FSM�� �����ϱ� ���� �̰��� ȣ���Ѵ�.
	void Update()const{
		// ���� ���°� �����ϸ�, �װ��� execute �޼ҵ带 ȣ���Ѵ�.
		if(m_pGlobalState) m_pGlobalState->Execute(m_pOwner);

		// ���� ���¿� ���ؼ� �����ϰ�
		if(m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
	}

	// ���ο� ���·� ��ȭ��Ų��.
	void ChangeState(CState<EntityType>* _pNewState){
		assert(_pNewState && "<CStateMachine::ChangeState>: trying to change to a null state");

		// ���� ������ ����� �����Ѵ�.
		m_pPreviousState = m_pCurrentState;

		// ���� ������ exit �޼ҵ带 ȣ���Ѵ�.
		m_pCurrentState->Exit(m_pOwner);

		// ���¸� ���ο� ���·� ��ȭ��Ų��.
		m_pCurrentState = _pNewState;

		// ���ο� ������ enter �޼ҵ带 ȣ���Ѵ�.
		m_pCurrentState->Enter(m_pOwner);
	}

	// ���¸� ���� ���·� �ٽ� ��ȭ��Ų��.
	void RevertToPreviousState(){
		ChangeState(m_pPreviousState);
	}

	bool HandleMessage(const Telegram& _rMsg)const{
		// �켱 ���� ���°� ��ȿ�ϰ� �޽����� ó���� �� �ִ����� �˾ƺ���.
		if(m_pCurrentState && m_pCurrentState->OnMessage(m_pOwner, _rMsg)){
			return true;
		}

		// ó���� �� ���� ���� ���°� ��ġ�Ǿ� �ִٸ� �޽����� ���� ���·� ������.
		if(m_pGlobalState && m_pGlobalState->OnMessage(m_pOwner, _rMsg)){
			return false;
		}

		return false;
	}

	// ������(accessor)
	CState<EntityType>* CurrentState() const{return m_pCurrentState;}
	CState<EntityType>* GlobalState() const{return m_pGlobalState;}
	CState<EntityType>* PreviousState() const{return m_pPreviousState;}

	// ���� ���� ������ ������ �Ű������� �Ѱܹ��� Ŭ������ ���İ� ���ٸ�
	// ������ ��ȯ
	bool isInState(CState<EntityType>* st){	return CurrentState() == st;}
};

#endif