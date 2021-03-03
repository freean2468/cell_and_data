#ifndef _TEXT_H_
#define _TEXT_H_

#include <d3dx9core.h>
#include <string>
#include "Timer.h"
#include "StateMachine.h"

class CText{
private:
	ID3DXFont* m_pFont;

	std::string m_strFile;

	RECT m_Rect;

	D3DXCOLOR m_Color;

	// Typing
	CTimer*		m_pGapTimer;
	std::string::size_type	m_nLength;

	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CText>* m_pStateMachine;

public:
	CText();
	CText(std::string _strText);
	~CText();

	void InitFont(int _nWidth, int _nHeight, int _nWeight, bool _bItal, char* _pStyle);
	void InitValiable(){m_nLength = 0;}

	void SetFontScale(int _nScale);

	void SetColor(D3DXCOLOR _Color){m_Color = _Color;}
	void FineRect(RECT* _pRect);

	/*void SetString(int _nValue){::_itoa_s(_nValue, &m_Str[0],sizeof( 10);}
	void SetString(char* _pStr){StringCbCopy(m_Str,sizeof(m_Str),_pStr);}*/
	void SetString(std::string _String);
	void SetString(int _String);

	void Update(RECT* _pRect);

	void PreRenderLine(D3DXVECTOR3* _pvPos);	// 출력 좌표 설정
	void PostRenderLine();

	void RenderLine();
	void RenderTypingLine();

	CStateMachine<CText>* GetFSM(){return m_pStateMachine;}

	ID3DXFont* GetFont(){return m_pFont;}
	CTimer* GetGap(){return m_pGapTimer;}
	std::string::size_type GetLength(){return m_nLength;}
};

#endif _TEXT_H_