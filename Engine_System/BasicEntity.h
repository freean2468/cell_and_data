//////////////////////////////////////////////////////
// 각종 오브젝트들의 공통 부분을 담고 있는 조상 클래스
//////////////////////////////////////////////////////
#ifndef _BasicEntity_H_
#define _BasicEntity_H_

#include "DirectXEntity.h"
#include "Timer.h"

class CBasicEntity : public CDirectXEntity{
public:
	typedef enum Direction {RIGHT = 0, LEFT} DIRECTION;				// 방향

protected:
	// Object 애니메이션 관련 변수
	int m_nCol;								// (열)가로,행동 인덱스
	int m_nRow;								// (행)세로,방향 인덱스
	DWORD	m_dwDelaytime;					// 프레임간격
	CTimer	m_Timer;						// 시간 클래스

	DIRECTION m_eDirection;

public:
	CBasicEntity(int _nEntityType);
	virtual ~CBasicEntity();

	////////////////////////////////////////////////
	// 기본 공통 함수
	virtual void ResizeObject(float _fVal);
	virtual void ResizeObject(float _fWidth, float _fHeight);

	virtual void ResizeVertex(float _fWidth, float _fHeight);

//	virtual void Animation();

	void SetRow(DIRECTION _eDir){m_nRow = _eDir;}
	int GetRow(){return m_nRow;}

	void SetCol(int _nWidth){m_nCol = _nWidth;}
	int GetCol(){return m_nCol;}

	DIRECTION GetDirection(){return m_eDirection;}
	void	SetDirection(DIRECTION _eDirection);
};

#endif