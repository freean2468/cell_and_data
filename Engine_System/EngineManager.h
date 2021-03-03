/////////////////////////////////////////////////////
// CEngineManager클래스는 이 엔진의 시스템을 총괄함
////////////////////////////////////////////////////

#ifndef _EngineManager_H_
#define _EngineManager_H_

#include "SystemDefines.h"
#include "Information.h"
#include "SystemFrame.h"
#include <dinput.h>

class CEngineManager{
private:
	// Application Class app는 어플리케이션을 다루는 클래스이기에 랩 할 수가 없다.
	// Pipe-line 관련 MATRIX 변수
	D3DXMATRIX m_mView;
	D3DXMATRIX m_mProj;
	D3DXMATRIX m_mWorld;

	//////////////////////////////////////////////////////////
	//BM 변수
	//////////////////////////////////////////////////////////
	HWND					m_hWnd;		// 응용 프로그램의 메인 윈도우 객체를 가리킨다.
	HWND					m_hEditWnd;	// Edit창 객체
	HINSTANCE			m_hInstance;

	IDirect3DDevice9* m_pDevice;	// 장치 인터페이스 변수

	LPDIRECTINPUTDEVICE8  m_pKeyboard;	// Input Keyboard Interface stuff
	BYTE	m_KeyState[256];	// Input Key State stuff
	BYTE	m_OldCode;

	LPDIRECTINPUTDEVICE8  m_pMouse;	// Input Keyboard Interface stuff
	HANDLE m_hMouseEvent;

	ID3DXFont*	m_pFont;		// 폰트 인터페이스 변수
	ID3DXFont*	m_pFontForCoSystem;
	ID3DXSprite* m_pSprite;	// 스프라이트 인터페이스 변수

	ID3DXLine* m_pLine;			// Line

	////////////////////////////////////////////////////////////
	//BM 랩 클래스
	////////////////////////////////////////////////////////////
	// 정보 계산 및 출력 담당(Debug용)
	CInformation* m_pInfo;

	// 시스템 프레임 담당
	CSystemFrame* m_pFrame;

	// 마우스 상태 1 = Up, 0 = Down->Up, -1 = Down
	int m_nLButtonState;

    // 생성자와 소멸자를 복사하고 할당은 private이어야 한다.
	CEngineManager(const CEngineManager&);
	CEngineManager& operator=(const CEngineManager&);
public:
	CEngineManager();
	~CEngineManager();

	static CEngineManager* Instance(){
		 static CEngineManager instance;

		 return &instance;
	}

	///////////////////////////////////////////////////
	// CEngineManager 클래스 제공 함수
	//////////////////////////////////////////////////
	void Initialize();
	void Loading();
	bool IsViewOut(D3DXVECTOR3* _pvObjectPos);
	void InitializeEdit();
	void EditWndUpdate(char* _pBuffer, int _nLength);

	// ---------------- Base Get Funtion ------------
	D3DXMATRIX* GetWorldMat();
	D3DXMATRIX* GetViewMat();
	D3DXMATRIX* GetProjMat();

	// ---------------- Direct Input function -------
	void UpdateDI();
	void CheckKeyDown();
	bool KeyDown(BYTE p_code);
	bool KeyUp(BYTE p_code);

	// ---------------- Text out function -----------
	void TextOutBegin();
	void TextOutEnd();

	// ---------------- Line Render function --------
	void LineRenderBegin();
	void LineRenderEnd();

	//////////////////////////////////////////////////
	// EngineManager wrap 클래스 Set 함수 wrap 함수
	//////////////////////////////////////////////////
	void SetInfo();
	void SetFrame();
	void SetTerrain();
	void SetSound();

	///////////////////////////////////////////////////
	// EngineManager 랩 클래스 Set 함수
	///////////////////////////////////////////////////
	void SetCInformation(CInformation* _pInfo){m_pInfo = _pInfo;}
	void SetCSystemFrame(CSystemFrame* _pFrame){m_pFrame = _pFrame;}

	///////////////////////////////////////////////////
	// EngineManager 랩 클래스 Get 함수
	///////////////////////////////////////////////////
	CInformation* GetpInformation(){return m_pInfo;}
	CSystemFrame* GetpSystemFrame(){return m_pFrame;}

	///////////////////////////////////////////////////
	// 변수 Get 함수
	///////////////////////////////////////////////////
	IDirect3DDevice9*	GetpDevice(){return m_pDevice;}	
	IDirect3DDevice9**	GetppDevice(){return &m_pDevice;}

	LPDIRECTINPUTDEVICE8 GetpDIKeyboard(){return m_pKeyboard;}
	LPDIRECTINPUTDEVICE8* GetppDIKeyboard(){return &m_pKeyboard;}
	LPDIRECTINPUTDEVICE8 GetpDIMouse(){return m_pMouse;}
	LPDIRECTINPUTDEVICE8* GetppDIMouse(){return &m_pMouse;}

	HANDLE GetMouseEvent(){return m_hMouseEvent;}

	ID3DXFont* GetpFont(){return m_pFont;}
	ID3DXFont* GetFontForCoSystem(){return m_pFontForCoSystem;}

	ID3DXSprite* GetpSprite(){return m_pSprite;}
	ID3DXSprite** GetppSprite(){return &m_pSprite;}

	ID3DXLine*	GetLine(){return m_pLine;}

	HWND	Gethwnd(){return m_hWnd;}
	HWND	GetEdit(){return m_hEditWnd;}
	HINSTANCE Gethinstance(){return m_hInstance;}

	float GetTimeDelta(){return m_pFrame->GetTimeDeltaOfOrigin();}
	float GetAdjustedTimeDelta(){return m_pFrame->GetAdjustedTimeDelta();}

	int GetLButtonState(){return m_nLButtonState;}

	///////////////////////////////////////////////////
	// 변수 Set 함수
	///////////////////////////////////////////////////
	void Sethwnd(HWND _hWnd){m_hWnd = _hWnd;}
	void Sethinstance(HINSTANCE _hInstance){m_hInstance = _hInstance;}
	void SetpDevice(IDirect3DDevice9* _pDevice){m_pDevice = _pDevice;}
	void SetLButtonState(int _nTemp){m_nLButtonState = _nTemp;}
};

// CEngineManager의 인스턴스를 쉽게 접근할 수 있는 방법을 제공한다.
#define EngineMgr CEngineManager::Instance()

#endif