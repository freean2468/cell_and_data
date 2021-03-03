#ifndef _CGrowth_H_
#define _CGrowth_H_

#include "../Engine_System/Timer.h"

class CGrowth{
public:
	typedef enum Growth {FIRST, SECOND, THIRD} GROWTH;

private:
	GROWTH m_eGrowth;		// ���� Ÿ�� ����
	int m_nStep;				// �ܰ躰 ����

	float m_fLimit;			// ���� �Ѱ�
	float m_fPresent;		// ���� ���嵵
	float m_fInit;			// �� ó�� ���嵵

	float m_fFrequency;	// ���嵵 ��� ��
	float m_fRatio;			// ���� ����

	CTimer* m_pTimer;		// ���� �ӵ�
	DWORD m_dwTime;

public:
	CGrowth(GROWTH _eGrowth);
	CGrowth(GROWTH _eGrowth, float _fLimit, float _fInit, float _fFrequency, DWORD _dwTime = 10);
	~CGrowth(){}

	void Update();

	void SetGrowth(GROWTH p_eGrowth);
	GROWTH GetGrowth(){return m_eGrowth;}
	int GetStep(){return m_nStep;}

	float GetPresent(){return m_fPresent;}
	float GetLimit(){return m_fLimit;}

	bool IsGrowthEnd(){return m_fPresent >= m_fLimit;}

	bool less(CGrowth* _pGrowth)const;
	bool less_equal(CGrowth* _pGrowth)const;
	bool greater(CGrowth* _pGrowth)const;
	bool greater_equal(CGrowth* _pGrowth)const;
	bool equal(CGrowth* _pGrowth)const;

	bool less(GROWTH _eGrowth)const;
	bool less_equal(GROWTH _eGrowth)const;
	bool greater(GROWTH _eGrowth)const;
	bool greater_equal(GROWTH _eGrowth)const;
	bool equal(GROWTH _eGrowth)const;

	bool IsGrowth(GROWTH _pGrowth);

	void IncreaseGrowthFrequency(float _fVal){m_fFrequency += _fVal;}
};

#endif