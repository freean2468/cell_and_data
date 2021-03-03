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

// 포인트 스프라이트를 저장하기 위한 버텍스 버퍼를 만들고 텍스처를 만드는 등의
// DIrect3D의 장치 의존적인 초기화 작업을 처리한다.
bool CParticle::init(IDirect3DDevice9* _pDevice, const char* _pstrTexFileName){
	// vertex buffer's size does not equal the number of particles in our system.  We
	// use the vertex buffer to draw a portion of our particles at a time.  The arbitrary
	// size we choose for the vertex buffer is specified by the m_dwVBSize variable.

	m_pDevice = _pDevice; // save a ptr to the device

	HRESULT hr = 0;

	// 동적 버텍스 버퍼 이용
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

// 이 메서드는 시스템 내의 모든 파티클 속성을 리셋한다.
void CParticle::reset(){
	std::list<Attribute>::iterator i;
	for(i = m_Particles.begin(); i != m_Particles.end(); i++){
		resetParticle(&(*i));
	}
}

// 클래스에 파티클을 추가한다. 리스트에 추가히기 전에 파티클을 초기화
void CParticle::addParticle(){
	Attribute _pAttribute;

	resetParticle(&_pAttribute);

	m_Particles.push_back(_pAttribute);
}

// 렌더링에 앞서 지정해야 할 초기 렌더 상태를 지정한다.
void CParticle::preRender(){
	// ZBuffer 연산 꺼줌
	m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	m_pDevice->SetRenderState(D3DRS_POINTSIZE, DU::FtoDw(m_fSize));
	m_pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, DU::FtoDw(0.0f));

	// 알파채널1 = Texture 컬러로 알파 지정
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	//m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
	
	// 두 알파채널을 곱하여 조정하여 최종 결과물 결정
	//m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	

	// 거리에 따른 파티클의 크기를 제어한다.
	m_pDevice->SetRenderState(D3DRS_POINTSCALE_A, DU::FtoDw(0.0f));
	m_pDevice->SetRenderState(D3DRS_POINTSCALE_B, DU::FtoDw(0.0f));
	m_pDevice->SetRenderState(D3DRS_POINTSCALE_C, DU::FtoDw(1.0f));

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	// 블렌딩 인수를 지정하여 알파 성분이 투명도를 결정하도록 함
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

//	EngineMgr->GetpSprite()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
}

// 특정 파티클 클래스가 지정했을 수 있는 렌더 상태를 복구하는 데 이용된다.
void CParticle::postRender(){
//	EngineMgr->GetpSprite()->End();

	m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE,false);
	m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	// ZBuffer 연산 켜줌
	/*m_pDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);*/

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, true);
}

// 현재 클래스에 파티클이 없는 경우 True를 리턴
bool CParticle::isEmpty(){
	return m_Particles.empty();
}

// 클래스 내의 파티클이 모두 죽은 경우 True를 리턴
// 죽은 상태는 파티클이 존재하지만 죽은 것으로 표시된 상태를 의미
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

// 속성 리스트 _particle을 검색하여 죽은 파티클을 리스트에서 제거한다.
void CParticle::removeDeadParticles(){
	std::list<Attribute>::iterator i;

	i = m_Particles.begin();

	while(i != m_Particles.end()){
		if(i->m_bAlive == false){
			// erase는 다음 반복자를 리턴하므로 우리가 반복자를 증가시킬 필요가 없다.
			i = m_Particles.erase(i);
		}
		else{
			i++;	// next in list
		}
	}
}

// 모든 파티클들 삭제
void CParticle::removeParticles(){
	std::list<Attribute>::iterator i;

	i = m_Particles.begin();

	while(i != m_Particles.end()){		
		i = m_Particles.erase(i);
	}
}

void CParticle::render(){
	if(!m_Particles.empty()){
		// 렌더 상태를 지정한다.
		preRender();

		D3DXMATRIXA16 mtMatrix;
		D3DXMatrixIdentity(&mtMatrix);

		m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

		m_pDevice->SetFVF(Particle::FVF);
		m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(Particle));
		m_pDevice->SetTexture(0, m_pTex);	

		// 버텍스 버퍼를 벗어날 경우 처음부터 시작한다.
		if(m_dwVBOffset >= m_dwVBSize)
			m_dwVBOffset = 0;

		Particle* v = 0;

		m_pVB->Lock(
			m_dwVBOffset * sizeof(Particle),
			m_dwVBBatchSize * sizeof(Particle),
			(void**)&v,
			m_dwVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		// 모든 파티클이 렌더링될 때까지
		std::list<Attribute>::iterator i;
		for(i = m_Particles.begin(); i != m_Particles.end(); i++){
			if(i->m_bAlive){
				// 한 단계의 생존한 파티클을 다음 버텍스 버퍼 세그먼트로 복사한다.
				v->m_vPosition = i->m_vPosition;
				v->m_vColor = (D3DXCOLOR)i->m_vColor;
				v++;	// next element;
				numParticlesInBatch++;	// 단계 카운터를 증가시킨다.
			

				// 현재 단계가 모두 채워져 있는가?
				if(numParticlesInBatch == m_dwVBBatchSize){
					// 버텍스 버퍼로 복사된 마지막 단계의 파티클을 그린다.
					m_pVB->Unlock();

					m_pDevice->DrawPrimitive(
						D3DPT_POINTLIST,
						m_dwVBOffset,
						m_dwVBBatchSize);

					// 단계가 그려지는 동안 다음 단계를 파티클로 채운다.

					// 다음 단계의 처음 오프셋으로 이동한다.
					m_dwVBOffset += m_dwVBBatchSize;

					// 버텍스 버퍼의 경계를 넘는 메모리로 오프셋을 설정하지 않는다.
					// 경계를 넘을 경우 처음부터 시작한다.
					if(m_dwVBOffset >= m_dwVBSize)
						m_dwVBOffset = 0;

					m_pVB->Lock(
						m_dwVBOffset * sizeof(Particle),
						m_dwVBBatchSize * sizeof(Particle),
						(void**)&v,
						m_dwVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0; // 다음 단계를 위한 리셋
				}//end if
			}//end if
		}//end for
		m_pVB->Unlock();

		//(numParticlesInBatch == m_dwVBBatchSize) 조건이 만족되지 못하여
		// 마지막 단계가 렌더링되지 않는 경우가 발생할 수 있다. 일부만 채워진 단계는
		// 바로 이곳에서 렌더링된다.

		if(numParticlesInBatch){
			m_pDevice->DrawPrimitive(
				D3DPT_POINTLIST,
				m_dwVBOffset,
				numParticlesInBatch);
		}

		D3DXMatrixIdentity(&mtMatrix);
		m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

		// 다음 블록
		m_dwVBOffset += m_dwVBBatchSize;
		postRender();
	} // end if
} // end render()