#include "App.h"
#include "EngineManager.h"
#include "../Side Engine/resource.h"
#include "../Engine_Misc/DirectUtils.h"
#include "../Engine_Logic/SectionManager.h"
#include "../Engine_System/EffectManager.h"
#include "../Engine_System/MP3Manager.h"
#include "../Engine_System/CameraManager.h"
#include "../Engine_System/MouseManager.h"
#include "../Engine_System/MessageManager.h"
#include <ctime>

// Static 변수 초기화
char CApp::m_szAppName[] = "Cell & Data";
bool CApp::m_bScreen = false;

//constructor
CApp::CApp() : m_pDevice(NULL) 
{
	log = new CLog("app");
}

//destructor
CApp::~CApp(){
	if(m_pMainWnd != NULL){
		delete m_pMainWnd;
		m_pMainWnd = NULL;
	}//if
	delete log;
}//CApp::~CApp()

// EngineMgr 초기화&셋팅
void CApp::InitBaseManager(){
	EngineMgr->SetpDevice(m_pDevice);
	EngineMgr->Sethwnd(m_pMainWnd->GetSafeHwnd());

	EngineMgr->Initialize();
}

// 메인 애플리케이션 윈도우 초기화 & Direct3D 초기화
HRESULT CApp::InitD3D(HINSTANCE hInstance,
					int width, 
					int height,
					bool windowed,
					D3DDEVTYPE deviceType,
					IDirect3DDevice9** device)
{
	log->insertLog("InitInstance entry\n");
	// Create the main application window.
	WNDCLASSEX wc;

	wc.cbSize				= sizeof( WNDCLASSEX );
	wc.style				= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc			= (WNDPROC)WndProc;
	wc.cbClsExtra			= 0;
	wc.cbWndExtra			= 0;
	wc.hInstance			= hInstance;
	wc.hIcon				= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor				= LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName			= 0;
	wc.lpszClassName		= m_szAppName;
	wc.hIconSm				= NULL;

	if(!RegisterClassEx(&wc)){
		OutputDebugString("RegisterClass() - FAILED");

		return false;
	}

	// FullScreen 여부 설정
	if(IDYES == MessageBox(this->m_pMainWnd->GetSafeHwnd(), "FullScreen?",m_szAppName,MB_YESNO))
		m_bScreen = true;
	else
		m_bScreen = false;

	m_hInstance = hInstance;
	EngineMgr->Sethinstance(hInstance);

	// 스크린 모드에 따른 window style 지정
	if(m_bScreen){
		m_pMainWnd = new CWnd(m_szAppName,					 //Window class name
							m_szAppName,					 //Window caption		
							WS_POPUP,									//window style
							0,																//initial x position
							0,																//initial y position
							width,												//initial x size
							height,											//initial y size
							NULL, /*parent hWnd*///parent window handle
							NULL, /* menu */				 //window menu handle
							m_hInstance,						//program instance handle
							0 /*extra*/);				 //creation parameters
	}
	else{
		m_pMainWnd = new CWnd(m_szAppName,					 //Window class name
							m_szAppName,					 //Window caption
							WS_OVERLAPPEDWINDOW,		 //window style
							0,							 //initial x position
							0,							 //initial y position
							width,						 //initial x size
							height,						 //initial y size
							NULL, /*parent hWnd*/			 //parent window handle
							NULL, /* menu */				 //window menu handle
							m_hInstance,				 //program instance handle
							0 /*extra*/);				 //creation parameters
	}	

	if(!m_pMainWnd->GetSafeHwnd()){
		OutputDebugString("CreateWindow() - FAILED");
		return false;
	}

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Init D3D

	HRESULT hr = 0;

	// Step 1 : Create the IDirect3D9 object.

	IDirect3D9* d3d9 = 0;
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if(!d3d9){OutputDebugString("Direct3DCreate9() - FAILED");return false;	}

	LPDIRECTINPUT8 _pIDDevice;

	// ====================================== ID
	hr = DirectInput8Create(m_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_pIDDevice, NULL); 

	if FAILED(hr){ OutputDebugString("DirectInput8Create() - FAILED");return false;	} 

	// ====================================== Keyboard

	hr = _pIDDevice->CreateDevice(GUID_SysKeyboard, EngineMgr->GetppDIKeyboard(), NULL); 

	if FAILED(hr){ return FALSE; } 

	hr = EngineMgr->GetpDIKeyboard()->SetDataFormat(&c_dfDIKeyboard); 

	if FAILED(hr){ return FALSE; } 

	hr = EngineMgr->GetpDIKeyboard()->SetCooperativeLevel(m_pMainWnd->GetSafeHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 

	if FAILED(hr){ return FALSE; } 

	EngineMgr->GetpDIKeyboard()->Acquire();
	// ================================ end

	// ================================ Mouse
	// Retrieve the system mouse
	if( FAILED( _pIDDevice->CreateDevice( GUID_SysMouse, EngineMgr->GetppDIMouse(), NULL ) ) ){
		return S_OK;
	}

	// A data format specifies which controls on a device we are interested in,
	// and how they should be reported. This tells DInput that we will be
	// passing a MouseState structure to IDirectInputDevice::GetDeviceState().
	if( FAILED( hr = EngineMgr->GetpDIMouse()->SetDataFormat( &c_dfDIMouse ) ) )
		return hr;

	// Set the cooperative level to let DInput know how this device should
	// interact with the system and with other DInput applications.
	if( FAILED( hr = EngineMgr->GetpDIMouse()->SetCooperativeLevel(m_pMainWnd->GetSafeHwnd(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND ) ) )
		return hr;
//
//	hr = EngineMgr->GetpDIMouse()->SetEventNotification(EngineMgr->GetMouseEvent());
//
//	if (FAILED(hr)) {
//			return FALSE;
//	}
//
//#define SAMPLE_BUFFER_SIZE  16
//
//	DIPROPDWORD dipdw;
//	// the header
//	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
//	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
//	dipdw.diph.dwObj        = 0;
//	dipdw.diph.dwHow        = DIPH_DEVICE;
//	// the data
//	dipdw.dwData            = SAMPLE_BUFFER_SIZE;
//
//	hr = EngineMgr->GetpDIMouse()->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
//
//	if (FAILED(hr)) {
//			return FALSE;
//	}

	EngineMgr->GetpDIMouse()->Acquire();
	// ================================= end	

	// Step 2 : Check for hardware vp.

	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);

	// VertexProcessing 하드웨어 지원 여부 확인
	int vp = 0;
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
			vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
			vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	RECT t_rcWindowClient;

	// 원하는 해상도의 WIndow를 정확히 생성
	GetClientRect(m_pMainWnd->GetSafeHwnd(), &t_rcWindowClient);

	int t_nOffsetX = (width - (t_rcWindowClient.right - t_rcWindowClient.left));
	int t_nOffsetY = (height - (t_rcWindowClient.bottom - t_rcWindowClient.top));

	::SetWindowPos(m_pMainWnd->GetSafeHwnd(), NULL, 0, 0, width + t_nOffsetX, height + t_nOffsetY, NULL);

	// Step 3 : Fill out the D3DPRESENT_PARAMETERS structure.
	m_d3dpp.BackBufferWidth							= width;
	m_d3dpp.BackBufferHeight						= height;
	m_d3dpp.BackBufferFormat						= D3DFMT_A8R8G8B8;
	m_d3dpp.BackBufferCount							= 1;
	m_d3dpp.MultiSampleType							= D3DMULTISAMPLE_NONE;
	m_d3dpp.MultiSampleQuality					= 0;
	m_d3dpp.SwapEffect									= D3DSWAPEFFECT_DISCARD;
	m_d3dpp.hDeviceWindow								= m_pMainWnd->GetSafeHwnd();
	m_d3dpp.Windowed										= !m_bScreen;
	m_d3dpp.EnableAutoDepthStencil			= true;
	m_d3dpp.AutoDepthStencilFormat			= D3DFMT_D24S8;
	m_d3dpp.Flags												= 0;
	m_d3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
	m_d3dpp.PresentationInterval				= NULL;

	// Step 4 : Create the device.

	hr = d3d9->CreateDevice(	D3DADAPTER_DEFAULT,			// primary adapter
								deviceType,					// device type
								m_pMainWnd->GetSafeHwnd(),	// window associated with device
								vp,							// vertex processing
								&m_d3dpp,						// present parameters
								device);					// return created device

	if(FAILED(hr)){
		// try again using a 16-bit depth buffer
		m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		hr = d3d9->CreateDevice(	D3DADAPTER_DEFAULT,
														deviceType,
														m_pMainWnd->GetSafeHwnd(),
														vp,
														&m_d3dpp,
														device);

		if(FAILED(hr)){
			d3d9->Release();	// done with d3d9 object
			OutputDebugString("CreateDevice() - FAILED");
			return false;
		}
	}

	_pIDDevice->Release();
	d3d9->Release();	// done with d3d9 object

	log->insertLog("InitInstance done\n");

	return true;
}//CApp::InitInstance

// 자원의 할당이나 장치 특성의 확인, 애플리케이션 상태의 설정 등의 사전 준비 함수
bool CApp::Setup(){
	HRESULT hr = 0;

	srand(unsigned int(time(NULL)));

	// Lights.
	//D3DXVECTOR3 lightDir(0.707f, /*-0.707f*/0.0f, 0.707f);
	//D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);
	//D3DLIGHT9 light = DU::InitDirectionalLight(&lightDir, &color);

	D3DLIGHT9 dir;
	::ZeroMemory(&dir, sizeof(dir));
	dir.Type      = D3DLIGHT_DIRECTIONAL;
	dir.Diffuse   = DU::WHITE;
	dir.Specular  = DU::WHITE * 0.0f;
	dir.Ambient   = DU::WHITE * 0.6f;
	dir.Direction = D3DXVECTOR3(0.0f, 0.0f, 0.1f);

	// 현재 재질을 가진 오브젝트들이 빛이 비추어져야 
	// 여러 AlphaBlending효과가 됨.

	EngineMgr->GetpDevice()->SetLight(0, &dir);
	EngineMgr->GetpDevice()->LightEnable(0, true);

	dir.Direction = D3DXVECTOR3(0.0f, 0.0f, -0.1f);

	// 이 부분을 없애면 재질이 빛의 영향을 받는다.
	EngineMgr->GetpDevice()->SetLight(1, &dir);
	EngineMgr->GetpDevice()->LightEnable(1, true);

	EngineMgr->GetpDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	EngineMgr->GetpDevice()->SetRenderState(D3DRS_SPECULARENABLE, true);

	return true;
}

// Setup 함수에서 할당된 자원을 해제
void CApp::Cleanup(){
	// EngineMgr 클래스 소멸자에서 해제
}

// PreRendering(프리렌더링)
void CApp::PreRendering(void){
	 EngineMgr->GetpDevice()->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,	0x00000000, 1.0f, 0);

	 // 그리기를 시작한다.
	 EngineMgr->GetpDevice()->BeginScene();

	 EngineMgr->GetpDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	 EngineMgr->GetpDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	 EngineMgr->GetpDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
}

