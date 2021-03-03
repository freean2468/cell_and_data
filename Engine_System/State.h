////////////////////////////////////////////////////
// ���� ������ ���Ͽ� ���� ���� ���� Ŭ����
////////////////////////////////////////////////////
#ifndef _State_H_
#define _State_H_

struct Telegram;

template <class EntityType>
class CState{
public:
  virtual ~CState(){}

  // ���¿� ������ �� �̰��� ����ȴ�.
  virtual void Enter(EntityType*)=0;

  // �̰��� ���� �ܰ迡�� entity�� ���� �Լ��� ȣ��ȴ�.
  virtual void Execute(EntityType*)=0;

  // �̰��� ���� ���� �ÿ� ����ȴ�.
  virtual void Exit(EntityType*)=0;

  // ������Ʈ�� �޽��� �߼۱�κ��� �޽����� �����ϸ� �� �κ��� ����ȴ�.
  virtual bool OnMessage(EntityType* , const Telegram&)=0;
};

#endif