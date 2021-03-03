#ifndef BOX3D_H
#define BOX3D_H

//-----------------------------------------------------------------------------
//
//  Name:   CBox3D.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//	Modifier : Hoon-il Song (Sider)
//
//  Desc:   aligned bounding
//          box class
//-----------------------------------------------------------------------------

#include "../Engine_Math&Physics/Vector2D.h"

class CBox3D{
private:
	// Window coordinate system variation
  Vector2D  m_vTopLeft;
  Vector2D  m_vBottomRight;

  Vector2D  m_vCenter;

	// DirectX coordinte system variation
	Vector2D  m_vTopLeftTF;
	Vector2D  m_vBottomRightTF;

	Vector2D  m_vCenterTF;

	float			m_fLineWeight;
	float			m_fBlinkingFrequency;
	bool			m_bLineState;
  
public:
  CBox3D(Vector2D _vTL, Vector2D _BR);

	~CBox3D();

  //returns true if the bbox described by other intersects with this one
  bool isOverlappedWith(const CBox3D& other)const{
    return !((other.Top() > this->Bottom()) ||
           (other.Bottom() < this->Top()) ||
           (other.Left() > this->Right()) ||
           (other.Right() < this->Left()));
  }

  
  Vector2D	TopLeft()const{return m_vTopLeft;}
  Vector2D	BottomRight()const{return m_vBottomRight;}

	Vector2D	TopLeftTF()const{return m_vTopLeftTF;}
  Vector2D	BottomRightTF()const{return m_vBottomRightTF;}

  double    Top()const{return m_vTopLeft.y;}
  double    Left()const{return m_vTopLeft.x;}
  double    Bottom()const{return m_vBottomRight.y;}
  double    Right()const{return m_vBottomRight.x;}
  Vector2D	Center()const{return m_vCenter;}

	double    TopTF()const{return m_vTopLeftTF.y;}
	double    LeftTF()const{return m_vTopLeftTF.x;}
	double    BottomTF()const{return m_vBottomRightTF.y;}
	double    RightTF()const{return m_vBottomRightTF.x;}
	Vector2D	CenterTF()const{return m_vCenterTF;}

	float			GetLineWeight()const{return m_fLineWeight;}

	void			Update();
  void			Render(ID3DXLine* p_pLine, D3DXCOLOR* p_pColor, bool RenderCenter = false)const;
	void		  Render(D3DXCOLOR* p_pColor, bool RenderCenter = false)const;
	void			RenderCoordinateXY(D3DXVECTOR2* p_pCo)const;
	void			RenderCoordinateXY(Vector2D* p_pCo)const;
};
  
#endif