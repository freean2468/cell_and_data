#include "EngineManager.h"
#include "CameraManager.h"
#include "../Game_Factor/WorldManager.h"
#include "../Engine_System/MouseManager.h"
#include "App.h"

// 생성자에서는 초기화만을 담당한다.
CEngineManager::CEngineManager() :m_pDevice(NULL),
								m_pFont(NULL),
								m_pSprite(NULL),
								m_pInfo(NULL),
								m_pFrame(NULL),
								m_nLButtonState(-1),
								m_OldCode(0),
								m_hEditWnd(0),
								m_hMouseEvent(CreateEvent(NULL, false, false, NULL))
{
	
}

CEngineManager::~CEngineManager(){
	// Device는 어플리케이션에서 해제한다.
	// 해제 순서는 생성 순서의 반대로(스택)
	
	Delete<CSystemFrame*>( m_pFrame );
	//  해제를 하려 하면 오류가 뜬다.
//	Delete<CInformation*>( m_pInfo );

	Release<ID3DXSprite*>(GetpSprite());
	Release<ID3DXFont*>(GetpFont());
	Release<ID3DXFont*>(m_pFontForCoSystem);

	m_pKeyboard->Unacquire();
	m_pKeyboard->Release();

	m_pMouse->Unacquire();
	m_pMouse->Release();
}

void CEngineManager::InitializeEdit(){
	m_hEditWnd = CreateWindow(TEXT("Edit"), NULL, WS_CHILD | WS_CLIPCHILDREN, 
														100, 100, 100, 100, Gethwnd(), (HMENU)1, Gethinstance(), NULL);
}

void CEngineManager::EditWndUpdate(char* _pBuffer, int _nLength){
	::GetWindowText(EngineMgr->GetEdit(), _pBuffer, _nLength);
	::SetFocus(EngineMgr->GetEdit());
}

D3DXMATRIX* CEngineManager::GetWorldMat(){
	// 월드 행렬
	D3DXMatrixIdentity(&m_mWorld);

	return &m_mWorld;
}

D3DXMATRIX* CEngineManager::GetViewMat(){
	// 뷰 행렬 설정	
	CameraMgr->GetCamera()->GetViewMatrix(&m_mView);
	
	return &m_mView;
}

D3DXMATRIX* CEngineManager::GetProjMat(){
	// 프로젝션 행렬 설정
	D3DXMatrixPerspectiveFovLH(&m_mProj,
															D3DX_PI / 4.0f, // 45 - degree
															(float)(SYSTEMWIDTH)/(float)(SYSTEMHEIGHT),
															1.0f,
															2000.0f);

	return &m_mProj;
}

