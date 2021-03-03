/*
CApp�� �������α׷��� �ʱ�ȭ, ��ť��Ʈ�� ���� ���� ���� ����Ѵ�.
���� ������ �ڵ�� ���� �����츦 �����ϴ� AddDocTemplate()�Լ��� �ִ�
�� Ŭ������ �Ϸ��� ���ø����̼��� ��ƾ�� ����Ѵ�.
*/
#ifndef _App_H_
#define _App_H_

#include "Wnd.h"
#include <d3d9.h>
#include "../Engine_System/Log.h"

// class CApp
// ���� ��ü
class CApp{
private:
	// ���� ��ü ������ ���ؼ�
	// �����ڿ� �Ҹ��ڸ� �����ϰ� �Ҵ��� private�̾�� �Ѵ�.
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
	CWnd*										m_pMainWnd;				// ���� ���α׷��� ���� ������ ��ü�� ����Ų��.

public:
	CApp();
	virtual ~CApp();	

	static CApp* Instance(){
		static CApp instance;

		return &instance;
	}

	WPARAM ExitInstance();
	
	HRESULT InitD3D(
	HINSTANCE hInstance,										// [�Է�] ���ø����̼� �ν��Ͻ�
	int width, int height,								// [�Է�] �ĸ� ���� ũ��
	bool windowed,																// [�Է�] ������ (true) Ȥ�� ��ü ȭ�� (false)
	D3DDEVTYPE deviceType,								// [�Է�] HAL Ȥ�� REF
	IDirect3DDevice9** device);			// [���] ������� ��ġ
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

// Main�Լ��� Wndproc�� �����Լ��� ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

#define AppMgr CApp::Instance()

#endif