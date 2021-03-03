///////////////////////////////////////////////////////
// DirectX ���� ��������� �Լ����� ����
// ���� DIrectX ���� �������̽��� ���� �����ϱ� ����
// ��å ����
///////////////////////////////////////////////////////
#ifndef _DirectUtils_H_
#define _DirectUtils_H_

#include "../Engine_Math&Physics/Vector2D.h"

// Classes and Structures
struct Vertex{
	Vertex(){}
	Vertex(
		float x, float y, float z,
		float nx, float ny, float nz,
		float u, float v)
	{
		_x  = x;  _y  = y;  _z  = z;
		_nx = nx; _ny = ny; _nz = nz;	//	
		_u  = u;  _v  = v;		
	}
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _u, _v; // texture coordinates
	
	static const DWORD FVF;
};

namespace DU{
	// COM �������̽��� �����ϰ� null�� ����
	template<class T> void Release(T t){
		if(t){
   		t->Release();
			t = 0;
		}
	}

	// ������� ��ü�� �����ϰ� �����͸� null�� ����
	template<class T> void Delete(T t){
		if(t){
			delete t;
			t = NULL;
		}
	}

	//
	// Colors
	//
	const D3DXCOLOR      WHITE( D3DCOLOR_XRGB(255, 255, 255) );
	const D3DXCOLOR      GRAY( D3DCOLOR_XRGB(127, 127, 127) );
	const D3DXCOLOR      BLACK( D3DCOLOR_XRGB(  0,   0,   0) );
	const D3DXCOLOR        RED( D3DCOLOR_XRGB(255,   0,   0) );
	const D3DXCOLOR      GREEN( D3DCOLOR_XRGB(  0, 255,   0) );
	const D3DXCOLOR       BLUE( D3DCOLOR_XRGB(  0,   0, 255) );
	const D3DXCOLOR     YELLOW( D3DCOLOR_XRGB(255, 255,   0) );
	const D3DXCOLOR       CYAN( D3DCOLOR_XRGB(  0, 255, 255) );
	const D3DXCOLOR    MAGENTA( D3DCOLOR_XRGB(255,   0, 255) );

	const D3DXCOLOR BEACH_SAND( D3DCOLOR_XRGB(255, 249, 157) );
	const D3DXCOLOR DESERT_SAND( D3DCOLOR_XRGB(250, 205, 135) );

	const D3DXCOLOR LIGHTGREEN( D3DCOLOR_XRGB( 60, 184, 120) );
	const D3DXCOLOR  PUREGREEN( D3DCOLOR_XRGB(  0, 166,  81) );
	const D3DXCOLOR  DARKGREEN( D3DCOLOR_XRGB(  0, 114,  54) );

	const D3DXCOLOR LIGHT_YELLOW_GREEN( D3DCOLOR_XRGB(124, 197, 118) );
	const D3DXCOLOR  PURE_YELLOW_GREEN( D3DCOLOR_XRGB( 57, 181,  74) );
	const D3DXCOLOR  DARK_YELLOW_GREEN( D3DCOLOR_XRGB( 25, 123,  48) );

	const D3DXCOLOR LIGHTBROWN(D3DCOLOR_XRGB(198, 156, 109));
	const D3DXCOLOR DARKBROWN( D3DCOLOR_XRGB(115, 100,  87));

	// ����
	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);

	const D3DMATERIAL9 WHITE_MTRL  = InitMtrl(WHITE, WHITE, WHITE, BLACK, 2.0f);
	const D3DMATERIAL9 RED_MTRL    = InitMtrl(RED, RED, RED, BLACK, 2.0f);
	const D3DMATERIAL9 GREEN_MTRL  = InitMtrl(GREEN, GREEN, GREEN, BLACK, 2.0f);
	const D3DMATERIAL9 BLUE_MTRL   = InitMtrl(BLUE, BLUE, BLUE, BLACK, 2.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 2.0f);

	// ����
	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);
	D3DLIGHT9 InitPointLight(D3DXVECTOR3* _pvPos, D3DXCOLOR* color);
	D3DLIGHT9 InitSpotLight(D3DXVECTOR3* _pvPos, D3DXVECTOR3* direction, D3DXCOLOR* color);

	// ��Ʈ
	ID3DXFont* IniFont(int wid, int hei, int wei, bool ital, char* style);
	void IniFont(ID3DXFont* _pFont, int wid, int hei, int wei, bool ital, char* style);
	void SetFontScale(ID3DXFont* _pFont, int _nScale);
    
	const DWORD        NumSubSets = 3;

	void SetupMatrices();
	void RenderTerrain();
	void RenderBG();
	void RenderMirror();
	void RenderShadow();
	void RenderBoundingVolume();

	const float INFINITY = FLT_MAX;
	const float EPSILON = 0.001f;

	// ��� �ڽ�
	struct BoundingBox{
		BoundingBox();

		bool isPointInside(D3DXVECTOR3& p);
		D3DXVECTOR3 _min;
		D3DXVECTOR3 _max;
	};

	// ��� ��ü
	struct BoundingSphere{
		BoundingSphere();

		D3DXVECTOR3 _center;
		float _radius;
	};

	// ���� Ŭ����
	struct Ray	{
		D3DXVECTOR3 m_vOrigin;
		D3DXVECTOR3 _direction;
	};

	bool ComputeBoundingSphere(ID3DXMesh* mesh, DU::BoundingSphere* sphere);
	bool ComputeBoundingBox(ID3DXMesh* mesh, DU::BoundingBox* box);

	// ���� �ȿ� �ִ� ������ float�� ����
	float GetRandomFloat(float lowBound, float highBound);

	// �ּ��� min�� �ִ��� max�� ���ǵ� ���� ���� ���� ���͸� ���
	void GetRandomVector(D3DXVECTOR3* out, D3DXVECTOR3* min, D3DXVECTOR3* max);

	// 1D ���� ������ �⺻ ���� ����
	float Lerp(float a, float b, float t);
	
	// float -> DWORD ����ȯ
	DWORD FtoDw(float f);

	// ��ŷ ����
	Ray CalcPickingRay(int x, int y);
	void TransformRay(DU::Ray* ray, D3DXMATRIX* T);
	bool raySphereIntersectionTest(Ray* ray, BoundingSphere* sphere);

	// ��ǥ ��ȯ
	D3DXVECTOR2 TransformCoSystemWinToDX2D(float p_x, float p_y);
	Vector2D TransformCoSystemWinToDX2D(Vector2D* p_pV);

	// ------------------------------- Draw
	void VBLineRender(const std::vector<Vector2D> &points, D3DXCOLOR* p_pColor);

	// DirectX 2D Object Organ Rotate
	float CalAngleConsiderTexture(Vector2D _vPos);
	float CalAngleConsiderTexture(D3DXVECTOR3 _vPos);
}

#endif