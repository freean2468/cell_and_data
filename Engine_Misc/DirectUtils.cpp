#include "DirectUtils.h"
#include "../Engine_System/EngineManager.h"
#include "../Engine_System/CameraManager.h"

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

float DU::CalAngleConsiderTexture(Vector2D _vPos){
	Vector2D O(0, 1);
	
	_vPos.Normalize();
	O.Normalize();

	double angle = acos(_vPos.Dot(O));

	// x�� ��� ������ ����Ű�� ȸ�� ������ ������ �ٲ���� �Ѵ�.
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

	// x�� ��� ������ ����Ű�� ȸ�� ������ ������ �ٲ���� �Ѵ�.
	if(t_vPos.x > 0)
		angle *= -1;

	return (float)angle;
}

void DU::SetupMatrices(){
	// ���� ���	
	EngineMgr->GetpDevice()->SetTransform(D3DTS_WORLD, EngineMgr->GetWorldMat());

	// �� ��� ����
	EngineMgr->GetpDevice()->SetTransform(D3DTS_VIEW, EngineMgr->GetViewMat());

	// �������� ��� ����
	EngineMgr->GetpDevice()->SetTransform(D3DTS_PROJECTION, EngineMgr->GetProjMat());
}

void DU::SetFontScale(ID3DXFont* _pFont, int _nScale){
	switch(_nScale){
		case 1: DU::IniFont(_pFont, 4, 2, 200, false, "���� ���"); break;
		case 2: DU::IniFont(_pFont, 6, 3, 200, false, "���� ���"); break;
		case 3: DU::IniFont(_pFont, 8, 4, 200, false, "���� ���"); break;
		case 4: DU::IniFont(_pFont, 10, 5, 300, false, "���� ���"); break;
		case 6: DU::IniFont(_pFont, 14, 7, 300, false, "���� ���"); break;
		case 7: DU::IniFont(_pFont, 16, 8, 400, false, "���� ���"); break;
		case 8: DU::IniFont(_pFont, 18, 9, 400, false, "���� ���"); break;
		case 9: DU::IniFont(_pFont, 20, 10, 400, false, "���� ���"); break;
		case 5:
		default:
			DU::IniFont(_pFont, 13, 6, 300, false, "���� ���"); break;
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

// ��� ��ü �浹 ���
bool DU::ComputeBoundingSphere(ID3DXMesh* mesh,			// ��� ��ü �浹�� ����� �޽��� ��� ��ü
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

// ��� ���� �浹 ���
bool DU::ComputeBoundingBox(ID3DXMesh* mesh,   // ��� ���� �浹�� ����� �޽��� ��� ����
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


// ���� �ʱ�ȭ
D3DMATERIAL9 DU::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p){
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = a;
	mtrl.Diffuse = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power = p;
	return mtrl;
}


// ���⼺ ���� �ʱ�ȭ
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

// �� ���� �ʱ�ȭ
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

// ����Ʈ ���� �ʱ�ȭ
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

// ��Ʈ �ʱ�ȭ
ID3DXFont* DU::IniFont(int wid, int hei, int wei, bool ital, char* style){	
	D3DXFONT_DESC lf;

	ZeroMemory(&lf, sizeof(D3DXFONT_DESC));
	lf.Height			= wid;		// ���� ����
	lf.Width			= hei;		// ���� ����
	lf.Weight			= wei;		// ������ ����, ���� 0(����) - 1000(�β���)
	lf.Italic			= ital;
	lf.CharSet		= DEFAULT_CHARSET;
	::strcpy_s(lf.FaceName, 32, style);	// �۲� ��Ÿ��
	
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
	lf.Height			= wid;		// ���� ����
	lf.Width			= hei;		// ���� ����
	lf.Weight			= wei;		// ������ ����, ���� 0(����) - 1000(�β���)
	lf.Italic			= ital;
	lf.CharSet		= DEFAULT_CHARSET;
	::strcpy_s(lf.FaceName, sizeof(lf.FaceName), style);	// �۲� ��Ÿ��

	if(FAILED(D3DXCreateFontIndirect(EngineMgr->GetpDevice(), &lf, &_pFont))){
		OutputDebugString("D3DXCreateFontIndirect() - FAILED");
		::PostQuitMessage(0);
	}
}

DU::BoundingBox::BoundingBox(){
	// ���Ѵ��� ���� ��� ����
	_min.x = DU::INFINITY;
	_min.y = DU::INFINITY;
	_min.z = DU::INFINITY;
	_max.x = -DU::INFINITY;
	_max.y = -DU::INFINITY;
	_max.z = -DU::INFINITY;
}

bool DU::BoundingBox::isPointInside(D3DXVECTOR3& p){
	//������ ����Ʈ�� ��� ���� ���� �ִ°�?
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

// ���� float�� ����
float DU::GetRandomFloat(float lowBound, float highBound){
	if(lowBound >= highBound)	// �߸��� �Է�
		return lowBound;

	//[0,1] ������ ���� float�� ��´�.
	float f = (rand() % 10000) * 0.0001f;

	// [lowBound, highBound] ������ float�� �����Ѵ�.
	return (f * (highBound - lowBound)) + lowBound;
}

// ���� Vector�� ����
void DU::GetRandomVector(D3DXVECTOR3* out, D3DXVECTOR3* min, D3DXVECTOR3* max){
	out->x = GetRandomFloat(min->x, max->x);
	out->y = GetRandomFloat(min->y, max->y);
	out->z = GetRandomFloat(min->z, max->z);
}

// float�� dword�� ����ȯ
DWORD DU::FtoDw(float f){
	return *((DWORD*)&f);
}

// ���콺 ��ũ�� ��ǥ�� 3D �������� ��ȯ
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

// ��ũ�� ������ ������ ���� �����̽� or ���� �����̽��� ��ȯ
void DU::TransformRay(DU::Ray* ray, D3DXMATRIX* T){
	// ������ ������ ��ȯ�Ѵ�. w = 1
	D3DXVec3TransformCoord(
		&ray->m_vOrigin,
		&ray->m_vOrigin,
		T);

	// ������ ������ ��ȯ�Ѵ�. w = 0
	D3DXVec3TransformNormal(
		&ray->_direction,
		&ray->_direction,
		T);

	// ������ ����ȭ�Ѵ�.
	D3DXVec3Normalize(&ray->_direction, &ray->_direction);
}

// ��豸ü�� ���콺 ������ ���� Ȯ�� �Լ�
bool DU::raySphereIntersectionTest(DU::Ray* ray, DU::BoundingSphere* sphere){
	if(sphere == 0)
		return false;

	D3DXVECTOR3 v = ray->m_vOrigin - sphere->_center;

	float b = 2.0f * D3DXVec3Dot(&ray->_direction, &v);
	float c = D3DXVec3Dot(&v, &v) - (sphere->_radius * sphere->_radius);

	// �Ǻ���
	float discriminant = (b*b) - (4.0f * c);

	// ������ ���� ���� �׽�Ʈ
	if(discriminant<0.0f)
		return false;

	discriminant = sqrtf(discriminant);

	float s0 = (-b + discriminant) / 2.0f;
	float s1 = (-b - discriminant) / 2.0f;

	// �ذ� >= 0�� ��� ��ü�� �����ϴ� ���̴�.
	if(s0 >= 0.0f || s1 >= 0.0f)
		return true;

	return false;
}

// ��ǥ ��ȯ
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