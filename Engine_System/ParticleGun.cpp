#include "ParticleGun.h"

CParticleGun::CParticleGun(CCamera* _pCamera) : CParticle(0.8f,
														2048,
														0,
														512),
												m_pCamera(_pCamera)
{
}

void CParticleGun::resetParticle(Attribute* _pAttribute){
	_pAttribute->m_bAlive = true;

	D3DXVECTOR3 cameraPos;
	m_pCamera->GetPosition(&cameraPos);

	D3DXVECTOR3 cameraDir;
	m_pCamera->GetLook(&cameraDir);

	// ��ƼŬ ��ġ�� ī�޶� ��ġ�� �̿��Ѵ�.
	_pAttribute->m_vPosition = cameraPos;
	_pAttribute->m_vPosition.y -= 1.0f;	// ī�޶󺸴� �ణ �Ʒ������� �̵���
									// ���� ��� �ִ� �� ���� ȿ���� ��´�.

	// ī�޶� �ٶ󺸴� �������� �߻��Ѵ�.
	_pAttribute->m_vVelocity = cameraDir * 100.0f;

	// ���
	_pAttribute->m_vColor = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	_pAttribute->m_fAge = 0.0f;
	_pAttribute->m_fLifeTime = 1.0f;	// ������ 1��
}

void CParticleGun::update(float _fTimeDelta){
	std::list<Attribute>::iterator i;

	for(i = m_Particles.begin(); i != m_Particles.end(); i++){
		i->m_vPosition += i->m_vVelocity * _fTimeDelta;

		i->m_fAge += _fTimeDelta;

		if(i->m_fAge > i->m_fLifeTime)	// kill
			i->m_bAlive = false;
	}
	removeDeadParticles();
}