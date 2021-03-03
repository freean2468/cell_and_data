#include "DirectUtils.h"
#include "../Engine_System/EngineManager.h"
#include "../Engine_System/CameraManager.h"

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

float DU::CalAngleConsiderTexture(Vector2D _vPos){
	Vector2D O(0, 1);
	
	_vPos.Normalize();
	O.Normalize();

	double angle = acos(_vPos.Dot(O));

	// x가 양수 방향을 가리키면 회전 각도를 음수로 바꿔줘야 한다.
	if(_vPos.x > 0)
		angle *= -1;

	return (float)angle;
}

float DU::CalAngleConsiderTexture(D3DXVECTOR3 _vPos){
	Vector2D t_vPos((double)_vPos.x, (double)_vPos.y);
	Vector2D O(0, 1);
	
	t_vPos.Normalize();
	O.Normalize();

	double angle = acos(t_vPos.Dot(O));

	// x가 양수 방향을 가리키면 회전 각도를 음수로 바꿔줘야 한다.
	if(t_vPos.x > 0)
		angle *= -1;

	return (float)angle;
}

void DU::SetupMatrices(){
	// 월드 행렬	
	EngineMgr->GetpDevice()->SetTransform(D3DTS_WORLD, EngineMgr->GetWorldMat());

	// 뷰 행렬 설정
	EngineMgr->GetpDevice()->SetTransform(D3DTS_VIEW, EngineMgr->GetViewMat());

	// 프로젝션 행렬 설정
	EngineMgr->GetpDevice()->SetTransform(D3DTS_PROJECTION, EngineMgr->GetProjMat());
}

void DU::SetFontScale(ID3DXFont* _pFont, int _nScale){
	switch(_nScale){
		case 1: DU::IniFont(_pFont, 4, 2, 200, false, "맑은 고딕"); break;
		case 2: DU::IniFont(_pFont, 6, 3, 200, false, "맑은 고딕"); break;
		case 3: DU::IniFont(_pFont, 8, 4, 200, false, "맑은 고딕"); break;
		case 4: DU::IniFont(_pFont, 10, 5, 300, false, "맑은 고딕"); break;
		case 6: DU::IniFont(_pFont, 14, 7, 300, false, "맑은 고딕"); break;
		case 7: DU::IniFont(_pFont, 16, 8, 400, false, "맑은 고딕"); break;
		case 8: DU::IniFont(_pFont, 18, 9, 400, false, "맑은 고딕"); break;
		case 9: DU::IniFont(_pFont, 20, 10, 400, false, "맑은 고딕"); break;
		case 5:
		default:
			DU::IniFont(_pFont, 13, 6, 300, false, "맑은 고딕"); break;
	}
}

void DU::RenderBG(){

}	

void DU::RenderMirror(){
	
}

void DU::RenderShadow(){
	
}

void DU::RenderBoundingVolume(){
	////
	//// Draw bounding volume in blue and at 10% opacity
	//D3DMATERIAL9 blue = DU::BLUE_MTRL;
	//blue.Diffuse.a = 0.10f; // 10% opacity

	//AppMgr->GetpDevice()->SetMaterial(&blue);
	//AppMgr->GetpDevice()->SetTexture(0, 0); // disable texture

	//AppMgr->GetpDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//AppMgr->GetpDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//AppMgr->GetpDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//if( AppMgr->RenderBoundingSphere )
	//	AppMgr->SphereMesh->DrawSubset(0);
	//else
	//	AppMgr->BoxMesh->DrawSubset(0);

	//AppMgr->GetpDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

// 경계 구체 충돌 계산
bool DU::ComputeBoundingSphere(ID3DXMesh* mesh,			// 경계 구체 충돌을 계산할 메쉬와 경계 구체
						   DU::BoundingSphere* sphere){	
	HRESULT hr = 0;
							   
	BYTE* v = 0;
	mesh->LockVertexBuffer(0, (void**)&v);

	hr = D3DXComputeBoundingSphere(
		(D3DXVECTOR3*)v,
		mesh->GetNumVertices(),
		D3DXGetFVFVertexSize(mesh->GetFVF()),
		&sphere->_center,
		&sphere->_radius);

	mesh->UnlockVertexBuffer();

	if(FAILED(hr))
		return false;
	return true;
}

// 경계 상자 충돌 계산
bool DU::ComputeBoundingBox(ID3DXMesh* mesh,   // 경계 상자 충돌을 계산할 메쉬와 경계 상자
						DU::BoundingBox* box){
	HRESULT hr = 0;

	BYTE* v = 0;
	mesh->LockVertexBuffer(0, (void**)&v);

	hr = D3DXComputeBoundingBox(
		(D3DXVECTOR3*)v,
		mesh->GetNumVertices(),
		D3DXGetFVFVertexSize(mesh->GetFVF()),
		&box->_min,
		&box->_max);

	mesh->UnlockVertexBuffer();

	if(FAILED(hr))
		return false;

	return true;
}


// 재질 초기화
D3DMATERIAL9 DU::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p){
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = a;
	mtrl.Diffuse = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power = p;
	return mtrl;
}


