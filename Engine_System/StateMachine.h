////////////////////////////////////////////////////
// 유한 상태 기계 클래스
// 상태들을 관리
////////////////////////////////////////////////////
#ifndef _StateMachine_H_
#define _StateMachine_H_

#include "State.h"
#include <assert.h>
#include <stdlib.h>

template <class EntityType>
class CStateMachine{
private:
	// 이 인스턴스를 소유하는 에이전트를 가리키는 포인터
	EntityType* m_pOwner;

	CState<EntityType>* m_pCurrentState;

	// 에이전트가 속해 있었던 마지막 상태의 기록
	CState<EntityType>* m_pPreviousState;

	// 이 상태 논리는 FSM이 갱신될 때마다 호출된다.
	CState<EntityType>* m_pGlobalState;
public:
	CStateMachine(EntityType* _pOwner):m_pOwner(_pOwner),
									m_pCurrentState(NULL),
									m_pPreviousState(NULL),
									m_pGlobalState(NULL)
	{}

	// FSM을 초기화하기 위해 다음 메소드들을 사용한다.
	void SetCurrentState(CState<EntityType>* _pSetCurrent){m_pCurrentState = _pSetCurrent;}
	void SetGlobalState(CState<EntityType>* _pSetGlobal){m_pGlobalState = _pSetGlobal;}
	void SetPreviousState(CState<EntityType>* _pSetPrevious){m_pPreviousState = _pSetPrevious;}

	// FSM을 갱신하기 위해 이것을 호출한다.
	void Update()const{
		// 전역 상태가 존재하면, 그것의 execute 메소드를 호출한다.
		if(m_pGlobalState) m_pGlobalState->Execute(m_pOwner);

		// 현재 상태에 대해서 동일하게
		if(m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
	}

	// 새로운 상태로 변화시킨다.
	void ChangeState(CState<EntityType>* _pNewState){
		assert(_pNewState && "<CStateMachine::ChangeState>: trying to change to a null state");

		// 이전 상태의 기록을 유지한다.
		m_pPreviousState = m_pCurrentState;

		// 기존 상태의 exit 메소드를 호출한다.
		m_pCurrentState->Exit(m_pOwner);

		// 상태를 새로운 상태로 변화시킨다.
		m_pCurrentState = _pNewState;

		// 새로운 상태의 enter 메소드를 호출한다.
		m_pCurrentState->Enter(m_pOwner);
	}

	// 상태를 이전 상태로 다시 변화시킨다.
	void RevertToPreviousState(){
		ChangeState(m_pPreviousState);
	}

	bool HandleMessage(const Telegram& _rMsg)const{
		// 우선 현재 상태가 유효하고 메시지를 처리할 수 있는지를 알아본다.
		if(m_pCurrentState && m_pCurrentState->OnMessage(m_pOwner, _rMsg)){
			return true;
		}

		// 처리할 수 없고 전역 상태가 설치되어 있다면 메시지를 전역 상태로 보낸다.
		if(m_pGlobalState && m_pGlobalState->OnMessage(m_pOwner, _rMsg)){
			return false;
		}

		return false;
	}

	// 접근자(accessor)
	CState<EntityType>* CurrentState() const{return m_pCurrentState;}
	CState<EntityType>* GlobalState() const{return m_pGlobalState;}
	CState<EntityType>* PreviousState() const{return m_pPreviousState;}

	// 만약 현재 상태의 형식이 매개변수로 넘겨받은 클래스의 형식과 같다면
	// 참값을 반환
	bool isInState(CState<EntityType>* st){	return CurrentState() == st;}
};

#endif