////////////////////////////////////////////////////////////////////////////////
// NumberArray Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _NumberArray_H_
#define _NumberArray_H_

#include "Number.h"

class CNumberArray{
private:
	D3DXVECTOR3 m_vPos;

	std::vector<CNumber*> m_Number;
	
	CTimer* m_UpdateGap;
	DWORD m_dwUpdateGap;

	int m_nValue;
	int m_nMaxPlace;	// �ִ� �ڸ���
	int m_nPlace;			// �ڸ���
	int m_nIndex;			// ��ȿ �ε���

	float m_fSumWidth;			

public:
	CNumberArray(D3DXVECTOR3* _pvPos, int _nPlace, int _nValue, DWORD _dwGap);
	~CNumberArray();

	void Initialize();
	void InitNumberList();
	void Update();
	void Render();

	float GetSumWidth(){return m_fSumWidth;}

	int GetValue(){return m_nValue;}
	void SetValue(int _nValue){if(m_UpdateGap->IsElapseTimer()){m_UpdateGap->InitTimer(m_dwUpdateGap); m_nValue = _nValue;}}

	D3DXVECTOR3* GetPos3D(){return &m_vPos;}
};

#endif