#include "Particle.h"

const DWORD Particle::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

CParticle::CParticle() : m_pDevice(NULL),
						m_pVB(NULL),
						m_pTex(NULL)
{
}

CParticle::CParticle(float _fSize, DWORD _dwVBSize, DWORD _dwVBOffset, 
										 DWORD _dwVBBatchSize) : m_pDevice(NULL),
																m_pVB(NULL),
																m_pTex(NULL),
																m_fSize(_fSize),
																m_dwVBSize(_dwVBSize),
																m_dwVBOffset(_dwVBOffset),
																m_dwVBBatchSize(_dwVBBatchSize)
{
}

CParticle::CParticle(D3DXVECTOR3* _pvOrigin, float _fSize, DWORD _dwVBSize, 
										 DWORD _dwVBOffset, DWORD _dwVBBatchSize) : m_pDevice(NULL),
																					m_pVB(NULL),
																					m_pTex(NULL),
																					m_vOrigin(*_pvOrigin),
																					m_fSize(_fSize),
																					m_dwVBSize(_dwVBSize),
																					m_dwVBOffset(_dwVBOffset),
																					m_dwVBBatchSize(_dwVBBatchSize)
{
}

CParticle::CParticle(DU::BoundingBox* _BoundingBox, float _fSize, DWORD _dwVBSize, 
										 DWORD _dwVBOffset, DWORD _dwVBBatchSize) : m_pDevice(NULL),
																					m_pVB(NULL),
																					m_pTex(NULL),
																					m_BoundingBox(*_BoundingBox),
																					m_fSize(_fSize),
																					m_dwVBSize(_dwVBSize),
																					m_dwVBOffset(_dwVBOffset),
																					m_dwVBBatchSize(_dwVBBatchSize)
{
}

CParticle::CParticle(DU::BoundingBox* _BoundingBox, D3DXVECTOR3* _pvOrigin, float _fSize, 
									 DWORD _dwVBSize, DWORD _dwVBOffset, DWORD _dwVBBatchSize) : 
																								m_pDevice(NULL),
																								m_pVB(NULL),
																								m_pTex(NULL),
																								m_BoundingBox(*_BoundingBox),
																								m_vOrigin(*_pvOrigin),
																								m_fSize(_fSize),
																								m_dwVBSize(_dwVBSize),
																								m_dwVBOffset(_dwVBOffset),
																								m_dwVBBatchSize(_dwVBBatchSize)
{
}

CParticle::~CParticle(){
	Release<IDirect3DVertexBuffer9*>(m_pVB);
	Release<IDirect3DTexture9*>(m_pTex);
	removeParticles();
}

// ����Ʈ ��������Ʈ�� �����ϱ� ���� ���ؽ� ���۸� ����� �ؽ�ó�� ����� ����
// DIrect3D�� ��ġ �������� �ʱ�ȭ �۾��� ó���Ѵ�.
bool CParticle::init(IDirect3DDevice9* _pDevice, const char* _pstrTexFileName){
	// vertex buffer's size does not equal the number of particles in our system.  We
	// use the vertex buffer to draw a portion of our particles at a time.  The arbitrary
	// size we choose for the vertex buffer is specified by the m_dwVBSize variable.

	m_pDevice = _pDevice; // save a ptr to the device

	HRESULT hr = 0;

	// ���� ���ؽ� ���� �̿�
	hr = m_pDevice->CreateVertexBuffer(
		m_dwVBSize * sizeof(Particle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		Particle::FVF,
		D3DPOOL_DEFAULT, // D3DPOOL_MANAGED can't be used with D3DUSAGE_DYNAMIC 
		&m_pVB,
		0);
	
	if(FAILED(hr))	{
		OutputDebugString("CreateVertexBuffer() - FAILED");
		return false;
	}

	hr = D3DXCreateTextureFromFile(
		m_pDevice,
		_pstrTexFileName,
		&m_pTex);

	if(FAILED(hr))	{
		OutputDebugString("D3DXCreateTextureFromFile() - FAILED");
		return false;
	}

	return true;
}

// �� �޼���� �ý��� ���� ��� ��ƼŬ �Ӽ��� �����Ѵ�.
void CParticle::reset(){
	std::list<Attribute>::iterator i;
	for(i = m_Particles.begin(); i != m_Particles.end(); i++){
		resetParticle(&(*i));
	}
}

// Ŭ������ ��ƼŬ�� �߰��Ѵ�. ����Ʈ�� �߰����� ���� ��ƼŬ�� �ʱ�ȭ
void CParticle::addParticle(){
	Attribute _pAttribute;

	resetParticle(&_pAttribute);

	m_Particles.push_back(_pAttribute);
}

// �������� �ռ� �����ؾ� �� �ʱ� ���� ���¸� �����Ѵ�.
void CParticle::preRender(){
	// ZBuffer ���� ����
	m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	m_pDevice->SetRenderState(D3DRS_POINTSIZE, DU::FtoDw(m_fSize));
	m_pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, DU::FtoDw(0.0f));

	// ����ä��1 = Texture �÷��� ���� ����
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	//m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
	
	// �� ����ä���� ���Ͽ� �����Ͽ� ���� ����� ����
	//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	

	// �Ÿ��� ���� ��ƼŬ�� ũ�⸦ �����Ѵ�.
	m_pDevice->SetRenderState(D3DRS_POINTSCALE_A, DU::FtoDw(0.0f));
	m_pDevice->SetRenderState(D3DRS_POINTSCALE_B, DU::FtoDw(0.0f));
	m_pDevice->SetRenderState(D3DRS_POINTSCALE_C, DU::FtoDw(1.0f));

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	// ���� �μ��� �����Ͽ� ���� ������ ������ �����ϵ��� ��
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

//	EngineMgr->GetpSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
}

