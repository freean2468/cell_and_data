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

	// ���ؽ� ���� ����
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

	// �ؽ��� �̹����� �������� �������� �Ѵٰ� ����
	if(_eDirection == RIGHT){
		this->GetRot3D()->y = 0.0f;
	}
	else{
		this->GetRot3D()->y = D3DX_PI;
	}		
}

// ����� �ִϸ��̼��� �ʿ� ����.
// ���� �ʿ��� ���� ���⿡ ���� ĳ���� ȸ��
//// �ִϸ��̼� �Լ�
//void CBasicEntity::Animation(){
//	// ������ Ÿ���� 0�� �ƴ϶��
//	if(m_Timer.IsValidTimer()){
//		// ������ Ÿ���� �� �����ٸ�
//		if(m_Timer.IsElapseTimer()){
//			// ���� ����������
//			m_nCol+=1;
//			// ���� �������� ���ٸ� �ٽ� ó������
//			if(m_pTexture.GetSize() <= (m_nCol * m_pTexture.GetHeight())){
//				m_nCol = 0;
//			}
//			// ������ Ÿ�� �ٽ� �ʱ�ȭ
//			m_Timer.InitTimer(m_dwDelaytime);
//		}
//	}
//}