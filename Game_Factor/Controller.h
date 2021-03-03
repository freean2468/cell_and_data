#ifndef _CController_H_
#define _CController_H_

#include "Data.h"
#include "Virus.h"
#include "Vacine.h"

class CController{
private:
	CData*	m_pControl;
	CVirus* m_pVirus;

	bool m_bGrowing;

	// ���� ��Ʈ�ѷ��� ���̷��� �������� ������ �����Ϳ� �׵��� OldMaxSpeed�� ���� �����̳�
	std::vector<CData*> m_CrossingDataCon;
	std::vector<double>	m_OldMaxSpeedCon;

	std::vector<CVacine*> m_CrossingVacineCon;

	double m_nSecondBRadius;
	double m_nThirdBRadius;

private:
	CController();
	CController(const CController&);
	CController& operator =(const CController&);

public:
	~CController();
	static CController* Instance(){
		static CController instance;

		return &instance;
	}

	void Grow(CGrowth::GROWTH _eGrowth);

	void SetControlData(CData* _pData){m_pControl = _pData;}
	CData* GetControlData(){return m_pControl;}

	void SetController(CVirus* _pVirus){	m_pVirus = _pVirus; }
	CVirus* GetController(){return m_pVirus;}

	std::vector<CData*>* GetCrossingDataCon(){return &m_CrossingDataCon;}
	std::vector<double>*	GetOldMaxSpeedCon(){return &m_OldMaxSpeedCon;}

	std::vector<CVacine*>* GetCrossingVacineCon(){return &m_CrossingVacineCon;}

	void SetSecondBRadius(double _dRadius){ m_nSecondBRadius = _dRadius; }
	void SetThirdBRadius(double _dRadius){ m_nThirdBRadius = _dRadius;}

	bool GetGrowing(){return m_bGrowing;}
};

#define Controller CController::Instance()

#endif