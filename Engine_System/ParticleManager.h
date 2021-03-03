/////////////////////////////////////////////////////
// CParticleManagerŬ������ �� ������ �ý����� �Ѱ���
////////////////////////////////////////////////////

#ifndef _ParticleManager_H_
#define _ParticleManager_H_

#include "Particle.h"
#include "../Engine_Data Structures/DLinkedList.h"

class CParticleManager{
private:
	CParticle* m_pSnow; // ��ƼŬ(��) ���
	
	CParticle* m_pDirt;	// ��ƼŬ(����) ���
	
	CParticle* m_pFirework; // ��ƼŬ(����) ���
	
	CParticle* m_pGun; // ��ƼŬ(��) ���
	
	CDLinkedList<CParticle*> m_pExhaustList;// ��ƼŬ(�ſ�) ���
	
	CParticle* m_pKindling;	// ��ƼŬ(�Ҿ�) ���

  // �����ڿ� �Ҹ��ڸ� �����ϰ� �Ҵ��� private�̾�� �Ѵ�.
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