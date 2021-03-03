#ifndef WINDOW_UTILS_H
#define WINDOW_UTILS_H

#include <Windows.h>
#include "../Engine_Math&Physics/Vector2D.h"
#include <CommDlg.h>

//macro to detect keypresses
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) == 0xffff8000) ? 1 : 0)

#define WAS_KEY_PRESSED(vk_code) ((GetKeyState(vk_code) & 0x8000f))
#define IS_KEY_PRESSED(vk_code) ((GetAsyncKeyState(vk_code) == 0xffff8001))

//Call this to refresh the client window
inline void RedrawWindow(HWND hwnd, bool RedrawBackGround = true){
  InvalidateRect(hwnd, NULL, RedrawBackGround);
  UpdateWindow(hwnd);
}

//Call this to refresh the client window
inline void RedrawWindowRect(HWND hwnd, bool RedrawBackGround, RECT& RedrawArea)
{
  InvalidateRect(hwnd, &RedrawArea, RedrawBackGround);
  UpdateWindow(hwnd);
}

WCHAR* CharToWChar(const char* _pstrSrc);

//Changes the state of a menu item given the item identifier, the 
//desired state and the HWND of the menu owner
void ChangeMenuState(HWND hwnd, UINT MenuItem, UINT state);

//if b is true MenuItem is checked, otherwise it is unchecked
void CheckMenuItemAppropriately(HWND hwnd, UINT MenuItem, bool b);


//this is a replacement for the StringCchLength function found in the 
//platform SDK. See MSDN for details. Only ever used for checking toolbar
//strings
bool CheckBufferLength(char* buff, int MaxLength, unsigned int& BufferLength);

void ErrorBox(std::string& _rMsg);
void ErrorBox(char* _pstrMsg);

//gets the coordinates of the cursor relative to an active window 
Vector2D GetClientCursorPosition();

//gets the coordinates of the cursor relative to an active window 
Vector2D GetClientCursorPosition(HWND hwnd);


//two handy functions from Mr Petzold. They open a common dialog box to
//grab a filename
void FileInitialize (HWND hwnd,
                     OPENFILENAME& ofn,
                     const std::string& defaultFileTypeDescription,
                     const std::string& defaultFileExtension);

BOOL FileOpenDlg (HWND               hwnd,
                  PTSTR              pstrFileName,
                  PTSTR              pstrTitleName,
                  const std::string& defaultFileTypeDescription,
                  const std::string& defaultFileExtension);

BOOL FileSaveDlg (HWND hwnd,
                  PTSTR pstrFileName,
                  PTSTR pstrTitleName,
                  const std::string& defaultFileTypeDescription,
                  const std::string& defaultFileExtension);

//call this to resize the specified window to the specified size.
void ResizeWindow(HWND hwnd, int cx, int cy);

int  GetWindowHeight(HWND hwnd);
int  GetWindowWidth(HWND hwnd);

#endif