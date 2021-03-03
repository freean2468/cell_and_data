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

	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CSecretData>* m_pStateMachine;

public:
	CSecretData(CGrowth::GROWTH _eGrowth, Vector2D _vPos);
	~CSecretData();

	void CreateFireWalls();
	void Initialize();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.	
	virtual void Update(double _dTimeElapsed = SYSTEM_FRAME_INTERVAL_VER_60);

	void	RenderFireWalls(bool _bNormalRender, ID3DXLine* _pLine);

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CSecretData>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CSecretData>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& _rMsg){return m_pStateMachine->HandleMessage(_rMsg);	}

	CGrowth* GetGrowth(){return m_pGrowth;}
	CDataBomb* GetDataBomb(){return m_pDataBomb;}
	const std::vector<CWall3D>&					 GetFireWalls(){return m_FireWalls;}
};

#endif