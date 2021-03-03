#include "Information.h"
#include "SystemDefines.h"
#include "CameraManager.h"

CInformation::CInformation(): m_dwFrameCntForNon(0),
							m_fTimeElapsedForNon(0),
							m_dwTimeElapsedForAdjusted(0),
							m_fTimeElapsedForAdjusted(0),
							m_fFPS(0),
							m_fFPSAdjusted(0),
							m_vAdjusted(Vector2D(0, 0)),
							m_vAbsoluted(Vector2D(0, 0)),
							m_vNowPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
							m_vDisPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
							m_vFirstPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
							m_vLastPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
							m_eSpace(CInformation::DOWN)
{
	m_Rect.left = 0;
	m_Rect.top = 0;
	m_Rect.right = SYSTEMWIDTH;
	m_Rect.bottom = SYSTEMHEIGHT;
}

CInformation::~CInformation(){

}

void CInformation::CalcInformation(float _fTimeDelta){
	// FPS계산
	FPSCalculation(_fTimeDelta);

	// 마우스 좌표 갱신
	sprintf_s(m_crdString, 59, "AdX : %.2f, AdY : %.2f AbX : %.2f, AbY : %.2f", m_vAdjusted.x, m_vAdjusted.y,m_vAbsoluted.x, m_vAbsoluted.y);
	m_crdString[59] = '\0'; // mark end of string

	// 카메라 계산
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	this->SetCameraPos(&t_vPos);
	sprintf_s(m_cameraString, 59, "CX : %.2f, CY : %.2f, CZ : %.2f", m_vNowPos.x, m_vNowPos.y, m_vNowPos.z);
	m_cameraString[59] = '\0'; // mark end of string

	// 왼쪽 Shift키 입력
	if(GetAsyncKeyState(VK_LSHIFT) & 0x8000f){
		switch(m_eSpace){
			case DOWN:
				m_eSpace = CInformation::DOWN;
				m_vLastPos = *(this->GetCameraPos());
				break;
			case UP:
				m_eSpace = CInformation::UP;
				m_vFirstPos = *(this->GetCameraPos());
				break;
		}
		if(m_vFirstPos != 0 && m_vLastPos != 0){
			m_vDisPos = m_vFirstPos - m_vLastPos;
			sprintf_s(m_distanceString, 59, "DX : %.2f, DY : %.2f", m_vDisPos.x, m_vDisPos.y);
			m_crdString[59] = '\0'; // mark end of string
			m_vFirstPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_vLastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}
}

void CInformation::FPSCalculation(float _fTimeDelta){
	m_dwFrameCntForNon++;
	m_fTimeElapsedForNon += _fTimeDelta;

	if(m_fTimeElapsedForNon >= 1.0f){
		m_fFPS = (float)m_dwFrameCntForNon / m_fTimeElapsedForNon;

		sprintf_s(m_FPSString, 29, "FPS : %.2f", m_fFPS);
		m_FPSString[29] = '\0'; // mark end of string

		m_fTimeElapsedForNon = 0.0f;
		m_dwFrameCntForNon = 0;
	}
}

void CInformation::FPSAdjustedCalculation(float _fTimeDelta){
	m_dwTimeElapsedForAdjusted++;
	m_fTimeElapsedForAdjusted += _fTimeDelta;

	if(m_fTimeElapsedForAdjusted >= 1.0f){
		m_fFPSAdjusted = (float)m_dwTimeElapsedForAdjusted / m_fTimeElapsedForAdjusted;

		sprintf_s(m_FPSAdjustedString, 29, "FPSAdjusted : %.2f", m_fFPSAdjusted);
		m_FPSAdjustedString[29] = '\0'; // mark end of string

		m_fTimeElapsedForAdjusted = 0.0f;
		m_dwTimeElapsedForAdjusted = 0;
	}
}

void CInformation::DrawInformation(ID3DXFont* _pFont, ID3DXSprite* _pSprite){
	_pSprite->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE );

	RECT rect;

	rect = m_Rect;
      
	// FPS 출력
	_pFont->DrawText(_pSprite, m_FPSString, -1, &rect, DT_TOP | DT_LEFT | DT_WORDBREAK, 0xffff0000);      
	_pFont->DrawText(_pSprite, m_FPSAdjustedString, -1, &rect, DT_BOTTOM | DT_LEFT | DT_WORDBREAK, 0xffff0000);

	// 마우스 좌표 출력
	_pFont->DrawText(_pSprite, m_crdString, -1, &rect, DT_TOP | DT_RIGHT | DT_WORDBREAK, 0xffff0000);

	// 카메라 좌표 출력
	_pFont->DrawText(_pSprite, m_cameraString, -1, &rect, DT_BOTTOM | DT_RIGHT | DT_WORDBREAK, 0xffff0000);

	// 카메라상의 좌표 간격 출력
//	_pFont->DrawText(_pSprite, m_distanceString, -1, &rect, DT_BOTTOM | DT_LEFT, 0xffff0000);

	_pSprite->End();
}