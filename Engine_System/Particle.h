////////////////////////////////////////////////////////////////
// ��ƼŬ Ŭ����
// ������ ��ƼŬ�� ���� ���� �� Ŭ������ ����ؼ� �����.
// ��� ����� ������ ���� �ƴϹǷ� ������� ��ƼŬ�� ���� Ŀ�����ؾ� �� �� ����
// ��å ����
////////////////////////////////////////////////////////////////
#ifndef _Particle_H_
#define _Particle_H_

#include "../Engine_Misc/DirectUtils.h"
#include <list>

struct Particle{
	D3DXVECTOR3 m_vPosition;
	D3DXCOLOR		m_vColor;
	static const DWORD FVF;
};

struct Attribute{
	D3DXVECTOR3 m_vPosition;			// ���� �����̽� ���� ��ƼŬ ��ġ
	D3DXVECTOR3 m_vVelocity;			// ��ƼŬ�� �ӵ�, ������ �ʴ� �̵� ������ ����Ѵ�.
	D3DXVECTOR3 m_vAcceleration;	// ��ƼŬ�� ����, ������ �ʴ� �̵� ������ ����Ѵ�.
	float				m_fLifeTime;			// ��ƼŬ�� �Ҹ��� ������ �����Ǵ� �ð�
	float				m_fAge;						// ��ƼŬ�� ���� ����
	D3DXCOLOR		m_vColor;					// ��ƼŬ�� �÷�
	D3DXCOLOR		m_vColorFade;			// ��ƼŬ�� �÷��� �ð��� �帧�� ���� ����ϴ� ���
	bool				m_bAlive;				// ��ƼŬ�� ������ ��� True, �Ҹ��� ��� False
};

class CParticle{
protected:
	IDirect3DDevice9*				m_pDevice;
	D3DXVECTOR3							m_vOrigin;			// Ŭ������ ��õ. �ý��� ������ ��ƼŬ�� ���۵Ǵ� ��
	DU::BoundingBox					m_BoundingBox;	// ��� ���ڴ� ��ƼŬ�� �̵��� �� �ִ� ���Ǹ� �����ϴ� �� �̿�ȴ�.
	float										m_fEmitRate;		// Ŭ������ ���ο� ��ƼŬ�� �߰��Ǵ� ����. ������ �ʴ� ��ƼŬ ���� ���
	float										m_fSize;				// Ŭ���� �� ��� ��ƼŬ�� ũ��
	IDirect3DTexture9*			m_pTex;
	IDirect3DVertexBuffer9*	m_pVB;
	std::list<Attribute>		m_Particles;		// �ý��� �� ��ƼŬ �Ӽ��� ����Ʈ (��ƼŬ�� ����� �����ϰ� �����ϴ� �� �� ����Ʈ�� �̿�
	int											m_nMaxParticles;// �־��� �ð� ���� Ŭ������ ���� �� �ִ� �ִ� ��ƼŬ�� ��

	DWORD m_dwVBSize;				// ���ؽ� ���۰� ������ �� �ִ� ��ƼŬ�� ��. ���� ��ƼŬ Ŭ���� ���� ��ƼŬ ���ʹ� ������
	DWORD m_dwVBOffset;			// ���ؽ� ���ۿ��� ���縦 ������ ��ƼŬ �� ���� �ܰ���ǿ����(��ƼŬ ����)
	DWORD m_dwVBBatchSize;	// �ϳ��� �ܰ迡 ���ǵ� ��ƼŬ�� ��

public:
	CParticle();
	CParticle(float _fSize, DWORD _dwVBSize, DWORD _dwVBOffset, DWORD _dwVBBatchSize);
	CParticle(D3DXVECTOR3* _pvOrigin, float _fSize, DWORD _dwVBSize, DWORD _dwVBOffset, DWORD _dwVBBatchSize);
	CParticle(DU::BoundingBox* _BoundingBox, float _fSize, DWORD _dwVBSize, DWORD _dwVBOffset, DWORD _dwVBBatchSize);
	CParticle(DU::BoundingBox* _BoundingBox, D3DXVECTOR3* _pvOrigin, float _fSize, DWORD _dwVBSize, DWORD _dwVBOffset, DWORD _dwVBBatchSize);
	
	virtual ~CParticle();

	virtual bool init(IDirect3DDevice9* _pDevice, const char* _pstrTexFileName);
	virtual void reset();
	virtual void resetParticle(Attribute* _pAttribute) = 0;
	virtual void removeParticles();
	virtual void addParticle();
	virtual void update(float _fTimeDelta) = 0;

	virtual void preRender();
	virtual void render();
	virtual void postRender();

	bool isEmpty();
	bool isDead();

protected:
	virtual void removeDeadParticles();
};

#endif