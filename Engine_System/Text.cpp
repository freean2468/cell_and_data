#include "Text.h"
#include "TextOwnedStates.h"
#include "../Engine_Misc/DirectUtils.h"
#include "EngineManager.h"

CText::CText() : m_pFont(NULL), 
				m_pStateMachine(NULL),
				m_pGapTimer(new CTimer(0)), 
				m_nLength(0)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CText>(this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(TextNormal->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);	

	this->InitFont(25, 12, 400, false, "맑은 고딕");
	m_strFile.clear();

	m_Color = D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f);
}

CText::CText(std::string _strText) : m_pFont(NULL), 
																	m_pStateMachine(NULL),
																	m_pGapTimer(new CTimer(0)), 
																	m_nLength(0)
{
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CText>(this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(TextNormal->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);	

	this->InitFont(25, 12, 400, false, "맑은 고딕");
	m_strFile.clear();
	m_strFile = _strText;

	m_Color = D3DXCOLOR(-1.0f, 1.0f, -1.0f, 1.0f);
}

CText::~CText(){
	Delete< CStateMachine<CText>* >(m_pStateMachine);
	Release<ID3DXFont*>(m_pFont); 
	Delete<CTimer*>(m_pGapTimer);
}

void CText::InitFont(int _nWidth, int _nHeight, int _nWeight, bool _bItal, char* _pStyle){
	m_pFont = DU::IniFont(_nWidth, _nHeight, _nWeight, _bItal, _pStyle);
}

void CText::SetFontScale(int _nScale){
	switch(_nScale){
		case 1:InitFont(10, 5, 300, false, "맑은 고딕"); break;
		case 3:InitFont(14, 7, 300, false, "맑은 고딕"); break;
		case 4:InitFont(16, 8, 400, false, "맑은 고딕"); break;
		case 5:InitFont(18, 9, 400, false, "맑은 고딕"); break;
		case 6:InitFont(20, 10, 400, false, "맑은 고딕"); break;
		case 7:InitFont(22, 11, 400, false, "맑은 고딕"); break;
		case 8:InitFont(24, 12, 400, false, "맑은 고딕"); break;
		case 9:InitFont(32, 16, 800, false, "맑은 고딕"); break;
		case 2:
		default:
				InitFont(12, 6, 300, false, "맑은 고딕"); break;
	}
}

void CText::SetString(std::string _String){
	m_strFile.clear();
	m_strFile = _String;
}

void CText::SetString(int _String){
	m_strFile.clear();
	char t_strChar[12];

	::_itoa_s(_String, &t_strChar[0], 12, 10);
	m_strFile = t_strChar;
}

void CText::Update(RECT* _pRect){
	RECT t_Rect;

	t_Rect.bottom = -100;
	t_Rect.top = 100;
	t_Rect.left = -100;
	t_Rect.right = 100;

	if(_pRect == NULL){
		FineRect(&t_Rect);
	}
	else
		FineRect(_pRect);

	m_pStateMachine->Update();

	PostRenderLine();
}

void CText::FineRect(RECT* _pRect){
	m_Rect.bottom = (-_pRect->bottom - 10);
	m_Rect.top = (-_pRect->top + 10);
	m_Rect.left = (_pRect->left + 10);
	m_Rect.right = (_pRect->right - 10);
}

void CText::PreRenderLine(D3DXVECTOR3* _pvPos){
	EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D 공간상에 텍스트 출력

	D3DXVECTOR3 _vPos;			// 위치 벡터
	D3DXMATRIXA16 _pos;			// 위치 변환 행렬
	D3DXVECTOR3 _vScale;		// 크기 벡터
	D3DXMATRIXA16 _scale;		// 크기 변환 행렬
	D3DXMATRIXA16 _rotation;	// 회전 변환 행렬
	D3DXVECTOR3 _vRotate;		// 회전 벡터

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&_pos, _pvPos->x, _pvPos->y, _pvPos->z);

	D3DXMATRIXA16 rX/*, rY, rZ*/;
	D3DXMatrixIdentity(&rX);
	//D3DXMatrixIdentity(&rY);
	//D3DXMatrixIdentity(&rZ);
	D3DXMatrixRotationX(&rX, D3DX_PI);
	//D3DXMatrixRotationY(&rY, D3DX_PI);
	//D3DXMatrixRotationZ(&rZ, ObjectMgr->GetEntity(m_eOwner)->GetBody()->GetPriRot()->z);

	_rotation = rX/*,rY, rZ*/;

	//D3DXMatrixScaling(&_scale, ObjectMgr->GetEntity(m_eOwner)->GetBody()->GetPriSca()->x, ObjectMgr->GetEntity(m_eOwner)->GetBody()->GetPriSca()->y, ObjectMgr->GetEntity(m_eOwner)->GetBody()->GetPriSca()->z);

	mtMatrix = mtMatrix * /*_scale*/_rotation * _pos;

	EngineMgr->GetpSprite()->SetTransform(&mtMatrix);
}

void CText::PostRenderLine(){
	EngineMgr->GetpSprite()->End();

	D3DXMATRIXA16 mtMatrix;

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	EngineMgr->GetpSprite()->SetTransform(&mtMatrix);
}

void CText::RenderLine(){
	// Text 출력
	m_pFont->DrawText(EngineMgr->GetpSprite(), m_strFile.c_str(), -1, &m_Rect,		DT_CENTER | DT_VCENTER | DT_WORDBREAK , m_Color);
}

void CText::RenderTypingLine(){
	if(static_cast<std::string::size_type>(m_nLength) < m_strFile.length()){
		if(m_pGapTimer->IsElapseTimer()){
			m_nLength++;
			m_pGapTimer->InitTimer(50);
		}
	}

	std::string t_Copy;
	t_Copy = m_strFile;

	std::string t_Str;

	t_Str.resize(m_nLength+1);

	unsigned int i;

	for(i = 0; i < m_nLength; ++i){
		t_Str[i] = t_Copy[i];
	}

	if(m_nLength < m_strFile.length()){
		t_Str[i+1]='|';
	}

	// Text 출력
	m_pFont->DrawText(EngineMgr->GetpSprite(), t_Str.c_str(), -1, &m_Rect, 	DT_CENTER | DT_VCENTER | DT_WORDBREAK , m_Color);
}