// 좀 더 다듬어 보자.
bool CEngineManager::IsViewOut(D3DXVECTOR3* _pvObjectPos){
	D3DXVECTOR3 t_vCameraPos;
	D3DXVECTOR3 t_vCameraHeading(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 t_vDist;

	CameraMgr->GetCamera()->GetPosition(&t_vCameraPos);

	t_vDist = *_pvObjectPos - t_vCameraPos;

	::D3DXVec3Normalize(&t_vDist, &t_vDist);
	::D3DXVec3Normalize(&t_vCameraHeading, &t_vCameraHeading);

	float t_fDot = D3DXVec3Dot(&t_vDist, &t_vCameraHeading);

	if(t_fDot < 0.0f) 
		return true;

	float t_fRad = acosf(t_fDot);

	if(t_fRad > D3DX_PI/4.0f) 
		return true;

	return false;
}

//------------------------- KeyPresses -----------------------------
void CEngineManager::CheckKeyDown(){
	if(EngineMgr->KeyDown(DIK_P)){
		WorldMgr->TogglePause();
	}
}

bool CEngineManager::KeyDown(BYTE p_code){
	if(m_KeyState[p_code] & 0x80) 
		return true; 
	else 
		return false;
}

bool CEngineManager::KeyUp(BYTE p_code){
	if(!KeyDown(m_OldCode) && p_code == m_OldCode){
		m_OldCode = 0;
		return true;
	}

	if(m_KeyState[p_code] & 0x80){
		m_OldCode = p_code;
	}

	return false;
}

void CEngineManager::UpdateDI(){
	// Keyboard
	if(FAILED(m_pKeyboard->GetDeviceState(sizeof(m_KeyState), (LPVOID)m_KeyState))){
		m_pKeyboard->Acquire();
	}

	DIMOUSESTATE t_MouseState; 
	HRESULT hr;

	t_MouseState.lX = 0; t_MouseState.lY = 0;

	 // Poll the device to read the current state
  hr = m_pMouse->Poll();
  if( FAILED( hr ) ){
    hr = m_pMouse->Acquire();
    while( hr == DIERR_INPUTLOST )
      hr = m_pMouse->Acquire();

    return;
  }

  if( FAILED( hr = m_pMouse->GetDeviceState( sizeof( DIMOUSESTATE ), &t_MouseState ) ) )
    return; 
	
	float t_fDistX = (float)t_MouseState.lX;
	float t_fDistY = (float)t_MouseState.lY;

	if(t_fDistX < 100.0f && t_fDistY < 100.0f){
		MouseMgr->UpdateCursorPosition(t_fDistX, t_fDistY);

		if(t_MouseState.rgbButtons[0] & 0x80){	MouseMgr->SetLeftDown(true);		}
		else{			MouseMgr->SetLeftDown(false);		}

		if(t_MouseState.rgbButtons[1] & 0x80){	MouseMgr->SetRightDown(true);		}
		else{			MouseMgr->SetRightDown(false);		}
	}
}

void CEngineManager::TextOutBegin(){
	m_pSprite->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D 공간상에 텍스트 출력
}

void CEngineManager::TextOutEnd(){
	m_pSprite->End();

	D3DXMATRIXA16 mtMatrix;

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	m_pSprite->SetTransform(&mtMatrix);
}

void CEngineManager::LineRenderBegin(){
	m_pDevice->BeginScene();

	D3DXCreateLine(m_pDevice, &m_pLine);

	m_pLine->SetWidth(3.0f);
	m_pLine->SetAntialias(true);

	m_pLine->Begin();

	// ZBuffer 연산 꺼줌
	m_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
}

void CEngineManager::LineRenderEnd(){
	// ZBuffer 연산 켜줌
	m_pDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	m_pLine->End();

	m_pLine->Release();

	m_pDevice->EndScene();
}

void CEngineManager::Loading(){
	DU::SetupMatrices();

	AppMgr->PreRendering();

	GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D 공간상에 텍스트 출력

	D3DXMATRIXA16 _rotation;	// 회전 변환 행렬
	D3DXVECTOR3 _vRotate;		// 회전 벡터

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMATRIXA16 rX;
	D3DXMatrixIdentity(&rX);
	D3DXMatrixRotationX(&rX, D3DX_PI);
	_rotation = rX;

	mtMatrix *= _rotation;

	GetpSprite()->SetTransform(&mtMatrix);

	RECT rect;

	rect.right = SYSTEMWIDTH/2 - 70;
	rect.left = -SYSTEMWIDTH/2;
	rect.top = -SYSTEMHEIGHT/2;
	rect.bottom = SYSTEMHEIGHT/2 - 50;

	// Text 출력     
	m_pFont->DrawText(GetpSprite(), "Loading...", -1, &rect, DT_RIGHT | DT_BOTTOM , 0xff00ff00);

	GetpSprite()->End();

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	GetpSprite()->SetTransform(&mtMatrix);

	AppMgr->PostRendering();
}

// 초기화&셋팅 함수
void CEngineManager::Initialize(){
	// 폰트 설정
	m_pFont = DU::IniFont(17, 10, 500, false, "Times New Roman");
	m_pFontForCoSystem = DU::IniFont(11, 6, 200, false, "맑은 고딕");

	// 스프라이트 생성
	D3DXCreateSprite(GetpDevice(), GetppSprite() );

	Loading();

	// SetInformation
	SetInfo();

	// SetSystemFrame
	SetFrame();
	
	// SetTerrain
//	SetTerrain();
}

void CEngineManager::SetInfo(){
	this->SetCInformation(new CInformation());
}

void CEngineManager::SetFrame(){
	this->SetCSystemFrame(new CSystemFrame());

	this->GetpSystemFrame()->SetFramePerSec(60.0f);
}