/////////////////////////////////////////////////////
// CEngineManagerŬ������ �� ������ �ý����� �Ѱ���
////////////////////////////////////////////////////

#ifndef _EngineManager_H_
#define _EngineManager_H_

#include "SystemDefines.h"
#include "Information.h"
#include "SystemFrame.h"
#include <dinput.h>

class CEngineManager{
private:
	// Application Class app�� ���ø����̼��� �ٷ�� Ŭ�����̱⿡ �� �� ���� ����.
	// Pipe-line ���� MATRIX ����
	D3DXMATRIX m_mView;
	D3DXMATRIX m_mProj;
	D3DXMATRIX m_mWorld;

	//////////////////////////////////////////////////////////
	//BM ����
	//////////////////////////////////////////////////////////
	HWND					m_hWnd;		// ���� ���α׷��� ���� ������ ��ü�� ����Ų��.
	HWND					m_hEditWnd;	// Editâ ��ü
	HINSTANCE			m_hInstance;

	IDirect3DDevice9* m_pDevice;	// ��ġ �������̽� ����

	LPDIRECTINPUTDEVICE8  m_pKeyboard;	// Input Keyboard Interface stuff
	BYTE	m_KeyState[256];	// Input Key State stuff
	BYTE	m_OldCode;

	LPDIRECTINPUTDEVICE8  m_pMouse;	// Input Keyboard Interface stuff
	HANDLE m_hMouseEvent;

	ID3DXFont*	m_pFont;		// ��Ʈ �������̽� ����
	ID3DXFont*	m_pFontForCoSystem;
	ID3DXSprite* m_pSprite;	// ��������Ʈ �������̽� ����

	ID3DXLine* m_pLine;			// Line

	////////////////////////////////////////////////////////////
	//BM �� Ŭ����
	////////////////////////////////////////////////////////////
	// ���� ��� �� ��� ���(Debug��)
	CInformation* m_pInfo;

	// �ý��� ������ ���
	CSystemFrame* m_pFrame;

	// ���콺 ���� 1 = Up, 0 = Down->Up, -1 = Down
	int m_nLButtonState;

    // �����ڿ� �Ҹ��ڸ� �����ϰ� �Ҵ��� private�̾�� �Ѵ�.
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
	// CEngineManager Ŭ���� ���� �Լ�
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
	// EngineManager wrap Ŭ���� Set �Լ� wrap �Լ�
	//////////////////////////////////////////////////
	void SetInfo();
	void SetFrame();
	void SetTerrain();
	void SetSound();

	///////////////////////////////////////////////////
	// EngineManager �� Ŭ���� Set �Լ�
	///////////////////////////////////////////////////
	void SetCInformation(CInformation* _pInfo){m_pInfo = _pInfo;}
	void SetCSystemFrame(CSystemFrame* _pFrame){m_pFrame = _pFrame;}

	///////////////////////////////////////////////////
	// EngineManager �� Ŭ���� Get �Լ�
	///////////////////////////////////////////////////
	CInformation* GetpInformation(){return m_pInfo;}
	CSystemFrame* GetpSystemFrame(){return m_pFrame;}

	///////////////////////////////////////////////////
	// ���� Get �Լ�
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
	// ���� Set �Լ�
	///////////////////////////////////////////////////
	void Sethwnd(HWND _hWnd){m_hWnd = _hWnd;}
	void Sethinstance(HINSTANCE _hInstance){m_hInstance = _hInstance;}
	void SetpDevice(IDirect3DDevice9* _pDevice){m_pDevice = _pDevice;}
	void SetLButtonState(int _nTemp){m_nLButtonState = _nTemp;}
};

// CEngineManager�� �ν��Ͻ��� ���� ������ �� �ִ� ����� �����Ѵ�.
#define EngineMgr CEngineManager::Instance()

#endif