// Rendiring(렌더링)
void CApp::Rendering(float _fTimeDelta){
	// Section State에 따라서 Update내용이 달라진다.
	SectionMgr->GetSection()->Update();		

	// Camera
	CameraMgr->CameraMode();

	// Alpha Effect
	EffectMgr->AlphaPlaneUpdate();

	// Sound
	MP3Mgr->Fade();

	// Mouse
	MouseMgr->CursorUpdate();

	// Message
	MessageMgr->Update();

	// Check
	EngineMgr->CheckKeyDown();

	// Information
	//EngineMgr->GetpInformation()->DrawInformation(EngineMgr->GetpFont(), EngineMgr->GetpSprite());
}

// Post Rendering(포스트 렌더링)
HRESULT CApp::PostRendering(void){
	// 그리기가 끝났음을 알린다.
	EngineMgr->GetpDevice()->EndScene();

	// 그려진 Scene을 백버퍼로 전송한다.(실제로 이부분에서 화면에 그려진다.)
	return EngineMgr->GetpDevice()->Present(NULL, NULL, NULL, NULL);
}

// 프리리셋
void CApp::PreReset(void){

}

// 디바이스 복귀
// 현재 정상 구현 x
HRESULT CApp::RestoreDevice(void){
	HRESULT Result = m_pDevice->TestCooperativeLevel();

	while(Result == D3DERR_DEVICELOST){
		while(Result != D3DERR_DEVICENOTRESET){
			MSG t_Msg;
			Sleep(1000);	// 1초간 대기
			// 1초간 정지했을 때를 위해 메시지 펌프루틴을 넣는다.
			PeekMessage(&t_Msg, 0, 0, 0, PM_REMOVE);
			TranslateMessage(&t_Msg);
			DispatchMessage(&t_Msg);
			Result = m_pDevice->TestCooperativeLevel();	// 상태를 다시 조사한다
		}
		if(FAILED(m_pDevice->Reset(&m_d3dpp))) Result = D3DERR_DEVICELOST;
	}

	return S_OK;
}