// 방향성 광원 초기화
D3DLIGHT9 DU::InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color){
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = *color * 0.4f;
	light.Diffuse = *color;
	light.Specular = *color * 0.6f;
	light.Direction = *direction;

	return light;
}

// 점 광원 초기화
D3DLIGHT9 DU::InitPointLight(D3DXVECTOR3* _pvPos, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_POINT;
	light.Ambient   = *color * 0.6f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *_pvPos;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;

	return light;
}

// 스포트 광원 초기화
D3DLIGHT9 DU::InitSpotLight(D3DXVECTOR3* _pvPos, D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_SPOT;
	light.Ambient   = *color * 0.0f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *_pvPos;
	light.Direction = *direction;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;
	light.Theta        = 0.4f;
	light.Phi          = 0.9f;

	return light;
}

// 폰트 초기화
ID3DXFont* DU::IniFont(int wid, int hei, int wei, bool ital, char* style){	
	D3DXFONT_DESC lf;

	ZeroMemory(&lf, sizeof(D3DXFONT_DESC));
	lf.Height			= wid;		// 논리적 단위
	lf.Width			= hei;		// 논리적 단위
	lf.Weight			= wei;		// 굵기의 단위, 범위 0(얇음) - 1000(두꺼움)
	lf.Italic			= ital;
	lf.CharSet		= DEFAULT_CHARSET;
	::strcpy_s(lf.FaceName, 32, style);	// 글꼴 스타일
	
	ID3DXFont* font;
	if(FAILED(D3DXCreateFontIndirect(EngineMgr->GetpDevice(), &lf, &font))){
		OutputDebugString("D3DXCreateFontIndirect() - FAILED");
		::PostQuitMessage(0);
	}
	return font;
}

void DU::IniFont(ID3DXFont* _pFont, int wid, int hei, int wei, bool ital, char* style){
	D3DXFONT_DESC lf;

	ZeroMemory(&lf, sizeof(D3DXFONT_DESC));
	lf.Height			= wid;		// 논리적 단위
	lf.Width			= hei;		// 논리적 단위
	lf.Weight			= wei;		// 굵기의 단위, 범위 0(얇음) - 1000(두꺼움)
	lf.Italic			= ital;
	lf.CharSet		= DEFAULT_CHARSET;
	::strcpy_s(lf.FaceName, sizeof(lf.FaceName), style);	// 글꼴 스타일

	if(FAILED(D3DXCreateFontIndirect(EngineMgr->GetpDevice(), &lf, &_pFont))){
		OutputDebugString("D3DXCreateFontIndirect() - FAILED");
		::PostQuitMessage(0);
	}
}

DU::BoundingBox::BoundingBox(){
	// 무한대의 작은 경계 상자
	_min.x = DU::INFINITY;
	_min.y = DU::INFINITY;
	_min.z = DU::INFINITY;
	_max.x = -DU::INFINITY;
	_max.y = -DU::INFINITY;
	_max.z = -DU::INFINITY;
}

bool DU::BoundingBox::isPointInside(D3DXVECTOR3& p){
	//지정된 포인트가 경계 상자 내에 있는가?
	if(p.x >= _min.x && p.y >= _min.y && p.z >= _min.z &&
		p.x <= _max.x && p.y <= _max.y && p.z <= _max.z){
		return true;		
	}
	else{
		return false;
	}
}

DU::BoundingSphere::BoundingSphere(){
	_radius = 0.0f;
}

float DU::Lerp(float a, float b, float t){
	return a - (a*t) + (b*t);
}

// 랜덤 float를 생성
float DU::GetRandomFloat(float lowBound, float highBound){
	if(lowBound >= highBound)	// 잘못된 입력
		return lowBound;

	//[0,1] 범위의 임의 float를 얻는다.
	float f = (rand() % 10000) * 0.0001f;

	// [lowBound, highBound] 범위의 float을 리턴한다.
	return (f * (highBound - lowBound)) + lowBound;
}

