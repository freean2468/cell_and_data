#include "Box3D.h"
#include "../Engine_System/EngineManager.h"
#include "../Engine_System/CameraManager.h"

CBox3D::CBox3D(Vector2D _vTL, Vector2D _BR) : m_vTopLeft(_vTL),
											m_vBottomRight(_BR),
											m_vCenter((_vTL+_BR)/2.0),
											m_vTopLeftTF(Vector2D(0,0)),
											m_vBottomRightTF(Vector2D(0,0)),
											m_vCenterTF(Vector2D(0,0)),
											m_bLineState(true)
{
	m_fLineWeight = (float)(::RandFloat())+3.0f;
	m_fBlinkingFrequency = (float)(::RandFloat())*0.05f;
}

CBox3D::~CBox3D(){

}

void CBox3D::Update(){
//	m_vTopLeftTF = DU::TransformCoSystemWinToDX2D(&m_vTopLeft);
//	m_vBottomRightTF = DU::TransformCoSystemWinToDX2D(&m_vBottomRight);
//	m_vCenterTF = DU::TransformCoSystemWinToDX2D(&m_vCenter);

	if(m_bLineState){		
		m_fLineWeight+=m_fBlinkingFrequency;	
	}
	else{
		m_fLineWeight-=m_fBlinkingFrequency;	
	}

	if(m_fLineWeight > 5.0f){	
		m_bLineState = false;
	}
	else if(m_fLineWeight < 1.0f){ 
		m_bLineState = true;
	}
}

void CBox3D::Render(D3DXCOLOR* p_pColor, bool RenderCenter)const{
	D3DXVECTOR3 p[3];

	EngineMgr->LineRenderBegin();

	p[0].x = (float)Left();			p[0].y = (float)Top();		p[0].z = 0.0f;
	p[1].x = (float)Right();		p[1].y = (float)Top();		p[1].z = 0.0f;
	p[2].x = (float)Left();			p[2].y = (float)Bottom(); p[2].z = 0.0f;

	EngineMgr->GetLine()->DrawTransform(p, 3, &(*EngineMgr->GetWorldMat() * *EngineMgr->GetViewMat() * *EngineMgr->GetProjMat()), *p_pColor);

	p[0].x = (float)Left();			p[0].y = (float)Bottom(); p[0].z = 0.0f;
	p[1].x = (float)Right();		p[1].y = (float)Bottom(); p[1].z = 0.0f;
	p[2].x = (float)Right();		p[2].y = (float)Top();		p[2].z = 0.0f;

	EngineMgr->GetLine()->DrawTransform(p, 3, &(*EngineMgr->GetWorldMat() * *EngineMgr->GetViewMat() * *EngineMgr->GetProjMat()), *p_pColor);

	p[0].x = (float)Left();			p[0].y = (float)Top();		p[0].z = 0.0f;
	p[1].x = (float)Left();			p[1].y = (float)Bottom();	p[1].z = 0.0f;
	p[2].x = (float)Right();		p[2].y = (float)Bottom(); p[2].z = 0.0f;

	EngineMgr->GetLine()->DrawTransform(p, 3, &(*EngineMgr->GetWorldMat() * *EngineMgr->GetViewMat() * *EngineMgr->GetProjMat()), *p_pColor);

	p[0].x = (float)Right();		p[0].y = (float)Top();		p[0].z = 0.0f;
	p[1].x = (float)Right();		p[1].y = (float)Bottom();	p[1].z = 0.0f;
	p[2].x = (float)Left();			p[2].y = (float)Top();		p[2].z = 0.0f;

	EngineMgr->GetLine()->DrawTransform(p, 3, &(*EngineMgr->GetWorldMat() * *EngineMgr->GetViewMat() * *EngineMgr->GetProjMat()), *p_pColor);

	EngineMgr->LineRenderEnd();
}

