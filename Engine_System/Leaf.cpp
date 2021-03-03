#include "Leaf.h"
#include "EngineManager.h"

CLeaf::CLeaf(CDirectXEntity* _pOrigin, int _nNumParticles, float _fRadius) :CParticle(10,
																					50,
																					0,
																					25),
																			m_pOrigin(_pOrigin),
																			m_fRadius(_fRadius)
{
	for(int i =0;i<_nNumParticles; i++)
		addParticle();
	
	int _nRand = ::RandInt(1, 4);

	if(_nRand == 1)				init(EngineMgr->GetpDevice(), "./Image/Particle/Leaf/Leaf_1.dds");
	else if(_nRand == 2)	init(EngineMgr->GetpDevice(), "./Image/Particle/Leaf/Leaf_2.dds");
	else if(_nRand == 3)	init(EngineMgr->GetpDevice(), "./Image/Particle/Leaf/Leaf_3.dds");
	else if(_nRand == 4)	init(EngineMgr->GetpDevice(), "./Image/Particle/Leaf/Leaf_4.dds");
}

CLeaf::~CLeaf(){

}

void CLeaf::resetParticle(Attribute* _pAttribute){
	_pAttribute->m_bAlive = true;
	//m_fSize = (float)RandInRange(m_fSize*0.5f, m_fSize*1.5f);

	// 위치 지정을위해 임의의 x, z 좌표를 얻는다.
	_pAttribute->m_vPosition.x = m_pOrigin->GetPos3D()->x + (float)::RandInRange(-m_fRadius, m_fRadius);
	_pAttribute->m_vPosition.y = m_pOrigin->GetPos3D()->y + (float)::RandInRange(-m_fRadius, m_fRadius);
	_pAttribute->m_vPosition.z = 0.0f;

	_pAttribute->m_vColor = D3DXCOLOR(255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f,	255.0f/255.0f);
}

void CLeaf::update(float _fTimeDelta){
	std::list<Attribute>::iterator i;

	for(i = m_Particles.begin(); i != m_Particles.end(); i++){
		return;
	}
}