// 랜덤 Vector를 생성
void DU::GetRandomVector(D3DXVECTOR3* out, D3DXVECTOR3* min, D3DXVECTOR3* max){
	out->x = GetRandomFloat(min->x, max->x);
	out->y = GetRandomFloat(min->y, max->y);
	out->z = GetRandomFloat(min->z, max->z);
}

// float를 dword로 형변환
DWORD DU::FtoDw(float f){
	return *((DWORD*)&f);
}

// 마우스 스크린 좌표를 3D 광선으로 변환
DU::Ray DU::CalcPickingRay(int x, int y){
	float px = 0.0f;
	float py = 0.0f;

	D3DVIEWPORT9 vp;
	EngineMgr->GetpDevice()->GetViewport(&vp);

	D3DXMATRIX proj;
	EngineMgr->GetpDevice()->GetTransform(D3DTS_PROJECTION, &proj);

	px = (((2.0f*x) / vp.Width) - 1.0f) / proj(0, 0);
	py = (((-2.0f*y) / vp.Height) + 1.0f) / proj(1, 1);

	DU::Ray ray;
	ray.m_vOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ray._direction = D3DXVECTOR3(px, py, 1.0f);

	return ray;
}

// 스크린 포인터 광선을 로컬 스페이스 or 월드 스페이스로 변환
void DU::TransformRay(DU::Ray* ray, D3DXMATRIX* T){
	// 광선의 원점을 변환한다. w = 1
	D3DXVec3TransformCoord(
		&ray->m_vOrigin,
		&ray->m_vOrigin,
		T);

	// 광선의 방향을 변환한다. w = 0
	D3DXVec3TransformNormal(
		&ray->_direction,
		&ray->_direction,
		T);

	// 방향을 정규화한다.
	D3DXVec3Normalize(&ray->_direction, &ray->_direction);
}

// 경계구체와 마우스 광선의 교차 확인 함수
bool DU::raySphereIntersectionTest(DU::Ray* ray, DU::BoundingSphere* sphere){
	if(sphere == 0)
		return false;

	D3DXVECTOR3 v = ray->m_vOrigin - sphere->_center;

	float b = 2.0f * D3DXVec3Dot(&ray->_direction, &v);
	float c = D3DXVec3Dot(&v, &v) - (sphere->_radius * sphere->_radius);

	// 판별식
	float discriminant = (b*b) - (4.0f * c);

	// 가상의 수에 대한 테스트
	if(discriminant<0.0f)
		return false;

	discriminant = sqrtf(discriminant);

	float s0 = (-b + discriminant) / 2.0f;
	float s1 = (-b - discriminant) / 2.0f;

	// 해가 >= 0일 경우 구체를 교차하는 것이다.
	if(s0 >= 0.0f || s1 >= 0.0f)
		return true;

	return false;
}

// 좌표 변환
D3DXVECTOR2 DU::TransformCoSystemWinToDX2D(float p_x, float p_y){
	D3DXVECTOR3 _vTemp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CameraMgr->GetCamera()->GetPosition(&_vTemp);

	return D3DXVECTOR2(((p_x)-(float)(SYSTEMWIDTH/2))-_vTemp.x, -((p_y)-(float)(SYSTEMHEIGHT/2))+_vTemp.y);
}

Vector2D DU::TransformCoSystemWinToDX2D(Vector2D* p_pV){
	D3DXVECTOR3 _vTemp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CameraMgr->GetCamera()->GetPosition(&_vTemp);

	return Vector2D(((p_pV->x)+(SYSTEMWIDTH/2))-_vTemp.x, (-(p_pV->y)+(SYSTEMHEIGHT/2))+_vTemp.y);
}

void DU::VBLineRender(const std::vector<Vector2D> &points, D3DXCOLOR* p_pColor){
	D3DXVECTOR2 p[2];
	Vector2D Points;

	EngineMgr->LineRenderBegin(); 
  
  for (unsigned int i=1; i<points.size(); ++i){
		Points = DU::TransformCoSystemWinToDX2D(&Vector2D(points[i-1].x, points[i-1].y));

		p[0].x = (float)Points.x;   p[0].y = (float)Points.y;

		Points = DU::TransformCoSystemWinToDX2D(&Vector2D(points[i].x, points[i].y));

		p[1].x = (float)Points.x;  p[1].y = (float)Points.y; 

		EngineMgr->GetLine()->Draw( p, 2, *p_pColor );
  }

	Points = DU::TransformCoSystemWinToDX2D(&Vector2D(points[0].x, points[0].y));

	p[0].x = (float)Points.x;   p[0].y = (float)Points.y;

	EngineMgr->GetLine()->Draw( p, 2, *p_pColor );

	EngineMgr->LineRenderEnd();
}