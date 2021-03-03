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

// �̹����� �ҷ����� ��ġ �������̽��� ��������Ʈ �������̽��� �����Ѵ�.
bool CLineEntity::InitObject(IDirect3DDevice9* _pDevice, float _fAlpha){
	m_pDevice = _pDevice;

	m_Mtrl = DU::WHITE_MTRL;
	m_Mtrl.Diffuse.a = _fAlpha;

	// �ؽ�ó �����͸� �ε��Ѵ�
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

	//// �߽�
	//m_vCenter /= (float)GetPointNum();

	//CreateVertices();
}

void CLineEntity::CreateVertices(){
	// ���ؽ� ���� ����
	m_pDevice->CreateVertexBuffer(	(3 + (GetPointNum()-3)*3) * sizeof(Vertex),
																D3DUSAGE_WRITEONLY,
																Vertex::FVF,
																D3DPOOL_MANAGED,
																&m_pQuad,
																0);

	// �ε��� ���� ����
	m_pDevice->CreateIndexBuffer((3 + (GetPointNum()-3)*3) * sizeof(WORD),
																D3DUSAGE_WRITEONLY,
																D3DFMT_INDEX16,
																D3DPOOL_MANAGED,
																&m_pIndex,
																0);

	// �� ���� �ﰢ������ ������ �簢��,
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

	// �ﰢ�� ����
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

// ���۵� 
void CLineEntity::ResizeVertex(float _fWidth, float _fHeight){
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

	for(int i = 0; i < GetPointNum(); ++i){
		v[i] = Vertex((float)m_Points.at(i).x * _fWidth, (float)m_Points.at(i).y * _fHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	}

	m_pQuad->Unlock();	
}

// �������� �ռ� �����ؾ� �� �ʱ� ���� ���¸� �����Ѵ�.
void CLineEntity::preRender(){
	// ZBuffer ���� ����
	m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, true);

	m_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// ����ä��1 = ���ݻ� �÷��� ���� ����
	// ����ä��2 = Texture �÷��� ���� ����
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	// �� ����ä���� ���Ͽ� �����Ͽ� ���� ����� ����
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	

	// ���� �μ��� �����Ͽ� ���� ������ ������ �����ϵ��� ��
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

// ������Ʈ�� �׸���.
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

//	m_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	// 2���� �ؽ�ó ���
//	m_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION );	/// ī�޶� ��ǥ�� ��ȯ

	// ������ �ؽ�ó�� Ȱ��ȭ�Ѵ�.
	m_pDevice->SetMaterial(&m_Mtrl);
	m_pDevice->SetTexture(0, m_pTexture);

	m_pDevice->SetStreamSource(0, m_pQuad, 0, sizeof(Vertex));

	// Ȱ��ȭ�� �ؽ�ó�� �̿��� �⺻���� �׸���.
	//m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);	
	m_pDevice->SetIndices(m_pIndex);

	unsigned int t_Vertices = (3 + ((GetPointNum()-3)*3));
	unsigned int t_nPrimCount = (GetPointNum()-2);

	m_pDevice->SetFVF(Vertex::FVF);

	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, t_Vertices, 0, t_nPrimCount);

	// ���� ��ǥ�� �������� �ǵ�����.
	D3DXMatrixIdentity(&mtMatrix);
	m_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

	postRender();
}

// Ư�� Ŭ������ �������� �� �ִ� ���� ���¸� �����ϴ� �� �̿�ȴ�.
void CLineEntity::postRender(){
	// ZBuffer ���� ����
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