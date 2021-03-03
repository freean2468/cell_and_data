#include "LineEntity.h"
#include "../Engine_Misc/DirectUtils.h"
#include "EngineManager.h"

CLineEntity::CLineEntity(int _nEntityType):CDirectXEntity(-1),
										m_vCenter(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
										m_nPointNum(0)
{
	D3DXMatrixIdentity(&m_mWorld);

	m_Mtrl.Ambient = DU::WHITE;
	m_Mtrl.Diffuse = DU::WHITE;
	m_Mtrl.Specular = DU::WHITE;
	m_Mtrl.Emissive = DU::WHITE;
	m_Mtrl.Power = 5.0f;
}

CLineEntity::~CLineEntity(){
	
}

// 이미지를 불러오며 장치 인터페이스와 스프라이트 인터페이스를 적재한다.
bool CLineEntity::InitObject(IDirect3DDevice9* _pDevice, float _fAlpha){
	m_pDevice = _pDevice;

	m_Mtrl = DU::WHITE_MTRL;
	m_Mtrl.Diffuse.a = _fAlpha;

	// 텍스처 데이터를 로드한다
	D3DXCreateTextureFromFileEx(m_pDevice, "./Image/Empty/Empty.dds",	D3DPOOL_DEFAULT, 
		D3DPOOL_DEFAULT, 1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, 
		D3DX_DEFAULT,	NULL, NULL, NULL, &m_pTexture);

	return true;
}

void CLineEntity::CreatePointsOnRandInRange(int _nBegin, int _nEnd){
	//SetPointNum(::RandInt(_nBegin, _nEnd));

	//double t_dMinLength = 10;
	//double t_dMaxLength = 50;

	//Vector2D t_vPoint(0, 0);
	//Vector2D t_vFacing(RandInRange(-1, 1), 2);
	//Vector2D t_vNextPoint;

	//double t_dDegree = 0;

	//t_vFacing.Normalize();

	//do{
	//	CMatrix4X4 t_mTransform;

	//	if(GetPoints()->size() == 0){
	//		t_vPoint.x -= ::RandInRange(t_dMinLength/2, t_dMinLength);
	//		GetPoints()->push_back(t_vPoint);
	//	}
	//	else if(GetPoints()->size() == GetPointNum()-1){
	//		t_vPoint.x += ::RandInRange(t_dMinLength/2, t_dMinLength);
	//		GetPoints()->push_back(t_vPoint);
	//	}
	//	else{
	//		if(GetPointNum() == 4){
	//			if(GetPoints()->size() == 2){
	//				t_vPoint = t_vFacing * t_dMinLength;
	//			}
	//			else{
	//				t_vPoint = t_vFacing * ::RandInRange(t_dMaxLength-5, t_dMaxLength+5);
	//			}
	//		}
	//		else if(GetPointNum() == 5){
	//			if(GetPoints()->size() == 3 || GetPoints()->size() == 2){
	//				t_vPoint = t_vFacing * t_dMinLength;
	//			}
	//			else{
	//				t_vPoint = t_vFacing * ::RandInRange(t_dMaxLength-5, t_dMaxLength+5);
	//			}
	//		}

	//		t_vNextPoint = Vector2D(RandInRange(-1, 1), RandInRange(2, 5));
	//		t_vNextPoint.Normalize();

	//		for(std::vector<Vector2D>::size_type i = 0; i < GetPoints()->size(); ++i){
	//			t_mTransform.Translate(GetPoints()->at(i));
	//		}

	//		double angle = acos(t_vFacing.Dot(t_vNextPoint));

	//		//rotate
	//		t_mTransform.RotateZ(angle);
	//		t_mTransform.Translate(t_vPoint);
	//		t_mTransform.TransformVector2Ds(t_vNextPoint);

	//		GetPoints()->push_back(t_vNextPoint);
	//		
	//		t_vFacing = Vector2D(RandInRange(-1, 1), 5);
	//		t_vFacing.Normalize();
	//	}

	//	t_vPoint = Vector2D(0,0);
	//}while(GetPointNum() != GetPoints()->size());

	//for(int i = 0; i < GetPointNum(); ++i){
	//	m_vCenter.x += (float)GetPoints()->at(i).x;
	//	m_vCenter.y += (float)GetPoints()->at(i).y;
	//}

	//// 중심
	//m_vCenter /= (float)GetPointNum();

	//CreateVertices();
}

void CLineEntity::CreateVertices(){
	// 버텍스 버퍼 생성
	m_pDevice->CreateVertexBuffer(	(3 + (GetPointNum()-3)*3) * sizeof(Vertex),
																D3DUSAGE_WRITEONLY,
																Vertex::FVF,
																D3DPOOL_MANAGED,
																&m_pQuad,
																0);

	// 인덱스 버퍼 생성
	m_pDevice->CreateIndexBuffer((3 + (GetPointNum()-3)*3) * sizeof(WORD),
																D3DUSAGE_WRITEONLY,
																D3DFMT_INDEX16,
																D3DPOOL_MANAGED,
																&m_pIndex,
																0);

	// 두 개의 삼각형으로 구성된 사각형,
	Vertex* v = 0;

	m_pQuad->Lock(0, 0, (void**)&v, 0);

	int t_nIndex = 0;
	int i;
	int j;

	for(i = 0; i < GetPointNum() - 3 + 1; ++i){
		for(j = t_nIndex; j < t_nIndex+3; ++j){
			if(j >= GetPointNum()){				
				if(GetPointNum() % 2 == 0){
					v[j+i] = Vertex((float)m_Points.at(0).x, (float)m_Points.at(0).y, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
					break;
				}
				else{
					v[j+i] = Vertex((float)m_Points.at(0).x, (float)m_Points.at(0).y, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
					v[j+i+1] = Vertex((float)m_Points.at(m_Points.size()/2).x, (float)m_Points.at(m_Points.size()/2).y, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
					break;
				}
			}
			else{
				v[j+i] = Vertex((float)m_Points.at(j).x, (float)m_Points.at(j).y, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
			}
		}
		t_nIndex+=2;
	}

	m_pQuad->Unlock();	

	// 삼각형 정의
	WORD* indices = 0;
	m_pIndex->Lock(0, 0, (void**)&indices, D3DLOCK_DISCARD | D3DLOCK_NOOVERWRITE);

	for(int i = 0; i < (3 + ((GetPointNum()-3)*3)); ++i)
		indices[i] = i;

	m_pIndex->Unlock();
}

void CLineEntity::ResizeObject(float _fVal){
	ResizeObject(_fVal, _fVal);
}

void CLineEntity::ResizeObject(float _fWidth, float _fHeight){
	ResizeVertex(_fWidth, _fHeight);
}

// 오작동 
void CLineEntity::ResizeVertex(float _fWidth, float _fHeight){
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

	for(int i = 0; i < GetPointNum(); ++i){
		v[i] = Vertex((float)m_Points.at(i).x * _fWidth, (float)m_Points.at(i).y * _fHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	}

	m_pQuad->Unlock();	
}

// 렌더링에 앞서 지정해야 할 초기 렌더 상태를 지정한다.
void CLineEntity::preRender(){
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
void CLineEntity::Render(){
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

	// 재질과 텍스처를 활성화한다.
	m_pDevice->SetMaterial(&m_Mtrl);
	m_pDevice->SetTexture(0, m_pTexture);

	m_pDevice->SetStreamSource(0, m_pQuad, 0, sizeof(Vertex));

	// 활성화된 텍스처를 이용해 기본형을 그린다.
	//m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);	
	m_pDevice->SetIndices(m_pIndex);

	unsigned int t_Vertices = (3 + ((GetPointNum()-3)*3));
	unsigned int t_nPrimCount = (GetPointNum()-2);

	m_pDevice->SetFVF(Vertex::FVF);

	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, t_Vertices, 0, t_nPrimCount);

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

	postRender();
}

// 특정 클래스가 지정했을 수 있는 렌더 상태를 복구하는 데 이용된다.
void CLineEntity::postRender(){
	// ZBuffer 연산 켜줌
	m_pDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CLineEntity::RenderLine(ID3DXLine* p_pLine, D3DXCOLOR* p_pColor){
	D3DXVECTOR3 p[3];

	for(int i = 0; i < GetPointNum()-1; ++i){
		p[0].x = (float)GetPoints()->at(i).x + m_vPos.x;			p[0].y = (float)GetPoints()->at(i).y + m_vPos.y ;			p[0].z = 0.0f;
		p[1].x = (float)GetPoints()->at(i+1).x + m_vPos.x;		p[1].y = (float)GetPoints()->at(i+1).y + m_vPos.y;		p[1].z = 0.0f;
		p[2].x = (float)GetPoints()->at(i).x  + m_vPos.x;		p[2].y = (float)GetPoints()->at(i).y + m_vPos.y;			p[2].z = 0.0f;

		p_pLine->DrawTransform(p, 3, &(*EngineMgr->GetWorldMat() * *EngineMgr->GetViewMat() * *EngineMgr->GetProjMat()), *p_pColor);
	}
}

D3DXMATRIX CLineEntity::CalMatWorld(){
	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&m_mPos, m_vPos.x, m_vPos.y, m_vPos.z);

	D3DXMATRIXA16 rX, rY, rZ;
	D3DXMatrixRotationZ(&rX, m_vRot.z);
	D3DXMatrixRotationY(&rY, m_vRot.y);
	D3DXMatrixRotationX(&rZ, m_vRot.x);

	m_mRotation = rX*rY*rZ;

	D3DXMatrixScaling(&m_mScale, m_vSca.x, m_vSca.y, m_vSca.z);
	mtMatrix = mtMatrix * m_mScale * m_mPos * m_mRotation;
	m_mWorld = mtMatrix;

	return m_mWorld;
}