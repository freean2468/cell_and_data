////////////////////////////////////////////////////
// �޽��� ����
////////////////////////////////////////////////////
#ifndef _Telegram_H_
#define _Telegram_H_

struct Telegram{
	std::string m_strMessage;

	// �� ������ ������ Entity
	int m_nSender;

	// �� ������ �޴� ��ƼƼ
	int m_nReceiver;

	// �޽��� ��ü. �̰͵��� 'MessageTypes.h'���� ���� ���ŵ� ��� ���̴�.
	int m_nMsg;

	// �޽������� ���� ���� �޼۵ǰų� Ư�� �ð� ���� �����ȴ�.
	// ������ �ʿ��ϸ�, �� �ʵ�� �ð� ������ ���� ����
	// �޽����� �������� �Ѵ�.
	double m_dDispatchTime;

	DWORD m_dwShowTime;

	// �޽����� �Բ� ���� �߰����� ����
	void* m_pExtraInfo;

	Telegram():m_dDispatchTime(-1),
              m_nSender(-1),
              m_nReceiver(-1),
              m_nMsg(-1),
							m_dwShowTime(-1)
	{m_strMessage.clear();}

	Telegram(double _dTime, int _nSender, int _nReceiver, int _nMsg, void* _pInfo = NULL): 
																																							m_dDispatchTime(_dTime),
																																							m_nSender(_nSender),
																																							m_nReceiver(_nReceiver),
																																							m_nMsg(_nMsg),
																																							m_dwShowTime(-1),
																																							m_pExtraInfo(_pInfo)
	{m_strMessage.clear();}

	Telegram(const char* _pstrMessage, double _dDelay, DWORD _dwTime): 
																				m_dDispatchTime(_dDelay),
																				m_nSender(-1),
																				m_nReceiver(-1),
																				m_nMsg(-1),
																				m_dwShowTime(_dwTime),
																				m_pExtraInfo(NULL)
	{m_strMessage = _pstrMessage;}
};

const double SmallestDelay = 0.25;

// std::<set>���� ������� �ڵ� ������ �Ǳ� ���ؼ��� ũ�� �񱳰� �̷������ �� ��,
// �Ʒ��� ������ �����ε� �Լ����� �̸� �����ϰ� ���ش�.
inline bool operator==(const Telegram& t1, const Telegram& t2){
  return ( fabs(t1.m_dDispatchTime-t2.m_dDispatchTime) < SmallestDelay) &&
          (t1.m_nSender == t2.m_nSender)        &&
          (t1.m_nReceiver == t2.m_nReceiver)    &&
          (t1.m_nMsg == t2.m_nMsg)							&&
          (t1.m_dwShowTime == t2.m_dwShowTime)		&&
					(t1.m_strMessage == t2.m_strMessage);
}

inline bool operator<(const Telegram& t1, const Telegram& t2){
  if (t1 == t2)
  {
    return false;
  }

  else
  {
    return  (t1.m_dDispatchTime < t2.m_dDispatchTime);
  }
}

inline std::ostream& operator<<(std::ostream& stream_os, const Telegram& t){
  stream_os << "time: " << t.m_dDispatchTime << "  m_nSender: " << t.m_nSender
     << "   m_nReceiver: " << t.m_nReceiver << "   m_nMsg: " << t.m_nMsg;

  return stream_os;
}

#endif