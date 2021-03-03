////////////////////////////////////////////////////////////////////////////////
// 몸체 클래스
// 각종 신체에 대한 정보들의 바탕이 되는 중요한 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Body_H_
#define _Body_H_

#include "Organ.h"

class CBody : public COrgan{
public:
	// 각도 상태
	// 최대라면 true, 최소라면 false
	bool m_bAngleState;

	// Body 사용 여부.
	// 사용하지 않는다면 실체가 없는 Body => 렌더하지 않음.
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