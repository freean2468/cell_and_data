#ifndef _RuntimeCmp_H_
#define _RuntimeCmp_H_

template <class T>
class CRuntimeCmp{
public:
	typedef enum CmpMode {NORMAL, REVERSE} CMPMODE;

private:
	CMPMODE m_eMode;

public:
	// 정렬 기준을 위한 생성자
	CRuntimeCmp(CMPMODE _eMode = NORMAL);
	~CRuntimeCmp();

	// 원소의 비교
	bool operator()(const T& _T1, const T& _T2) const{
		return m_eMode == NORMAL ? _T1 < _T2 : _T2 < _T1;
	}

	// 정렬 기준의 비교
	bool operator==(const CRuntimeCmp& _ref){
		return m_eMode == _ref.m_eMode;
	}
};

template<class T>
CRuntimeCmp<T>::CRuntimeCmp(CMPMODE _eMode) : m_eMode(_eMode)
{

}

template<class T>
CRuntimeCmp<T>::~CRuntimeCmp()
{

}


#endif