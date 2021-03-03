/*
CWndŬ������ ��� ������ Ŭ������ ���̽� Ŭ������ ���ȴ�.
������ �ڵ��� �ʿ���ϴ� ��� ������ API�Լ����� ���ϰ� �ְ�, ������ �ʿ��� �����Լ����� �����Ѵ�.
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