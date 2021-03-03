#include "ParticleManager.h"
#include "Snow.h"
#include "EngineManager.h"
#include "Dirt.h"
#include "Kindling.h"
#include "Exhaust.h"
#include "Firework.h"
#include "ParticleGun.h"
#include "CameraManager.h"

// �����ڿ����� �ʱ�ȭ���� ����Ѵ�.
CParticleManager::CParticleManager() : m_pSnow(NULL),
									m_pFirework(NULL),
									m_pDirt(NULL),
									m_pGun(NULL),
									m_pKindling(NULL)
{
}

CParticleManager::~CParticleManager(){
	// Device�� ���ø����̼ǿ��� �����Ѵ�.
	// ���� ������ ���� ������ �ݴ��(����)
	Delete<CParticle*>( m_pGun );
	Delete<CParticle*>( m_pFirework );
	Delete<CParticle*>( m_pSnow );
	Delete<CParticle*>( m_pKindling );
	Delete<CParticle*>( m_pDirt );
}

void CParticleManager::SetSnow(){
	DU::BoundingBox t_BoundingBox;

	t_BoundingBox._min = D3DXVECTOR3(-500.0f, -400.0f, -100.0f);
	t_BoundingBox._max = D3DXVECTOR3( 2500.0,  400.0f,  -50.0f);

	this->SetCSnow(new CSnow(&t_BoundingBox, 50));
	this->GetpSnow()->init(EngineMgr->GetpDevice(), "./Image/Particle/snowflake.dds");
}

void CParticleManager::SetDirt(float _fMinX, float _fMinY, float _fMinZ, float _fMaxX, float _fMaxY, float _fMaxZ, int _nNumParticles){
	DU::BoundingBox t_BoundingBox;

	t_BoundingBox._min = D3DXVECTOR3(_fMinX, _fMinY, _fMinZ);
	t_BoundingBox._max = D3DXVECTOR3(_fMaxX, _fMaxY, _fMaxZ);

	SetCDirt(new CDirt(&t_BoundingBox, _nNumParticles));	
}

void CParticleManager::SetKindling(float _fMinX, float _fMinY, float _fMinZ, float _fMaxX, float _fMaxY, float _fMaxZ, int _nNumParticles){
	DU::BoundingBox t_BoundingBox;

	t_BoundingBox._min = D3DXVECTOR3(_fMinX, _fMinY, _fMinZ);
	t_BoundingBox._max = D3DXVECTOR3(_fMaxX, _fMaxY, _fMaxZ);

	SetCKindling(new CKindling(&t_BoundingBox, _nNumParticles));	
}

void CParticleManager::SetExhaust(D3DXVECTOR3 _vOrigin, float _fMinX, float _fMinY, float _fMinZ, float _fMaxX, float _fMaxY, float _fMaxZ, int _nNumParticles){
	DU::BoundingBox t_BoundingBox;

	t_BoundingBox._min = D3DXVECTOR3(_fMinX, _fMinY, _fMinZ);
	t_BoundingBox._max = D3DXVECTOR3(_fMaxX, _fMaxY, _fMaxZ);

	m_pExhaustList.Append(new CExhaust(&t_BoundingBox, &_vOrigin, _nNumParticles));
}

void CParticleManager::UpdateExhaust(){
	// �ݺ��� ����
	CDListIterator<CParticle*> itr;
	
	// ExhaustList�κ��� �ݺ��� �ʱ�ȭ
	itr = m_pExhaustList.GetIterator();
	
	// ExhaustList�� ������
	for(itr.Start(); itr.Valid(); itr.Forth()){
		itr.Item()->update(EngineMgr->GetTimeDelta());
	}
}

void CParticleManager::RenderExhaust(){
	// �ݺ��� ����
	CDListIterator<CParticle*> itr;
	
	// ExhaustList�κ��� �ݺ��� �ʱ�ȭ
	itr = m_pExhaustList.GetIterator();
	
	// ExhaustList�� ������
	for(itr.Start(); itr.Valid(); itr.Forth()){
		itr.Item()->render();
	}
}

void CParticleManager::DeleteExhaust(){
	// �ݺ��� ����
	CDListIterator<CParticle*> itr;
	
	// ExhaustList�κ��� �ݺ��� �ʱ�ȭ
	itr = m_pExhaustList.GetIterator();
	
	// ExhaustList�� ������
	for(itr.Start(); itr.Valid();){
		Delete<CParticle*>(itr.Item());
		m_pExhaustList.Remove(itr);
	}
}

void CParticleManager::SetFireWork(){
	D3DXVECTOR3 origin(float(rand()%10), float(rand()%10), float(rand()%20+50));

	this->SetCFireWork(new CFirework(&origin, 3000));
	this->GetpFirework()->init(EngineMgr->GetpDevice(), "./Image/flare.bmp");
}

void CParticleManager::SetParticleGun(){
	this->SetCParticleGun(new CParticleGun( CameraMgr->GetCamera() ));
	this->GetpGun()->init(EngineMgr->GetpDevice(), "./Image/flare_alpha.dds");
}