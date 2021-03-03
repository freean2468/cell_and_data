#include "BasicEntity.h"
#include "../Engine_Misc/DirectUtils.h"

CBasicEntity::CBasicEntity(int _nEntityType):CDirectXEntity(_nEntityType),																					
											m_dwDelaytime(0),
											m_eDirection(RIGHT),
											m_nCol(CBasicEntity::RIGHT),
											m_nRow(CBasicEntity::RIGHT)
{
	D3DXMatrixIdentity(&m_mWorld);
}

CBasicEntity::~CBasicEntity(){
	
}

void CBasicEntity::ResizeObject(float _fVal){
	ResizeObject(_fVal, _fVal);
}

void CBasicEntity::ResizeObject(float _fWidth, float _fHeight){
	SetRadius(GetRadius() * ((_fWidth + _fHeight) * 0.5f));

	ResizeVertex(GetWidth() * _fWidth, GetHeight() * _fHeight);
}

void CBasicEntity::ResizeVertex(float _fWidth, float _fHeight){
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

void	CBasicEntity::SetDirection(DIRECTION _eDirection){
	m_eDirection = _eDirection;

	// 텍스쳐 이미지가 오른쪽을 기준으로 한다고 가정
	if(_eDirection == RIGHT){
		this->GetRot3D()->y = 0.0f;
	}
	else{
		this->GetRot3D()->y = D3DX_PI;
	}		
}

// 현재는 애니메이션이 필요 없다.
// 현재 필요한 것은 방향에 따른 캐릭터 회전
//// 애니메이션 함수
//void CBasicEntity::Animation(){
//	// 딜레이 타임이 0이 아니라면
//	if(m_Timer.IsValidTimer()){
//		// 딜레이 타임이 다 지났다면
//		if(m_Timer.IsElapseTimer()){
//			// 다음 프레임으로
//			m_nCol+=1;
//			// 다음 프레임이 없다면 다시 처음으로
//			if(m_pTexture.GetSize() <= (m_nCol * m_pTexture.GetHeight())){
//				m_nCol = 0;
//			}
//			// 딜레이 타임 다시 초기화
//			m_Timer.InitTimer(m_dwDelaytime);
//		}
//	}
//}