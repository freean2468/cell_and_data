/////////////////////////////////////////////////////
// CParticleManager클래스는 이 엔진의 시스템을 총괄함
////////////////////////////////////////////////////

#ifndef _ParticleManager_H_
#define _ParticleManager_H_

#include "Particle.h"
#include "../Engine_Data Structures/DLinkedList.h"

class CParticleManager{
private:
	CParticle* m_pSnow; // 파티클(눈) 담당
	
	CParticle* m_pDirt;	// 파티클(먼지) 담당
	
	CParticle* m_pFirework; // 파티클(폭죽) 담당
	
	CParticle* m_pGun; // 파티클(건) 담당
	
	CDLinkedList<CParticle*> m_pExhaustList;// 파티클(매연) 담당
	
	CParticle* m_pKindling;	// 파티클(불씨) 담당

  // 생성자와 소멸자를 복사하고 할당은 private이어야 한다.
	CParticleManager(const CParticleManager&);
	CParticleManager& operator=(const CParticleManager&);

public:
	CParticleManager();
	~CParticleManager();

	static CParticleManager* Instance(){
		 static CParticleManager instance;

		 return &instance;
	}

	void UpdateExhaust();
	void RenderExhaust();
	void DeleteExhaust();

	void SetSnow();
	void SetDirt(float _fMinX, float _fMinY, float _fMinZ, float _fMaxX, float _fMaxY, float _fMaxZ, int _nNumParticles);
	void SetKindling(float _fMinX, float _fMinY, float _fMinZ, float _fMaxX, float _fMaxY, float _fMaxZ, int _nNumParticles);
	void SetExhaust(D3DXVECTOR3 _vOrigin, float _fMinX, float _fMinY, float _fMinZ, float _fMaxX, float _fMaxY, float _fMaxZ, int _nNumParticles);
	void SetFireWork();
	void SetParticleGun();

	void SetCSnow(CParticle* _pSnow){m_pSnow = _pSnow;}
	void SetCDirt(CParticle* _pDirt){m_pDirt = _pDirt;}
	void SetCKindling(CParticle* _pKindling){m_pKindling = _pKindling;}
	void SetCFireWork(CParticle* _pFire){m_pFirework = _pFire;}
	void SetCParticleGun(CParticle* _pGun){m_pGun = _pGun;};

	CParticle* GetpSnow(){return m_pSnow;}
	CParticle* GetpDirt(){return m_pDirt;}
	CParticle* GetpKindling(){return m_pKindling;}
	CDLinkedList<CParticle*> GetpExhaust(){return m_pExhaustList;}
	CParticle* GetpFirework(){return m_pFirework;}
	CParticle* GetpGun(){return m_pGun;}
};

#define ParticleMgr CParticleManager::Instance()

#endif