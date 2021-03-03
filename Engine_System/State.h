////////////////////////////////////////////////////
// 상태 디자인 패턴에 쓰일 상태 조상 클래스
////////////////////////////////////////////////////
#ifndef _State_H_
#define _State_H_

struct Telegram;

template <class EntityType>
class CState{
public:
  virtual ~CState(){}

  // 상태에 진입할 때 이것이 실행된다.
  virtual void Enter(EntityType*)=0;

  // 이것은 갱신 단계에서 entity의 갱신 함수가 호출된다.
  virtual void Execute(EntityType*)=0;

  // 이것은 상태 퇴장 시에 실행된다.
  virtual void Exit(EntityType*)=0;

  // 에이전트가 메시지 발송기로부터 메시지를 접수하면 이 부분이 실행된다.
  virtual bool OnMessage(EntityType* , const Telegram&)=0;
};

#endif