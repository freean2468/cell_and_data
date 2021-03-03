#ifndef _SecretData_H_
#define _SecretData_H_

#include "../Engine_System/OrganEntity.h"
#include "Wall3D.h"
#include "DataBomb.h"
#include "Growth.h"
#include "../Engine_System/StateMachine.h"

class CSecretData : public COrganEntity{
public:
	typedef enum SecretDataAttType {HOLE, FIRST, SECOND, THIRD} SECRETDATAATTTYPE;

private:
	std::vector<CWall3D>	m_FireWalls;
	CDataBomb*				m_pDataBomb;

	CGrowth*				m_pGrowth;

	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CSecretData>* m_pStateMachine;

public:
	CSecretData(CGrowth::GROWTH _eGrowth, Vector2D _vPos);
	~CSecretData();

	void CreateFireWalls();
	void Initialize();

	// 이것은 반드시 설치되어야 한다.	
	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	void	RenderFireWalls(bool _bNormalRender, ID3DXLine* _pLine);

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CSecretData>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CSecretData>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){return m_pStateMachine->HandleMessage(_rMsg);	}

	CGrowth* GetGrowth(){return m_pGrowth;}
	CDataBomb* GetDataBomb(){return m_pDataBomb;}
	const std::vector<CWall3D>&					 GetFireWalls(){return m_FireWalls;}
};

#endif