#include "Wnd.h"

CWnd::CWnd(char* _pstrClassName,
		char* _pstrCaption,
		DWORD _dwStyle,
		int			_nPosX,
		int			_nPosY,
		int			_nSizeX,
		int			_nSizeY,
		HWND	 _hWndParent,
		HMENU _hMenu,
		HINSTANCE _hInstance,
		LPVOID	_lpVoid)
{
		m_hWnd = CreateWindow(_pstrClassName,
							_pstrCaption,	
							_dwStyle,					
							_nPosX,							
							_nPosY,							
							_nSizeX,						
							_nSizeY,						
							_hWndParent,
							_hMenu,				 
							_hInstance,			
							_lpVoid);				
}

HWND CWnd::GetSafeHwnd(){
	return this == NULL ? NULL : m_hWnd;
}//CWnd::GetSafeHwnd()

BOOL CWnd::ShowWindow(int _nCmdShow){
	return ::ShowWindow(GetSafeHwnd(), _nCmdShow);
}//CWnd::ShowWindow(int nCmdShow)

BOOL CWnd::UpdateWindow(){
	return ::UpdateWindow(GetSafeHwnd());
}//CWnd::UpdateWindow()