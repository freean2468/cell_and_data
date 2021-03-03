#ifndef _FIREWALL3D_H_
#define _FIREWALL3D_H_

class CFireWall3D : CWall2D{
  virtual void Render(ID3DXLine* p_pLine, D3DXCOLOR* p_pColor, bool RenderNormals = false)const;
};

#endif