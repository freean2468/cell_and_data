/*
CWnd클래스는 모든 윈도우 클래스의 베이스 클래스로 사용된다.
윈도우 핸들을 필요로하는 모든 윈도우 API함수들을 랩하고 있고, 구조상 필요한 가상함수들을 포함한다.
*/
#ifndef _Wnd_H_
#define	_Wnd_H_

#include <Windows.h>

class CWnd{
private:
	HWND m_hWnd;

public:
		CWnd(char* _pstrClassName,
			char* _pstrCaption,
			DWORD _dwStyle,
			int			_nPosX,
			int			_nPosY,
			int			_nSizeX,
			int			_nSizeY,
			HWND	 _hWndParent,
			HMENU _hMenu,
			HINSTANCE _hInstance,
			LPVOID	_lpVoid);

public:
	HWND GetSafeHwnd();
	BOOL ShowWindow(int _nCmdShow);
	BOOL UpdateWindow();
};	// class CWnd

#endif