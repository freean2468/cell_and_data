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

// Static ���� �ʱ�ȭ
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

// EngineMgr �ʱ�ȭ&����
void CApp::InitBaseManager(){
	EngineMgr->SetpDevice(m_pDevice);
	EngineMgr->Sethwnd(m_pMainWnd->GetSafeHwnd());

	EngineMgr->Initialize();
}

// ���� ���ø����̼� ������ �ʱ�ȭ & Direct3D �ʱ�ȭ
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

	// FullScreen ���� ����
	if(IDYES == MessageBox(this->m_pMainWnd->GetSafeHwnd(), "FullScreen?",m_szAppName,MB_YESNO))
		m_bScreen = true;
	else
		m_bScreen = false;

	m_hInstance = hInstance;
	EngineMgr->Sethinstance(hInstance);

	// ��ũ�� ��忡 ���� window style ����
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

	// VertexProcessing �ϵ���� ���� ���� Ȯ��
	int vp = 0;
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
			vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
			vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	RECT t_rcWindowClient;

	// ���ϴ� �ػ��� WIndow�� ��Ȯ�� ����
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

// �ڿ��� �Ҵ��̳� ��ġ Ư���� Ȯ��, ���ø����̼� ������ ���� ���� ���� �غ� �Լ�
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

	// ���� ������ ���� ������Ʈ���� ���� ���߾����� 
	// ���� AlphaBlendingȿ���� ��.

	EngineMgr->GetpDevice()->SetLight(0, &dir);
	EngineMgr->GetpDevice()->LightEnable(0, true);

	dir.Direction = D3DXVECTOR3(0.0f, 0.0f, -0.1f);

	// �� �κ��� ���ָ� ������ ���� ������ �޴´�.
	EngineMgr->GetpDevice()->SetLight(1, &dir);
	EngineMgr->GetpDevice()->LightEnable(1, true);

	EngineMgr->GetpDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	EngineMgr->GetpDevice()->SetRenderState(D3DRS_SPECULARENABLE, true);

	return true;
}

// Setup �Լ����� �Ҵ�� �ڿ��� ����
void CApp::Cleanup(){
	// EngineMgr Ŭ���� �Ҹ��ڿ��� ����
}

// PreRendering(����������)
void CApp::PreRendering(void){
	 EngineMgr->GetpDevice()->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,	0x00000000, 1.0f, 0);

	 // �׸��⸦ �����Ѵ�.
	 EngineMgr->GetpDevice()->BeginScene();

	 EngineMgr->GetpDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	 EngineMgr->GetpDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	 EngineMgr->GetpDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
}

// Rendiring(������)
void CApp::Rendering(float _fTimeDelta){
	// Section State�� ���� Update������ �޶�����.
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

// Post Rendering(����Ʈ ������)
HRESULT CApp::PostRendering(void){
	// �׸��Ⱑ �������� �˸���.
	EngineMgr->GetpDevice()->EndScene();

	// �׷��� Scene�� ����۷� �����Ѵ�.(������ �̺κп��� ȭ�鿡 �׷�����.)
	return EngineMgr->GetpDevice()->Present(NULL, NULL, NULL, NULL);
}

// ��������
void CApp::PreReset(void){

}

// ����̽� ����
// ���� ���� ���� x
HRESULT CApp::RestoreDevice(void){
	HRESULT Result = m_pDevice->TestCooperativeLevel();

	while(Result == D3DERR_DEVICELOST){
		while(Result != D3DERR_DEVICENOTRESET){
			MSG t_Msg;
			Sleep(1000);	// 1�ʰ� ���
			// 1�ʰ� �������� ���� ���� �޽��� ������ƾ�� �ִ´�.
			PeekMessage(&t_Msg, 0, 0, 0, PM_REMOVE);
			TranslateMessage(&t_Msg);
			DispatchMessage(&t_Msg);
			Result = m_pDevice->TestCooperativeLevel();	// ���¸� �ٽ� �����Ѵ�
		}
		if(FAILED(m_pDevice->Reset(&m_d3dpp))) Result = D3DERR_DEVICELOST;
	}

	return S_OK;
}

// ����Ʈ ����
void CApp::PostReset(void){

}

// ��� ����� �ڵ带 ����, �� �����Ӹ��� �Ͼ�� �ϴ� �۾��� ����
// ���⼭ �Ķ���� p_fTimeDelta�� �������� ���� original p_fTimeDelta��
// p_fTimeDelta ���ڴ� �� �������� ��� �ð�, �ʴ� �����Ӱ��� �ִϸ��̼� ����ȭ�� �̿�
bool CApp::Display(float _fTimeDelta){
	if( EngineMgr->GetpDevice() ){		
		DU::SetupMatrices();

#ifndef _Debug
	// ���� ���� ����� ���� ������ ���� p_fTimeDelta�� ����Ѵ�
	// Original Frame�� ����ϱ� ����
	// EngineMgr->GetpInformation()->CalcInformation(EngineMgr->GetpSystemFrame()->GetTimeDeltaOfOrigin());
#endif		

		if(!EngineMgr->GetpSystemFrame()->IsFrameSkip()){
			EngineMgr->GetpSystemFrame()->CalculationAdjustedTimeDelta();

			// Draw the scene:
			PreRendering();		

			Rendering(_fTimeDelta);

			HRESULT hr;

			// end the scene
			// ����̽��� �Ҿ��� ���� ����Ѵ�.
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
			// ����̽��� �Ҿ��� ���� ����Ѵ�.
			if(PostRendering() == D3DERR_DEVICELOST){
				PreReset();
				RestoreDevice();
				PostReset();
			}
		}
	}
	return true;
}

// ���ø����̼��� �޽��� ������ ����
int CApp::EnterMsgLoop(){
	MSG t_Msg;
	::ZeroMemory(&t_Msg, sizeof(t_Msg));

	while(t_Msg.message != WM_QUIT){
		if(PeekMessage(&t_Msg, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&t_Msg);
			DispatchMessage(&t_Msg);
		}
		else{
			// ������ ���� �ҿ� �ð��� ���
			EngineMgr->GetpSystemFrame()->CalculationTimeDeltaOfOrigin();

			if(EngineMgr->GetpSystemFrame()->Update(EngineMgr->GetTimeDelta())){
				// Direct Input Update
				EngineMgr->UpdateDI();
				AppMgr->Display(EngineMgr->GetTimeDelta());	// ���ø����̼� ���÷��� �Լ��� ȣ���Ѵ�.
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

// Global Main �Լ�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow){
	// ���� ���÷��� ������� Direct3D �ʱ�ȭ
	if(!AppMgr->InitD3D(hInstance, SYSTEMWIDTH, SYSTEMHEIGHT, true, D3DDEVTYPE_HAL, AppMgr->GetppDevice())){
		OutputDebugString("InitD3D() - FAILED");
		return 0;
	}

	// BaseManager �� ����
	AppMgr->InitBaseManager();

	// ���ø����̼� ���� �غ� ����
	if(!AppMgr->Setup()){
		OutputDebugString("Setup() - FAILED");
		return 0;
	}

	// �޽��� ���� ����
	AppMgr->EnterMsgLoop();

	// ���ø����̼� ����
	AppMgr->Cleanup();

	// IDirect3DDevice9 ��ü ����
	AppMgr->GetpDevice()->Release();

	return (int)AppMgr->ExitInstance();
}//WimMain()