/*
CApp는 응용프로그램의 초기화, 다큐먼트와 뷰의 결합 등을 담당한다.
메인 윈도우 핸들과 메인 윈도우를 생성하는 AddDocTemplate()함수가 있다
이 클래스는 일련의 어플리케이션의 루틴을 담당한다.
*/
#ifndef _App_H_
#define _App_H_

#include "Wnd.h"
#include <d3d9.h>
#include "../Engine_System/Log.h"

// class CApp
// 유일 객체
class CApp{
private:
	// 유일 객체 생성을 위해서
	// 생성자와 소멸자를 복사하고 할당은 private이어야 한다.
	CApp(const CApp&);
	CApp& operator=(const CApp&);

	static bool									m_bScreen;

protected:
	static char									m_szAppName[];
	HINSTANCE									m_hInstance;

	IDirect3DDevice9*							m_pDevice;  
	D3DPRESENT_PARAMETERS						m_d3dpp;

private:
	CLog										*log;

public:
	CWnd*										m_pMainWnd;				// 응용 프로그램의 메인 윈도우 객체를 가리킨다.

public:
	CApp();
	virtual ~CApp();	

	static CApp* Instance(){
		static CApp instance;

		return &instance;
	}

	WPARAM ExitInstance();
	
	HRESULT InitD3D(
	HINSTANCE hInstance,										// [입력] 애플리케이션 인스턴스
	int width, int height,								// [입력] 후면 버퍼 크기
	bool windowed,																// [입력] 윈도우 (true) 혹은 전체 화면 (false)
	D3DDEVTYPE deviceType,								// [입력] HAL 혹은 REF
	IDirect3DDevice9** device);			// [출력] 만들어진 장치
	int EnterMsgLoop();	

	void InitBaseManager();

	void PreRendering(void);
	void Rendering(float _fTimeDelta);
	HRESULT PostRendering(void);
	bool Setup();
	void Cleanup();
	bool Display(float _fTimeDelta);
	void PreReset(void);
	HRESULT RestoreDevice(void);
	void PostReset(void);

	HINSTANCE* GetInstance(){return &m_hInstance;}

	//virtual function
	virtual IDirect3DDevice9*	GetpDevice(){return m_pDevice;}	
	virtual IDirect3DDevice9**	GetppDevice(){return &m_pDevice;}
	virtual CWnd* GetpWnd(){return m_pMainWnd;}
};//class CApp

// Main함수와 Wndproc는 전역함수로 선언
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

#define AppMgr CApp::Instance()

#endif