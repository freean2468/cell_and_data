////////////////////////////////////////////////////////////////////////////////
// Engine에서 사용되는 헤더파일과 라이브러리, 상수등을 선언
////////////////////////////////////////////////////////////////////////////////
#ifndef _SystemDefines_H_
#define _SystemDefines_H_

#pragma warning (disable:4995)

#define WIN32_LEAN_AND_MEAN		// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.

#define DIRECTINPUT_VERSION 0x0800

#define _USE_MATH_DEFINES

//// window
//#include <windows.h>
//#include <WindowsX.h>
//#include <objbase.h>
//#include <mmsystem.h>
//#include <commdlg.h>
//#include <basetsd.h>
//
//// DirectX
//#include <d3d9.h>
//#include <d3dx9.h>
//#include <dinput.h>
//#include <D3dx9core.h>
//#include <dshow.h>
//#include <dsound.h>
//#include <dmusici.h>
//
//// Vorbis
////#include <vorbis/codec.h>
////#include <vorbis/vorbisfile.h>
//
//// 각종
//#include <string.h>
//#include <stdio.h>
//#include <iosfwd>
//#include <iomanip>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <time.h>
//#include <math.h>
//
//// STL
//#include <new>
//#include <vector>
//#include <list>
//#include <cmath>
//#include <limits>
//#include <cstdlib>
//#include <ctime>
//#include <set>
//#include <map>
//#include <cassert>

//using std::bad_alloc;

const int SYSTEMWIDTH = 800;
const int SYSTEMHEIGHT = 600;

//using std::ofstream;
//using std::ifstream;
//
//using std::string;
//using std::vector;
//using std::list;

#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#endif

#define SYSTEM_FRAME_INTERVAL_VER_60 0.01f
#define SYSTEM_FRAME_INTERVAL_VER_30 0.02f

#endif