// Ư�� ��ƼŬ Ŭ������ �������� �� �ִ� ���� ���¸� �����ϴ� �� �̿�ȴ�.
void CParticle::postRender(){
//	EngineMgr->GetpSprite()->End();

	m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE,false);
	m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	// ZBuffer ���� ����
	/*m_pDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);*/

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, true);
}

// ���� Ŭ������ ��ƼŬ�� ���� ��� True�� ����
bool CParticle::isEmpty(){
	return m_Particles.empty();
}

// Ŭ���� ���� ��ƼŬ�� ��� ���� ��� True�� ����
// ���� ���´� ��ƼŬ�� ���������� ���� ������ ǥ�õ� ���¸� �ǹ�
bool CParticle::isDead(){
	std::list<Attribute>::iterator i;
	for(i = m_Particles.begin(); i != m_Particles.end(); i++){
		// is there at least one living particle?  If yes,
		// the system is not dead.
		if( i->m_bAlive )
			return false;
	}
	// no living particles found, the system must be dead.
	return true;
}

// �Ӽ� ����Ʈ _particle�� �˻��Ͽ� ���� ��ƼŬ�� ����Ʈ���� �����Ѵ�.
void CParticle::removeDeadParticles(){
	std::list<Attribute>::iterator i;

	i = m_Particles.begin();

	while(i != m_Particles.end()){
		if(i->m_bAlive == false){
			// erase�� ���� �ݺ��ڸ� �����ϹǷ� �츮�� �ݺ��ڸ� ������ų �ʿ䰡 ����.
			i = m_Particles.erase(i);
		}
		else{
			i++;	// next in list
		}
	}
}

// ��� ��ƼŬ�� ����
void CParticle::removeParticles(){
	std::list<Attribute>::iterator i;

	i = m_Particles.begin();

	while(i != m_Particles.end()){		
		i = m_Particles.erase(i);
	}
}

void CParticle::render(){
	if(!m_Particles.empty()){
		// ���� ���¸� �����Ѵ�.
		preRender();

		D3DXMATRIXA16 mtMatrix;
		D3DXMatrixIdentity(&mtMatrix);

		m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

		m_pDevice->SetFVF(Particle::FVF);
		m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(Particle));
		m_pDevice->SetTexture(0, m_pTex);	

		// ���ؽ� ���۸� ��� ��� ó������ �����Ѵ�.
		if(m_dwVBOffset >= m_dwVBSize)
			m_dwVBOffset = 0;

		Particle* v = 0;

		m_pVB->Lock(
			m_dwVBOffset * sizeof(Particle),
			m_dwVBBatchSize * sizeof(Particle),
			(void**)&v,
			m_dwVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		// ��� ��ƼŬ�� �������� ������
		std::list<Attribute>::iterator i;
		for(i = m_Particles.begin(); i != m_Particles.end(); i++){
			if(i->m_bAlive){
				// �� �ܰ��� ������ ��ƼŬ�� ���� ���ؽ� ���� ���׸�Ʈ�� �����Ѵ�.
				v->m_vPosition = i->m_vPosition;
				v->m_vColor = (D3DXCOLOR)i->m_vColor;
				v++;	// next element;
				numParticlesInBatch++;	// �ܰ� ī���͸� ������Ų��.
			

				// ���� �ܰ谡 ��� ä���� �ִ°�?
				if(numParticlesInBatch == m_dwVBBatchSize){
					// ���ؽ� ���۷� ����� ������ �ܰ��� ��ƼŬ�� �׸���.
					m_pVB->Unlock();

					m_pDevice->DrawPrimitive(
						D3DPT_POINTLIST,
						m_dwVBOffset,
						m_dwVBBatchSize);

					// �ܰ谡 �׷����� ���� ���� �ܰ踦 ��ƼŬ�� ä���.

					// ���� �ܰ��� ó�� ���������� �̵��Ѵ�.
					m_dwVBOffset += m_dwVBBatchSize;

					// ���ؽ� ������ ��踦 �Ѵ� �޸𸮷� �������� �������� �ʴ´�.
					// ��踦 ���� ��� ó������ �����Ѵ�.
					if(m_dwVBOffset >= m_dwVBSize)
						m_dwVBOffset = 0;

					m_pVB->Lock(
						m_dwVBOffset * sizeof(Particle),
						m_dwVBBatchSize * sizeof(Particle),
						(void**)&v,
						m_dwVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0; // ���� �ܰ踦 ���� ����
				}//end if
			}//end if
		}//end for
		m_pVB->Unlock();

		//(numParticlesInBatch == m_dwVBBatchSize) ������ �������� ���Ͽ�
		// ������ �ܰ谡 ���������� �ʴ� ��찡 �߻��� �� �ִ�. �Ϻθ� ä���� �ܰ��
		// �ٷ� �̰����� �������ȴ�.

		if(numParticlesInBatch){
			m_pDevice->DrawPrimitive(
				D3DPT_POINTLIST,
				m_dwVBOffset,
				numParticlesInBatch);
		}

		D3DXMatrixIdentity(&mtMatrix);
		m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

		// ���� ���
		m_dwVBOffset += m_dwVBBatchSize;
		postRender();
	} // end if
} // end render()