// 포스트 리셋
void CApp::PostReset(void){

}

// 모든 드로잉 코드를 구현, 매 프레임마다 일어나야 하는 작업을 수행
// 여기서 파라미터 p_fTimeDelta는 조정되지 않은 original p_fTimeDelta다
// p_fTimeDelta 인자는 각 프레임의 경과 시간, 초당 프레임과의 애니메이션 동기화에 이용
bool CApp::Display(float _fTimeDelta){
	if( EngineMgr->GetpDevice() ){		
		DU::SetupMatrices();

#ifndef _Debug
	// 각종 정보 계산은 원래 프레임 간의 p_fTimeDelta를 사용한다
	// Original Frame을 계산하기 위함
	// EngineMgr->GetpInformation()->CalcInformation(EngineMgr->GetpSystemFrame()->GetTimeDeltaOfOrigin());
#endif		

		if(!EngineMgr->GetpSystemFrame()->IsFrameSkip()){
			EngineMgr->GetpSystemFrame()->CalculationAdjustedTimeDelta();

			// Draw the scene:
			PreRendering();		

			Rendering(_fTimeDelta);

			HRESULT hr;

			// end the scene
			// 디바이스를 잃었을 때를 대비한다.
			hr = PostRendering();

			if(hr == D3DERR_DEVICELOST){
				PreReset();
				RestoreDevice();
				PostReset();
			}
			else if(hr == D3DERR_DEVICENOTRESET){
				m_pDevice->Reset(&m_d3dpp);
			}
		}
		else if(!EngineMgr->GetpSystemFrame()->IsFrameSkip() || EngineMgr->GetpInformation()->GetFPSofOrgin() < EngineMgr->GetpSystemFrame()->GetLimitFPS()){
			EngineMgr->GetpSystemFrame()->CalculationAdjustedTimeDelta();

			// Draw the scene:
			PreRendering();		

			Rendering(_fTimeDelta);

			// end the scene
			// 디바이스를 잃었을 때를 대비한다.
			if(PostRendering() == D3DERR_DEVICELOST){
				PreReset();
				RestoreDevice();
				PostReset();
			}
		}
	}
	return true;
}

