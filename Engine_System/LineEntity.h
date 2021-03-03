//////////////////////////////////////////////////////
// 라인으로 Object를 감싸고 직접 Vertices를 설정,
// Object를 생성하는 클래스.
//////////////////////////////////////////////////////
#ifndef _LineEntity_H_
#define _LineEntity_H_

#include "DirectXEntity.h"

class CLineEntity : public CDirectXEntity{
private:
	int										m_nPointNum;
	std::vector<Vector2D>					m_Points;

	D3DXVECTOR3								m_vCenter;

public:
	CLineEntity(int _nEntityType);
	virtual ~CLineEntity();

	virtual void CreatePointsOnRandInRange(int _nBegin, int _nEnd);
	void CreateVertices();

	////////////////////////////////////////////////
	// 기본 공통 함수
	bool InitObject(IDirect3DDevice9* _pDevice, float _fAlpha);

	virtual void ResizeObject(float _fVal);
	virtual void ResizeObject(float _fWidth, float _fHeight);

	virtual void ResizeVertex(float _fWidth, float _fHeight);

	virtual void Render();
	virtual void preRender();
	virtual void postRender();

	virtual D3DXMATRIX CalMatWorld();

	void RenderLine(ID3DXLine* p_pLine, D3DXCOLOR* p_pColor);

	std::vector<Vector2D>* GetPoints(){return &m_Points;}

	int	GetPointNum(){return m_nPointNum;}
	void SetPointNum(int _nNum){m_nPointNum = _nNum;}

	void SetCenter(){
		for(int i = 0; i < GetPointNum(); ++i){
			m_vCenter.x += (float)GetPoints()->at(i).x;
			m_vCenter.y += (float)GetPoints()->at(i).y;
		}

		// 중심
		m_vCenter /= (float)GetPointNum();

		Vector2D t_vRadius(m_vCenter.x, m_vCenter.y);

		SetRadius((float)t_vRadius.Length());
	}

	D3DXVECTOR3 GetCenter(){return m_vCenter;}
	D3DXVECTOR3 GetCenterApplyScale(){return m_vCenter * GetAveSca2D();}
};

#endif