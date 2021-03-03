#include "DirectXEntity.h"
#include "../Engine_Misc/DirectUtils.h"
#include "EngineManager.h"

CDirectXEntity::CDirectXEntity(int _nEntityType):CBaseEntity(_nEntityType),
												m_pDevice(EngineMgr->GetpDevice()),
												m_pQuad(NULL),
												m_pIndex(NULL),
												m_vPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),		// 위치 벡터
												m_vSca(D3DXVECTOR3(1.0f, 1.0f, 1.0f)),	// 크기 벡터
												m_vRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),		// 회전 벡터
												m_vTransPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),		// 변환 벡터
												m_fWidth(0),
												m_fHeight(0),
												m_pTexture(NULL),
												m_Mtrl(DU::WHITE_MTRL),																									
												m_bAlphaState(true),
												m_bCycleRotY(true)
{
	D3DXMatrixIdentity(&m_mWorld);
}

CDirectXEntity::~CDirectXEntity(){
	Release<IDirect3DTexture9*>(m_pTexture);
	Release<IDirect3DVertexBuffer9*>(m_pQuad);
	Release<IDirect3DIndexBuffer9*>(m_pIndex);
}

// 이미지를 불러오며 장치 인터페이스와 스프라이트 인터페이스를 적재한다.
bool CDirectXEntity::InitObject(IDirect3DDevice9* _pDevice, const char* _pstrTexFileName, int _nWidth, int _nHeight, 
															float _fAlpha, int _nAction){
	m_pDevice = _pDevice;
	m_fWidth = (float)_nWidth;
	m_fHeight = (float)_nHeight;
	m_fWidthHalf = _nWidth/2.0f;
	m_fHeightHalf = _nHeight/2.0f;
	m_fRadius = (m_fWidthHalf + m_fHeightHalf) * 0.5f;

	// 800 : 1 카메라 비율
	// width : x 이미지 비율
	// = width / 800
//	float x;
//	float y;

	// 3D 카메라와 좌표계를 맞추기 위한 비율 연산
//	x = width/((float)SYSTEMHEIGHT-30);
//	y = height/((float)SYSTEMHEIGHT-30);

	float fHalfWidth = _nWidth * 0.5f;//x / (float)2;
	float fHalfHeight = _nHeight * 0.5f;//y / (float)2;

	// 버텍스 버퍼 생성
	m_pDevice->CreateVertexBuffer(
		6 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&m_pQuad,
		0);

	// 인덱스 버퍼 생성
	m_pDevice->CreateIndexBuffer(
		6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIndex,
		0);

	// 두 개의 삼각형으로 구성된 사각형,
	Vertex* v = 0;

	m_pQuad->Lock(0, 0, (void**)&v, 0);

	v[0] = Vertex(-fHalfWidth, -fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = Vertex(-fHalfWidth,  fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = Vertex( fHalfWidth,  fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[3] = Vertex(-fHalfWidth, -fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[4] = Vertex( fHalfWidth,  fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[5] = Vertex( fHalfWidth, -fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	m_pQuad->Unlock();	

	// 삼각형 정의
	WORD* indices = 0;
	m_pIndex->Lock(0, 0, (void**)&indices, 0);

	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 3; indices[4] = 4; indices[5] = 5;

	m_pIndex->Unlock();

	m_Mtrl = DU::WHITE_MTRL;
	m_Mtrl.Diffuse.a = _fAlpha;
	// 텍스처 데이터를 로드한다
	D3DXCreateTextureFromFileEx(m_pDevice, _pstrTexFileName,
		D3DPOOL_DEFAULT, D3DPOOL_DEFAULT, 1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
		NULL, NULL, NULL, &m_pTexture);
//	D3DXCreateTextureFromFile(m_pDevice, texFileName, &m_pTexture);

	return true;
}

void CDirectXEntity::TransformObject(){
	D3DXMATRIXA16 t_mTransform = CalMatWorld();

	m_vTransPos.x = t_mTransform._41;
	m_vTransPos.y = t_mTransform._42;
	m_vTransPos.z = t_mTransform._43;
}

void CDirectXEntity::ResizeObject(float _fVal){
	ResizeObject(_fVal, _fVal);
}

void CDirectXEntity::ResizeObject(float _fWidth, float _fHeight){
	SetRadius(GetRadius() * ((_fWidth + _fHeight) * 0.5f));

	ResizeVertex(GetWidth() * _fWidth, GetHeight() * _fHeight);
}

void CDirectXEntity::ResizeVertex(float _fWidth, float _fHeight){
	m_fWidth = _fWidth;
	m_fHeight = _fHeight;
	m_fWidthHalf = _fWidth/2.0f;
	m_fHeightHalf = _fHeight/2.0f;

	float fHalfWidth = _fWidth / 2.0f;//x / (float)2;
	float fHalfHeight = _fHeight / 2.0f;//y / (float)2;

	// 버텍스 버퍼 생성
	m_pDevice->CreateVertexBuffer(
		6 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&m_pQuad,
		0);

	Vertex* v = 0;

	m_pQuad->Lock(0, 0, (void**)&v, 0);

	v[0] = Vertex(-fHalfWidth, -fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = Vertex(-fHalfWidth,  fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = Vertex( fHalfWidth,  fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[3] = Vertex(-fHalfWidth, -fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[4] = Vertex( fHalfWidth,  fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[5] = Vertex( fHalfWidth, -fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	m_pQuad->Unlock();	
}

// 렌더링에 앞서 지정해야 할 초기 렌더 상태를 지정한다.
void CDirectXEntity::preRender(){
	// ZBuffer 연산 꺼줌
	m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, true);

	m_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// 알파채널1 = 난반사 컬러로 알파 지정
	// 알파채널2 = Texture 컬러로 알파 지정
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	// 두 알파채널을 곱하여 조정하여 최종 결과물 결정
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	

	// 블렌딩 인수를 지정하여 알파 성분이 투명도를 결정하도록 함
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

// 오브젝트를 그린다.
void CDirectXEntity::Render(){
	preRender();

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&m_mPos, m_vPos.x, m_vPos.y, m_vPos.z);

	D3DXMATRIXA16 rX, rY, rZ;
	D3DXMatrixRotationZ(&rX, m_vRot.z);
	D3DXMatrixRotationY(&rY, m_vRot.y);
	D3DXMatrixRotationX(&rZ, m_vRot.x);

	m_mRotation = rX*rY*rZ;

	D3DXMatrixScaling(&m_mScale, m_vSca.x, m_vSca.y, m_vSca.z);
	mtMatrix = mtMatrix * m_mRotation * m_mScale * m_mPos;
	m_mWorld = mtMatrix;

	m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

//	m_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	// 2차원 텍스처 사용
//	m_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION );	/// 카메라 좌표계 변환

	m_pDevice->SetFVF(Vertex::FVF);
	m_pDevice->SetStreamSource(0, m_pQuad, 0, sizeof(Vertex));

	// 재질과 텍스처를 활성화한다.
	m_pDevice->SetMaterial(&m_Mtrl);
	m_pDevice->SetTexture(0, m_pTexture);

	// 활성화된 텍스처를 이용해 기본형을 그린다.
	//m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);	
	m_pDevice->SetIndices(m_pIndex);
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

	postRender();
}

// 특정 클래스가 지정했을 수 있는 렌더 상태를 복구하는 데 이용된다.
void CDirectXEntity::postRender(){
	// ZBuffer 연산 켜줌
	m_pDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

D3DXMATRIX CDirectXEntity::CalMatWorld(){
	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&m_mPos, m_vPos.x, m_vPos.y, m_vPos.z);

	D3DXMATRIXA16 rX, rY, rZ;
	D3DXMatrixRotationZ(&rX, m_vRot.z);
	D3DXMatrixRotationY(&rY, m_vRot.y);
	D3DXMatrixRotationX(&rZ, m_vRot.x);

	m_mRotation = rX*rY*rZ;

	D3DXMatrixScaling(&m_mScale, m_vSca.x, m_vSca.y, m_vSca.z);
	mtMatrix = mtMatrix * m_mRotation * m_mScale * m_mPos;
	m_mWorld = mtMatrix;

	return m_mWorld;
}

void CDirectXEntity::BlinkAlpha(float _fMin, float _fMax, float _fFrequency){
	switch(GetAlphaState()){
		case true:
			GetMtrl()->Diffuse.a += _fFrequency;

			if(GetMtrl()->Diffuse.a > _fMax){
				SetAlphaState(false);
			}
			break;
		case false:
			GetMtrl()->Diffuse.a -= _fFrequency;

			if(GetMtrl()->Diffuse.a < _fMin){
				SetAlphaState(true);
			}
			break;
	}
}

void CDirectXEntity::CycleRotX(float _fMax, float _fFrequency){
	if(m_bCycleRotX){
		m_vRot.x += _fFrequency;
		if(abs(m_vRot.x) > _fMax)	m_bCycleRotX = !m_bCycleRotX;
	}
	else{
		m_vRot.x -= _fFrequency;
		if(abs(m_vRot.x) > _fMax)	m_bCycleRotX = !m_bCycleRotX;
	}
}

void CDirectXEntity::CycleRotY(float _fMax, float _fFrequency){
	if(m_bCycleRotY){
		m_vRot.y += _fFrequency;
		if(abs(m_vRot.y) > _fMax)	m_bCycleRotY = !m_bCycleRotY;
	}
	else{
		m_vRot.y -= _fFrequency;
		if(abs(m_vRot.y) > _fMax)	m_bCycleRotY = !m_bCycleRotY;
	}
}

void CDirectXEntity::CycleRotZ(float _fMax, float _fFrequency){
	if(m_bCycleRotZ){
		m_vRot.z += _fFrequency;
		if(abs(m_vRot.z) > _fMax)	m_bCycleRotZ = !m_bCycleRotZ;
	}
	else{
		m_vRot.z -= _fFrequency;
		if(abs(m_vRot.z) > _fMax)	m_bCycleRotZ = !m_bCycleRotZ;
	}
}