// 애플리케이션의 메시지 루프를 포장
int CApp::EnterMsgLoop(){
	MSG t_Msg;
	::ZeroMemory(&t_Msg, sizeof(t_Msg));

	while(t_Msg.message != WM_QUIT){
		if(PeekMessage(&t_Msg, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&t_Msg);
			DispatchMessage(&t_Msg);
		}
		else{
			// 프레임 간의 소요 시간을 계산
			EngineMgr->GetpSystemFrame()->CalculationTimeDeltaOfOrigin();

			if(EngineMgr->GetpSystemFrame()->Update(EngineMgr->GetTimeDelta())){
				// Direct Input Update
				EngineMgr->UpdateDI();
				AppMgr->Display(EngineMgr->GetTimeDelta());	// 어플리케이션 디스플레이 함수를 호출한다.
			}
		}
	}
	return (int)t_Msg.wParam;
}

WPARAM CApp::ExitInstance(){
	return 0L;	// msg.wParam;
}//CApp::ExitInstance

//Window procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);
	short tmpDelta;

	switch(iMsg){
		case WM_MOUSEWHEEL:
			if(CameraMgr->GetMode() == CCameraManager::MOUSE){
				CameraMgr->GetCamera()->GetPosition(&t_vPos);
			
				tmpDelta = HIWORD(wParam);

				switch(tmpDelta){
					case 120:
						CameraMgr->SetDestinationZ(t_vPos.z + 50.0f);
						break;
					case -120:			
						CameraMgr->SetDestinationZ(t_vPos.z - 50.0f);
						break;
				}
			}
			return true;
		case WM_DESTROY:
			PostQuitMessage(0);
			return true;
	}
	
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}//WndProc()

// Global Main 함수
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow){
	// 메인 디스플레이 윈도우와 Direct3D 초기화
	if(!AppMgr->InitD3D(hInstance, SYSTEMWIDTH, SYSTEMHEIGHT, true, D3DDEVTYPE_HAL, AppMgr->GetppDevice())){
		OutputDebugString("InitD3D() - FAILED");
		return 0;
	}

	// BaseManager 랩 수행
	AppMgr->InitBaseManager();

	// 어플리케이션 사전 준비 수행
	if(!AppMgr->Setup()){
		OutputDebugString("Setup() - FAILED");
		return 0;
	}

	// 메시지 루프 진입
	AppMgr->EnterMsgLoop();

	// 애플리케이션 정리
	AppMgr->Cleanup();

	// IDirect3DDevice9 객체 해제
	AppMgr->GetpDevice()->Release();

	return (int)AppMgr->ExitInstance();
}//WimMain()