////////////////////////////////////////////////////////////////////////////////
// ��ü Ŭ����
// ���� ��ü�� ���� �������� ������ �Ǵ� �߿��� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Body_H_
#define _Body_H_

#include "Organ.h"

class CBody : public COrgan{
public:
	// ���� ����
	// �ִ��� true, �ּҶ�� false
	bool m_bAngleState;

	// Body ��� ����.
	// ������� �ʴ´ٸ� ��ü�� ���� Body => �������� ����.
	bool m_bBodyFake;

public:
	CBody():COrgan(){m_bBodyFake = false;}
	CBody(D3DXVECTOR3 _vPos, D3DXVECTOR3 _vSca, D3DXVECTOR3 _vRot, D3DXVECTOR3 _vCen);
	virtual	~CBody();

	virtual void Update(){}

	void Render();

	virtual bool HandleMessage(const Telegram& _rMsg){return false;}

	virtual void SettingOrgan(D3DXVECTOR3* _pvChainPos, D3DXVECTOR3* _pvChainSca, D3DXVECTOR3* _pvChainRot, D3DXVECTOR3* _pvChainCen);
	virtual void Render(D3DXVECTOR3* _vPos, D3DXVECTOR3* _pvSca, D3DXVECTOR3* _pvRot, D3DXVECTOR3* _pvCen);
};

#endif