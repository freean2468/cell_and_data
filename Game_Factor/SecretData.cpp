#include "SecretData.h"
#include "../Engine_System/EntityType.h"
#include "SecretDataOwnedStates.h"

CSecretData::CSecretData(CGrowth::GROWTH _eGrowth, Vector2D _vPos):COrganEntity(SECRETDATA)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CSecretData>(this);

	LoadEntityData("./script/GameFactor/SecretData/SecretData.txt");

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(SecretDataMaintain->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	this->UniformOrganColor(D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f));

	m_pGrowth = new CGrowth(_eGrowth);	

	if(GetGrowth()->IsGrowth(CGrowth::FIRST)){
		ResizeObject(0.15f);
	}
	else if(GetGrowth()->IsGrowth(CGrowth::SECOND)){
		ResizeObject(0.35f);
	}

	this->SetPos(_vPos);
	GetBody()->GetPriPos()->x = (float)_vPos.x;
	GetBody()->GetPriPos()->y = (float)_vPos.y;

	m_pDataBomb = new CDataBomb(GetBody()->GetPriPos(), 200);

	CreateFireWalls();
}

CSecretData::~CSecretData(){
	Delete<CDataBomb*>(m_pDataBomb);
	Delete<CStateMachine<CSecretData>*>(m_pStateMachine);
	Delete<CGrowth*>(m_pGrowth);
}


void CSecretData::CreateFireWalls(){    
	Vector2D t_vPos = Vector2D(GetBody()->GetPriPos()->x, GetBody()->GetPriPos()->y);

	Vector2D walls[4] = {Vector2D(t_vPos.x - GetRadius()*4.0, t_vPos.y - GetRadius()*4.0),
                       Vector2D(t_vPos.x - GetRadius()*4.0, t_vPos.y + GetRadius()*4.0),
                       Vector2D(t_vPos.x + GetRadius()*4.0, t_vPos.y + GetRadius()*4.0),
                       Vector2D(t_vPos.x + GetRadius()*4.0, t_vPos.y - GetRadius()*4.0)};

	for(int i = 0; i < 3; i++){
		m_FireWalls.push_back(CWall3D(walls[i],walls[i+1]));
	}
	m_FireWalls.push_back(CWall3D(walls[3],walls[0]));
}

void CSecretData::Update(double _dTimeElapsed){
	m_pStateMachine->Update();
}

void CSecretData::RenderFireWalls(bool _bNormalRender, ID3DXLine* _pLine){
	for(unsigned int w=0; w<m_FireWalls.size(); ++w){
    m_FireWalls[w].Render(_pLine, &D3DXCOLOR(1.0f, -1.0f, -1.0f, 1.0f), _bNormalRender);  //true flag shows normals
  }
}