//////////////////////////////////////////////////////
// ���� ������Ʈ���� ���� �κ��� ��� �ִ� ���� Ŭ����
//////////////////////////////////////////////////////
#ifndef _BasicEntity_H_
#define _BasicEntity_H_

#include "DirectXEntity.h"
#include "Timer.h"

class CBasicEntity : public CDirectXEntity{
public:
	typedef enum Direction {RIGHT = 0, LEFT} DIRECTION;				// ����

protected:
	// Object �ִϸ��̼� ���� ����
	int m_nCol;								// (��)����,�ൿ �ε���
	int m_nRow;								// (��)����,���� �ε���
	DWORD	m_dwDelaytime;					// �����Ӱ���
	CTimer	m_Timer;						// �ð� Ŭ����

	DIRECTION m_eDirection;

public:
	CBasicEntity(int _nEntityType);
	virtual ~CBasicEntity();

	////////////////////////////////////////////////
	// �⺻ ���� �Լ�
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