void CBox3D::Render(ID3DXLine* p_pLine, D3DXCOLOR* p_pColor, bool RenderCenter)const{
	D3DXVECTOR3 p[3];

	// 월드 행렬
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	// 뷰 행렬 설정
	D3DXMATRIX matView;
	
	CameraMgr->GetCamera()->GetViewMatrix(&matView);
	
	// 프로젝션 행렬 설정
	D3DXMATRIX Proj;
	D3DXMatrixPerspectiveFovLH(
			&Proj,
			D3DX_PI / 4.0f, // 45 - degree
			(float)(SYSTEMWIDTH)/(float)(SYSTEMHEIGHT),
			1.0f,
			1000.0f);

	if(!EngineMgr->IsViewOut(&D3DXVECTOR3(static_cast<float>(Left()), static_cast<float>(Top()), 0.0f))
		|| !EngineMgr->IsViewOut(&D3DXVECTOR3(static_cast<float>(Right()), static_cast<float>(Bottom()), 0.0f))
		|| !EngineMgr->IsViewOut(&D3DXVECTOR3(static_cast<float>(Left()), static_cast<float>(Bottom()), 0.0f))
		|| !EngineMgr->IsViewOut(&D3DXVECTOR3(static_cast<float>(Right()), static_cast<float>(Top()), 0.0f)))
	{
		p[0].x = (float)Left();			p[0].y = (float)Top();		p[0].z = 0.0f;
		p[1].x = (float)Right();		p[1].y = (float)Top();		p[1].z = 0.0f;
		p[2].x = (float)Left();			p[2].y = (float)Bottom(); p[2].z = 0.0f;

		p_pLine->DrawTransform(p, 3, &(*EngineMgr->GetWorldMat() * *EngineMgr->GetViewMat() * *EngineMgr->GetProjMat()), *p_pColor);

		p[0].x = (float)Left();			p[0].y = (float)Bottom(); p[0].z = 0.0f;
		p[1].x = (float)Right();		p[1].y = (float)Bottom(); p[1].z = 0.0f;
		p[2].x = (float)Right();		p[2].y = (float)Top();		p[2].z = 0.0f;

		p_pLine->DrawTransform(p, 3, &(*EngineMgr->GetWorldMat() * *EngineMgr->GetViewMat() * *EngineMgr->GetProjMat()), *p_pColor);

		p[0].x = (float)Left();			p[0].y = (float)Top();		p[0].z = 0.0f;
		p[1].x = (float)Left();			p[1].y = (float)Bottom();	p[1].z = 0.0f;
		p[2].x = (float)Right();		p[2].y = (float)Bottom(); p[2].z = 0.0f;

		p_pLine->DrawTransform(p, 3, &(*EngineMgr->GetWorldMat() * *EngineMgr->GetViewMat() * *EngineMgr->GetProjMat()), *p_pColor);

		p[0].x = (float)Right();		p[0].y = (float)Top();		p[0].z = 0.0f;
		p[1].x = (float)Right();		p[1].y = (float)Bottom();	p[1].z = 0.0f;
		p[2].x = (float)Left();			p[2].y = (float)Top();		p[2].z = 0.0f;

		p_pLine->DrawTransform(p, 3, &(*EngineMgr->GetWorldMat() * *EngineMgr->GetViewMat() * *EngineMgr->GetProjMat()), *p_pColor);
	}
}

void	CBox3D::RenderCoordinateXY(Vector2D* p_pCo)const{
	D3DXVECTOR3 _vPos;			// 위치 벡터
	D3DXMATRIXA16 _pos;			// 위치 변환 행렬
	D3DXMATRIXA16 _rotation;	// 회전 변환 행렬

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&_pos, (float)p_pCo->x + 35.0f, (float)p_pCo->y+15.0f, 0.0f);

	D3DXMATRIXA16 rX;
	D3DXMatrixIdentity(&rX);
	D3DXMatrixRotationX(&rX, D3DX_PI);

	_rotation = rX;

	mtMatrix = mtMatrix * _rotation * _pos;

	EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

	RECT rect;

	rect.right = (long)(+100.0f);
	rect.left = (long)(-100.0f);
	rect.top = (long)(-100.0f);
	rect.bottom = (long)(+100.0f);

	char t_Co[16];	char t_X[8];	char t_Y[8];

	::_itoa_s((int)p_pCo->x, t_X, 8,10);
	::_itoa_s((int)p_pCo->y, t_Y, 8,10);

	strcat_s(t_X, 1, ",");
	strcpy_s(t_Co,8, t_X);
	strcat_s(t_Co,8, t_Y);

	t_Co[15] = '\0';

	// Text 출력
	EngineMgr->GetFontForCoSystem()->DrawText(EngineMgr->GetpSprite(), t_Co, -1, &rect, DT_CENTER | DT_VCENTER | DT_WORDBREAK , D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f));     
}

void CBox3D::RenderCoordinateXY(D3DXVECTOR2* p_pCo)const{
	D3DXVECTOR3 _vPos;			// 위치 벡터
	D3DXMATRIXA16 _pos;			// 위치 변환 행렬
	D3DXMATRIXA16 _rotation;	// 회전 변환 행렬

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&_pos, p_pCo->x + 35.0f, p_pCo->y+15.0f, 0.0f);

	D3DXMATRIXA16 rX;
	D3DXMatrixIdentity(&rX);
	D3DXMatrixRotationX(&rX, D3DX_PI);

	_rotation = rX;

	mtMatrix = mtMatrix * _rotation * _pos;

	EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

	RECT rect;

	rect.right = (long)(+100.0f);
	rect.left = (long)(-100.0f);
	rect.top = (long)(-100.0f);
	rect.bottom = (long)(+100.0f);

	char t_Co[16];	char t_X[8];	char t_Y[8];

	::_itoa_s((int)p_pCo->x, t_X, 8,10);
	::_itoa_s((int)p_pCo->y, t_Y, 8,10);

	strcat_s(t_X, 1, ",");
	strcpy_s(t_Co,8, t_X);
	strcat_s(t_Co,8, t_Y);

	t_Co[15] = '\0';

	// Text 출력
	EngineMgr->GetFontForCoSystem()->DrawText(EngineMgr->GetpSprite(), t_Co, -1, &rect, DT_CENTER | DT_VCENTER | DT_WORDBREAK , D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f));
}