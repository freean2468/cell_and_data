////////////////////////////////////////////////////
// 메시지 정보
////////////////////////////////////////////////////
#ifndef _Telegram_H_
#define _Telegram_H_

struct Telegram{
	std::string m_strMessage;

	// 이 정보를 보내는 Entity
	int m_nSender;

	// 이 전보를 받는 엔티티
	int m_nReceiver;

	// 메시지 자체. 이것들은 'MessageTypes.h'파일 내에 열거된 모든 것이다.
	int m_nMsg;

	// 메시지들은 지금 당장 급송되거나 특정 시간 동안 지연된다.
	// 지연이 필요하면, 이 필드는 시간 도장이 찍힌 다음
	// 메시지가 보내져야 한다.
	double m_dDispatchTime;

	DWORD m_dwShowTime;

	// 메시지와 함께 따라갈 추가적인 정보
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

// std::<set>에서 순서대로 자동 정렬이 되기 위해서는 크기 비교가 이루어져야 할 것,
// 아래의 연산자 오버로딩 함수들이 이를 가능하게 해준다.
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