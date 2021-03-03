////////////////////////////////////////////////////
// Mouse 담당 관리 클래스
////////////////////////////////////////////////////
#ifndef _MouseManager_H_
#define _MouseManager_H_

#include "Body.h"

class CMouseManager{
public:
	typedef enum MouseType {NORMAL, DIRECTION} MOUSETYPE;

private:
	CBody* m_pCursor[2];

	MOUSETYPE m_eType;

	D3DXVECTOR3 m_vSpot;

	bool m_bSomethingCollision;

	bool m_bUseCursor;

	bool m_bLeftDown;
	bool m_bRightDown;

	bool m_bLeftClick;

	bool	m_bOldLeftDown;
	bool	m_bOldRightDown;

private:
	CMouseManager();
	CMouseManager(const CMouseManager&);
	CMouseManager& operator =(const CMouseManager&);

public:
	~CMouseManager();
	static CMouseManager* Instance(){
		static CMouseManager instance;

		return &instance;
	}

	void Initialize();

	// Cursor 업데이트
	void UpdateCursorPosition(float _fX, float _fY);
	void CursorUpdate();

	void SetType(MOUSETYPE _eType){m_eType = _eType;}
	int	 GetType(){return m_eType;}

	void SetUseCursor(bool _bUse){m_bUseCursor = _bUse;}
	void OffCursor(){m_bUseCursor = false;}
	void OnCursor(){m_bUseCursor = true;}
	void ToggleUseCursor(){m_bUseCursor = !m_bUseCursor;}

	void SetLeftDown(bool _bDown){m_bOldLeftDown = m_bLeftDown; m_bLeftDown = _bDown;}
	void SetRightDown(bool _bDown){m_bOldRightDown = m_bRightDown; m_bRightDown = _bDown;}

	bool GetLeftDown(){return m_bLeftDown;}
	bool GetRighttDown(){return m_bRightDown;}
	
	bool LeftDownTheMoment();
	bool RightDownTheMoment();

	bool LeftClick();
	bool RightClick();
	
	D3DXVECTOR3* GetCursorPos(){return &m_vSpot;}
	CBody* GetCursor(int _nIndex){return m_pCursor[_nIndex];}

	bool Something(){return m_bSomethingCollision;}
	void OnSomething(){m_bSomethingCollision = true;}
	void OffSomething(){m_bSomethingCollision = false;}

	float CalRotClickBetweenPos(Vector2D _vPos);
	Vector2D CalHeadingClickBetweenPos(Vector2D _vPos);
};

#define MouseMgr CMouseManager::Instance()

#endif